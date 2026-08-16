const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra" };

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn addBinary(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    name: []const u8,
    impl_file: []const u8,
) void {
    const is_root = dirExists(b, "piscine-c/rush00");
    const dir = if (is_root) "piscine-c/rush00" else ".";

    const exe = b.addExecutable(.{
        .name = name,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    exe.root_module.addCSourceFiles(.{
        .root = b.path(dir),
        .files = &.{ "main.c", "ft_putchar.c", impl_file },
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(dir));
    b.installArtifact(exe);
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) void {
    addBinary(b, target, optimize, "rush00-ex00", "rush00.c");
    addBinary(b, target, optimize, "rush00-ex02", "rush02.c");
    addBinary(b, target, optimize, "rush00-ex03", "rush03.c");
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    configure(b, target, optimize);
}
