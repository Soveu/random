#![feature(asm)]

fn rdtscp() -> (u64, u32) {
    let high: u32;
    let low: u32;
    let aux: u32;

    unsafe {
        asm!("rdtscp",
            out("edx") high,
            out("eax") low,
            out("ecx") aux,
            options(nomem, nostack),
        )
    }

    let timestamp: u64 = (high as u64) << 32;
    let timestamp = timestamp | (low as u64);
    (timestamp, aux)
}

fn main() {
    let (timestamp, aux) = rdtscp();
    println!("{:?}", aux);
}
