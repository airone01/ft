const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror" };

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

fn buildFramework(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    libft: *std.Build.Step.Compile,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "rushes/libunit/framework");
    const prefix = if (is_root) "rushes/libunit" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

    const framework_dir = b.pathJoin(&.{ prefix, "framework" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const lib = b.addLibrary(.{
        .name = "unit",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(framework_dir),
        .files = collectFileNames(b, framework_dir, ".c"),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(framework_dir));
    lib.root_module.addIncludePath(b.path(libft_inc));
    lib.root_module.linkLibrary(libft);
    return lib;
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) void {
    const is_root = dirExists(b, "rushes/libunit/framework");
    const prefix = if (is_root) "rushes/libunit" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

    const framework_dir = b.pathJoin(&.{ prefix, "framework" });
    const tests_dir = b.pathJoin(&.{ prefix, "tests" });
    const real_tests_dir = b.pathJoin(&.{ prefix, "real_tests" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const libunit = buildFramework(b, target, optimize, deps.libft);

    // Self-tests: tests the libunit framework itself
    const tests_exe = b.addExecutable(.{
        .name = "libunit-tests",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    tests_exe.root_module.addCSourceFiles(.{
        .root = b.path(tests_dir),
        .files = collectFilesRecursively(b, tests_dir, ".c"),
        .flags = c_flags,
    });
    tests_exe.root_module.addIncludePath(b.path(tests_dir));
    tests_exe.root_module.addIncludePath(b.path(framework_dir));
    tests_exe.root_module.addIncludePath(b.path(libft_inc));
    tests_exe.root_module.linkLibrary(libunit);
    tests_exe.root_module.linkLibrary(deps.libft);
    b.installArtifact(tests_exe);

    // Integration tests: tests libft functions using libunit
    const real_exe = b.addExecutable(.{
        .name = "libunit-real-tests",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    real_exe.root_module.addCSourceFiles(.{
        .root = b.path(real_tests_dir),
        .files = collectFilesRecursively(b, real_tests_dir, ".c"),
        .flags = c_flags,
    });
    real_exe.root_module.addIncludePath(b.path(real_tests_dir));
    real_exe.root_module.addIncludePath(b.path(framework_dir));
    real_exe.root_module.addIncludePath(b.path(libft_inc));
    real_exe.root_module.linkLibrary(libunit);
    real_exe.root_module.linkLibrary(deps.libft);
    b.installArtifact(real_exe);
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
    configure(b, target, optimize, .{ .libft = lft });
}
