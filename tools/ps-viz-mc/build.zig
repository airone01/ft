const std = @import("std");

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

pub fn configure(
    b: *std.Build,
    _: std.Build.ResolvedTarget,
    _: std.builtin.OptimizeMode,
) void {
    const is_root = dirExists(b, "tools/ps-viz-mc");
    const prefix = if (is_root) "tools/ps-viz-mc" else ".";
    const manifest = b.pathJoin(&.{ prefix, "Cargo.toml" });
    const binary = if (is_root) "target/release/mcps" else "target/release/mcps";

    const cargo_build = b.addSystemCommand(&.{
        "cargo", "build", "--release", "--manifest-path", b.pathFromRoot(manifest),
    });
    const generated = b.allocator.create(std.Build.GeneratedFile) catch @panic("OOM");
    generated.* = .{ .step = &cargo_build.step, .path = b.pathFromRoot(binary) };
    const install_bin = b.addInstallBinFile(.{ .generated = .{ .file = generated } }, "mcps");
    b.getInstallStep().dependOn(&install_bin.step);
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    configure(b, target, optimize);
}
