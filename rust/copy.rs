use std::ptr;

/* SAFETY:
 * offset < init
 * ptr points to a buffer large enough (init+len)
 * ptr[..init] is initialized */
pub unsafe fn lz4_extend_unchecked(
    ptr: *mut u8,
    init: usize,
    offset: usize,
    len: usize)
{
    let mut to_write = len;
    let mut avaliable = init.wrapping_sub(offset);

    let src = ptr.add(offset);
    let mut dst = ptr.add(init);
    let src = src as *const u8;

    if avaliable == 1 {
        return ptr::write_bytes(dst, *src, len);
    }

    while to_write > avaliable {
        ptr::copy_nonoverlapping(src, dst, avaliable);
        dst = dst.add(avaliable);
        to_write -= avaliable;
        avaliable *= 2;
    }

    return ptr::copy_nonoverlapping(src, dst, to_write);
}

fn main() {
    let mut buf = [0u8; 16];
    buf[0] = 1;
    buf[1] = 2;

    unsafe {
        let ptr = buf.as_mut_ptr();
        let init = 2usize;
        let offset = 0usize;
        let len = 8usize;

        lz4_extend_unchecked(ptr, init, offset, len);
    }

    println!("{:?}", buf);
}
