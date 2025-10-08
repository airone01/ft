"""Common compiler options for the entire monorepo."""

# Standard C compiler flags
CC_COPTS = [
    "-Wall",
    "-Werror",
    "-Wextra",
    "-Wpedantic",
    "-Wshadow",
    "-Wunused",
    "-Wconversion",
    "-Wsign-conversion",
    "-Wpointer-arith",
    "-Wformat=2",
    "-Wfloat-equal",
    "-Wwrite-strings",
    "-fno-omit-frame-pointer",
    "-O2",
    "-march=native",
    "-ffunction-sections",
    "-fdata-sections",
    "-ffast-math",
    "-g3",
]

# Standard C++ compiler flags (C++98 compatible)
CXX_COPTS = [
    "-Wall",
    "-Wextra",
    "-Werror",
    "-std=c++98",
    "-g3",
]

# Linker flags for projects using math library
MATH_LINKOPTS = ["-lm"]

# Linker flags for projects using readline
READLINE_LINKOPTS = ["-lreadline"]

# Linker flags for projects using MiniLibX
MLX_LINKOPTS = [
    "-lmlx",
    "-lXext",
    "-lX11",
    "-lm",
]
