const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
    gnl: *std.Build.Step.Compile,
};

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

fn addBinary(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    name: []const u8,
    excludes: []const []const u8,
    deps: Deps,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-2/push_swap/src");
    const prefix = if (is_root) "milestone-2/push_swap" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const gnl_prefix = if (is_root) "milestone-1/get_next_line" else "../../milestone-1/get_next_line";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });
    const gnl_inc = b.pathJoin(&.{ gnl_prefix, "includes" });

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
        .files = collectFileNamesExcluding(b, src_dir, ".c", excludes),
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(inc_dir));
    exe.root_module.addIncludePath(b.path(libft_inc));
    exe.root_module.addIncludePath(b.path(gnl_inc));
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

fn buildDeps(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) Deps {
    const is_root = dirExists(b, "milestone-0/libft/src");
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const gnl_prefix = if (is_root) "milestone-1/get_next_line" else "../../milestone-1/get_next_line";

    const libft_src = b.pathJoin(&.{ libft_prefix, "src" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const lft = b.addLibrary(.{
        .name = "ft",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lft.root_module.addCSourceFiles(.{
        .root = b.path(libft_src),
        .files = collectFileNamesExcluding(b, libft_src, ".c", &.{}),
        .flags = c_flags,
    });
    lft.root_module.addIncludePath(b.path(libft_inc));

    const gnl_src = b.pathJoin(&.{ gnl_prefix, "src" });
    const gnl_inc = b.pathJoin(&.{ gnl_prefix, "includes" });

    const gnl = b.addLibrary(.{
        .name = "gnl",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    gnl.root_module.addCSourceFiles(.{
        .root = b.path(gnl_src),
        .files = &.{
            "get_next_line.c",
            "get_next_line_utils.c",
            "files_utils.c",
            "files_utils2.c",
        },
        .flags = c_flags,
    });
    gnl.root_module.addIncludePath(b.path(gnl_inc));
    gnl.root_module.addIncludePath(b.path(libft_inc));

    return .{ .libft = lft, .gnl = gnl };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const deps = buildDeps(b, target, optimize);
    const artifacts = configure(b, target, optimize, deps);

    b.installArtifact(artifacts.push_swap);
    b.installArtifact(artifacts.checker);
}
