const std = @import("std");
const helpers = @import("../../build_helpers.zig");

const src_dir = "milestone-1/ft_printf/src";
pub const include_path = "milestone-1/ft_printf/includes";

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra", "-Werror", "-Wpedantic" };

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
        .files = helpers.collectFileNames(b, src_dir, ".c"),
        .flags = c_flags,
    });
    lib.root_module.addIncludePath(b.path(include_path));
    lib.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    lib.root_module.linkLibrary(libft);
    return lib;
}
