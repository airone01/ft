#!/usr/bin/env bash

ANSI_RED='\033[0;31m'
ANSI_GREEN='\033[0;32m'
ANSI_BLUE='\033[0;34m'
ANSI_NC='\033[0m'

# Maps project names to their directory paths
declare -A PROJECT_PATHS
PROJECT_PATHS["libft"]="milestone-0-libft"
PROJECT_PATHS["get_next_line"]="milestone-1-get_next_line"
PROJECT_PATHS["ft_printf"]="milestone-1-ft_printf"
PROJECT_PATHS["push_swap"]="milestone-2-push_swap"

usage() {
  echo -e "${ANSI_BLUE}Git Project Manager 📦${ANSI_NC}"
  echo -e "Usage:"
  echo -e "  ${ANSI_BLUE}gpm${ANSI_NC} submit <project-name> <target-repo-url> ${ANSI_GREEN}# Submit (force push) a project to the 42 intra${ANSI_NC}"
  echo -e "  ${ANSI_BLUE}gpm${ANSI_NC} test <project-name>                     ${ANSI_GREEN}# Test submission processing without pushing${ANSI_NC}"
  exit 1
}

# Function to parse .push file and read exact file names
parse_push_file() {
  local push_file="$1"
  local base_dir="$2"
  local files_to_include=()

  if [ ! -f "$push_file" ]; then
    echo -e "${ANSI_RED}❌ No .push file found${ANSI_NC}"
    echo -e "${ANSI_BLUE}ℹ️  Including all files by default${ANSI_NC}"
    echo "*" >"$push_file"
  fi

  while IFS= read -r filename || [ -n "$filename" ]; do
    # Skip comments and empty lines
    [[ $filename =~ ^[[:space:]]*# ]] && continue
    [[ -z $filename ]] && continue

    # Remove leading and trailing whitespace
    filename=$(echo "$filename" | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//')

    # Handle absolute paths (relative to project root)
    if [[ $filename == /* ]]; then
      filename="${filename#/}"
      if [ -f "$base_dir/$filename" ]; then
        files_to_include+=("$base_dir/$filename")
      else
        echo -e "${ANSI_RED}Warning: File not found: $filename${ANSI_NC}"
      fi
    else
      # Handle relative paths
      if [ -f "$base_dir/$filename" ]; then
        files_to_include+=("$base_dir/$filename")
      else
        echo -e "${ANSI_RED}Warning: File not found: $filename${ANSI_NC}"
      fi
    fi
  done <"$push_file"

  printf "%s\n" "${files_to_include[@]}"
}

# Extract function content from a file
extract_function() {
  local file="$1"
  local func_name="$2"
  local start_pattern="// GPM? begin ${func_name}"
  local end_pattern="// GPM? end ${func_name}"
  local content

  content=$(awk -v start="$start_pattern" -v end="$end_pattern" '
        $0 == start { p = 1; next }
        $0 == end { p = 0; next }
        p { print }
    ' "$file")

  if [ -z "$content" ]; then
    echo -e "${ANSI_RED}❌ Function ${func_name} not found or empty in ${file}${ANSI_NC}" >&2
    return 1
  fi

  echo "$content"
  return 0
}

# Process a single file for GPM directives
process_gpm_directives() {
  local input_file="$1"
  local output_file="$2"
  local temp_file
  temp_file=$(mktemp)

  # Copy input to temp file, we'll process it line by line
  cp "$input_file" "$temp_file"

  # Process GPM function includes and removals
  while IFS= read -r line; do
    if [[ $line =~ ^.*//[[:space:]]*GPM:[[:space:]]*([a-zA-Z0-9_]+)[[:space:]]*$ ]]; then
      func_name="${BASH_REMATCH[1]}"
      # Search for function in all project directories
      func_file=""
      for proj_dir in "${PROJECT_PATHS[@]}"; do
        if [[ -f "$proj_dir/${func_name}.c" ]]; then
          func_file="$proj_dir/${func_name}.c"
          break
        fi
      done

      if [[ -n "$func_file" ]]; then
        echo -e "${ANSI_BLUE}📦 Including ${func_name} from ${func_file}${ANSI_NC}"
        # Create a temporary file for the function content
        func_content=$(extract_function "$func_file" "$func_name")
        if [ $? -eq 0 ]; then
          # Replace the GPM line with the function content
          echo "$func_content" >"${temp_file}.func"
          sed -i'' "/${line//\//\\/}/r ${temp_file}.func" "$temp_file"
          sed -i'' "/${line//\//\\/}/d" "$temp_file"
          rm "${temp_file}.func"
        fi
      else
        echo -e "${ANSI_RED}❌ Warning: Function ${func_name} not found${ANSI_NC}"
      fi
    elif [[ $line =~ ^.*//[[:space:]]*GPM![[:space:]]*$ ]]; then
      # Remove lines marked with GPM!
      sed -i'' "/${line//\//\\/}/d" "$temp_file"
    fi
  done <"$input_file"

  # Move processed file to output location
  mv "$temp_file" "$output_file"
}

# Process all files in a directory for GPM directives
process_directory() {
  local input_dir="$1"
  local output_dir="$2"

  # Create output directory if it doesn't exist
  mkdir -p "$output_dir"

  # Process each .c and .h file
  find "$input_dir" -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    relative_path="${file#$input_dir/}"
    output_file="$output_dir/$relative_path"
    mkdir -p "$(dirname "$output_file")"
    process_gpm_directives "$file" "$output_file"
  done

  # Copy all other files without processing
  find "$input_dir" -type f ! \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    relative_path="${file#$input_dir/}"
    output_file="$output_dir/$relative_path"
    mkdir -p "$(dirname "$output_file")"
    cp "$file" "$output_file"
  done
}

# Function to process files for testing/submission
prepare_submission() {
  local project_name="$1"
  local temp_dir
  local processed_dir

  temp_dir=$(mktemp -d)
  processed_dir=$(mktemp -d)

  process_directory "$project_name" "$processed_dir" >/dev/null

  local push_file="$project_name/.push"
  if [ ! -f "$push_file" ]; then
    echo -e "${ANSI_RED}❌ No .push file found${ANSI_NC}" >&2
    rm -rf "$temp_dir" "$processed_dir"
    return 1
  fi

  readarray -t included_files <"$push_file"
  if [ ${#included_files[@]} -eq 0 ]; then
    echo -e "${ANSI_RED}❌ No files in .push file${ANSI_NC}" >&2
    rm -rf "$temp_dir" "$processed_dir"
    return 1
  fi

  cd "$temp_dir" || exit

  for file in "${included_files[@]}"; do
    file=$(echo "$file" | sed 's/#.*//g' | xargs)
    [ -z "$file" ] && continue

    if [ -f "$processed_dir/$file" ]; then
      mkdir -p "$(dirname "$file")"
      cp "$processed_dir/$file" "$file"
    else
      echo -e "${ANSI_RED}❌ Warning: File $file not found${ANSI_NC}" >&2
    fi
  done

  echo "$temp_dir"
  rm -rf "$processed_dir"
}

# Test submission processing
test_project() {
  local project_name="$1"
  local output_dir

  echo -e "${ANSI_BLUE}🧪 Testing submission for ${project_name}...${ANSI_NC}"

  # Capture output_dir without printing prepare_submission's output
  local output_dir
  output_dir=$(prepare_submission "$project_name" 2>&1)
  if [ $? -ne 0 ]; then
    return 1
  fi

  # Get the last line which contains the temp directory
  local temp_dir
  temp_dir=$(echo "$output_dir" | tail -n1)

  echo -e "${ANSI_BLUE}📝 Processed files in: ${output_dir}${ANSI_NC}"
  echo -e "${ANSI_GREEN}✅ Test complete! Review the files in ${output_dir}${ANSI_NC}"
  echo -e "${ANSI_BLUE}ℹ️  Remember to remove the directory when done${ANSI_NC}"
}

# Submit a project to the 42 intra
submit_project() {
  local project_name="$1"
  local target_repo="$2"
  local submission_dir
  local original_dir

  original_dir=$(pwd)

  echo -e "${ANSI_BLUE}📤 Submitting ${project_name}...${ANSI_NC}"

  submission_dir=$(prepare_submission "$project_name")
  if [ $? -ne 0 ]; then
    return 1
  fi

  cd "$submission_dir" || exit

  # Initialize git and push
  git init
  git add .
  git commit -m "chore(gpm): submission of ${PROJECT_NAME}" -m "
⣇⣿⠘⣿⣿⣿⡿⡿⣟⣟⢟⢟⢝⠵⡝⣿⡿⢂⣼⣿⣷⣌⠩⡫⡻⣝⠹⢿⣿⣷
⡆⣿⣆⠱⣝⡵⣝⢅⠙⣿⢕⢕⢕⢕⢝⣥⢒⠅⣿⣿⣿⡿⣳⣌⠪⡪⣡⢑⢝⣇
⡆⣿⣿⣦⠹⣳⣳⣕⢅⠈⢗⢕⢕⢕⢕⢕⢈⢆⠟⠋⠉⠁⠉⠉⠁⠈⠼⢐⢕⢽
⡗⢰⣶⣶⣦⣝⢝⢕⢕⠅⡆⢕⢕⢕⢕⢕⣴⠏⣠⡶⠛⡉⡉⡛⢶⣦⡀⠐⣕⢕
⡝⡄⢻⢟⣿⣿⣷⣕⣕⣅⣿⣔⣕⣵⣵⣿⣿⢠⣿⢠⣮⡈⣌⠨⠅⠹⣷⡀⢱⢕
⡝⡵⠟⠈⢀⣀⣀⡀⠉⢿⣿⣿⣿⣿⣿⣿⣿⣼⣿⢈⡋⠴⢿⡟⣡⡇⣿⡇⡀⢕
⡝⠁⣠⣾⠟⡉⡉⡉⠻⣦⣻⣿⣿⣿⣿⣿⣿⣿⣿⣧⠸⣿⣦⣥⣿⡇⡿⣰⢗⢄ This commit was generated by Git Project Manager
⠁⢰⣿⡏⣴⣌⠈⣌⠡⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣬⣉⣉⣁⣄⢖⢕⢕⢕ Visit https://github.com/airone01/ft
⡀⢻⣿⡇⢙⠁⠴⢿⡟⣡⡆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣵⣿
⡻⣄⣻⣿⣌⠘⢿⣷⣥⣿⠇⣿⣿⣿⣿⣿⣿⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣷⢄⠻⣿⣟⠿⠦⠍⠉⣡⣾⣿⣿⣿⣿⣿⣿⢸⣿⣦⠙⣿⣿⣿⣿⣿⣿⣿⣿⠟
⡕⡑⣑⣈⣻⢗⢟⢞⢝⣻⣿⣿⣿⣿⣿⣿⣿⠸⣿⠿⠃⣿⣿⣿⣿⣿⣿⡿⠁⣠
⡝⡵⡈⢟⢕⢕⢕⢕⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⠿⠋⣀⣈⠙
⡝⡵⡕⡀⠑⠳⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⢉⡠⡲⡫⡪⡪⡣"
  git remote add origin "${target_repo}"
  if ! git push -f origin main; then
    echo -e "${ANSI_RED}❌ Failed to push to repository${ANSI_NC}"
    cd "$original_dir" && rm -rf "$submission_dir"
    exit 1
  fi

  cd "$original_dir" && rm -rf "$submission_dir"
  echo -e "${ANSI_GREEN}✅ Project pushed to ${target_repo}${ANSI_NC}"
}

add_project() {
  REPO_URL=$1
  PROJECT_NAME=$2
  ORIGINAL_DIR=$(pwd)

  echo -e "${ANSI_BLUE}🚀 Adding project ${PROJECT_NAME}...${ANSI_NC}"

  # Create temporary directory
  TEMP_DIR=$(mktemp -d)
  cd "$TEMP_DIR" || exit

  # Clone the project repo
  echo -e "${ANSI_BLUE}📥 Cloning repository...${ANSI_NC}"
  if ! git clone "${REPO_URL}" "${PROJECT_NAME}"; then
    echo -e "${ANSI_RED}❌ Failed to clone repository${ANSI_NC}"
    cd "$ORIGINAL_DIR" && rm -rf "$TEMP_DIR"
    exit 1
  fi

  # Get all commit messages
  cd "${PROJECT_NAME}" || exit
  COMMIT_LOG=$(git log --pretty=format:"- %s%n%b" | sed '/^$/N;/^\n$/D')
  cd "$ORIGINAL_DIR" || exit

  # Create project directory and move files
  echo -e "${ANSI_BLUE}📦 Moving project files...${ANSI_NC}"
  mkdir -p "${PROJECT_NAME}"
  cp -r "${TEMP_DIR}/${PROJECT_NAME}"/* "${PROJECT_NAME}/"

  # Clean up temp directory
  rm -rf "$TEMP_DIR"

  # Add and commit with full history in commit message
  git add "${PROJECT_NAME}"
  git commit -m "chore(gpm): add project ${PROJECT_NAME}" -m "Original commit history:" -m "$COMMIT_LOG"

  echo -e "${ANSI_GREEN}✅ Successfully added ${PROJECT_NAME}${ANSI_NC}"
}

case "$1" in
"submit")
  if [ "$#" -ne 3 ]; then
    usage
  fi
  submit_project "$2" "$3"
  ;;
"test")
  if [ "$#" -ne 2 ]; then
    usage
  fi
  test_project "$2"
  ;;
*)
  usage
  ;;
esac
