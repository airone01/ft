const std = @import("std");

const src_dir = "pcc/libasm/src";
const asm_sources = &[_][]const u8{ "ft_strlen.s", "ft_strcpy.s", "ft_strcmp.s", "ft_write.s", "ft_read.s", "ft_strdup.s", "ft_atoi_base_bonus.s", "ft_list_push_front_bonus.s", "ft_list_remove_if_bonus.s", "ft_list_size_bonus.s", "ft_list_sort_bonus.s" };

fn nasmAtLeast3(b: *std.Build) bool {
    const result = std.process.run(b.allocator, b.graph.io, .{
        .argv = &.{ "nasm", "--version" },
    }) catch return false;
    defer b.allocator.free(result.stdout);
    defer b.allocator.free(result.stderr);
    // output is e.g. "NASM version 3.0.0" or "NASM version 2.16.01"
    return std.mem.indexOf(u8, result.stdout, "NASM version 3.") != null or
        std.mem.indexOf(u8, result.stdout, "NASM version 4.") != null;
}

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

    const suppress_plt_warn = nasmAtLeast3(b);

    for (asm_sources) |src| {
        var argv: std.ArrayList([]const u8) = .empty;
        argv.appendSlice(b.allocator, &.{ "nasm", "-f", "elf64", "-Wall", "-Werror" }) catch @panic("OOM");
        // -w-reloc-rel-dword suppresses a nasm 3.x warning for WRT ..plt calls;
        // the flag doesn't exist in nasm 2.x so only pass it when nasm >= 3.
        if (suppress_plt_warn)
            argv.append(b.allocator, "-w-reloc-rel-dword") catch @panic("OOM");
        argv.append(b.allocator, "-o") catch @panic("OOM");
        const nasm = b.addSystemCommand(argv.items);
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
