const std = @import("std");

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

fn collectFileNames(b: *std.Build, dir_rel: []const u8, ext: []const u8) []const []const u8 {
    const io = b.graph.io;
    var dir = b.build_root.handle.openDir(io, dir_rel, .{ .iterate = true }) catch return &.{};
    defer dir.close(io);
    var list: std.ArrayList([]const u8) = .empty;
    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind != .file) continue;
        if (!std.mem.endsWith(u8, entry.name, ext)) continue;
        list.append(b.allocator, b.dupe(entry.name)) catch @panic("OOM");
    }
    return list.toOwnedSlice(b.allocator) catch @panic("OOM");
}

const cpp_flags: []const []const u8 = &.{
    "-Wall", "-Wextra", "-Werror", "-std=c++98",
};

pub fn configure(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) void {
    const is_root = dirExists(b, "milestone-5/cpp05");
    const module_dir = if (is_root) "milestone-5/cpp05" else ".";
    const module_name = "cpp05";

    const io = b.graph.io;
    var dir = b.build_root.handle.openDir(io, module_dir, .{ .iterate = true }) catch return;
    defer dir.close(io);
    var it = dir.iterate();
    while (it.next(io) catch null) |entry| {
        if (entry.kind != .directory) continue;
        if (!std.mem.startsWith(u8, entry.name, "ex")) continue;
        const ex_name = b.dupe(entry.name);
        const ex_dir = b.pathJoin(&.{ module_dir, ex_name });

        const src_subdir = b.pathJoin(&.{ ex_dir, "src" });
        const src_dir = if (dirExists(b, src_subdir)) src_subdir else ex_dir;

        const sources = collectFileNames(b, src_dir, ".cpp");
        if (sources.len == 0) continue;

        const exe = b.addExecutable(.{
            .name = b.fmt("{s}-{s}", .{ module_name, ex_name }),
            .root_module = b.createModule(.{
                .target = target,
                .optimize = optimize,
                .link_libcpp = true,
            }),
        });
        exe.root_module.addCSourceFiles(.{
            .root = b.path(src_dir),
            .files = sources,
            .flags = cpp_flags,
        });
        exe.root_module.addIncludePath(b.path(ex_dir));
        const inc_dir = b.pathJoin(&.{ ex_dir, "includes" });
        if (dirExists(b, inc_dir)) {
            exe.root_module.addIncludePath(b.path(inc_dir));
        }
        b.installArtifact(exe);
    }
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    configure(b, target, optimize);
}
