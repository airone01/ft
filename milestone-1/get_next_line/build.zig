const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-1/get_next_line/src");
    const prefix = if (is_root) "milestone-1/get_next_line" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const lib = b.addLibrary(.{
        .name = "gnl",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
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
    lib.root_module.addIncludePath(b.path(inc_dir));
    lib.root_module.addIncludePath(b.path(libft_inc));
    return lib;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = configure(b, target, optimize);
    b.installArtifact(lib);
}
