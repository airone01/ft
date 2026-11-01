const std = @import("std");

const TestCase = struct {
    name: []const u8,
    code: []const u8,
    expected_exit: u8 = 0,
    expected_stdout: ?[]const u8 = null,
    stdin_data: []const u8 = "",
};

const tests = [_]TestCase{
    // ==================== ARITHMETIC ====================
    .{
        .name = "arith_add",
        .code =
        \\main() {
        \\  auto a, b, c;
        \\  a = 15;
        \\  b = 27;
        \\  c = a + b;
        \\  if (c != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "arith_sub",
        .code =
        \\main() {
        \\  auto a, b, c;
        \\  a = 100;
        \\  b = 58;
        \\  c = a - b;
        \\  if (c != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "arith_mul",
        .code =
        \\main() {
        \\  auto a, b, c;
        \\  a = 6;
        \\  b = 7;
        \\  c = a * b;
        \\  if (c != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "arith_div",
        .code =
        \\main() {
        \\  auto a, b, c;
        \\  a = 84;
        \\  b = 2;
        \\  c = a / b;
        \\  if (c != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "arith_mod",
        .code =
        \\main() {
        \\  auto a, b, c;
        \\  a = 142;
        \\  b = 100;
        \\  c = a % b;
        \\  if (c != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "arith_precedence",
        .code =
        \\main() {
        \\  auto x;
        \\  x = 2 + 3 * 4;
        \\  if (x != 14) return (1);
        \\  x = (2 + 3) * 4;
        \\  if (x != 20) return (2);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== BITWISE ====================
    .{
        .name = "bitwise_and_or_xor",
        .code =
        \\main() {
        \\  auto a, b;
        \\  a = 65280; /* 0xFF00 in decimal */
        \\  b = 4080;  /* 0x0FF0 in decimal */
        \\  if ((a & b) != 3840) return (1);  /* 0x0F00 */
        \\  if ((a | b) != 65520) return (2); /* 0xFFF0 */
        \\  if ((a ^ b) != 61680) return (3); /* 0xF0F0 */
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "bitwise_shifts",
        .code =
        \\main() {
        \\  auto a;
        \\  a = 1;
        \\  if ((a << 4) != 16) return (1);
        \\  if ((16 >> 2) != 4) return (2);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "bitwise_not",
        .code =
        \\main() {
        \\  auto a;
        \\  a = 0;
        \\  if (~a != -1) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== COMPARISONS ====================
    .{
        .name = "comparisons",
        .code =
        \\main() {
        \\  if (!(5 == 5)) return (1);
        \\  if (5 != 5) return (2);
        \\  if (!(5 < 10)) return (3);
        \\  if (10 < 5) return (4);
        \\  if (!(5 <= 5)) return (5);
        \\  if (!(5 <= 6)) return (6);
        \\  if (!(10 > 5)) return (7);
        \\  if (5 > 10) return (8);
        \\  if (!(5 >= 5)) return (9);
        \\  if (!(6 >= 5)) return (10);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== LOGICAL & SHORT-CIRCUIT ====================
    .{
        .name = "logical_not",
        .code =
        \\main() {
        \\  if (!0 != 1) return (1);
        \\  if (!1 != 0) return (2);
        \\  if (!42 != 0) return (3);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "short_circuit_and",
        .code =
        \\main() {
        \\  auto side_effect;
        \\  side_effect = 0;
        \\  if (0 && (side_effect = 1)) {
        \\    return (1);
        \\  }
        \\  if (side_effect != 0) return (2);
        \\  if (1 && (side_effect = 1)) {
        \\    if (side_effect != 1) return (3);
        \\  } else {
        \\    return (4);
        \\  }
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "short_circuit_or",
        .code =
        \\main() {
        \\  auto side_effect;
        \\  side_effect = 0;
        \\  if (1 || (side_effect = 1)) {
        \\    if (side_effect != 0) return (1);
        \\  } else {
        \\    return (2);
        \\  }
        \\  if (0 || (side_effect = 1)) {
        \\    if (side_effect != 1) return (3);
        \\  } else {
        \\    return (4);
        \\  }
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== INCREMENT / DECREMENT ====================
    .{
        .name = "inc_dec_vars",
        .code =
        \\main() {
        \\  auto x, y;
        \\  x = 10;
        \\  y = x++;
        \\  if (y != 10) return (1);
        \\  if (x != 11) return (2);
        \\  y = ++x;
        \\  if (y != 12) return (3);
        \\  if (x != 12) return (4);
        \\  y = x--;
        \\  if (y != 12) return (5);
        \\  if (x != 11) return (6);
        \\  y = --x;
        \\  if (y != 10) return (7);
        \\  if (x != 10) return (8);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== CONTROL FLOW ====================
    .{
        .name = "if_else",
        .code =
        \\main() {
        \\  auto a, r;
        \\  a = 1;
        \\  if (a) r = 10; else r = 20;
        \\  if (r != 10) return (1);
        \\  a = 0;
        \\  if (a) r = 10; else r = 20;
        \\  if (r != 20) return (2);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "nested_if_else",
        .code =
        \\main() {
        \\  auto a, b, r;
        \\  a = 0;
        \\  b = 1;
        \\  r = 0;
        \\  if (a)
        \\    if (b) r = 1;
        \\    else r = 2;
        \\  else
        \\    r = 3;
        \\  if (r != 3) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "while_loop",
        .code =
        \\main() {
        \\  auto i, sum;
        \\  i = 1;
        \\  sum = 0;
        \\  while (i <= 10) {
        \\    sum = sum + i;
        \\    i++;
        \\  }
        \\  if (sum != 55) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "while_break",
        .code =
        \\main() {
        \\  auto i;
        \\  i = 0;
        \\  while (1) {
        \\    i++;
        \\    if (i == 5)
        \\      break;
        \\  }
        \\  if (i != 5) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "switch_case",
        .code =
        \\main() {
        \\  auto x, r;
        \\  x = 2;
        \\  r = 0;
        \\  switch (x) {
        \\    case 1: r = 10; break;
        \\    case 2: r = 20; break;
        \\    case 3: r = 30; break;
        \\    default: r = 99; break;
        \\  }
        \\  if (r != 20) return (1);
        \\  x = 5;
        \\  switch (x) {
        \\    case 1: r = 10; break;
        \\    case 2: r = 20; break;
        \\    default: r = 99; break;
        \\  }
        \\  if (r != 99) return (2);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "goto_label",
        .code =
        \\main() {
        \\  auto x;
        \\  x = 0;
        \\  goto skip;
        \\  x = 100;
        \\skip:
        \\  if (x != 0) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== RECURSION ====================
    .{
        .name = "recursion_fact",
        .code =
        \\fact(n) {
        \\  if (n <= 1) return (1);
        \\  return (n * fact(n - 1));
        \\}
        \\main() {
        \\  auto r;
        \\  r = fact(5);
        \\  if (r != 120) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "recursion_fib",
        .code =
        \\fib(n) {
        \\  if (n <= 0) return (0);
        \\  if (n == 1) return (1);
        \\  return (fib(n - 1) + fib(n - 2));
        \\}
        \\main() {
        \\  auto r;
        \\  r = fib(7);
        \\  if (r != 13) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== FUNCTION CALLS ====================
    .{
        .name = "call_0_args",
        .code =
        \\f0() { return (42); }
        \\main() {
        \\  if (f0() != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "call_1_arg",
        .code =
        \\f1(a) { return (a * 2); }
        \\main() {
        \\  if (f1(21) != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "call_2_args",
        .code =
        \\f2(a, b) { return (a * 10 + b); }
        \\main() {
        \\  if (f2(4, 2) != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "call_3_args",
        .code =
        \\f3(a, b, c) { return (a * 100 + b * 10 + c); }
        \\main() {
        \\  if (f3(1, 2, 3) != 123) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "call_4_args",
        .code =
        \\f4(a, b, c, d) { return (a * 1000 + b * 100 + c * 10 + d); }
        \\main() {
        \\  if (f4(1, 2, 3, 4) != 1234) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "call_nested",
        .code =
        \\add(a, b) { return (a + b); }
        \\mul(a, b) { return (a * b); }
        \\main() {
        \\  auto r;
        \\  r = add(mul(2, 3), mul(4, 5));
        \\  if (r != 26) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== POINTERS & ARRAYS ====================
    .{
        .name = "address_of_and_deref",
        .code =
        \\main() {
        \\  auto x, p;
        \\  x = 42;
        \\  p = &x;
        \\  if (*p != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "array_index_and_inc",
        .code =
        \\main() {
        \\  extrn v;
        \\  v[0] = 10;
        \\  v[1] = 20;
        \\  if (v[0] != 10) return (1);
        \\  if (v[1] != 20) return (2);
        \\  v[0]++;
        \\  if (v[0] != 11) return (3);
        \\  v[1]--;
        \\  if (v[1] != 19) return (4);
        \\  return (0);
        \\}
        \\v[10];
        ,
        .expected_exit = 0,
    },

    // ==================== GLOBALS ====================
    .{
        .name = "global_scalars_and_vectors",
        .code =
        \\extrn g1, g2, gv;
        \\main() {
        \\  if (g1 != 42) return (1);
        \\  if (g2 != 0) return (2);
        \\  if (gv[0] != 100) return (3);
        \\  if (gv[1] != 200) return (4);
        \\  if (gv[2] != 0) return (5);
        \\  return (0);
        \\}
        \\g1 42;
        \\g2;
        \\gv[5] 100, 200;
        ,
        .expected_exit = 0,
    },

    // ==================== FLOATS ====================
    .{
        .name = "float_ops",
        .code =
        \\main() {
        \\  auto f1, f2, f3;
        \\  f1 = 1.5;
        \\  f2 = 2.5;
        \\  f3 = f1 #+ f2;
        \\  /* 4.0 in IEEE-754: 0x40800000 = 1082130432 */
        \\  if (f3 != 1082130432) return (1);
        \\  f3 = f2 #- f1;
        \\  /* 1.0 in IEEE-754: 0x3f800000 = 1065353216 */
        \\  if (f3 != 1065353216) return (2);
        \\  f3 = f1 #* f2;
        \\  /* 3.75: 0x40700000 = 1081081856 */
        \\  if (f3 != 1081081856) return (3);
        \\  f3 = 5.0 #/ 2.0;
        \\  /* 2.5: 0x40200000 = 1075838976 */
        \\  if (f3 != 1075838976) return (4);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "float_casts",
        .code =
        \\main() {
        \\  auto i, f, i2;
        \\  i = 42;
        \\  f = # i;
        \\  /* 42.0 in IEEE-754: 1109917696 */
        \\  if (f != 1109917696) return (1);
        \\  i2 = ## f;
        \\  if (i2 != 42) return (2);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "float_cmps",
        .code =
        \\main() {
        \\  if (!(1.5 #< 2.5)) return (1);
        \\  if (2.5 #< 1.5) return (2);
        \\  if (!(2.5 #> 1.5)) return (3);
        \\  if (!(2.0 #== 2.0)) return (4);
        \\  if (2.0 #!= 2.0) return (5);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== SYMBOL TABLE SCOPE ====================
    .{
        .name = "cross_func_symbol_pollution",
        .code =
        \\func1() {
        \\  auto x;
        \\  x = 10;
        \\}
        \\func2(x) {
        \\  return (x);
        \\}
        \\main() {
        \\  auto r;
        \\  r = func2(42);
        \\  if (r != 42) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },

    // ==================== STANDARD LIBRARY (LIBB) ====================
    .{
        .name = "libb_char",
        .code =
        \\main() {
        \\  extrn char;
        \\  auto s;
        \\  s = "ABCD";
        \\  if (char(s, 0) != 'A') return (1);
        \\  if (char(s, 1) != 'B') return (2);
        \\  if (char(s, 2) != 'C') return (3);
        \\  if (char(s, 3) != 'D') return (4);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_exit",
        .code =
        \\main() {
        \\  extrn exit;
        \\  exit(42);
        \\  return (0);
        \\}
        ,
        .expected_exit = 42,
    },
    .{
        .name = "libb_time",
        .code =
        \\extrn t;
        \\main() {
        \\  extrn time;
        \\  t[0] = 0;
        \\  time(t);
        \\  if (t[0] <= 1000000000) return (1);
        \\  return (0);
        \\}
        \\t[2];
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_getuid",
        .code =
        \\main() {
        \\  extrn getuid;
        \\  if (getuid() < 0) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_chdir",
        .code =
        \\main() {
        \\  extrn chdir;
        \\  if (chdir("/tmp") != 0) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_close",
        .code =
        \\main() {
        \\  extrn close;
        \\  /* close non-existent fd 999 returns -EBADF (-9) */
        \\  if (close(999) != -9) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_unlink",
        .code =
        \\main() {
        \\  extrn unlink;
        \\  /* unlink non-existent file returns -ENOENT (-2) */
        \\  if (unlink("/nonexistent_xyz_12345") != -2) return (1);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_fork_wait",
        .code =
        \\main() {
        \\  extrn fork, wait, exit;
        \\  auto pid, wpid;
        \\  pid = fork();
        \\  if (pid == 0) {
        \\    exit(0);
        \\  }
        \\  wpid = wait();
        \\  if (wpid == pid) return (0);
        \\  return (1);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_write",
        .code =
        \\main() {
        \\  extrn write;
        \\  write(1, "B_WRITE_TEST\n", 13);
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_putchar",
        .code =
        \\main() {
        \\  extrn putchar;
        \\  putchar('O');
        \\  putchar('K');
        \\  putchar('\n');
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
    .{
        .name = "libb_printf",
        .code =
        \\main() {
        \\  extrn printf;
        \\  printf("%d %s\n", 42, "OK");
        \\  return (0);
        \\}
        ,
        .expected_exit = 0,
    },
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
    _ = iter.next(); // Skip self path

    const b_path_arg = iter.next();
    const brt0_path_arg = iter.next();
    const libb_path_arg = iter.next();

    // Determine paths with fallbacks
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

        // Write B source file
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

        // Step 1: Run B compiler
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

        // Step 2: Assemble with as --32
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

        // Step 3: Link with ld
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

        // Step 4: Run under qemu-i386 -strace
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
