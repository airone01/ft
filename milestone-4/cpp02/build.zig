const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

pub fn configure(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) void {
    helpers.buildCppModule(b, target, optimize, "milestone-4/cpp02", "cpp02");
}
