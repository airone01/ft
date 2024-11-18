#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

usage() {
    echo -e "${BLUE}Git Project Manager 📦${NC}"
    echo -e "Usage:"
    echo -e "  $0 add <repo-url> <project-name> ${GREEN}# Add project to central repo${NC}"
    echo -e "  $0 extract <project-name> <target-repo-url> ${GREEN}# Extract and force push project${NC}"
    exit 1
}

add_project() {
    REPO_URL=$1
    PROJECT_NAME=$2
    ORIGINAL_DIR=$(pwd)

    echo -e "${BLUE}🚀 Adding project ${PROJECT_NAME}...${NC}"

    # Create temporary directory
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR" || exit

    # Clone the project repo
    echo -e "${BLUE}📥 Cloning repository...${NC}"
    if ! git clone "${REPO_URL}" "${PROJECT_NAME}"; then
        echo -e "${RED}❌ Failed to clone repository${NC}"
        cd "$ORIGINAL_DIR" && rm -rf "$TEMP_DIR"
        exit 1
    fi

    # Get all commit messages
    cd "${PROJECT_NAME}" || exit
    COMMIT_LOG=$(git log --pretty=format:"- %s%n%b")
    cd "$ORIGINAL_DIR" || exit

    # Create project directory and move files
    echo -e "${BLUE}📦 Moving project files...${NC}"
    mkdir -p "${PROJECT_NAME}"
    cp -r "${TEMP_DIR}/${PROJECT_NAME}"/* "${PROJECT_NAME}/"

    # Clean up temp directory
    rm -rf "$TEMP_DIR"

    # Add and commit with full history in commit message
    git add "${PROJECT_NAME}"
    git commit -m "Add ${PROJECT_NAME}" -m "Original commit history:" -m "$COMMIT_LOG"

    echo -e "${GREEN}✅ Successfully added ${PROJECT_NAME}${NC}"
}

extract_project() {
    PROJECT_NAME=$1
    TARGET_REPO=$2
    ORIGINAL_DIR=$(pwd)

    echo -e "${BLUE}📤 Extracting ${PROJECT_NAME}...${NC}"

    # Create temporary directory
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR" || exit

    # Initialize new repo
    git init

    # Copy latest version of files from main repo
    cp -r "${ORIGINAL_DIR}/${PROJECT_NAME}"/* .

    # Commit and force push
    git add .
    git commit -m "Project ${PROJECT_NAME} submission"
    git remote add origin "${TARGET_REPO}"
    if ! git push -f origin main; then
        echo -e "${RED}❌ Failed to push to repository${NC}"
        cd "$ORIGINAL_DIR" && rm -rf "$TEMP_DIR"
        exit 1
    fi

    cd "$ORIGINAL_DIR" && rm -rf "$TEMP_DIR"
    echo -e "${GREEN}✅ Project pushed to ${TARGET_REPO}${NC}"
}

case "$1" in
    "add")
        if [ "$#" -ne 3 ]; then
            usage
        fi
        add_project "$2" "$3"
        ;;
    "extract")
        if [ "$#" -ne 3 ]; then
            usage
        fi
        extract_project "$2" "$3"
        ;;
    *)
        usage
        ;;
esac