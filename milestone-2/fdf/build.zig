const std = @import("std");
const helpers = @import("../../build_helpers.zig");

const src_dir = "milestone-2/fdf/src";
const inc_dir = "milestone-2/fdf/includes";

// Omit -Wpedantic: mlx.h uses K&R-style function declarations
const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror" };

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: struct {
        libft: *std.Build.Step.Compile,
        ft_printf: *std.Build.Step.Compile,
        gnl: *std.Build.Step.Compile,
        minilibx: *std.Build.Step.Compile,
    },
) *std.Build.Step.Compile {
    const exe = b.addExecutable(.{
        .name = "fdf",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    exe.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = helpers.collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(inc_dir));
    exe.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    exe.root_module.addIncludePath(b.path("milestone-1/ft_printf/includes"));
    exe.root_module.addIncludePath(b.path("milestone-1/get_next_line/includes"));
    exe.root_module.addIncludePath(b.path("central/minilibx"));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.ft_printf);
    exe.root_module.linkLibrary(deps.gnl);
    exe.root_module.linkLibrary(deps.minilibx);
    exe.root_module.linkSystemLibrary("m", .{});
    exe.root_module.linkSystemLibrary("X11", .{});
    exe.root_module.linkSystemLibrary("Xext", .{});
    return exe;
}
