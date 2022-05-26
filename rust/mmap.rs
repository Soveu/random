#![feature(allocator_api)]
#![allow(unused_unsafe)]

use libc::{mmap, mprotect, munmap, mremap, PROT_READ, PROT_WRITE, PROT_EXEC, 
    PROT_NONE, MAP_SHARED, MAP_PRIVATE, MAP_ANONYMOUS, MAP_NORESERVE, MAP_FIXED, MAP_POPULATE,
    MREMAP_MAYMOVE, MAP_SHARED_VALIDATE};
use core::alloc::{Layout, AllocError, Allocator};
use core::ptr::{self, NonNull};

pub struct MmapAllocator;

fn round_to_page(x: usize) -> usize {
    if x % 4096 == 0 {
        return x;
    }

    return (x / 4096 + 1) * 4096;
}

unsafe impl Allocator for MmapAllocator {
    fn allocate(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        assert!(layout.align() <= 4096, "Cannot guarantee larger alignment than 4096");

        let prot = PROT_READ | PROT_WRITE;
        let flags = MAP_ANONYMOUS | MAP_NORESERVE;
        let size = round_to_page(layout.size());

        unsafe {
            let ptr = mmap(ptr::null_mut(), size, prot, flags, -1, 0) as *mut u8;
            let slice = ptr::slice_from_raw_parts_mut(ptr, size);
            return NonNull::new(slice).ok_or(AllocError);
        }
    }

    unsafe fn deallocate(&self, ptr: NonNull<u8>, layout: Layout) {
        unsafe {
            munmap(ptr.as_ptr() as *mut _, layout.size());
        }
    }

    fn allocate_zeroed(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        self.allocate(layout)
    }

    unsafe fn grow(
        &self,
        ptr: NonNull<u8>,
        old_layout: Layout,
        new_layout: Layout
    ) -> Result<NonNull<[u8]>, AllocError>
    {
        assert!(new_layout.align() <= 4096, "Cannot guarantee larger alignment than 4096");

        let flags = MREMAP_MAYMOVE;
        unsafe {
            let ptr = mremap(ptr.as_ptr() as *mut _, old_layout.size(), new_layout.size(), flags) as *mut u8;
            let slice = ptr::slice_from_raw_parts_mut(ptr, new_layout.size());
            return NonNull::new(slice).ok_or(AllocError);
        }
    }

    unsafe fn grow_zeroed(
        &self,
        ptr: NonNull<u8>,
        old_layout: Layout,
        new_layout: Layout
    ) -> Result<NonNull<[u8]>, AllocError>
    {
        self.grow(ptr, old_layout, new_layout)
    }

    unsafe fn shrink(
        &self,
        ptr: NonNull<u8>,
        old_layout: Layout,
        new_layout: Layout
    ) -> Result<NonNull<[u8]>, AllocError>
    {
        assert!(new_layout.align() <= 4096, "Cannot guarantee larger alignment than 4096");

        let flags = MREMAP_MAYMOVE;
        unsafe {
            let ptr = mremap(ptr.as_ptr() as *mut _, old_layout.size(), new_layout.size(), flags) as *mut u8;
            let slice = ptr::slice_from_raw_parts_mut(ptr, new_layout.size());
            return NonNull::new(slice).ok_or(AllocError);
        }
    }
}

use std::fs::File;
use std::os::unix::io::AsRawFd;

pub fn try_mmap_file(f: &File) -> Option<Box<[u8], MmapAllocator>> {
    let metadata = match f.metadata() {
        Ok(x) => x,
        Err(_) => return None,
    };

    let filelen = metadata.len();
    if filelen > usize::MAX as u64 {
        return None;
    }
    let filelen = filelen as usize;

    let fd = f.as_raw_fd();
    let prot = PROT_READ | PROT_WRITE;
    let flags = MAP_SHARED_VALIDATE | MAP_NORESERVE;

    unsafe {
        let ptr = mmap(ptr::null_mut(), filelen, prot, flags, fd, 0) as *mut u8;

        if ptr.is_null() {
            return None;
        }

        let slice = ptr::slice_from_raw_parts_mut(ptr, filelen);
        return Some(Box::from_raw_in(slice, MmapAllocator));
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let f = File::open("/proc/self/mem")?;
    let map = try_mmap_file(&f).unwrap();
    let ptr = &*map as *const [u8] as *const u8 as usize;
    println!("{:?}", &map[ptr..ptr+4096]);
}

