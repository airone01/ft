const std = @import("std");
const helpers = @import("../../build_helpers.zig");

const mlx_dir = "central/minilibx";
pub const include_path = mlx_dir;

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const lib = b.addLibrary(.{
        .name = "mlx",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    lib.root_module.addCSourceFiles(.{
        .root = b.path(mlx_dir),
        .files = helpers.collectFileNamesExcluding(b, mlx_dir, ".c", &.{ "mlx_lib_xpm.c", "mlx_ext_randr.c" }),
        .flags = &.{ "-Wall", "-Wextra" },
    });
    lib.root_module.addIncludePath(b.path(mlx_dir));
    lib.root_module.linkSystemLibrary("X11", .{});
    lib.root_module.linkSystemLibrary("Xext", .{});
    return lib;
}
