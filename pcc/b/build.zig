const std = @import("std");

fn dirExists(b: *std.Build, rel_path: []const u8) bool {
    const io = b.graph.io;
    var d = b.build_root.handle.openDir(io, rel_path, .{}) catch return false;
    d.close(io);
    return true;
}

const libb_sources = [_][]const u8{
    "char",
    "chdir",
    "chmod",
    "chown",
    "close",
    "creat",
    "ctime",
    "execl",
    "execv",
    "exit",
    "fork",
    "fstat",
    "getchar",
    "getuid",
    "lchar",
    "link",
    "mkdir",
    "open",
    "printf",
    "printn",
    "putchar",
    "read",
    "seek",
    "setuid",
    "stat",
    "time",
    "unlink",
    "wait",
    "write",
};

pub fn configure(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const is_root = dirExists(b, "pcc/b/src");
    const prefix = if (is_root) "pcc/b" else ".";
    const src_dir = b.pathJoin(&.{ prefix, "src" });
    const libb_dir = b.pathJoin(&.{ prefix, "libb" });

    // Step 1: Run yacc on parser.y to generate y.tab.c and y.tab.h
    const yacc_cmd = b.addSystemCommand(&.{ "yacc", "-d" });
    yacc_cmd.addFileArg(b.path(b.pathJoin(&.{ src_dir, "parser.y" })));
    yacc_cmd.addArg("-o");
    const y_tab_c = yacc_cmd.addOutputFileArg("y.tab.c");

    // Step 2: Run flex on lexer.l to generate lex.yy.c
    const flex_cmd = b.addSystemCommand(&.{ "flex", "-o" });
    const lex_yy_c = flex_cmd.addOutputFileArg("lex.yy.c");
    flex_cmd.addFileArg(b.path(b.pathJoin(&.{ src_dir, "lexer.l" })));
    flex_cmd.step.dependOn(&yacc_cmd.step);

    // Step 3: Build the B compiler executable
    const b_exe = b.addExecutable(.{
        .name = "B",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    b_exe.root_module.addCSourceFiles(.{
        .root = b.path(src_dir),
        .files = &.{
            "asm.c",
            "c2.c",
            "c2_1.c",
            "c2_2.c",
            "main.c",
            "symtab.c",
        },
        .flags = &.{ "-Wall", "-Wextra", "-Werror", "-Wno-array-parameter", "-g3", "-DFT_B_OPTI" },
    });
    b_exe.root_module.addCSourceFile(.{
        .file = y_tab_c,
        .flags = &.{ "-Wall", "-Wextra", "-g3", "-DFT_B_OPTI" },
    });
    b_exe.root_module.addCSourceFile(.{
        .file = lex_yy_c,
        .flags = &.{ "-Wall", "-Wextra", "-g3", "-DFT_B_OPTI" },
    });
    b_exe.root_module.addIncludePath(b.path(prefix));
    b_exe.root_module.addIncludePath(b.path(src_dir));
    b_exe.root_module.addIncludePath(y_tab_c.dirname());

    // Step 4: Build libb.a using B and the 32-bit assembler/archiver
    var obj_files: std.ArrayList(std.Build.LazyPath) = .empty;

    for (libb_sources) |name| {
        // Compile .b to .s via B
        const run_b = b.addRunArtifact(b_exe);
        const b_file = b.path(b.pathJoin(&.{ libb_dir, b.fmt("{s}.b", .{name}) }));
        run_b.setStdIn(.{ .lazy_path = b_file });
        const asm_file = run_b.captureStdOut(.{ .basename = b.fmt("{s}.s", .{name}) });

        // Assemble .s to 32-bit .o via `as --32`
        const as_cmd = b.addSystemCommand(&.{ "as", "--32", "-o" });
        const obj_file = as_cmd.addOutputFileArg(b.fmt("{s}.o", .{name}));
        as_cmd.addFileArg(asm_file);

        obj_files.append(b.allocator, obj_file) catch @panic("OOM");
    }

    // Archive all .o into libb.a via `ar rcs`
    const ar_cmd = b.addSystemCommand(&.{ "ar", "rcs" });
    const libb_a = ar_cmd.addOutputFileArg("libb.a");
    for (obj_files.items) |obj| {
        ar_cmd.addFileArg(obj);
    }

    const install_lib = b.addInstallLibFile(libb_a, "libb.a");
    b.getInstallStep().dependOn(&install_lib.step);

    return b_exe;
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const b_exe = configure(b, target, optimize);
    b.installArtifact(b_exe);

    const run_cmd = b.addRunArtifact(b_exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the B compiler");
    run_step.dependOn(&run_cmd.step);
}
