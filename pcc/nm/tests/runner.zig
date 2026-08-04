const std = @import("std");

const RunResult = struct {
    stdout: []const u8,
    stderr: []const u8,
    exit_code: u8,
};

fn runCmd(allocator: std.mem.Allocator, io: std.Io, args: []const []const u8) !RunResult {
    const res = try std.process.run(allocator, io, .{
        .argv = args,
    });
    const code: u8 = switch (res.term) {
        .exited => |c| c,
        else => 255,
    };
    return .{
        .stdout = res.stdout,
        .stderr = res.stderr,
        .exit_code = code,
    };
}

fn printOutputDiff(expected: []const u8, actual: []const u8, file_path: []const u8) void {
    std.debug.print("\n" ++ "=" ** 65 ++ "\n", .{});
    std.debug.print("OUTPUT MISMATCH for file: {s}\n", .{file_path});
    std.debug.print("=" ** 65 ++ "\n", .{});

    var exp_it = std.mem.splitScalar(u8, expected, '\n');
    var act_it = std.mem.splitScalar(u8, actual, '\n');

    var line_num: usize = 1;
    var mismatches: usize = 0;

    while (true) {
        const exp_line = exp_it.next();
        const act_line = act_it.next();

        if (exp_line == null and act_line == null) break;

        const e = exp_line orelse "<EOF>";
        const a = act_line orelse "<EOF>";

        if (!std.mem.eql(u8, e, a)) {
            mismatches += 1;
            if (mismatches <= 25) {
                std.debug.print("Line {d: >4}:\n  Expected (nm)   : '{s}'\n  Actual (ft_nm)  : '{s}'\n", .{ line_num, e, a });
            }
        }
        line_num += 1;
    }

    if (mismatches > 25) {
        std.debug.print("... and {d} more mismatched lines.\n", .{mismatches - 25});
    }
    std.debug.print("=" ** 65 ++ "\n\n", .{});
}

fn compareNm(allocator: std.mem.Allocator, io: std.Io, ft_nm_path: []const u8, file_path: []const u8) !void {
    const ft_res = try runCmd(allocator, io, &.{ ft_nm_path, file_path });
    defer allocator.free(ft_res.stdout);
    defer allocator.free(ft_res.stderr);

    const sys_res = try runCmd(allocator, io, &.{ "nm", file_path });
    defer allocator.free(sys_res.stdout);
    defer allocator.free(sys_res.stderr);

    var failed = false;

    if (ft_res.exit_code != sys_res.exit_code) {
        std.debug.print("\nEXIT CODE MISMATCH for '{s}': ft_nm returned {d}, system nm returned {d}\n", .{
            file_path,
            ft_res.exit_code,
            sys_res.exit_code,
        });
        failed = true;
    }

    if (!std.mem.eql(u8, sys_res.stdout, ft_res.stdout)) {
        printOutputDiff(sys_res.stdout, ft_res.stdout, file_path);
        failed = true;
    }

    if (failed) {
        return error.TestOutputMismatch;
    }
}

pub fn main(init: std.process.Init.Minimal) !void {
    const arena_allocator = std.heap.page_allocator;

    var threaded: std.Io.Threaded = .init(arena_allocator, .{
        .argv0 = .init(init.args),
        .environ = .{ .block = init.environ.block },
    });
    defer threaded.deinit();

    var iter = init.args.iterate();
    _ = iter.next(); // Skip self path

    const ft_nm_bin = iter.next() orelse {
        std.debug.print("Error: ft_nm binary path argument missing.\n", .{});
        return error.MissingArgument;
    };

    std.debug.print("\n[nm test runner] Using ft_nm binary: {s}\n", .{ft_nm_bin});

    var pass_count: usize = 0;
    var fail_count: usize = 0;

    // Process all passed target object files
    while (iter.next()) |target_path| {
        std.debug.print("[nm test runner] Comparing output for: {s} ... ", .{target_path});
        if (compareNm(arena_allocator, threaded.io(), ft_nm_bin, target_path)) |_| {
            std.debug.print("OK\n", .{});
            pass_count += 1;
        } else |err| {
            std.debug.print("FAILED ({s})\n", .{@errorName(err)});
            fail_count += 1;
        }
    }

    // Also test self (ft_nm binary)
    std.debug.print("[nm test runner] Comparing output for self binary: {s} ... ", .{ft_nm_bin});
    if (compareNm(arena_allocator, threaded.io(), ft_nm_bin, ft_nm_bin)) |_| {
        std.debug.print("OK\n", .{});
        pass_count += 1;
    } else |err| {
        std.debug.print("FAILED ({s})\n", .{@errorName(err)});
        fail_count += 1;
    }

    if (fail_count > 0) {
        std.debug.print("\nTest Summary: {d} passed, {d} failed.\n", .{ pass_count, fail_count });
        std.process.exit(1);
    } else {
        std.debug.print("\nTest Summary: All {d} nm comparison tests passed!\n", .{pass_count});
    }
}
