const std = @import("std");
const helpers = @import("../../build_helpers.zig");

const framework_dir = "rushes/libunit/framework";
const tests_dir = "rushes/libunit/tests";
const real_tests_dir = "rushes/libunit/real_tests";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror" };

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
};

fn buildFramework(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    libft: *std.Build.Step.Compile,
) *std.Build.Step.Compile {
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
        .files = helpers.collectFileNames(b, framework_dir, ".c"),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(framework_dir));
    lib.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    lib.root_module.linkLibrary(libft);
    return lib;
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) void {
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
        .files = helpers.collectFilesRecursively(b, tests_dir, ".c"),
        .flags = c_flags,
    });
    tests_exe.root_module.addIncludePath(b.path(tests_dir));
    tests_exe.root_module.addIncludePath(b.path(framework_dir));
    tests_exe.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
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
        .files = helpers.collectFilesRecursively(b, real_tests_dir, ".c"),
        .flags = c_flags,
    });
    real_exe.root_module.addIncludePath(b.path(real_tests_dir));
    real_exe.root_module.addIncludePath(b.path(framework_dir));
    real_exe.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    real_exe.root_module.linkLibrary(libunit);
    real_exe.root_module.linkLibrary(deps.libft);
    b.installArtifact(real_exe);
}
