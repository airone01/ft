const std = @import("std");

const src_dir = "milestone-1/get_next_line/src";
pub const include_path = "milestone-1/get_next_line/includes";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const lib = b.addLibrary(.{
        .name = "gnl",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    // main.c is a test file; excluded
    lib.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = &.{
            "get_next_line.c",
            "get_next_line_utils.c",
            "files_utils.c",
            "files_utils2.c",
        },
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(include_path));
    lib.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    return lib;
}
