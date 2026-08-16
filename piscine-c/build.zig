const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra" };
const days = &[_][]const u8{ "c00", "c01", "c02", "c03", "c04", "c05", "c06", "c07", "c08" };

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn collectFilesRecursively(b: *std.Build, dir_rel: []const u8, ext: []const u8) []const []const u8 {
    var list: std.ArrayList([]const u8) = .empty;
    collectFilesRecursivelyInto(b, dir_rel, "", ext, &list);
    return list.toOwnedSlice(b.allocator) catch @panic("OOM");
}

fn collectFilesRecursivelyInto(
    b: *std.Build,
    root: []const u8,
    sub: []const u8,
    ext: []const u8,
    list: *std.ArrayList([]const u8),
) void {
    const io = b.graph.io;
    const abs = if (sub.len == 0) root else b.pathJoin(&.{ root, sub });
    var dir = b.build_root.handle.openDir(io, abs, .{ .iterate = true }) catch return;
    defer dir.close(io);
    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind == .file) {
            if (!std.mem.endsWith(u8, entry.name, ext)) continue;
            const rel = if (sub.len == 0) b.dupe(entry.name) else b.pathJoin(&.{ sub, entry.name });
            list.append(b.allocator, rel) catch @panic("OOM");
        } else if (entry.kind == .directory) {
            const child = if (sub.len == 0) b.dupe(entry.name) else b.pathJoin(&.{ sub, entry.name });
            collectFilesRecursivelyInto(b, root, child, ext, list);
        }
    }
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) void {
    const is_root = dirExists(b, "piscine-c");
    const prefix = if (is_root) "piscine-c" else ".";

    for (days) |day| {
        const day_dir = b.pathJoin(&.{ prefix, day });
        const sources = collectFilesRecursively(b, day_dir, ".c");
        if (sources.len == 0) continue;

        const lib = b.addLibrary(.{
            .name = b.fmt("piscine-{s}", .{day}),
            .root_module = b.createModule(.{
                .target = target,
                .optimize = optimize,
                .link_libc = true,
            }),
        });
        lib.root_module.addCSourceFiles(.{
            .root = b.path(day_dir),
            .files = sources,
            .flags = c_flags,
        });
        lib.root_module.addIncludePath(b.path(day_dir));
        b.installArtifact(lib);
    }
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    configure(b, target, optimize);
}
