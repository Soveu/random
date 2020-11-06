#![feature(asm)]
#![feature(test)]

#[inline(always)]
fn rep_movsb(src: &[u8], dst: &mut [u8]) {
    unsafe {
        asm!(
            "rep movsb [rdi], [rsi]",
            inout("rdi") dst.as_mut_ptr() => _,
            inout("rsi") src.as_ptr() => _,
            inout("rcx") src.len() => _,
            options(nostack, preserves_flags),
        );
    }
}

#[inline(always)]
fn rep_movsq(src: &[u8], dst: &mut [u8]) {
    let count = src.len();
    let qword_count = count >> 3;
    let byte_count = count & 0b111;

    unsafe {
        asm!(
            "rep movsq [rdi], [rsi]",
            "mov ecx, {byte_count:e}",
            "rep movsb [rdi], [rsi]",
            byte_count = in(reg) byte_count,
            inout("rcx") qword_count => _,
            inout("rdi") dst.as_mut_ptr() => _,
            inout("rsi") src.as_ptr() => _,
            options(nostack, preserves_flags)
        );
    }
}

#[inline(always)]
fn rdtsc() -> u64 {
    unsafe { core::arch::x86_64::_rdtsc() }
}

fn main2() {
    const N: usize = 1024 * 1024 * 2;
    let src = vec![42; N];
    let mut dst = vec![0; N];

    let repeat = 500;

    for offset in (0..64).step_by(1) {
        for chunk in (4..1024).step_by(1) {
            let s = &src[..chunk];
            let d = &mut dst[offset .. offset+chunk];

            let now = rdtsc();
            for _ in 0..repeat { 
                rep_movsb(s, d);
                rep_movsb(s, d);
                rep_movsb(s, d);
                rep_movsb(s, d);
            }

            let time = rdtsc() - now;
            let time = time as f64 / (repeat * chunk) as f64;
            println!("{} {} {}", offset, chunk, time / 4.0);
        }
    }
}

fn main() {
    const N: usize = 1024 * 1024 * 2;
    let src = vec![42; N];
    let mut dst = vec![0; N];

    let repeat = 500;
    let chunk = 0x1000;

    for x in (0..128).step_by(1) {
        for y in (0..128).step_by(1) {
            let s = &src[x .. x+chunk];
            let mut d = &mut dst[y .. y+chunk];

            use std::hint::black_box;

            let now = rdtsc();
            for _ in 0..repeat { 
                d.copy_from_slice(s);
                d = black_box(d);
                d.copy_from_slice(s);
                d = black_box(d);
                d.copy_from_slice(s);
                d = black_box(d);
                d.copy_from_slice(s);
                d = black_box(d);
            }

            let time = rdtsc() - now;
            let time = time as f64 / (repeat * chunk) as f64;
            println!("{} {} {}", x, y, time / 4.0);
        }
    }
}

