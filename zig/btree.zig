const std = @import("std");
const testing = std.testing;

const B: usize = 2;
const TWO_B = B * 2;

const BinarySearchResult = struct {
    found: bool,
    index: usize,
};

fn binary_search(
    comptime T: type,
    items: []const T,
    key: T,
) BinarySearchResult {
    var size: usize = items.len;
    var left: usize = 0;
    var right: usize = size;

    while (left < right) {
        const mid = left + size / 2;

        switch (std.math.order(items[mid], key)) {
            .lt => left = mid + 1,
            .gt => right = mid,
            .eq => return BinarySearchResult{
                .found = true,
                .index = mid,
            },
        }

        size = right - left;
    }

    return BinarySearchResult{
        .found = false,
        .index = left,
    };
}

test "binary_search" {
    try testing.expectEqual(
        BinarySearchResult{ .found = false, .index = 0 },
        binary_search(i32, &[_]i32{}, 42),
    );
    try testing.expectEqual(
        BinarySearchResult{ .found = true, .index = 0 },
        binary_search(i32, &[_]i32{42}, 42),
    );
    try testing.expectEqual(
        BinarySearchResult{ .found = true, .index = 1 },
        binary_search(i32, &[_]i32{ 1, 42 }, 42),
    );
    try testing.expectEqual(
        BinarySearchResult{ .found = false, .index = 1 },
        binary_search(i32, &[_]i32{ 1, 43 }, 42),
    );
}

const Key = i32;
const Value = []const u8;

const Node = struct {
    parent: ?*Node,
    size: usize,
    keys: [TWO_B]Key,
    values: [TWO_B]Value,
    edges: [TWO_B + 1]*Node,
};
const NEW_NODE = Node{
    .parent = null,
    .size = 0,
    .keys = undefined,
    .values = undefined,
    .edges = undefined,
};

const Root = struct {
    node: Node,

    fn search(self: *const Root, item: *i32) bool {
        _ = self;
        _ = item;
    }
    fn insert(self: *Root, item: i32) void {
        _ = self;
        _ = item;
    }
    fn remove(self: *Root, item: *i32) ?i32 {
        _ = self;
        _ = item;
    }
};

const OccupiedEntry = void;
const VacantEntry = void;

const Entry = union(enum) {
    occupied: OccupiedEntry,
    vacant: VacantEntry,
};
