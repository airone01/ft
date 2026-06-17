const std = @import("std");
const testing = std.testing;

const c = @cImport({
    @cInclude("unistd.h");
    @cInclude("ft_printf_bonus.h");
});

// Creates a pipe, calls ft_printf_fd into the write end, and returns the
// captured bytes. Closes both ends.
const Pipe = struct {
    r: c_int,
    w: c_int,

    fn open() !Pipe {
        var fds: [2]c_int = undefined;
        if (c.pipe(&fds) != 0) return error.PipeFailed;
        return .{ .r = fds[0], .w = fds[1] };
    }

    fn collect(self: Pipe, buf: []u8) ![]const u8 {
        _ = c.close(self.w);
        var total: usize = 0;
        while (true) {
            const n = c.read(self.r, buf.ptr + total, buf.len - total);
            if (n <= 0) break;
            total += @intCast(n);
        }
        _ = c.close(self.r);
        return buf[0..total];
    }
};

// ── Mandatory ─────────────────────────────────────────────────────────────────

test "%c: basic chars" {
    var buf: [8]u8 = undefined;
    for ([_]struct { val: u8, exp: []const u8 }{
        .{ .val = 'A', .exp = "A" },
        .{ .val = '0', .exp = "0" },
        .{ .val = '\n', .exp = "\n" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%c", @as(c_int, tc.val));
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 1), ret);
    }
}

test "%s: strings" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%s", @as([*c]const u8, "Hello 42!"));
        try testing.expectEqualStrings("Hello 42!", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 9), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%s", @as([*c]const u8, ""));
        try testing.expectEqualStrings("", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 0), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%s", @as([*c]const u8, null));
        try testing.expectEqualStrings("(null)", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 6), ret);
    }
}

test "%p: pointers" {
    var buf: [32]u8 = undefined;
    var exp_buf: [32]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%p", @as(?*anyopaque, null));
        try testing.expectEqualStrings("(nil)", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        var x: c_int = 42;
        const ptr: ?*anyopaque = &x;
        const exp = try std.fmt.bufPrint(&exp_buf, "0x{x}", .{@intFromPtr(ptr)});
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%p", ptr);
        try testing.expectEqualStrings(exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(exp.len)), ret);
    }
}

test "%d and %i: signed integers" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_int, exp: []const u8 }{
        .{ .fmt = "%d", .val = 42, .exp = "42" },
        .{ .fmt = "%d", .val = -42, .exp = "-42" },
        .{ .fmt = "%d", .val = 0, .exp = "0" },
        .{ .fmt = "%d", .val = std.math.maxInt(c_int), .exp = "2147483647" },
        .{ .fmt = "%d", .val = std.math.minInt(c_int), .exp = "-2147483648" },
        .{ .fmt = "%i", .val = std.math.maxInt(c_int), .exp = "2147483647" },
        .{ .fmt = "%i", .val = std.math.minInt(c_int), .exp = "-2147483648" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "%u: unsigned decimal" {
    var buf: [16]u8 = undefined;
    for ([_]struct { val: c_uint, exp: []const u8 }{
        .{ .val = 42, .exp = "42" },
        .{ .val = 0, .exp = "0" },
        .{ .val = std.math.maxInt(c_uint), .exp = "4294967295" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%u", tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "%x and %X: hexadecimal" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_uint, exp: []const u8 }{
        .{ .fmt = "%x", .val = 42, .exp = "2a" },
        .{ .fmt = "%x", .val = 0, .exp = "0" },
        .{ .fmt = "%x", .val = std.math.maxInt(c_uint), .exp = "ffffffff" },
        .{ .fmt = "%X", .val = 42, .exp = "2A" },
        .{ .fmt = "%X", .val = 0, .exp = "0" },
        .{ .fmt = "%X", .val = std.math.maxInt(c_uint), .exp = "FFFFFFFF" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "%%: percent sign" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, exp: []const u8 }{
        .{ .fmt = "%%", .exp = "%" },
        .{ .fmt = "%%%%%%", .exp = "%%%" },
        .{ .fmt = "100%% real", .exp = "100% real" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

// ── Bonus: #, +, space ────────────────────────────────────────────────────────

test "bonus %#x: alternate form" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_uint, exp: []const u8 }{
        .{ .fmt = "%#x", .val = 42, .exp = "0x2a" },
        .{ .fmt = "%#X", .val = 42, .exp = "0X2A" },
        .{ .fmt = "%#x", .val = 0, .exp = "0" }, // no prefix for zero
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "bonus %+d: plus flag" {
    var buf: [16]u8 = undefined;
    for ([_]struct { val: c_int, exp: []const u8 }{
        .{ .val = 42, .exp = "+42" },
        .{ .val = -42, .exp = "-42" },
        .{ .val = 0, .exp = "+0" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%+d", tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "bonus % d: space flag" {
    var buf: [16]u8 = undefined;
    for ([_]struct { val: c_int, exp: []const u8 }{
        .{ .val = 42, .exp = " 42" },
        .{ .val = -42, .exp = "-42" },
        .{ .val = 0, .exp = " 0" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "% d", tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "bonus %+ d: plus overrides space" {
    var buf: [8]u8 = undefined;
    const p = try Pipe.open();
    const ret = c.ft_printf_fd(p.w, "%+ d", @as(c_int, 42));
    try testing.expectEqualStrings("+42", try p.collect(&buf));
    try testing.expectEqual(@as(c_int, 3), ret);
}

// ── Bonus: width, -, 0, . ─────────────────────────────────────────────────────

test "bonus width: right-align" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%5d", @as(c_int, 42));
        try testing.expectEqualStrings("   42", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%10s", @as([*c]const u8, "42"));
        try testing.expectEqualStrings("        42", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 10), ret);
    }
}

test "bonus %-: left-align" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%-5d", @as(c_int, 42));
        try testing.expectEqualStrings("42   ", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%-10s", @as([*c]const u8, "42"));
        try testing.expectEqualStrings("42        ", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 10), ret);
    }
}

test "bonus %0: zero-pad" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%05d", @as(c_int, 42));
        try testing.expectEqualStrings("00042", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%010d", @as(c_int, -42));
        try testing.expectEqualStrings("-000000042", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 10), ret);
    }
}

test "bonus precision" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%.5d", @as(c_int, 42));
        try testing.expectEqualStrings("00042", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%.3s", @as([*c]const u8, "Hello 42!"));
        try testing.expectEqualStrings("Hel", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 3), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%.0d", @as(c_int, 0));
        try testing.expectEqualStrings("", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 0), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%.0s", @as([*c]const u8, "hello"));
        try testing.expectEqualStrings("", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 0), ret);
    }
}

test "bonus combined flags" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_uint, exp: []const u8 }{
        .{ .fmt = "%-10.5d", .val = 42, .exp = "00042     " },
        .{ .fmt = "%08.5d", .val = 42, .exp = "   00042" },
        .{ .fmt = "%+#10.5x", .val = 42, .exp = "   0x0002a" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

// ── Additional ────────────────────────────────────────────────────────────────

test "additional: %c with width" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%5c", @as(c_int, 'A'));
        try testing.expectEqualStrings("    A", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%-5c", @as(c_int, 'A'));
        try testing.expectEqualStrings("A    ", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
}

test "additional: %u with flags" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_uint, exp: []const u8 }{
        .{ .fmt = "%5u", .val = 42, .exp = "   42" },
        .{ .fmt = "%05u", .val = 42, .exp = "00042" },
        .{ .fmt = "%-5u", .val = 42, .exp = "42   " },
        .{ .fmt = "%.5u", .val = 42, .exp = "00042" },
        .{ .fmt = "%5u", .val = 0, .exp = "    0" },
        .{ .fmt = "%.0u", .val = 0, .exp = "" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "additional: %p with width" {
    var buf: [32]u8 = undefined;
    var exp_buf: [32]u8 = undefined;
    var left_buf: [32]u8 = undefined;
    var x: c_int = 42;
    const ptr: ?*anyopaque = &x;
    const addr = try std.fmt.bufPrint(&exp_buf, "0x{x}", .{@intFromPtr(ptr)});
    const total: usize = @max(20, addr.len);
    {
        const exp = try std.fmt.bufPrint(&left_buf, "{s:>20}", .{addr});
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%20p", ptr);
        try testing.expectEqualStrings(exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(total)), ret);
    }
    {
        const exp = try std.fmt.bufPrint(&left_buf, "{s:<20}", .{addr});
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%-20p", ptr);
        try testing.expectEqualStrings(exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(total)), ret);
    }
}

test "additional: %+d with width" {
    var buf: [16]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%+5d", @as(c_int, 42));
        try testing.expectEqualStrings("  +42", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%+05d", @as(c_int, 42));
        try testing.expectEqualStrings("+0042", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 5), ret);
    }
}

test "additional: zero flag ignored when precision given" {
    var buf: [16]u8 = undefined;
    // precision=3 gives "042", zero ignored, width=5 space-pads => "  042"
    const p = try Pipe.open();
    const ret = c.ft_printf_fd(p.w, "%05.3d", @as(c_int, 42));
    try testing.expectEqualStrings("  042", try p.collect(&buf));
    try testing.expectEqual(@as(c_int, 5), ret);
}

test "additional: multiple conversions" {
    var buf: [64]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%d + %d = %d", @as(c_int, 1), @as(c_int, 2), @as(c_int, 3));
        try testing.expectEqualStrings("1 + 2 = 3", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 9), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "hello %s!\n", @as([*c]const u8, "world"));
        try testing.expectEqualStrings("hello world!\n", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 13), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "%c%c%c", @as(c_int, 'f'), @as(c_int, 't'), @as(c_int, '_'));
        try testing.expectEqualStrings("ft_", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 3), ret);
    }
}

test "additional: empty and literal-only format" {
    var buf: [32]u8 = undefined;
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "");
        try testing.expectEqualStrings("", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 0), ret);
    }
    {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, "hello world");
        try testing.expectEqualStrings("hello world", try p.collect(&buf));
        try testing.expectEqual(@as(c_int, 11), ret);
    }
}

test "additional: %x with width and zero" {
    var buf: [16]u8 = undefined;
    for ([_]struct { fmt: [*:0]const u8, val: c_uint, exp: []const u8 }{
        .{ .fmt = "%8x", .val = 255, .exp = "      ff" },
        .{ .fmt = "%08x", .val = 255, .exp = "000000ff" },
        .{ .fmt = "%-8x", .val = 255, .exp = "ff      " },
        .{ .fmt = "%#010x", .val = 255, .exp = "0x000000ff" },
    }) |tc| {
        const p = try Pipe.open();
        const ret = c.ft_printf_fd(p.w, tc.fmt, tc.val);
        try testing.expectEqualStrings(tc.exp, try p.collect(&buf));
        try testing.expectEqual(@as(c_int, @intCast(tc.exp.len)), ret);
    }
}

test "additional: %d INT_MIN with width" {
    var buf: [16]u8 = undefined;
    const p = try Pipe.open();
    const ret = c.ft_printf_fd(p.w, "%15d", @as(c_int, std.math.minInt(c_int)));
    try testing.expectEqualStrings("    -2147483648", try p.collect(&buf));
    try testing.expectEqual(@as(c_int, 15), ret);
}
