const std = @import("std");

const TestCase = struct {
    name: []const u8,
    code: []const u8,
    expected_exit: u8 = 0,
    expected_stdout: ?[]const u8 = null,
    stdin_data: []const u8 = "",
};

fn testCase(comptime name: []const u8) TestCase {
    return .{
        .name = name,
        .code = @embedFile("test/" ++ name ++ ".b"),
        .expected_exit = 0,
    };
}

fn testCaseExit(comptime name: []const u8, expected_exit: u8) TestCase {
    return .{
        .name = name,
        .code = @embedFile("test/" ++ name ++ ".b"),
        .expected_exit = expected_exit,
    };
}

fn testCaseStdout(comptime name: []const u8, expected_stdout: []const u8) TestCase {
    return .{
        .name = name,
        .code = @embedFile("test/" ++ name ++ ".b"),
        .expected_exit = 0,
        .expected_stdout = expected_stdout,
    };
}

fn testCaseStdin(comptime name: []const u8, stdin_data: []const u8) TestCase {
    return .{
        .name = name,
        .code = @embedFile("test/" ++ name ++ ".b"),
        .expected_exit = 0,
        .stdin_data = stdin_data,
    };
}

const tests = [_]TestCase{
    // ============================== ARITHMETIC ===============================
    testCase("arith_add"),
    testCase("arith_sub"),
    testCase("arith_mul"),
    testCase("arith_div"),
    testCase("arith_mod"),
    testCase("arith_precedence"),

    // =============================== BITWISE =================================
    testCase("bitwise_and_or_xor"),
    testCase("bitwise_shifts"),
    testCase("bitwise_not"),

    // ========================= COMPARISONS & LOGICAL =========================
    testCase("comparisons"),
    testCase("logical_not"),
    testCase("short_circuit_and"),
    testCase("short_circuit_or"),

    // =============================== INC / DEC ===============================
    testCase("inc_dec_vars"),

    // ============================= CONTROL FLOW ==============================
    testCase("if_else"),
    testCase("nested_if_else"),
    testCase("while_loop"),
    testCase("while_break"),
    testCase("switch_case"),
    testCase("goto_label"),

    // =============================== RECURSION ===============================
    testCase("recursion_fact"),
    testCase("recursion_fib"),

    // ======================== FUNCTION CALLING & ARGS ========================
    testCase("call_0_args"),
    testCase("call_1_arg"),
    testCase("call_2_args"),
    testCase("call_3_args"),
    testCase("call_4_args"),
    testCase("call_nested"),

    // =========================== POINTERS & ARRAYS ===========================
    testCase("address_of_and_deref"),
    testCase("array_index_and_inc"),
    testCase("global_scalars_and_vectors"),

    // ================================ FLOATS =================================
    testCase("float_ops"),
    testCase("float_casts"),
    testCase("float_cmps"),

    // ======================== SYMBOL TABLE / SCOPING =========================
    testCase("cross_func_symbol_pollution"),

    // ========================= LIBB SYSCALLS & UTILS =========================
    testCase("libb_char"),
    testCaseExit("libb_exit", 42),
    testCase("libb_time"),
    testCase("libb_getuid"),
    testCase("libb_chdir"),
    testCase("libb_close"),
    testCase("libb_unlink"),
    testCase("libb_fork_wait"),
    testCase("libb_write"),
    testCase("libb_putchar"),
    testCase("libb_printf"),

    // ===================== UNARY & COMPOUND ASSIGNMENTS ======================
    testCase("unary_negation"),
    testCase("chained_assignment"),

    // =============================== SWITCH ==================================
    testCase("switch_default"),
    testCase("switch_fallthrough"),
    testCase("switch_nested"),

    // ================================= LOOPS =================================
    testCase("while_nested_break"),

    // =========================== ARRAYS & POINTERS ===========================
    testCase("array_post_inc_dec"),

    // ========================== FUNCTIONS & CALLING ==========================
    testCase("func_ptr_call"),
    testCase("call_6_args"),
    testCase("call_8_args"),
    testCase("mutual_recursion"),
    testCase("empty_return"),

    // ============================ SCOPE & GLOBALS ============================
    testCase("global_vector_negative_init"),
    testCase("param_shadows_global"),
    testCase("auto_shadows_global"),

    // ============================ LIBB UTILS & IO ============================
    testCase("libb_lchar"),
    testCase("libb_creat_write_close_unlink"),
    testCase("libb_open_read_close"),
    testCase("libb_seek"),
    testCase("libb_mkdir_chdir"),
    testCaseStdout("libb_printn", "42\n1101\n"),
    testCaseStdin("libb_getchar", "ABC"),
    testCase("libb_chmod"),
    testCase("libb_link"),
};

fn fileExists(io: std.Io, path: []const u8) bool {
    std.Io.Dir.accessAbsolute(io, path, .{}) catch return false;
    return true;
}

pub fn main(init: std.process.Init.Minimal) !void {
    const allocator = std.heap.page_allocator;
    var threaded: std.Io.Threaded = .init(allocator, .{
        .argv0 = .init(init.args),
        .environ = .{ .block = init.environ.block },
    });
    defer threaded.deinit();

    const io = threaded.io();

    var iter = init.args.iterate();
    _ = iter.next(); // skip self path

    const b_path_arg = iter.next();
    const brt0_path_arg = iter.next();
    const libb_path_arg = iter.next();

    const b_path = if (b_path_arg) |p| p else if (fileExists(io, "pcc/b/B")) "pcc/b/B" else if (fileExists(io, "./B")) "./B" else "zig-out/bin/B";
    const brt0_path = if (brt0_path_arg) |p| p else if (fileExists(io, "pcc/b/brt0.o")) "pcc/b/brt0.o" else if (fileExists(io, "./brt0.o")) "./brt0.o" else "pcc/b/brt0.o";
    const libb_path = if (libb_path_arg) |p| p else if (fileExists(io, "pcc/b/libb/libb.a")) "pcc/b/libb/libb.a" else if (fileExists(io, "./libb/libb.a")) "./libb/libb.a" else "zig-out/lib/libb.a";

    std.debug.print("==================================================\n", .{});
    std.debug.print("B Test Runner\n", .{});
    std.debug.print("  Compiler : {s}\n", .{b_path});
    std.debug.print("  brt0.o   : {s}\n", .{brt0_path});
    std.debug.print("  libb.a   : {s}\n", .{libb_path});
    std.debug.print("==================================================\n", .{});

    var passed: usize = 0;
    var failed: usize = 0;

    for (tests, 0..) |t, idx| {
        const pid = std.posix.system.getpid();
        const b_file = try std.fmt.allocPrint(allocator, "/tmp/b_test_{d}_{d}.b", .{ pid, idx });
        defer allocator.free(b_file);
        defer std.Io.Dir.deleteFileAbsolute(io, b_file) catch {};

        const s_file = try std.fmt.allocPrint(allocator, "/tmp/b_test_{d}_{d}.s", .{ pid, idx });
        defer allocator.free(s_file);
        defer std.Io.Dir.deleteFileAbsolute(io, s_file) catch {};

        const o_file = try std.fmt.allocPrint(allocator, "/tmp/b_test_{d}_{d}.o", .{ pid, idx });
        defer allocator.free(o_file);
        defer std.Io.Dir.deleteFileAbsolute(io, o_file) catch {};

        const bin_file = try std.fmt.allocPrint(allocator, "/tmp/b_test_{d}_{d}", .{ pid, idx });
        defer allocator.free(bin_file);
        defer std.Io.Dir.deleteFileAbsolute(io, bin_file) catch {};

        const stdin_file = try std.fmt.allocPrint(allocator, "/tmp/b_test_{d}_{d}.in", .{ pid, idx });
        defer allocator.free(stdin_file);
        defer std.Io.Dir.deleteFileAbsolute(io, stdin_file) catch {};

        // Write B source
        {
            var file = std.Io.Dir.createFileAbsolute(io, b_file, .{}) catch |err| {
                std.debug.print("[-] {s}: FAILED TO CREATE TEMP FILE: {s}\n", .{ t.name, @errorName(err) });
                failed += 1;
                continue;
            };
            try file.writeStreamingAll(io, t.code);
            file.close(io);
        }

        // Write stdin data if any
        if (t.stdin_data.len > 0) {
            var file = std.Io.Dir.createFileAbsolute(io, stdin_file, .{}) catch |err| {
                std.debug.print("[-] {s}: FAILED TO CREATE STDIN FILE: {s}\n", .{ t.name, @errorName(err) });
                failed += 1;
                continue;
            };
            try file.writeStreamingAll(io, t.stdin_data);
            file.close(io);
        }

        // Run B
        const b_cmd = try std.fmt.allocPrint(allocator, "{s} < {s} > {s}", .{ b_path, b_file, s_file });
        defer allocator.free(b_cmd);

        const res_b = std.process.run(allocator, io, .{
            .argv = &.{ "/bin/sh", "-c", b_cmd },
        }) catch |err| {
            std.debug.print("[-] {s}: FAILED TO SPAWN B: {s}\n", .{ t.name, @errorName(err) });
            failed += 1;
            continue;
        };
        defer allocator.free(res_b.stdout);
        defer allocator.free(res_b.stderr);

        if (res_b.term != .exited or res_b.term.exited != 0) {
            std.debug.print("[-] {s}: FAILED AT COMPILER (B)\n", .{t.name});
            if (res_b.stderr.len > 0) {
                std.debug.print("    stderr: {s}\n", .{res_b.stderr});
            }
            failed += 1;
            continue;
        }

        // Assemble
        const res_as = std.process.run(allocator, io, .{
            .argv = &.{ "as", "--32", s_file, "-o", o_file },
        }) catch |err| {
            std.debug.print("[-] {s}: FAILED TO SPAWN AS: {s}\n", .{ t.name, @errorName(err) });
            failed += 1;
            continue;
        };
        defer allocator.free(res_as.stdout);
        defer allocator.free(res_as.stderr);

        if (res_as.term != .exited or res_as.term.exited != 0) {
            std.debug.print("[-] {s}: FAILED AT ASSEMBLER (as)\n", .{t.name});
            if (res_as.stderr.len > 0) {
                std.debug.print("    stderr: {s}\n", .{res_as.stderr});
            }
            failed += 1;
            continue;
        }

        // Link
        const res_ld = std.process.run(allocator, io, .{
            .argv = &.{ "ld", "-m", "elf_i386", o_file, brt0_path, libb_path, "-o", bin_file },
        }) catch |err| {
            std.debug.print("[-] {s}: FAILED TO SPAWN LD: {s}\n", .{ t.name, @errorName(err) });
            failed += 1;
            continue;
        };
        defer allocator.free(res_ld.stdout);
        defer allocator.free(res_ld.stderr);

        if (res_ld.term != .exited or res_ld.term.exited != 0) {
            std.debug.print("[-] {s}: FAILED AT LINKER (ld)\n", .{t.name});
            if (res_ld.stderr.len > 0) {
                std.debug.print("    stderr: {s}\n", .{res_ld.stderr});
            }
            failed += 1;
            continue;
        }

        // Run under qemu-i386 -strace
        const qemu_cmd = if (t.stdin_data.len > 0)
            try std.fmt.allocPrint(allocator, "qemu-i386 -strace {s} < {s}", .{ bin_file, stdin_file })
        else
            try std.fmt.allocPrint(allocator, "qemu-i386 -strace {s}", .{bin_file});
        defer allocator.free(qemu_cmd);

        const res_qemu = std.process.run(allocator, io, .{
            .argv = &.{ "/bin/sh", "-c", qemu_cmd },
        }) catch |err| {
            std.debug.print("[-] {s}: FAILED TO SPAWN QEMU: {s}\n", .{ t.name, @errorName(err) });
            failed += 1;
            continue;
        };
        defer allocator.free(res_qemu.stdout);
        defer allocator.free(res_qemu.stderr);

        const actual_exit: u8 = switch (res_qemu.term) {
            .exited => |c| @intCast(c & 0xff),
            else => 255,
        };

        var ok = true;
        if (actual_exit != t.expected_exit) {
            ok = false;
        }
        if (t.expected_stdout) |expected_out| {
            if (!std.mem.eql(u8, res_qemu.stdout, expected_out)) {
                ok = false;
            }
        }

        if (ok) {
            std.debug.print("[+] {s}: PASSED\n", .{t.name});
            passed += 1;
        } else {
            std.debug.print("[-] {s}: FAILED (exit {d} != expected {d})\n", .{ t.name, actual_exit, t.expected_exit });
            if (res_qemu.stderr.len > 0) {
                // Print first 3 lines of strace output
                var line_it = std.mem.splitScalar(u8, res_qemu.stderr, '\n');
                var count: usize = 0;
                while (line_it.next()) |line| {
                    if (line.len == 0 or std.mem.startsWith(u8, line, "qemu-i386:")) continue;
                    std.debug.print("    strace: {s}\n", .{line});
                    count += 1;
                    if (count >= 3) break;
                }
            }
            failed += 1;
        }
    }

    std.debug.print("\nTest Summary: {d} passed, {d} failed out of {d} total tests.\n", .{ passed, failed, tests.len });

    if (failed > 0) {
        std.process.exit(1);
    }
}
