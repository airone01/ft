const std = @import("std");

const c_flags: []const []const u8 = &.{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-DFT_BONUS=1",
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

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const rel_prefix = if (dirExists(b, "pcc/nm/src")) "pcc/nm" else ".";
    const src_dir = b.pathJoin(&.{ rel_prefix, "src" });

    const exe = b.addExecutable(.{
        .name = "ft_nm",
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
    exe.root_module.linkSystemLibrary("c", .{});
    return exe;
}

pub fn addTests(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    test_step: *std.Build.Step,
    nm_exe: *std.Build.Step.Compile,
) void {
    const rel_prefix = if (dirExists(b, "pcc/nm/src")) "pcc/nm" else ".";
    const runner_file = b.pathJoin(&.{ rel_prefix, "tests", "runner.zig" });
    const fixtures_dir = b.pathJoin(&.{ rel_prefix, "tests", "fixtures" });

    const symbols_obj = b.addObject(.{
        .name = "symbols",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    symbols_obj.root_module.addCSourceFiles(.{
        .root = b.path(fixtures_dir),
        .files = &.{"symbols.c"},
        .flags = c_flags,
    });

    const empty_obj = b.addObject(.{
        .name = "empty",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    empty_obj.root_module.addCSourceFiles(.{
        .root = b.path(fixtures_dir),
        .files = &.{"empty.c"},
        .flags = c_flags,
    });

    const sections_obj = b.addObject(.{
        .name = "multiple_sections",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    sections_obj.root_module.addCSourceFiles(.{
        .root = b.path(fixtures_dir),
        .files = &.{"multiple_sections.c"},
        .flags = c_flags,
    });

    const test_exe = b.addExecutable(.{
        .name = "nm_tests",
        .root_module = b.createModule(.{
            .root_source_file = b.path(runner_file),
            .target = target,
            .optimize = optimize,
        }),
    });

    const run_tests = b.addRunArtifact(test_exe);
    run_tests.addArtifactArg(nm_exe);
    run_tests.addArtifactArg(symbols_obj);
    run_tests.addArtifactArg(empty_obj);
    run_tests.addArtifactArg(sections_obj);

    test_step.dependOn(&run_tests.step);
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = configure(b, target, optimize);
    b.installArtifact(exe);

    const test_step = b.step("test", "Run nm comparison tests");
    addTests(b, target, optimize, test_step, exe);
}
