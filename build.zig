const std = @import("std");

const minilibx_mod = @import("central/minilibx/build.zig");
const libft_mod = @import("milestone-0/libft/build.zig");
const ft_printf_mod = @import("milestone-1/ft_printf/build.zig");
const gnl_mod = @import("milestone-1/get_next_line/build.zig");
const fdf_mod = @import("milestone-2/fdf/build.zig");
const pipex_mod = @import("milestone-2/pipex/build.zig");
const push_swap_mod = @import("milestone-2/push_swap/build.zig");
const minishell_mod = @import("milestone-3/minishell/build.zig");
const philosophers_mod = @import("milestone-3/philosophers/build.zig");
const cub3d_mod = @import("milestone-4/cub3d/build.zig");
const cpp00_mod = @import("milestone-4/cpp00/build.zig");
const cpp01_mod = @import("milestone-4/cpp01/build.zig");
const cpp02_mod = @import("milestone-4/cpp02/build.zig");
const cpp03_mod = @import("milestone-4/cpp03/build.zig");
const cpp04_mod = @import("milestone-4/cpp04/build.zig");
const cpp05_mod = @import("milestone-5/cpp05/build.zig");
const cpp06_mod = @import("milestone-5/cpp06/build.zig");
const cpp07_mod = @import("milestone-5/cpp07/build.zig");
const cpp08_mod = @import("milestone-5/cpp08/build.zig");
const cpp09_mod = @import("milestone-5/cpp09/build.zig");
const piscine_c_mod = @import("piscine-c/build.zig");
const rush00_mod = @import("piscine-c/rush00/build.zig");
const rush01_mod = @import("piscine-c/rush01/build.zig");
const rush02_mod = @import("piscine-c/rush02/build.zig");
const hotrace_mod = @import("rushes/hotrace/build.zig");
const libunit_mod = @import("rushes/libunit/build.zig");
const libasm_mod = @import("pcc/libasm/build.zig");
const minecraft_viz_mod = @import("tools/push-swap-visualizer-minecraft/build.zig");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Shared libraries
    const mlx = minilibx_mod.configure(b, target, optimize);
    const lft = libft_mod.configure(b, target, optimize);
    b.installArtifact(lft);
    const printf = ft_printf_mod.configure(b, target, optimize, lft);
    b.installArtifact(printf);
    const gnl = gnl_mod.configure(b, target, optimize);
    b.installArtifact(gnl);

    // Milestone 2
    b.installArtifact(fdf_mod.configure(b, target, optimize, .{
        .libft = lft, .ft_printf = printf, .gnl = gnl, .minilibx = mlx,
    }));
    const pipex = pipex_mod.configure(b, target, optimize,
        pipex_mod.Deps{ .libft = lft, .ft_printf = printf, .gnl = gnl });
    b.installArtifact(pipex.mandatory);
    b.installArtifact(pipex.bonus);
    const ps = push_swap_mod.configure(b, target, optimize,
        push_swap_mod.Deps{ .libft = lft, .gnl = gnl });
    b.installArtifact(ps.push_swap);
    b.installArtifact(ps.checker);

    // Milestone 3
    b.installArtifact(minishell_mod.configure(b, target, optimize, .{
        .libft = lft, .ft_printf = printf,
    }));
    b.installArtifact(philosophers_mod.configure(b, target, optimize, .{ .libft = lft }));

    // Milestone 4
    const cub3d = cub3d_mod.configure(b, target, optimize, cub3d_mod.Deps{
        .libft = lft, .ft_printf = printf, .gnl = gnl, .minilibx = mlx,
    });
    b.installArtifact(cub3d.mandatory);
    b.installArtifact(cub3d.bonus);
    cpp00_mod.configure(b, target, optimize);
    cpp01_mod.configure(b, target, optimize);
    cpp02_mod.configure(b, target, optimize);
    cpp03_mod.configure(b, target, optimize);
    cpp04_mod.configure(b, target, optimize);

    // Milestone 5
    cpp05_mod.configure(b, target, optimize);
    cpp06_mod.configure(b, target, optimize);
    cpp07_mod.configure(b, target, optimize);
    cpp08_mod.configure(b, target, optimize);
    cpp09_mod.configure(b, target, optimize);

    // Piscine C
    piscine_c_mod.configure(b, target, optimize);
    rush00_mod.configure(b, target, optimize);
    rush01_mod.configure(b, target, optimize);
    rush02_mod.configure(b, target, optimize);

    // Rushes
    hotrace_mod.configure(b, target, optimize);
    libunit_mod.configure(b, target, optimize, libunit_mod.Deps{ .libft = lft });

    // PCC
    b.installArtifact(libasm_mod.configure(b, target, optimize));

    // External tools
    minecraft_viz_mod.configure(b, target, optimize);
}
