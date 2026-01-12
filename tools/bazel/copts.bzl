"""Common compiler options for the entire monorepo."""

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

CXX_COPTS = [
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wpedantic",
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
] + MATH_LINKOPTS
