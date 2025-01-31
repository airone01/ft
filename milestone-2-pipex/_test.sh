#!/usr/bin/env bash
# This "tests" the program with arbitrary requirements defined by me :-)
# Make your own tests!

GREEN="\033[1;32m"
RED="\033[1;31m"
GREY="\033[1;90m"
BLACK_WHITE="\033[1;30;47m"
RESET="\033[0m"

VALGRIND="valgrind --show-leak-kinds=all --trace-children=yes --child-silent-after-fork=yes --track-fds=yes --leak-check=full --trace-children-skip=/bin/*,/usr/bin/*,/nix/*"
CMD="sort"
PROG="./pipex"
FILE_IN="file_bee" # Bee Movie script
FILE_OUT=$(mktemp)
CMDS_MIN=1
CMDS_MAX=1024

# Runs once and get the output
# echo -e "${BLACK_WHITE} #### 1. Normal #### ${RESET}"
# OG_RESULT=$(yes "$CMD" | head -n $CMDS_MAX | xargs -I {} echo -n "| {} " | xargs -0 bash -c "cat $FILE_IN {}" 2>/dev/null)
# YOUR_RESULT=$($PROG $FILE_IN $(yes "$CMD" | head -n $CMDS_MAX | tr '\n' ' ') /dev/stdout)
# OG_RESULT_LEN=$(echo "$OG_RESULT" | wc -c)
# YOUR_RESULT_LEN=$(echo "$YOUR_RESULT" | wc -c)

# printf "A. Length"
# if [ "$OG_RESULT_LEN" -eq "$YOUR_RESULT_LEN" ]; then
#   echo -e "\t${GREEN}SUCCESS ✓${RESET}"
# else
#   echo -e "\t${RED}FAIL ✗${RESET}"
# fi
# echo -e "${GREY}Original:\t$OG_RESULT_LEN${RESET}"
# echo -e "${GREY}Yours:\t\t$YOUR_RESULT_LEN${RESET}"

# # Runs again with valgrind
# echo -e "${BLACK_WHITE} #### 2. With valgrind #### ${RESET}"
# RESULT_NO_ERR=$($VALGRIND $PROG $FILE_IN $(yes "$CMD" | head -n $CMDS_MAX | tr '\n' ' ') /dev/null 2>/dev/null)

# printf "A. Empty"
# if [ -z "$RESULT_NO_ERR" ]; then
#   echo -e "\t${GREEN}SUCCESS ✓${RESET}"
# else
#   echo -e "\t${RED}FAIL ✗${RESET}"
# fi

# printf "B. Leaks"
# RESULT_ERR_TO_STDOUT=$($VALGRIND $PROG $FILE_IN $(yes "$CMD" | head -n $CMDS_MAX | tr '\n' ' ') $FILE_OUT 2>&1)
# echo "$RESULT_ERR_TO_STDOUT" | grep -q "no leaks are possible"
# if [ $? -eq 0 ]; then
#   echo -e "\t${GREEN}SUCCESS ✓${RESET}"
# else
#   echo -e "\t${RED}FAIL ✗${RESET}"
# fi

# echo "C. Allocs stats"
# ALLOCS=$(echo "$RESULT_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) allocs.*/\1/')
# FREES=$(echo "$RESULT_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) frees.*/\1/')
# BYTES=$(echo "$RESULT_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) bytes.*/\1/')
# echo -e "${GREY}Allocs:\t\t$ALLOCS${RESET}"
# echo -e "${GREY}Frees:\t\t$FREES${RESET}"
# echo -e "${GREY}Bytes:\t\t$BYTES${RESET}"

# echo -e "${BLACK_WHITE} #### 3. Time measurements #### ${RESET}"
# RESULT_OG=$( (time yes "$CMD" | head -n $CMDS_MAX | xargs -I {} echo -n "| {} " | xargs -0 bash -c "cat $FILE_IN {}" 2>/dev/null >/dev/null) 2>&1)
# RESULT_YOURS=$( (time $PROG $FILE_IN $(yes "$CMD" | head -n $CMDS_MAX | tr '\n' ' ') /dev/null 2>/dev/null >/dev/null) 2>&1)

# echo -e "A. Original:\n${GREY}${RESULT_OG}${RESET}"
# echo -e "B. Yours:\n${GREY}${RESULT_YOURS}${RESET}"

# echo -e "${BLACK_WHITE} #### 4. PIP (pipex in pipex) with valgrind #### ${RESET}"

# printf "A. Empty"
# RESULT_PIP_EMPTY=$(${PROG} ${FILE_IN} ${prog}\ /dev/stdin\ ${CMD}\ ${CMD}\ /dev/stdout wc\ ${CMD} ${CMD} /dev/null 2>/dev/null)
# if [ -z "$RESULT_PIP_EMPTY" ]; then
#   echo -e "\t${GREEN}SUCCESS ✓${RESET}"
# else
#   echo -e "\t${RED}FAIL ✗${RESET}"
# fi

printf "B. Leaks"
RESULT_PIP_ERR_TO_STDOUT=$(${VALGRIND} ${PROG} ${FILE_IN} ${PROG}\ /dev/stdin\ ${CMD}\ ${CMD}\ /dev/stdout ${CMD} ${CMD} /dev/null 2>&1)
echo "$RESULT_PIP_ERR_TO_STDOUT" | grep -q "no leaks are possible"
if [ $? -eq 0 ]; then
  echo -e "\t${GREEN}SUCCESS ✓${RESET}"
else
  echo -e "\t${RED}FAIL ✗${RESET}"
fi

echo "C. Allocs stats"
ALLOCS=$(echo "$RESULT_PIP_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) allocs.*/\1/')
FREES=$(echo "$RESULT_PIP_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) frees.*/\1/')
BYTES=$(echo "$RESULT_PIP_ERR_TO_STDOUT" | grep "total heap usage:" | sed -E 's/.* ([0-9,]+) bytes.*/\1/')

echo -e "${GREY}Allocs:\t\t$ALLOCS${RESET}"
echo -e "${GREY}Frees:\t\t$FREES${RESET}"
echo -e "${GREY}Bytes:\t\t$BYTES${RESET}"
