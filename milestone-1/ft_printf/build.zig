const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

const src_dir = "milestone-1/ft_printf/src";
const test_file = "milestone-1/ft_printf/test.zig";
pub const include_path = "milestone-1/ft_printf/includes";
const libft_include = "milestone-0/libft/includes";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

// Bonus source files that must not be compiled into the mandatory library.
const bonus_files: []const []const u8 = &.{
    "ft_printf_bonus.c",
    "printf_u_bonus.c",
    "printf_c_bonus.c",
};

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    libft: *std.Build.Step.Compile,
) *std.Build.Step.Compile {
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
        .files = helpers.collectFileNamesExcluding(b, src_dir, ".c", bonus_files),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(include_path));
    lib.root_module.addIncludePath(b.path(libft_include));
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
    // Build a bonus-enabled library (all sources except the mandatory entry point).
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
        .files = helpers.collectFileNamesExcluding(b, src_dir, ".c", &.{"ft_printf.c"}),
        .flags = c_flags,
    });
    bonus_lib.root_module.addIncludePath(b.path(include_path));
    bonus_lib.root_module.addIncludePath(b.path(libft_include));
    bonus_lib.root_module.linkLibrary(libft);

    const test_mod = b.createModule(.{
        .root_source_file = b.path(test_file),
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    test_mod.addIncludePath(b.path(include_path));
    test_mod.addIncludePath(b.path(libft_include));
    test_mod.linkLibrary(bonus_lib);

    const tests = b.addTest(.{ .root_module = test_mod });

    test_step.dependOn(&b.addRunArtifact(tests).step);
}
