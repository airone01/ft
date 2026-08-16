const std = @import("std");
const helpers = @import("../../tools/build_helpers.zig");

pub fn configure(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) void {
    helpers.buildCppModule(b, target, optimize, "milestone-4/cpp00", "cpp00");
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    configure(b, target, optimize);
}
