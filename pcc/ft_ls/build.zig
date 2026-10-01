const std = @import("std");

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
};

const base_c_flags: []const []const u8 = &.{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-DFT_BONUS=1",
};

const release_c_flags: []const []const u8 = &.{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-DFT_BONUS=1",
    "-O3",
    "-DNDEBUG",
    "-fno-plt",
};

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn collectFileNamesRec(b: *std.Build, base_dir: []const u8, sub_dir: []const u8, ext: []const u8, list: *std.ArrayList([]const u8)) void {
    const io = b.graph.io;
    const current_rel = if (sub_dir.len == 0) base_dir else b.pathJoin(&.{ base_dir, sub_dir });
    var dir = b.build_root.handle.openDir(io, current_rel, .{ .iterate = true }) catch return;
    defer dir.close(io);

    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind == .directory) {
            if (std.mem.startsWith(u8, entry.name, ".")) continue;
            const child_sub = if (sub_dir.len == 0) b.dupe(entry.name) else b.pathJoin(&.{ sub_dir, entry.name });
            collectFileNamesRec(b, base_dir, child_sub, ext, list);
        } else if (entry.kind == .file) {
            if (std.mem.endsWith(u8, entry.name, ext)) {
                const rel_file = if (sub_dir.len == 0) b.dupe(entry.name) else b.pathJoin(&.{ sub_dir, entry.name });
                list.append(b.allocator, rel_file) catch @panic("OOM");
            }
        }
    }
}

fn collectFileNames(b: *std.Build, dir_rel: []const u8, ext: []const u8) []const []const u8 {
    var list: std.ArrayList([]const u8) = .empty;
    collectFileNamesRec(b, dir_rel, "", ext, &list);
    return list.toOwnedSlice(b.allocator) catch @panic("OOM");
}

fn addIncludePathsRec(b: *std.Build, module: *std.Build.Module, base_dir: []const u8, sub_dir: []const u8) void {
    const io = b.graph.io;
    const current_rel = if (sub_dir.len == 0) base_dir else b.pathJoin(&.{ base_dir, sub_dir });
    module.addIncludePath(b.path(current_rel));

    var dir = b.build_root.handle.openDir(io, current_rel, .{ .iterate = true }) catch return;
    defer dir.close(io);

    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind == .directory) {
            if (std.mem.startsWith(u8, entry.name, ".")) continue;
            const child_sub = if (sub_dir.len == 0) b.dupe(entry.name) else b.pathJoin(&.{ sub_dir, entry.name });
            addIncludePathsRec(b, module, base_dir, child_sub);
        }
    }
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "pcc/ft_ls/src");
    const rel_prefix = if (is_root) "pcc/ft_ls" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const src_dir = b.pathJoin(&.{ rel_prefix, "src" });

    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const c_flags = switch (optimize) {
        .Debug => base_c_flags,
        else => release_c_flags,
    };

    const exe = b.addExecutable(.{
        .name = "ft_ls",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .strip = (optimize != .Debug),
        }),
    });
    exe.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    addIncludePathsRec(b, exe.root_module, src_dir, "");
    exe.root_module.addIncludePath(b.path(libft_inc));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkSystemLibrary("c", .{});
    return exe;
}

fn buildDeps(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) Deps {
    const is_root = dirExists(b, "pcc/ft_ls/src");
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

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
        .flags = release_c_flags,
    });
    lft.root_module.addIncludePath(b.path(libft_inc));

    return .{ .libft = lft };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const deps = buildDeps(b, target, optimize);
    const exe = configure(b, target, optimize, deps);
    b.installArtifact(exe);
}
