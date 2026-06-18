const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

const src_dir = "milestone-4/cub3d/src";
const inc_dir = "milestone-4/cub3d/includes";

// K&R casts in mlx hooks require suppressing strict function pointer warnings
const c_flags: []const []const u8 = &.{
    "-Wall",                                    "-Wextra",                        "-Werror",
    "-Wno-incompatible-function-pointer-types", "-Wno-cast-function-type-strict", "-Wno-cast-function-type",
};

pub const Deps = struct {
    libft: *std.Build.Step.Compile,
    ft_printf: *std.Build.Step.Compile,
    gnl: *std.Build.Step.Compile,
    minilibx: *std.Build.Step.Compile,
};

fn addBinary(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    name: []const u8,
    exclude_suffixes: []const []const u8,
    deps: Deps,
) *std.Build.Step.Compile {
    const exe = b.addExecutable(.{
        .name = name,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    exe.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = helpers.collectFileNamesExcludingEndsWith(b, src_dir, exclude_suffixes),
        .flags = c_flags,
    });
    exe.root_module.addIncludePath(b.path(inc_dir));
    exe.root_module.addIncludePath(b.path("milestone-0/libft/includes"));
    exe.root_module.addIncludePath(b.path("milestone-1/ft_printf/includes"));
    exe.root_module.addIncludePath(b.path("milestone-1/get_next_line/includes"));
    exe.root_module.addIncludePath(b.path("central/minilibx"));
    exe.root_module.linkLibrary(deps.libft);
    exe.root_module.linkLibrary(deps.ft_printf);
    exe.root_module.linkLibrary(deps.gnl);
    exe.root_module.linkLibrary(deps.minilibx);
    exe.root_module.linkSystemLibrary("m", .{});
    exe.root_module.linkSystemLibrary("X11", .{});
    exe.root_module.linkSystemLibrary("Xext", .{});
    return exe;
}

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    deps: Deps,
) struct { mandatory: *std.Build.Step.Compile, bonus: *std.Build.Step.Compile } {
    const mandatory = addBinary(b, target, optimize, "cub3d", &.{ "_b.c", "_b2.c" }, deps);
    const bonus = addBinary(b, target, optimize, "cub3d_bonus", &.{ "_m.c", "_m2.c" }, deps);
    return .{ .mandatory = mandatory, .bonus = bonus };
}
