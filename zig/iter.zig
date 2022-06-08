const std = @import("std");

fn slice_item_type(comptime T: type) type {
    return @typeInfo(T).Array.child;
}
fn func_return_type(comptime F: type) type {
    return @typeInfo(F).Fn.return_type orelse void;
}

const SizeHint = struct { lower_bound: usize, higher_bound: ?usize };

fn SliceIter(comptime T: type) type {
    return struct {
        slice: []const T,

        const Self = @This();
        const Item = T;

        pub fn next(self: *Self) ?Item {
            if (self.slice.len == 0) {
                return null;
            }
            const ret = self.slice[0];
            self.slice = self.slice[1..];
            return ret;
        }

        pub fn next_back(self: *Self) ?Item {
            if (self.slice.len == 0) {
                return null;
            }
            const new_len = self.slice.len - 1;
            const ret = self.slice[new_len];
            self.slice = self.slice[0..new_len];
            return ret;
        }

        pub fn size_hint(self: Self) SizeHint {
            return SizeHint{ .lower_bound = self.slice.len, .higher_bound = self.slice.len };
        }

        pub fn exact_size_hint(self: Self) usize {
            return self.slice.len;
        }
    };
}

fn slice_iter(comptime T: type, s: []const T) SliceIter(T) {
    return SliceIter(T){ .slice = s };
}

fn RevIter(comptime Iter: type) type {
    return struct {
        iter: Iter,

        const Self = @This();
        const Item = Iter.Item;

        pub fn next(self: *Self) ?Item {
            return self.iter.next_back();
        }

        pub fn next_back(self: *Self) ?Item {
            return self.iter.next();
        }

        pub usingnamespace if (@hasDecl(Iter, "size_hint")) struct {
            pub fn size_hint(self: Self) SizeHint {
                return self.iter.size_hint();
            }
        } else struct {};

        pub usingnamespace if (@hasDecl(Iter, "exact_size_hint")) struct {
            pub fn exact_size_hint(self: Self) usize {
                return self.iter.exact_size_hint();
            }
        } else struct {};
    };
}

fn rev(x: anytype) RevIter(@TypeOf(x)) {
    return RevIter(@TypeOf(x)){ .iter = x };
}

fn MapIter(comptime Iter: type, comptime Fn: type, comptime Context: type) type {
    return struct {
        iter: Iter,
        f: Fn,
        context: Context,

        const Self = @This();
        const Item = func_return_type(Fn);

        fn apply(self: *Self, item: Iter.Item) ?Item {
            if (comptime @typeInfo(Fn).Fn.args.len == 1 and Context == void) {
                return self.f(item);
            }
            return self.f(item, self.context);
        }

        pub fn next(self: *Self) ?Item {
            const x = self.iter.next() orelse return null;
            return self.apply(x);
        }

        pub usingnamespace if (@hasDecl(Iter, "next_back")) struct {
            pub fn next_back(self: *Self) ?Item {
                const x = self.iter.next_back() orelse return null;
                return self.apply(x);
            }
        } else struct {};

        pub usingnamespace if (@hasDecl(Iter, "size_hint")) struct {
            pub fn size_hint(self: Self) SizeHint {
                return self.iter.size_hint();
            }
        } else struct {};

        pub usingnamespace if (@hasDecl(Iter, "exact_size_hint")) struct {
            pub fn exact_size_hint(self: Self) usize {
                return self.iter.exact_size_hint();
            }
        } else struct {};
    };
}

fn map(iter: anytype, f: anytype, context: anytype) MapIter(@TypeOf(iter), @TypeOf(f), @TypeOf(context)) {
    const RetType = MapIter(@TypeOf(iter), @TypeOf(f), @TypeOf(context));
    return RetType{
        .iter = iter,
        .f = f,
        .context = context,
    };
}

fn Enumerate(comptime Iter: type) type {
    return struct {
        iter: Iter,
        count: usize,

        const Self = @This();
        const Item = struct { count: usize, item: func_return_type(@TypeOf(Iter.next)) };

        pub fn next(self: *Self) ?Item {
            const x = self.iter.next() orelse return null;
            const i = self.count;
            self.count += 1;
            return Item{ .count = i, .item = x };
        }

        pub usingnamespace if (@hasDecl(Iter, "next_back") and @hasDecl(Iter, "exact_size_hint")) struct {
            pub fn next_back(self: *Self) ?Item {
                const x = self.iter.next_back() orelse return null;
                const i = self.iter.exact_size_hint();
                return Item{ .count = i + self.count, .item = x };
            }
        } else struct {};

        pub usingnamespace if (@hasDecl(Iter, "size_hint")) struct {
            pub fn size_hint(self: Self) SizeHint {
                return self.iter.size_hint();
            }
        } else struct {};

        pub usingnamespace if (@hasDecl(Iter, "exact_size_hint")) struct {
            pub fn exact_size_hint(self: Self) usize {
                return self.iter.exact_size_hint();
            }
        } else struct {};
    };
}

fn enumerate(iter: anytype) Enumerate(@TypeOf(iter)) {
    return Enumerate(@TypeOf(iter)){ .iter = iter, .count = 0 };
}

fn Flatten(comptime Iter: type) type {
    return struct {
        iter: Iter,
        current_iter: ?Iter.Item,

        const Self = @This();
        const Item = Iter.Item.Item;

        pub fn next(self: *Self) ?Item {
            if (self.current_iter) |*i| {
                if (i.next()) |r| {
                    return r;
                }
            }

            self.current_iter = self.iter.next() orelse return null;
            return self.next();
        }
    };
}

fn flatten(iter: anytype) Flatten(@TypeOf(iter)) {
    return Flatten(@TypeOf(iter)){ .iter = iter, .current_iter = null };
}

fn double(x: i32) i32 {
    return 2 * x;
}
fn slice_into_iter(s: []const i32) SliceIter(i32) {
    return slice_iter(i32, s);
}

pub fn main() void {
    var slice = slice_iter(i32, &[_]i32{ 1, 2, 3 });
    var rev_slice = rev(slice);
    var map_rev_slice = map(rev_slice, double, void{});
    var rev_enum_map_rev_slice = rev(enumerate(map_rev_slice));

    std.debug.print("{}\n", .{rev_enum_map_rev_slice.size_hint()});
    while (slice.next()) |x| {
        std.debug.print("{d}\n", .{x});
    }
    std.debug.print("Now in reverse!\n", .{});
    while (rev_slice.next()) |x| {
        std.debug.print("{d}\n", .{x});
    }
    std.debug.print("Now in reverse, doubled!\n", .{});
    while (map_rev_slice.next()) |x| {
        std.debug.print("{d}\n", .{x});
    }
    std.debug.print("Now in reverse, doubled, enumerated AND REVERSED AGAIN!\n", .{});
    while (rev_enum_map_rev_slice.next()) |x| {
        std.debug.print("{d}\n", .{x});
    }

    const recursive = &[_][]const i32{
        &[_]i32{ 1, 2, 3 },
        &[_]i32{},
        &[_]i32{ 7, 8 },
    };
    const siter = slice_iter([]const i32, recursive);
    var flat_iter = flatten(map(siter, slice_into_iter, void{}));
    std.debug.print("Flatten\n", .{});
    while (flat_iter.next()) |x| {
        std.debug.print("{d}\n", .{x});
    }
}
