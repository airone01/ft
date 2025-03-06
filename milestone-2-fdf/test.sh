#!/bin/bash

# FDF Project Tester
# This script tests various aspects of the FDF wireframe renderer

# Text formatting
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

# Test directory setup
TEST_DIR="fdf_test_files"
mkdir -p "$TEST_DIR"

# Check for xdotool
check_xdotool() {
  if ! command -v xdotool &>/dev/null; then
    echo -e "${YELLOW}${BOLD}Warning:${RESET} xdotool is not installed. Auto-closing tests will be skipped."
    echo "You can install it with: sudo apt-get install xdotool (Ubuntu/Debian)"
    return 1
  fi
  return 0
}

# Check if FDF executable exists
if [ ! -f "./fdf" ]; then
  echo -e "${RED}${BOLD}Error:${RESET} FDF executable not found at ./fdf"
  echo "Make sure your program is compiled and located in the current directory."
  exit 1
fi

# Function to print section headers
print_header() {
  echo -e "\n${BLUE}${BOLD}$1${RESET}"
  echo -e "${BLUE}${BOLD}$(printf '=%.0s' $(seq 1 ${#1}))${RESET}\n"
}

# Function to run a test and check if it passes
run_test() {
  local test_name="$1"
  local test_command="$2"
  local expected_result="$3"
  local auto_close="$4"

  echo -e "${BOLD}Testing:${RESET} $test_name"

  # if [ "$auto_close" = "true" ] && check_xdotool; then
  #   # Run in background and auto-close after 2 seconds
  #   $test_command &
  #   local pid=$!
  #   sleep 2
  #   if ps -p $pid >/dev/null; then
  #     # Find window ID and send ESC
  #     local win_id=$(xdotool search --pid $pid --class fdf)
  #     if [ -n "$win_id" ]; then
  #       xdotool key --window $win_id Escape
  #       sleep 0.5
  #     else
  #       echo -e "  ${YELLOW}⚠ Window not found, terminating process${RESET}"
  #       kill $pid
  #     fi
  #   fi
  #   wait $pid
  #   local exit_code=$?
  # else
  # Run normally
  $test_command >/dev/null 2>&1
  local exit_code=$?
  # fi

  if [ $exit_code -eq 0 ]; then
    if [ "$expected_result" = "pass" ]; then
      echo -e "  ${GREEN}✓ PASS${RESET}"
      return 0
    else
      echo -e "  ${RED}✗ FAIL (Expected failure, but got success)${RESET}"
      return 1
    fi
  else
    if [ "$expected_result" = "fail" ]; then
      echo -e "  ${GREEN}✓ PASS (Expected failure)${RESET}"
      return 0
    else
      echo -e "  ${RED}✗ FAIL${RESET}"
      return 1
    fi
  fi
}

# Generate test files
generate_test_files() {
  print_header "Generating Test Files"

  # 1. Basic 3x3 test map
  cat >"$TEST_DIR/basic_3x3.fdf" <<EOF
0 0 0
0 1 0
0 0 0
EOF
  echo -e "Created basic 3x3 test map"

  # 2. Flat map
  cat >"$TEST_DIR/flat.fdf" <<EOF
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
EOF
  echo -e "Created flat map"

  # 3. Diagonal ridge
  cat >"$TEST_DIR/diagonal.fdf" <<EOF
9 0 0 0 0
0 9 0 0 0
0 0 9 0 0
0 0 0 9 0
0 0 0 0 9
EOF
  echo -e "Created diagonal ridge map"

  # 4. Pyramid
  cat >"$TEST_DIR/pyramid.fdf" <<EOF
0 0 0 0 0
0 1 1 1 0
0 1 2 1 0
0 1 1 1 0
0 0 0 0 0
EOF
  echo -e "Created pyramid map"

  # 5. Map with colors
  cat >"$TEST_DIR/colors.fdf" <<EOF
0 0 0 0 0
0 0,0xFF0000 0,0xFF0000 0,0xFF0000 0
0 0,0xFF0000 1,0x00FF00 0,0xFF0000 0
0 0,0xFF0000 0,0xFF0000 0,0xFF0000 0
0 0 0 0 0
EOF
  echo -e "Created map with colors"

  # 6. Invalid map (non-rectangular)
  cat >"$TEST_DIR/invalid_nonrect.fdf" <<EOF
0 0 0
0 0
0 0 0 0
EOF
  echo -e "Created invalid non-rectangular map"

  # 7. Invalid map (with characters)
  cat >"$TEST_DIR/invalid_chars.fdf" <<EOF
0 0 0
0 A 0
0 0 0
EOF
  echo -e "Created invalid map with characters"

  # 8. Large map
  python3 -c "
import random
size = 50
with open('$TEST_DIR/large.fdf', 'w') as f:
    for i in range(size):
        for j in range(size):
            height = int((i/2 + j/2) % 10)
            f.write(f'{height}')
            if j < size-1:
                f.write(' ')
        f.write('\n')
" 2>/dev/null || {
    echo -e "${YELLOW}Warning: Could not generate large map (Python required)${RESET}"
    cat >"$TEST_DIR/large.fdf" <<EOF
0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1 0
0 1 2 2 2 2 2 2 1 0
0 1 2 3 3 3 3 2 1 0
0 1 2 3 4 4 3 2 1 0
0 1 2 3 4 4 3 2 1 0
0 1 2 3 3 3 3 2 1 0
0 1 2 2 2 2 2 2 1 0
0 1 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0 0 0
EOF
    echo -e "Created alternative large map (10x10)"
  }

  # 9. Empty file
  touch "$TEST_DIR/empty.fdf"
  echo -e "Created empty file"

  # 10. A single point
  echo "5" >"$TEST_DIR/single_point.fdf"
  echo -e "Created single point map"
}

# Basic functionality tests
test_basic_functionality() {
  print_header "Basic Functionality Tests"

  local pass_count=0
  local total_tests=0

  # Test 1: Run with valid 3x3 map
  run_test "Valid 3x3 map" "./fdf $TEST_DIR/basic_3x3.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 2: Run with flat map
  run_test "Flat map" "./fdf $TEST_DIR/flat.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 3: Run with diagonal map
  run_test "Diagonal ridge map" "./fdf $TEST_DIR/diagonal.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 4: Run with pyramid map
  run_test "Pyramid map" "./fdf $TEST_DIR/pyramid.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 5: Run with color map
  run_test "Map with colors" "./fdf $TEST_DIR/colors.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 6: Run with large map
  run_test "Large map" "./fdf $TEST_DIR/large.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 7: Run with single point
  run_test "Single point map" "./fdf $TEST_DIR/single_point.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Basic Functionality Results:${RESET} $pass_count/$total_tests tests passed"
}

# Error handling tests remain the same but without auto-close since they should fail
test_error_handling() {
  print_header "Error Handling Tests"

  local pass_count=0
  local total_tests=0

  # Test 1: No arguments
  run_test "No arguments" "./fdf" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 2: Too many arguments
  run_test "Too many arguments" "./fdf $TEST_DIR/basic_3x3.fdf extra_arg" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 3: File doesn't exist
  run_test "File doesn't exist" "./fdf nonexistent_file.fdf" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 4: Invalid non-rectangular map
  run_test "Invalid non-rectangular map" "./fdf $TEST_DIR/invalid_nonrect.fdf" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 5: Invalid map with characters
  run_test "Invalid map with characters" "./fdf $TEST_DIR/invalid_chars.fdf" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 6: Empty file
  run_test "Empty file" "./fdf $TEST_DIR/empty.fdf" "fail"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Error Handling Results:${RESET} $pass_count/$total_tests tests passed"
}

# Memory test (basic check for leaks)
test_memory() {
  print_header "Memory Test"

  if command -v valgrind >/dev/null 2>&1; then
    echo -e "${BOLD}Running memory test with Valgrind${RESET}"
    valgrind --leak-check=full ./fdf "$TEST_DIR/basic_3x3.fdf" >"$TEST_DIR/valgrind_output.txt" 2>&1

    if grep -q "All heap blocks were freed -- no leaks are possible" "$TEST_DIR/valgrind_output.txt"; then
      echo -e "  ${GREEN}✓ No memory leaks detected${RESET}"
    else
      local leak_summary=$(grep "definitely lost" "$TEST_DIR/valgrind_output.txt")
      echo -e "  ${RED}✗ Memory leaks detected:${RESET}"
      echo -e "    $leak_summary"
      echo -e "  See $TEST_DIR/valgrind_output.txt for details"
    fi
  else
    echo -e "${YELLOW}Valgrind not found. Skipping memory test.${RESET}"
    echo -e "To install Valgrind:"
    echo -e "  - On Ubuntu/Debian: sudo apt-get install valgrind"
    echo -e "  - On macOS: brew install valgrind"
    echo -e "  - On Fedora: sudo dnf install valgrind"
  fi
}

test_map_sizes() {
  print_header "Map Size Tests"

  local pass_count=0
  local total_tests=0

  # Generate maps of different sizes
  python3 -c "
  with open('$TEST_DIR/tiny.fdf', 'w') as f:
      f.write('1')

  with open('$TEST_DIR/small_5x5.fdf', 'w') as f:
      for i in range(5):
          f.write(' '.join(['1' if i == j else '0' for j in range(5)]) + '\n')

  with open('$TEST_DIR/medium_50x50.fdf', 'w') as f:
      for i in range(50):
          f.write(' '.join(['1' if (i+j) % 10 == 0 else '0' for j in range(50)]) + '\n')

  with open('$TEST_DIR/large_100x100.fdf', 'w') as f:
      for i in range(100):
          f.write(' '.join(['1' if (i*j) % 25 == 0 else '0' for j in range(100)]) + '\n')
  " 2>/dev/null || echo -e "${YELLOW}Warning: Could not generate size test maps (Python required)${RESET}"

  # Test different sizes
  run_test "Tiny map (1x1)" "./fdf $TEST_DIR/tiny.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "Small map (5x5)" "./fdf $TEST_DIR/small_5x5.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "Medium map (50x50)" "./fdf $TEST_DIR/medium_50x50.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "Large map (100x100)" "./fdf $TEST_DIR/large_100x100.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Map Size Tests Results:${RESET} $pass_count/$total_tests tests passed"
}

test_edge_cases() {
  print_header "Edge Case Tests"

  local pass_count=0
  local total_tests=0

  # Create test files
  echo "" >"$TEST_DIR/blank_line.fdf"
  echo "0 0 0" >"$TEST_DIR/blank_line.fdf"
  echo "" >>"$TEST_DIR/blank_line.fdf"
  echo "0 0 0" >>"$TEST_DIR/blank_line.fdf"

  echo "0 0 0\r0 0 0\r0 0 0" >"$TEST_DIR/windows_endings.fdf"

  echo "0,0xFF0000 0,0x00FF00 0,0x0000FF" >"$TEST_DIR/all_colors.fdf"

  echo "0 0 0" >"$TEST_DIR/trailing_spaces.fdf"
  echo "0 0 0   " >>"$TEST_DIR/trailing_spaces.fdf"
  echo "   0 0 0" >>"$TEST_DIR/trailing_spaces.fdf"

  # Run the tests
  run_test "File with blank lines" "./fdf $TEST_DIR/blank_line.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "File with Windows line endings" "./fdf $TEST_DIR/windows_endings.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "File with all colors" "./fdf $TEST_DIR/all_colors.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  run_test "File with trailing spaces" "./fdf $TEST_DIR/trailing_spaces.fdf" "pass" "true"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Edge Case Tests Results:${RESET} $pass_count/$total_tests tests passed"
}

test_performance() {
  print_header "Performance Tests"

  local max_time=5.0 # Maximum acceptable time in seconds

  # Create a large map if it doesn't exist
  if [ ! -f "$TEST_DIR/large.fdf" ]; then
    python3 -c "
    size = 100
    with open('$TEST_DIR/performance.fdf', 'w') as f:
        for i in range(size):
            for j in range(size):
                height = (i * j) % 20
                f.write(f'{height}')
                if j < size-1:
                    f.write(' ')
            f.write('\n')
    " 2>/dev/null || echo -e "${YELLOW}Warning: Could not generate performance test map (Python required)${RESET}"
  else
    cp "$TEST_DIR/large.fdf" "$TEST_DIR/performance.fdf"
  fi

  echo -e "${BOLD}Testing performance with large map${RESET}"

  # Time the execution
  /usr/bin/time -f "%e" ./fdf "$TEST_DIR/performance.fdf" >/dev/null 2>"$TEST_DIR/time_result.txt" &
  local pid=$!

  # Wait a moment then send ESC
  sleep 3
  if check_xdotool && ps -p $pid >/dev/null; then
    local win_id=$(xdotool search --pid $pid --class fdf)
    if [ -n "$win_id" ]; then
      xdotool key --window $win_id Escape
    else
      kill $pid 2>/dev/null
    fi
  fi

  wait $pid
  local exit_code=$?
  local execution_time=$(cat "$TEST_DIR/time_result.txt")

  echo -e "Execution time: ${YELLOW}$execution_time seconds${RESET}"

  if (($(echo "$execution_time < $max_time" | bc -l))); then
    echo -e "  ${GREEN}✓ Good performance (under $max_time seconds)${RESET}"
  else
    echo -e "  ${RED}✗ Poor performance (over $max_time seconds)${RESET}"
  fi

  if [ $exit_code -ne 0 ]; then
    echo -e "  ${RED}✗ Program crashed during performance test${RESET}"
  fi
}

test_command_line_args() {
  print_header "Command Line Arguments Tests"

  local pass_count=0
  local total_tests=0

  # Test with no arguments
  run_test "No arguments" "./fdf" "fail" "false"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test with non-existent file
  run_test "Non-existent file" "./fdf nonexistent_file.fdf" "fail" "false"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test with directory instead of file
  run_test "Directory as argument" "./fdf $TEST_DIR" "fail" "false"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test with too many arguments
  run_test "Too many arguments" "./fdf $TEST_DIR/basic_3x3.fdf extra_arg" "fail" "false"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Command Line Arguments Tests Results:${RESET} $pass_count/$total_tests tests passed"
}

# Main function
main() {
  echo -e "${BOLD}${BLUE}FDF Project Tester${RESET}"
  echo -e "Testing executable: ${YELLOW}./fdf${RESET}"

  # Check for xdotool
  check_xdotool

  # Generate test files
  generate_test_files

  # Run tests
  test_basic_functionality
  test_error_handling
  test_map_sizes
  test_edge_cases
  test_command_line_args
  test_performance
  test_memory

  print_header "Testing Complete"
  echo -e "All test files are located in the ${YELLOW}$TEST_DIR${RESET} directory."
  echo -e "You can use these files for manual testing as well.\n"
}

# Run the main function
main
