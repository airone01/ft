#!/usr/bin/env bash

make all bonus

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

function test_result {
    if [ "$1" -eq 0 ]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}KO${NC}"
    fi
}

# Test 1: Non-numeric parameters
./push_swap a b c | grep -q "Error"
test_result $?

# Test 2: Duplicate numeric parameters
./push_swap 1 2 3 2 | grep -q "Error"
test_result $?

# Test 3: Numeric parameters including one greater than MAXINT
./push_swap 1 2 2147483648 | grep -q "Error"
test_result $?

echo -e "\nBasic tests:"

# Test 4: No parameters
output=$(./push_swap)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

# Test 5: Single parameter
output=$(./push_swap 42)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

# Test 6: Two sorted parameters
output=$(./push_swap 2 3)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

# Test 7: Sorted sequence of four numbers
output=$(./push_swap 0 1 2 3)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

# Test 8: Sorted sequence of ten numbers
output=$(./push_swap 0 1 2 3 4 5 6 7 8 9)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

# Test 10: Sorted output validation
ARG="2 1 0"
./push_swap $ARG | ./checker_linux $ARG | grep -q "OK"
test_result $?

# Test 11: Random values between 0 and 3
ARG=$(shuf -i 0-3 -n 3 | tr '\n' ' ')
instructions=$(./push_swap $ARG | wc -l)
./push_swap $ARG | ./checker_linux $ARG | grep -q "OK" && [ $instructions -le 3 ]
test_result $?

# Test 12: Specific 5-value list
ARG="1 5 2 4 3"
instructions=$(./push_swap $ARG | wc -l)
./push_swap $ARG | ./checker_linux $ARG | grep -q "OK" && [ $instructions -le 12 ]
test_result $?

# Test 13: Random 5-value list
ARG=$(shuf -i 0-100 -n 5 | tr '\n' ' ')
instructions=$(./push_swap $ARG | wc -l)
./push_swap $ARG | ./checker_linux $ARG | grep -q "OK" && [ $instructions -le 12 ]
test_result $?

# Test 14: Checker duplicate numeric parameter
./checker 1 2 3 2 | grep -q "Error"
test_result $?

# Test 15: Checker parameter greater than MAXINT
./checker 1 2 2147483648 | grep -q "Error"
test_result $?

# Test 16: Checker without parameters
output=$(./checker)
if [ -z "$output" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

echo here

# Test 17: Checker invalid instruction
printf "invalid\n" | ./checker 1 2 3 | grep -q "Error"
test_result $?

# Test 18: Checker instruction with spaces
printf " sa \n" | ./checker 1 2 3 | grep -q "Error"
test_result $?

# Test 19: Checker valid list, invalid sort instructions
printf "sa\npb\nrrr\n" | ./checker 0 9 1 8 2 7 3 6 4 5 | grep -q "KO"
test_result $?

# Test 20: Checker valid list, invalid instructions
ARG="0 9 1 8 2"
printf "pb\nra\nra\nsa\nra\n" | ./checker $ARG | grep -q "KO"
test_result $?

# Test 21: Checker valid list, valid instructions
ARG="0 9 1 8 2"
printf "pb\nra\npb\nra\nsa\nra\npa\npa\n" | ./checker $ARG | grep -q "OK"
test_result $?

# Test 22: Checker valid list, no instructions
ARG="0 1 2"
./checker $ARG </dev/null | grep -q "OK"
test_result $?

# End of tests

echo -e "\nComplexity tests (provided checker):"
# Minimal
./complexity 100 100 700 -f ./push_swap ./checker_linux
# Maximal
./complexity 500 100 5500 -f ./push_swap ./checker_linux

echo -e "\nComplexity tests (bonus checker):"
# Minimal
./complexity 100 100 700 -f ./push_swap ./checker
# Maximal
./complexity 500 100 5500 -f ./push_swap ./checker
