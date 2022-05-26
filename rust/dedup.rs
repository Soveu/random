#![feature(test)]
#![feature(slice_partition_dedup)]

#![allow(unused_parens)]
#![allow(unused_variables)]

use std::ptr;
use std::hint::black_box;
use std::mem;

const ITERATIONS: usize = 1000;
const ITEMS: usize = 100_000;

#[repr(transparent)]
#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
struct DropWord(u16);

impl Drop for DropWord {
    #[inline(never)]
    fn drop(&mut self) {
        self.0 = 0;
    }
}

#[repr(transparent)]
#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
struct DropTable([u16; 64]);

/*
impl Drop for DropTable {
    #[inline(never)]
    fn drop(&mut self) {
    }
}
*/

fn time_unit() -> u64 {
    use std::arch::x86_64::_rdtsc;
    unsafe { _rdtsc() }
}

fn random_sorted_vec(mut seed: u32, len: usize) -> Vec<i16> {
    let mut ret = Vec::with_capacity(len);
    for _ in 0..len {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;

        ret.push(seed as i16);
    }

    ret.sort();
    return ret;
}

fn test() {
    let mut correct = random_sorted_vec(0x42, 1000);
    let mut tested = random_sorted_vec(0x42, 1000);
    correct.sort();
    tested.sort();

    dedup_by_old(&mut correct, |a, b| a == b);
    dedup_by_new_new(&mut tested, |a, b| a == b);
    println!("correctlen={}, testedlen={}", correct.len(), tested.len());
    assert_eq!(correct, tested);
    print!("it works\n");
}

fn main() {
    test();

    /*
    let mut nondup: Vec<_> = (0..65535u32 * 8)
        //.map(|x| DropTable([x; 64]))
        .collect();

    //nondup.insert(0, DropTable([0; 64]));
    //nondup.insert(0, 0);

    let begin = time_unit();
    for iteration in 0..1000 {
        dedup_by_old(&mut nondup, |a, b| a == b);
        black_box(nondup.first());
    }
    let end = time_unit();
    let old_time = end - begin;

    //nondup.insert(0, DropTable([0; 64]));
    //nondup.insert(0, 0);

    let begin = time_unit();
    for iteration in 0..1000 {
        dedup_by_new_new(&mut nondup, |a, b| a == b);
        black_box(nondup.first());
    }
    let end = time_unit();
    let new_time = end - begin;
    
    print!("No duplicates - New-Old-Ratio: {}\n",
        (new_time as f32) / (old_time as f32));
    */

    let mut total_old_time = 0;
    for iteration in 0..ITERATIONS {
        let mut vec = random_sorted_vec(0x42, ITEMS);
        let begin = time_unit();
        dedup_by_old(&mut vec, |a, b| a == b);
        black_box(vec.first());
        let end = time_unit();
        total_old_time += (end - begin);
    }

    let mut total_new_time = 0;
    for iteration in 0..ITERATIONS {
        let mut vec = random_sorted_vec(0x42, ITEMS);
        let begin = time_unit();
        dedup_by_new_new(&mut vec, |a, b| a == b);
        black_box(vec.first());
        let end = time_unit();
        total_new_time += (end - begin);
    }

    print!("Some duplicates - New-Old-Ratio: {}\n",
        (total_new_time as f32) / (total_old_time as f32));

    let mut total_old_time = 0;
    for iteration in 0..ITERATIONS {
        let mut vec = vec![0u16; ITEMS];
        let begin = time_unit();
        dedup_by_old(&mut vec, |a, b| a == b);
        black_box(vec.first());
        let end = time_unit();
        total_old_time += (end - begin);
    }

    let mut total_new_time = 0;
    for iteration in 0..ITERATIONS {
        let mut vec = vec![0u16; ITEMS];
        let begin = time_unit();
        dedup_by_new_new(&mut vec, |a, b| a == b);
        black_box(vec.first());
        let end = time_unit();
        total_new_time += (end - begin);
    }

    print!("All duplicates - New-Old-Ratio: {}\n",
        (total_new_time as f32) / (total_old_time as f32));
}

#[inline(never)]
pub fn dedup_by_old<T, F>(seif: &mut Vec<T>, same_bucket: F)
where
    F: FnMut(&mut T, &mut T) -> bool,
{
    let len = {
        let (dedup, _) = seif.as_mut_slice().partition_dedup_by(same_bucket);
        dedup.len()
    };
    seif.truncate(len);
}

#[inline(never)]
pub fn dedup_by_new<T, F>(seif: &mut Vec<T>, mut same_bucket: F)
where
    F: FnMut(&mut T, &mut T) -> bool,
{
    let len = seif.len();
    if len <= 1 {
        return;
    }

    let ptr = seif.as_mut_ptr();
    let mut read: usize = 1;
    let mut write: usize = 1;
   
    /* Drop items while going through Vec, it should be more efficient than
     * doing slice dedup + truncate */
    unsafe {
        while read < len {
            let read_ptr = ptr.add(read);
            let prev_ptr = ptr.add(write.wrapping_sub(1));

            if same_bucket(&mut *read_ptr, &mut *prev_ptr) {
                /* We have found duplicate, drop it in-place */
                ptr::drop_in_place(read_ptr);
            } else {
                let write_ptr = ptr.add(write);

                /* Looks like doing just a copy can be faster than
                 * conditional `copy_nonoverlapping` */
                ptr::copy(read_ptr, write_ptr, 1);

                write += 1;
            }

            read += 1;
        }

        seif.set_len(write);
    }
}


#[inline(never)]
pub fn dedup_by_new_new<T, F>(seif: &mut Vec<T>, mut is_dupe: F)
where
    F: FnMut(&mut T, &mut T) -> bool,
{
    let len = seif.len();
    if len == 0 {
        return;
    }

    unsafe {
        seif.set_len(1);

        let ptr = seif.as_mut_ptr();
        let mut read: usize = 1;
        let mut hole: usize = 1;

        'outer: loop {
            if read >= len {
                break 'outer;
            }

            while is_dupe(&mut *ptr.add(hole-1), &mut *ptr.add(read)) {
                ptr::drop_in_place(ptr.add(read));
                read += 1;

                if read == len {
                    break 'outer;
                }
            }

            let copy_begin = read;
            read += 1;

            while read != len && !is_dupe(&mut *ptr.add(read-1), &mut *ptr.add(read)) {
                read += 1;
            }

            let copy_len = read - copy_begin;
            ptr::copy(ptr.add(copy_begin), ptr.add(hole), copy_len);
            hole += copy_len;
        }

        seif.set_len(hole);
    }
}

