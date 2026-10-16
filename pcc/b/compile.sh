#!/usr/bin/env sh

# This file defines the `compile` shell function, which compiles some B code to
# Intel assembly with `./B`, and then uses `gcc` to compile this assembly to a
# native executable binary, `a.out`.
# To use this file, source it (`source compile.sh`), run `compile <file.b>`,
# and then test the result `./a.out`.

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
