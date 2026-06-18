const std = @import("std");
const helpers = @import("../tools/build_helpers.zig");

const c_flags: []const []const u8 = &.{ "-Wall", "-Wextra" };
const days = &[_][]const u8{ "c00", "c01", "c02", "c03", "c04", "c05", "c06", "c07", "c08" };

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) void {
    for (days) |day| {
        const day_dir = b.pathJoin(&.{ "piscine-c", day });
        const sources = helpers.collectFilesRecursively(b, day_dir, ".c");
        if (sources.len == 0) continue;

        const lib = b.addLibrary(.{
            .name = b.fmt("piscine-{s}", .{day}),
            .root_module = b.createModule(.{
                .target = target,
                .optimize = optimize,
                .link_libc = true,
            }),
        });
        lib.root_module.addCSourceFiles(.{
            .root = b.path(day_dir),
            .files = sources,
            .flags = c_flags,
        });
        lib.root_module.addIncludePath(b.path(day_dir));
        b.installArtifact(lib);
    }

    // BSQ is not built because I'm lazy
}
