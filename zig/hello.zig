const std = @import("std");
const expect = std.testing.expect;
const test_allocator = std.testing.allocator;

const S = struct {
    ptr: *i32,
};

fn modify(_x: [64]u64) void {
    var x = _x;
    x[1] = 42;
}

test "modify" {
    const x: [64]u64 = undefined;
    modify(x);

    var a: i32 = 1;
    const s = S{ .ptr = &a };
    s.ptr.* = 42;
    try expect(a == 42);
}

test "ifs" {
    const a = true;
    var x: u16 = 0;
    x += if (a) 1 else 2;
    try expect(x == 1);
}

test "while" {
    var i: u8 = 2;
    while (i < 100) {
        i *= 2;
    }
    try expect(i == 128);
}

test "while with break" {
    var sum: u8 = 0;
    var i: u8 = 0;
    while (i <= 3) : (i += 1) {
        if (i == 2) break;
        sum += i;
    }
    try expect(sum == 1);
}

test "for" {
    const string = "asdf";
    for (string) |character, index| {
        std.debug.print("{d} {d}", .{ character, index });
    }
}

test "defer" {
    var x: f64 = 5.0;
    {
        defer x += 2;
        defer x /= 2;
    }
    try expect(x == 4.5);
}

test "error" {
    const AllocationError = error{OutOfMemory};
    const FileOpenError = error{
        AccessDenied,
        OutOfMemory,
        FileNotFound,
    };

    const err: FileOpenError = AllocationError.OutOfMemory;
    try expect(err == FileOpenError.OutOfMemory);

    const maybe_error: AllocationError!u16 = 10;
    const no_error = maybe_error catch 0;
    try expect(@TypeOf(no_error) == u16);
    try expect(no_error == 10);
}

test "pointers" {
    var x: u16 = 0;
    var xp = &x;
    xp.* = 1;
    try expect(x == 1);
}

fn total(s: []const i32) i32 {
    var sum: i32 = 0;
    for (s) |v| sum += v;
    return sum;
}

test "slice" {
    const array = [_]i32{ 1, 2, 3, 4, 5 };
    const slice = array[1..3];
    try expect(total(slice) == 5);
}

test "dir" {
    const cwd = std.fs.cwd();
    try cwd.makeDir("testtmp");
    const dir = try cwd.openDir("testtmp", .{ .iterate = true });
    defer {
        cwd.deleteTree("testtmp") catch unreachable;
    }

    _ = try dir.createFile("x", .{});
}
