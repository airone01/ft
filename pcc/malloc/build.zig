const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
};

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

fn buildDeps(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) Deps {
    const is_root = dirExists(b, "pcc/malloc/src");

    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const libft_src = b.pathJoin(&.{ libft_prefix, "src" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const libft = b.addLibrary(.{
        .name = "ft",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    libft.root_module.addCSourceFiles(.{
        .root = b.path(libft_src),
        .files = collectFileNames(b, libft_src, ".c"),
        .flags = c_flags,
    });
    libft.root_module.addIncludePath(b.path(libft_inc));

    return .{ .libft = libft };
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) struct { malloc: *std.Build.Step.Compile } {
    const is_root = dirExists(b, "pcc/malloc/src");

    const prefix = if (is_root) "pcc/malloc" else ".";
    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = src_dir;

    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const lib = b.addLibrary(.{
        .name = "ft_malloc",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(inc_dir));
    lib.root_module.addIncludePath(b.path(libft_inc));

    lib.root_module.linkLibrary(deps.libft);

    return .{ .malloc = lib };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const deps: Deps = buildDeps(b, target, optimize);
    const artifacts = configure(b, target, optimize, deps);

    b.installArtifact(artifacts.malloc);
}
