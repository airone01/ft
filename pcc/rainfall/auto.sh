#!/usr/bin/env bash

###############################################################################
#                               __         ___         __ __                  #
#                  .----.---.-.|__|.-----.'  _|.---.-.|  |  |                 #
#                  |   _|  _  ||  ||     |   _||  _  ||  |  |                 #
#                  |__| |___._||__||__|__|__|  |___._||__|__|                 #
#                        This script requires sshpass.                        #
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
  local ptr="p_${level}"
  printf '%sok%s %s\n' "${GREEN}" "${RESET}" "${CYAN}${!ptr}${RESET}" >&2
}

# --------------------------------------------------------------------------- #

cat >&2 <<a
             __         ___         __ __
.----.---.-.|__|.-----.'  _|.---.-.|  |  |
|   _|  _  ||  ||     |   _||  _  ||  |  |
|__| |___._||__||__|__|__|  |___._||__|__|

a

pre 0
p_0=level0
report 0

pre 1
sc_run level0 "${p_0}" 'echo "cat ~level1/.pass" |./level0 423'
report 1
