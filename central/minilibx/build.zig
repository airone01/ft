const std = @import("std");

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn collectFileNamesExcluding(
    b: *std.Build,
    dir_rel: []const u8,
    ext: []const u8,
    excludes: []const []const u8,
) []const []const u8 {
    const io = b.graph.io;
    var dir = b.build_root.handle.openDir(io, dir_rel, .{ .iterate = true }) catch return &.{};
    defer dir.close(io);
    var list: std.ArrayList([]const u8) = .empty;
    var it = dir.iterate();
    outer: while (it.next(io) catch null) |entry| {
        if (entry.kind != .file) continue;
        if (!std.mem.endsWith(u8, entry.name, ext)) continue;
        for (excludes) |ex| {
            if (std.mem.eql(u8, entry.name, ex)) continue :outer;
        }
        list.append(b.allocator, b.dupe(entry.name)) catch @panic("OOM");
    }
    return list.toOwnedSlice(b.allocator) catch @panic("OOM");
}

fn addNixSystemIncludePaths(b: *std.Build, module: *std.Build.Module) void {
    const val = b.graph.environ_map.get("NIX_CFLAGS_COMPILE") orelse return;
    var it = std.mem.tokenizeScalar(u8, val, ' ');
    while (it.next()) |flag| {
        if (std.mem.startsWith(u8, flag, "-I")) {
            module.addSystemIncludePath(.{ .cwd_relative = b.dupe(flag[2..]) });
        } else if (std.mem.eql(u8, flag, "-isystem")) {
            if (it.next()) |path| {
                module.addSystemIncludePath(.{ .cwd_relative = b.dupe(path) });
            }
        }
    }
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "central/minilibx");
    const mlx_dir = if (is_root) "central/minilibx" else ".";

    const lib = b.addLibrary(.{
        .name = "mlx",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(mlx_dir),
        .files = collectFileNamesExcluding(b, mlx_dir, ".c", &.{ "mlx_lib_xpm.c", "mlx_ext_randr.c" }),
        .flags = &.{ "-Wall", "-Wextra" },
    });
    lib.root_module.addIncludePath(b.path(mlx_dir));
    addNixSystemIncludePaths(b, lib.root_module);
    return lib;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = configure(b, target, optimize);
    b.installArtifact(lib);
}
