const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

const src_dir = "piscine-c/rush02/ex00";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    lft: *std.Build.Step.Compile,
) void {
    const exe = b.addExecutable(.{
        .name = "rush02",
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
    exe.root_module.addIncludePath(b.path(src_dir));
    exe.root_module.linkLibrary(lft);
    b.installArtifact(exe);
}
