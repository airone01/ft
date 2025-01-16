#!/usr/bin/env bash

# Reset
Color_Off='\033[0m'       # Text Reset

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

# Script path. duh
# SCRIPTPATH=$(dirname $0)
# SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
SCRIPTPATH="$(realpath -LP ~/ford)"
MAKEFILEPATH="$(realpath -mLP "${SCRIPTPATH}/Makefile")"

if [ $# -eq 1 ]; then
  if [ $1 = "--help" ] || [ $1 = "-h" ] || [ $# -eq 0 ]; then
    echo "Usage: war <project> [--list]"
    exit 0
  fi
  FORD_PATH=$1
fi

title() {
  echo -e "${On_Black}${BIWhite}     $1 ${Color_Off}"
}
ok() {
  echo -en "${On_Green}${BIWhite} OK ${Color_Off} $1"
}
ko() {
  echo -en "${On_Red}${BIWhite} KO ${Color_Off}${BIRed} $1"
}

assert_1() {
  RESULT="$(./a.out "$1")"
  if [[ "$RESULT" == "$2" ]]; then
    ok "'$(echo $1|sed 's/\n/\\n/g')'\n";
  else
    ko "'$(echo $1|sed 's/\n/\\n/g')'\nExpected: '$2'\nGot     : '$RESULT'\n";
  fi
}
assert_2() {
  RESULT="$(./a.out "$1" "$2")"
  if [[ "$RESULT" == "$3" ]]; then
    ok "'$(echo $1|sed 's/\n/\\n/g')'\n";
  else
    ko "'$(echo $1|sed 's/\n/\\n/g')'\nExpected: '$3'\nGot     : '$RESULT'\n";
  fi
}

fbuild() {
  if [ -z "${EXO}" ]; then
    ko "fbuild(${PROJ}): EXO is undefined\n"
    return 1;
  fi
  if [ -z "${PROG}" ]; then
    PROG="$(realpath "${EXO}/${PROJ}.out")";
  fi
  if [ -z "${MAIN}" ]; then
    MAIN="$(realpath "${SCRIPTPATH}/mains/${PROJ}")";
  fi
  if [ -z "${SRCS}" ]; then
    SRCS="$(realpath "${EXO}/${PROJ}.c")";
  fi
  MAIN="$(realpath -mLP "${SCRIPTPATH}/${MAIN}.c")"
  title "Debug info"
  echo -en "SCRIPTPATH: ${SCRIPTPATH}\nMAKEFILEPATH: ${MAKEFILEPATH}\nEXO: ${EXO}\nPROJ: ${PROJ}\nPROG: ${PROG}\nMAIN: ${MAIN}\nSRCS: ${SRCS}\n"
  title "make"
  make --makefile="${MAKEFILEPATH}" re;
}

c04() {
  EXO="ex00"
  PROJ="ft_strlen";
  fbuild;
  # ftest;
}
if [[ "$1" == "c04" ]]; then
  c04;
fi

# For atoi
if [[ "$1" == "atoi" ]]; then
  title "Testing for ft_atoi"
  assert_1 "1234" "1234";
  assert_1 "" "0";
  assert_1 "    1234" "1234";
  assert_1 "-1" "-1";
  assert_1 "1" "1";
  assert_1 "-69420" "-69420";
  assert_1 "abc123" "0";
  assert_1 "2147483647" "2147483647";
  assert_1 "-2147483648" "-2147483648";
  assert_1 "-" "0";
  assert_1 "+++--+-123" "-123";
  assert_1 "      +++--+-123" "-123";
  assert_1 "      +++- -+-123" "0";
  assert_1 "-0012gfg4" "-12";
  # assert_1 "-999999999999" "-2147483648";
  # assert_1 "1231231231311133" "2147483647";
fi

# Classic "int-like string"
if [[ "$1" == "int_str" ]]; then
  title "Testing nbr strings"
  assert_1 "1234" "1234";
  assert_1 "0" "0";
  assert_1 "-1" "-1";
  assert_1 "1" "1";
  assert_1 "-69420" "-69420";
  assert_1 "2147483647" "2147483647";
  assert_1 "-2147483648" "-2147483648";
  # assert_1 "-999999999999" "-2147483648";
  # assert_1 "1231231231311133" "2147483647";
fi

# For strlen
if [[ "$1" == "strlen" ]]; then
  title "Testing for ft_strlen"
  assert_1 "1234" "4";
  assert_1 "0" "1";
  assert_1 "" "0";
  assert_1 "aaaaaaaaaaaaaa" "14";
  assert_1 "              " "14";
  assert_1 "abcdefghijklmnopqrstuvwxyz" "26";
fi

# For putstr
if [[ "$1" == "putstr" ]]; then
  title "Testing for ft_putstr"
  assert_1 "1234" "1234";
  assert_1 "0" "0";
  assert_1 "" "";
  assert_1 "aaaaaaaaaaaaaa" "aaaaaaaaaaaaaa";
  assert_1 "              " "              ";
  assert_1 "abcdefghijklmnopqrstuvwxyz" "abcdefghijklmnopqrstuvwxyz";
  assert_1 "\n" "\n";
  assert_1 "\n\n" "\n\n";
fi

# For putstr_base
if [[ "$1" == "putstr_base" ]]; then
  title "Testing for ft_putstr_base: positive"
  assert_2 "1234" "0123456789" "1234";
  assert_2 "" "0123456789" "0";
  assert_2 "" "01" "0";
  assert_2 "69420" "01" "10000111100101100";
  assert_2 "69420" "0123456789ABCDEF" "10F2C";
  assert_2 "69420" "01234567" "207454";
  assert_2 "0" "0123456789" "0";
  assert_2 "69420" "0" "";
  assert_2 "69420" "" "";
  title "Testing for ft_putstr_base: negative"
  assert_2 "-1234" "0123456789" "-1234";
  assert_2 "-" "0123456789" "0";
  assert_2 "-" "01" "0";
  assert_2 "-69420" "01" "-10000111100101100";
  assert_2 "-69420" "0123456789ABCDEF" "-10F2C";
  assert_2 "-69420" "01234567" "-207454";
  assert_2 "-0" "0123456789" "0";
  assert_2 "-69420" "0" "";
  assert_2 "-69420" "" "";
fi

# For facto
if [[ "$1" == "facto" ]]; then
  title "Testing for ft_factorial"
  assert_1 "0" "1";
  assert_1 "1" "1";
  assert_1 "2" "2";
  assert_1 "3" "6";
  assert_1 "4" "24";
  assert_1 "5" "120";
  assert_1 "6" "720";
  assert_1 "7" "5040";
  assert_1 "8" "40320";
  assert_1 "9" "362880";
  assert_1 "10" "3628800";
  title "Testing for ft_factorial: edge-cases"
  assert_1 "-123" "0";
fi

# For pow
if [[ "$1" == "pow" ]]; then
  title "Testing for ft_power"
  assert_2 "0" "0" "1";
  assert_2 "100" "-1" "0";
  assert_2 "100" "-10" "0";
  assert_2 "100" "0" "1";
  assert_2 "2" "4" "16";
  assert_2 "3" "2" "9";
  assert_2 "4" "7" "16384";
fi

# For fibonacci sequence
if [[ "$1" == "fibo" ]]; then
  title "Testing for ft_fibonacci"
  assert_1 "15" "610";
  assert_1 "1" "1";
  assert_1 "10" "55";
  assert_1 "4" "3";
  assert_1 "7" "13";
  title "Testing for ft_fibonacci: edge cases"
  assert_1 "0" "0";
  assert_1 "1" "1";
  assert_1 "2" "1";
  assert_1 "3" "2";
  assert_1 "-1" "-1";
  assert_1 "-10" "-1";
fi

# For square root
if [[ "$1" == "sqrt" ]]; then
  title "Testing for ft_sqrt"
  assert_1 "25" "5";
  assert_1 "81" "9";
  title "Testing for ft_sqrt: edge cases"
  assert_1 "0" "0";
  assert_1 "2" "0";
  assert_1 "-1" "0";
  assert_1 "-10" "0";
fi

# For is_prime
if [[ "$1" == "prime" ]]; then
  title "Testing for ft_is_prime"
  assert_1 "2" "1";
  assert_1 "3" "1";
  assert_1 "16" "0";
  assert_1 "17" "1";
  assert_1 "21" "0";
  title "Testing for ft_is_prime: edge cases"
  assert_1 "0" "0";
  assert_1 "1" "0";
  assert_1 "-1" "0";
  assert_1 "-10" "0";
fi

# For find_next_prime
if [[ "$1" == "nprime" ]]; then
  title "Testing for ft_find_next_prime"
  assert_1 "2" "2";
  assert_1 "3" "3";
  assert_1 "16" "17";
  assert_1 "17" "17";
  assert_1 "18" "19";
  assert_1 "21" "23";
  title "Testing for ft_find_next_prime: edge cases"
  assert_1 "0" "2";
  assert_1 "1" "2";
  assert_1 "-1" "2";
  assert_1 "-10" "2";
fi
