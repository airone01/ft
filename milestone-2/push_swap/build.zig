const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

const src_dir = "milestone-2/push_swap/src";
const inc_dir = "milestone-2/push_swap/includes";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
    gnl: *std.Build.Step.Compile,
};

fn addBinary(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    name: []const u8,
    excludes: []const []const u8,
    deps: Deps,
) *std.Build.Step.Compile {
    const exe = b.addExecutable(.{
        .name = name,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    exe.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = helpers.collectFileNamesExcluding(b, src_dir, ".c", excludes),
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(inc_dir));
    exe.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    exe.root_module.addIncludePath(b.path("milestone-1/get_next_line/includes"));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.gnl);
    return exe;
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) struct { push_swap: *std.Build.Step.Compile, checker: *std.Build.Step.Compile } {
    const push_swap = addBinary(b, target, optimize, "push_swap", &.{"checker.c"}, deps);
    const checker = addBinary(b, target, optimize, "push_swap_checker", &.{"_main.c"}, deps);
    return .{ .push_swap = push_swap, .checker = checker };
}
