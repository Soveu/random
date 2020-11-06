#![feature(untagged_unions)]

#[repr(C)]
#[derive(Clone, Copy)]
struct RawPtr<T> {
    ptr: *const T,
    len: usize,
}

union FatPtr<T> {
    rust: *const [T],
    rust_mut: *mut [T],
    raw: RawPtr<T>,
}

fn main() {
}

