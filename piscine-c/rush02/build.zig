const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn collectFileNames(b: *std.Build, dir_rel: []const u8, ext: []const u8) []const []const u8 {
    const io = b.graph.io;
    var dir = b.build_root.handle.openDir(io, dir_rel, .{ .iterate = true }) catch return &.{};
    defer dir.close(io);
    var list: std.ArrayList([]const u8) = .empty;
    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind != .file) continue;
        if (!std.mem.endsWith(u8, entry.name, ext)) continue;
        list.append(b.allocator, b.dupe(entry.name)) catch @panic("OOM");
    }
    return list.toOwnedSlice(b.allocator) catch @panic("OOM");
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    lft: *std.Build.Step.Compile,
) void {
    const is_root = dirExists(b, "piscine-c/rush02");
    const prefix = if (is_root) "piscine-c/rush02" else ".";
    const src_dir = b.pathJoin(&.{ prefix, "ex00" });

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
        .files = collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(src_dir));
    exe.root_module.linkLibrary(lft);
    b.installArtifact(exe);
}

fn buildLibft(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-0/libft/src");
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const src_dir = b.pathJoin(&.{ libft_prefix, "src" });
    const inc_dir = b.pathJoin(&.{ libft_prefix, "includes" });

    const lft = b.addLibrary(.{
        .name = "ft",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lft.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    lft.root_module.addIncludePath(b.path(inc_dir));
    return lft;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lft = buildLibft(b, target, optimize);
    configure(b, target, optimize, lft);
}
