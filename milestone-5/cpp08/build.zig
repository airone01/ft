const std = @import("std");
const helpers = @import("../../build_helpers.zig");

pub fn configure(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) void {
    helpers.buildCppModule(b, target, optimize, "milestone-5/cpp08", "cpp08");
}
