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
    const install_bin = b.addInstallBinFile(b.path(binary), "mcps");
    install_bin.step.dependOn(&cargo_build.step);
    b.getInstallStep().dependOn(&install_bin.step);
}
