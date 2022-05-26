use std::mem;

const unsafe fn mod_inv(x: usize, m: usize) -> usize {
}

pub unsafe fn ptr_align_offset<T: Sized>(p: *const T, requested_align: usize) -> usize {
}

pub unsafe fn align_to<T, U>(s: &[T]) -> (&[T], &[U], &[T]) {
    let ptr = s.as_ptr() as usize;
    let mask = mem::align_of::<U>().wrapping_sub(1);

    if ptr & mask != ptr {
        /* ptr is not aligned */
        todo!();
    }
}
