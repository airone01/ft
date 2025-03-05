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

  echo -e "${BOLD}Testing:${RESET} $test_name"

  if $test_command >/dev/null 2>&1; then
    if [ "$expected_result" == "pass" ]; then
      echo -e "  ${GREEN}✓ PASS${RESET}"
      return 0
    else
      echo -e "  ${RED}✗ FAIL (Expected failure, but got success)${RESET}"
      return 1
    fi
  else
    if [ "$expected_result" == "fail" ]; then
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
  run_test "Valid 3x3 map" "./fdf $TEST_DIR/basic_3x3.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 2: Run with flat map
  run_test "Flat map" "./fdf $TEST_DIR/flat.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 3: Run with diagonal map
  run_test "Diagonal ridge map" "./fdf $TEST_DIR/diagonal.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 4: Run with pyramid map
  run_test "Pyramid map" "./fdf $TEST_DIR/pyramid.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 5: Run with color map
  run_test "Map with colors" "./fdf $TEST_DIR/colors.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 6: Run with large map
  run_test "Large map" "./fdf $TEST_DIR/large.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  # Test 7: Run with single point
  run_test "Single point map" "./fdf $TEST_DIR/single_point.fdf" "pass"
  [ $? -eq 0 ] && ((pass_count++))
  ((total_tests++))

  echo -e "\n${BOLD}Basic Functionality Results:${RESET} $pass_count/$total_tests tests passed"
}

# Error handling tests
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

# # Performance tests
# test_performance() {
#   print_header "Performance Tests"

#   # Test with large map and time execution
#   echo -e "${BOLD}Testing performance with large map${RESET}"
#   local start_time=$(date +%s.%N)
#   ./fdf "$TEST_DIR/large.fdf" >/dev/null 2>&1
#   local exit_code=$?
#   local end_time=$(date +%s.%N)
#   local execution_time=$(echo "$end_time - $start_time" | bc)

#   echo -e "Execution time: ${YELLOW}$execution_time seconds${RESET}"

#   if (($(echo "$execution_time < 2.0" | bc -l))); then
#     echo -e "  ${GREEN}✓ Good performance (under 2 seconds)${RESET}"
#   elif (($(echo "$execution_time < 5.0" | bc -l))); then
#     echo -e "  ${YELLOW}⚠ Acceptable performance (under 5 seconds)${RESET}"
#   else
#     echo -e "  ${RED}✗ Poor performance (over 5 seconds)${RESET}"
#   fi

#   if [ $exit_code -ne 0 ]; then
#     echo -e "  ${RED}✗ Program crashed during performance test${RESET}"
#   fi
# }

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

# Main function
main() {
  echo -e "${BOLD}${BLUE}FDF Project Tester${RESET}"
  echo -e "Testing executable: ${YELLOW}./fdf${RESET}"

  # Generate test files
  generate_test_files

  # Run tests
  test_basic_functionality
  test_error_handling
  # test_performance
  test_memory

  print_header "Testing Complete"
  echo -e "All test files are located in the ${YELLOW}$TEST_DIR${RESET} directory."
  echo -e "You can use these files for manual testing as well.\n"
}

# Run the main function
main
