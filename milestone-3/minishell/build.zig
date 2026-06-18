const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

const src_dir = "milestone-3/minishell/src";
const inc_dir = "milestone-3/minishell/includes";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: struct {
        libft: *std.Build.Step.Compile,
        ft_printf: *std.Build.Step.Compile,
    },
) *std.Build.Step.Compile {
    const exe = b.addExecutable(.{
        .name = "minishell",
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
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.ft_printf);
    exe.root_module.linkSystemLibrary("readline", .{});
    return exe;
}
