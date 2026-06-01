const std = @import("std");

const src_dir = "pcc/libasm/src";
const asm_sources = &[_][]const u8{
    "ft_strlen.s", "ft_strcpy.s", "ft_strcmp.s",
    "ft_write.s",  "ft_read.s",   "ft_strdup.s",
};

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    if (target.result.cpu.arch != .x86_64 or target.result.os.tag != .linux)
        @panic("libasm only supports x86-64 Linux");

    const lib = b.addLibrary(.{
        .name = "asm",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });

    for (asm_sources) |src| {
        // -w-reloc-rel-dword suppresses a NASM 3.x warning for WRT ..plt calls
        // that was not present in NASM 2.x; the code is correct for both versions.
        const nasm = b.addSystemCommand(&.{ "nasm", "-f", "elf64", "-Wall", "-Werror", "-w-reloc-rel-dword", "-o" });
        const obj_name = b.fmt("{s}.o", .{src[0 .. src.len - 2]});
        const obj = nasm.addOutputFileArg(obj_name);
        nasm.addFileArg(b.path(b.pathJoin(&.{ src_dir, src })));
        lib.root_module.addObjectFile(obj);
    }

    const test_exe = b.addExecutable(.{
        .name = "libasm-test",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    test_exe.root_module.addCSourceFiles(.{
        .root = b.path("pcc/libasm"),
        .files = &.{"test.c"},
        .flags = &.{ "-Wall", "-Wextra" },
    });
    test_exe.root_module.linkLibrary(lib);
    b.installArtifact(test_exe);

    return lib;
}
