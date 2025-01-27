#!/bin/bash

# Reset
Color_Off='\033[0m'       # Text Reset
Reverse='\033[7m'       # Reverse BG and FG

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White

if [ $# -eq 0 ]; then
  FORD_PATH=.
fi

if [ $# -eq 1 ]; then
  if [ $1 = "--help" ] || [ $1 = "-h" ]; then
    echo "Usage: ford [directory]"
    return 0
  fi
  FORD_PATH=$1
fi

title() {
  echo -e "${BIBlack}${Reverse}     $1 ${Color_Off}"
}
ok() {
  echo -en "${On_Green}${BIWhite} OK ${Color_Off} $1"
}
ko() {
  echo -en "${On_Red}${BIWhite} KO ${Color_Off}${BIRed} $1"
}
warn() {
  echo -en "${On_Yellow}${BIWhite} !! ${Color_Off}${BIYellow} $1"
}

# Norminette
title "NORM"
NORM_OK="$(norminette -R CheckForbiddenSourceHeader ${FORD_PATH} 2>&1|grep 'OK!')"
NORM_KO="$(norminette -R CheckForbiddenSourceHeader ${FORD_PATH} 2>&1|grep -ve '.*OK!' -e '^  ')"
if [ -n "${NORM_OK}" ]; then
  echo -ne "${NORM_OK}\n" | while read line ; do ok "$(echo ${line}|sed 's/: OK!//g')\n" ; done
fi
if [ -n "${NORM_KO}" ]; then
  ko "${NORM_KO}\n"
fi

# Additional files
title "Dir tree"
AF="$(find . -path ./.git -prune -o -name '*' -type f -print|grep -ve '.*\.c$' -e '.*\.h$' -e '.*\.cpp$')"
# if [ -z "${AF}" ]
if [ -n "${AF}" ]; then
  ko "Unwanted files? :\n${AF}\n";
else
  ok "Unwanted files\n";
fi
DIRS="$(find . -path ./.git -prune -o -name '*' -type d -print|grep -ve '.*/ex..$' -e '^\.$')"
if [ -n "${DIRS}" ]; then
  ko "Unwanted dirs:\n${DIRS}\n";
else
  ok "Unwanted dirs\n";
fi

# GIT
title "GIT"
GIT_EF="$(git status --porcelain|grep -e '??'|cut -c4-)"
if [ -n "${GIT_EF}" ]; then
  ko "Untracked files (use 'git add' then 'git commit' or remove!):\n${GIT_EF}\n";
else
  ok "Untracked files\n";
fi
GIT_ST="$(git status --porcelain|grep -ve '??')"
if [ -n "${GIT_ST}" ]; then
  ko "Uncommited changes (use 'git commit'!):\n${GIT_ST}\n";
else
  ok "Uncommited changes\n";
fi
GIT_PUSH="$(git log --branches --not --remotes --oneline --graph)"
if [ -n "${GIT_PUSH}" ]; then
  ko "!!! UNPUSHED COMMITS !!! Push to repo with 'git commit'!:\n${GIT_PUSH}\n";
else
  ok "Unpushed commits\n";
fi

# C files
title "C files"
C_LIB="$(grep -re '^#include <stdio.h>' -e '^#include <string.h>' -e '^#include <bsd' -e '^#include <limits.h>')"
if [ -n "${C_LIB}" ]; then
  ko "Forbidden libs (comment the line):\n${C_LIB}\n";
else
  ok "Forbidden libs\n";
fi
C_MAIN="$(grep -re '^int	*main(.*$')"
if [ -n "${C_MAIN}" ]; then
  warn "Main uncommented (comment the function):\n${C_MAIN}\n";
else
  ok "Main uncommented\n";
fi

# CC
title "CC/GCC (no compile!)"
CC_KO="$(cc -Wall -Werror -Wextra -fsyntax-only **/* 2>&1)"
if [ -n "${CC_KO}" ]; then
  ko "CC errors:\n${CC_KO}\n";
else
  ok "CC errors\n";
fi
