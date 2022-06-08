const std = @import("std");

const Op = opaque { bruh: i32, wat: i32 };

const Dirent64 = extern struct {
    inode: u64,
    offset: u64,
    reclen: u16,
    typ: u8,
};

fn pog(p: Op) i32 {
    return p.bruh;
}

pub fn main() void {
    std.debug.print("{}", .{Dirent64});
}
