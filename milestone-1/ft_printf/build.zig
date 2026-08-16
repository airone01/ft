const std = @import("std");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

const bonus_files: []const []const u8 = &.{
    "ft_printf_bonus.c",
    "printf_u_bonus.c",
    "printf_c_bonus.c",
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

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    libft: *std.Build.Step.Compile,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-1/ft_printf/src");
    const prefix = if (is_root) "milestone-1/ft_printf" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });

    const lib = b.addLibrary(.{
        .name = "ft_printf",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNamesExcluding(b, src_dir, ".c", bonus_files),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(inc_dir));
    lib.root_module.addIncludePath(b.path(libft_inc));
    lib.root_module.linkLibrary(libft);
    return lib;
}

pub fn addTests(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    test_step: *std.Build.Step,
    libft: *std.Build.Step.Compile,
) void {
    const is_root = dirExists(b, "milestone-1/ft_printf/src");
    const prefix = if (is_root) "milestone-1/ft_printf" else ".";
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";

    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const inc_dir = b.pathJoin(&.{ prefix, "includes" });
    const libft_inc = b.pathJoin(&.{ libft_prefix, "includes" });
    const test_file = b.pathJoin(&.{ prefix, "test.zig" });

    const bonus_lib = b.addLibrary(.{
        .name = "ft_printf_bonus_test",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    bonus_lib.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNamesExcluding(b, src_dir, ".c", &.{"ft_printf.c"}),
        .flags = c_flags,
    });
    bonus_lib.root_module.addIncludePath(b.path(inc_dir));
    bonus_lib.root_module.addIncludePath(b.path(libft_inc));
    bonus_lib.root_module.linkLibrary(libft);

    const test_mod = b.createModule(.{
        .root_source_file = b.path(test_file),
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    test_mod.addIncludePath(b.path(inc_dir));
    test_mod.addIncludePath(b.path(libft_inc));
    test_mod.linkLibrary(bonus_lib);

    const tests = b.addTest(.{ .root_module = test_mod });

    test_step.dependOn(&b.addRunArtifact(tests).step);
}

fn getLibft(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "milestone-0/libft/src");
    const libft_prefix = if (is_root) "milestone-0/libft" else "../../milestone-0/libft";
    const src_dir = b.pathJoin(&.{ libft_prefix, "src" });
    const inc_dir = b.pathJoin(&.{ libft_prefix, "includes" });

    const lib = b.addLibrary(.{
        .name = "ft",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = collectFileNamesExcluding(b, src_dir, ".c", &.{}),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(inc_dir));
    return lib;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const libft = getLibft(b, target, optimize);
    const printf_lib = configure(b, target, optimize, libft);
    b.installArtifact(printf_lib);

    const test_step = b.step("test", "Run ft_printf tests");
    addTests(b, target, optimize, test_step, libft);
}
