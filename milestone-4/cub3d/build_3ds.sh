#!/usr/bin/env bash
set -e

# This script builds cub3d for the 3DS using devkitARM and libctru.
# It should be run inside a 'nix develop .#threeDS' shell.

if [ -z "$DEVKITARM" ]; then
	echo "Error: DEVKITARM is not set. Run this inside 'nix develop .#threeDS'"
	exit 1
fi

CC=$DEVKITARM/bin/arm-none-eabi-gcc
STRIP=$DEVKITARM/bin/arm-none-eabi-strip
TOOL3DS=$DEVKITPRO/tools/bin/3dsxtool

INCLUDES="-Iincludes -I../../milestone-0/libft/includes -I../../milestone-1/ft_printf/includes -I../../milestone-1/get_next_line/includes -I../../central/minilibx -I3ds -I$DEVKITPRO/libctru/include -I$DEVKITARM/arm-none-eabi/include"
FLAGS="-D__3DS__ -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -O2 -Wall -Wno-incompatible-pointer-types"
LIBS="-L$DEVKITPRO/libctru/lib -lctru -lm"
SPECS="-specs=3dsx.specs"

SRCS=$(find src -name "*.c" | grep -v "_b.c" | grep -v "_b2.c")
SRCS="$SRCS 3ds/mlx_3ds.c"

# Dependencies
SRCS="$SRCS $(find ../../milestone-0/libft/src -name "*.c")"
SRCS="$SRCS $(find ../../milestone-1/ft_printf/src -name "*.c")"
SRCS="$SRCS $(find ../../milestone-1/get_next_line/src -name "*.c")"

echo "Compiling cub3d.elf..."
$CC $FLAGS $INCLUDES $SRCS $SPECS $LIBS -o cub3d.elf

echo "Generating SMDH..."
$DEVKITPRO/tools/bin/smdhtool --create "cub3d" "cub3d port" "airone01" icon.png cub3d.smdh

echo "Converting to cub3d.3dsx..."
$TOOL3DS cub3d.elf cub3d.3dsx --romfs=romfs --smdh=cub3d.smdh

echo "Success! cub3d.3dsx created."
