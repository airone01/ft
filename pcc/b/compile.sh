#!/usr/bin/env sh
compile() (
  set -e
  for i in $(seq 1 $#); do
    eval "S$i"="$(mktemp)"
    eval "O$i"="$(mktemp)"
    ./B <"$(eval echo \$"$i")" >"$(eval echo \$S"$i")"
    gcc -c -m32 -x assembler "$(eval echo \$S"$i")" -o "$(eval echo \$O"$i")"
    rm "$(eval echo \$S"$i")"
  done
  ld -m elf_i386 "$(eval echo $(seq -f "\$O%.0f" -s ' ' 1 $#))" brt0.o
  rm "$(eval echo $(seq -f "\$O%.0f" -s ' ' 1 $#))"
)
