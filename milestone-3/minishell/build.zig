const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
    ft_printf: *std.Build.Step.Compile,
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

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-3/minishell/src");
    const prefix = if (is_root) "milestone-3/minishell" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const printf_prefix = if (is_root) "milestone-1/ft_printf" else "../../milestone-1/ft_printf";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });
    const printf_inc = b.pathJoin(&.{ printf_prefix, "includes" });

    const exe = b.addExecutable(.{
        .name = "minishell",
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
    exe.root_module.addIncludePath(b.path(inc_dir));
    exe.root_module.addIncludePath(b.path(libft_inc));
    exe.root_module.addIncludePath(b.path(printf_inc));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.ft_printf);
    exe.root_module.linkSystemLibrary("readline", .{});
    return exe;
}

fn buildDeps(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) Deps {
    const is_root = dirExists(b, "milestone-0/libft/src");
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const printf_prefix = if (is_root) "milestone-1/ft_printf" else "../../milestone-1/ft_printf";

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
        .files = collectFileNames(b, libft_src, ".c"),
        .flags = c_flags,
    });
    lft.root_module.addIncludePath(b.path(libft_inc));

    const printf_src = b.pathJoin(&.{ printf_prefix, "src" });
    const printf_inc = b.pathJoin(&.{ printf_prefix, "includes" });

    const printf_lib = b.addLibrary(.{
        .name = "ft_printf",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    printf_lib.root_module.addCSourceFiles(.{
        .root = b.path(printf_src),
        .files = collectFileNamesExcluding(b, printf_src, ".c", &.{
            "ft_printf_bonus.c",
            "printf_u_bonus.c",
            "printf_c_bonus.c",
        }),
        .flags = c_flags,
    });
    printf_lib.root_module.addIncludePath(b.path(printf_inc));
    printf_lib.root_module.addIncludePath(b.path(libft_inc));
    printf_lib.root_module.linkLibrary(lft);

    return .{ .libft = lft, .ft_printf = printf_lib };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const deps = buildDeps(b, target, optimize);
    const exe = configure(b, target, optimize, deps);

    b.installArtifact(exe);
}
