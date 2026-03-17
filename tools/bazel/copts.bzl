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

MATH_LINKOPTS  = select({
    "//:on_nix": [],
    "//conditions:default": ["-lm"]
})
READLINE_LINKOPTS = select({
    "//:on_nix": [],
    "//conditions:default": ["-lreadline"]
})
MLX_LINKOPTS = select({
    "//:on_nix": [],
    "//conditions:default": [
        "-lmlx",
        "-lXext",
        "-lX11",
        "-lXpm",
    ],
}) + MATH_LINKOPTS

