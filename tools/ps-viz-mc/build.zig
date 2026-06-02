const std = @import("std");

const manifest = "tools/ps-viz-mc/Cargo.toml";
// Cargo places the binary at the workspace root target/, not the package's target/
const binary = "target/release/mcps";

pub fn configure(
    b: *std.Build,
    _: std.Build.ResolvedTarget,
    _: std.builtin.OptimizeMode,
) void {
    const cargo_build = b.addSystemCommand(&.{
        "cargo", "build", "--release", "--manifest-path", b.pathFromRoot(manifest),
    });
    // Declare the output as a GeneratedFile so Zig waits for cargo before
    // trying to access the binary (b.path() is for source files only).
    const generated = b.allocator.create(std.Build.GeneratedFile) catch @panic("OOM");
    generated.* = .{ .step = &cargo_build.step, .path = b.pathFromRoot(binary) };
    const install_bin = b.addInstallBinFile(.{ .generated = .{ .file = generated } }, "mcps");
    b.getInstallStep().dependOn(&install_bin.step);
}
