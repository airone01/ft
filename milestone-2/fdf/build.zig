const std = @import("std");

// Omit -Wpedantic: mlx.h uses K&R-style function declarations
const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
    ft_printf: *std.Build.Step.Compile,
    gnl: *std.Build.Step.Compile,
    minilibx: *std.Build.Step.Compile,
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
    deps: Deps,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-2/fdf/src");
    const prefix = if (is_root) "milestone-2/fdf" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const printf_prefix = if (is_root) "milestone-1/ft_printf" else "../../milestone-1/ft_printf";
    const gnl_prefix = if (is_root) "milestone-1/get_next_line" else "../../milestone-1/get_next_line";
    const mlx_prefix = if (is_root) "central/minilibx" else "../../central/minilibx";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });
    const printf_inc = b.pathJoin(&.{ printf_prefix, "includes" });
    const gnl_inc = b.pathJoin(&.{ gnl_prefix, "includes" });
    const mlx_dir = mlx_prefix;

    const exe = b.addExecutable(.{
        .name = "fdf",
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
    exe.root_module.addIncludePath(b.path(gnl_inc));
    exe.root_module.addIncludePath(b.path(mlx_dir));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.ft_printf);
    exe.root_module.linkLibrary(deps.gnl);
    exe.root_module.linkLibrary(deps.minilibx);
    exe.root_module.linkSystemLibrary("m", .{});
    exe.root_module.linkSystemLibrary("X11", .{});
    exe.root_module.linkSystemLibrary("Xext", .{});
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
    const gnl_prefix = if (is_root) "milestone-1/get_next_line" else "../../milestone-1/get_next_line";
    const mlx_prefix = if (is_root) "central/minilibx" else "../../central/minilibx";

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

    const mlx_dir = mlx_prefix;
    const mlx = b.addLibrary(.{
        .name = "mlx",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    mlx.root_module.addCSourceFiles(.{
        .root = b.path(mlx_dir),
        .files = collectFileNamesExcluding(b, mlx_dir, ".c", &.{ "mlx_lib_xpm.c", "mlx_ext_randr.c" }),
        .flags = &.{ "-Wall", "-Wextra" },
    });
    mlx.root_module.addIncludePath(b.path(mlx_dir));
    addNixSystemIncludePaths(b, mlx.root_module);

    return .{ .libft = lft, .ft_printf = printf_lib, .gnl = gnl, .minilibx = mlx };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const deps = buildDeps(b, target, optimize);
    const exe = configure(b, target, optimize, deps);

    b.installArtifact(exe);
}
