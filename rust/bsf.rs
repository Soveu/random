#![feature(asm)]

fn main() {
    let flags1: u32;
    let flags2: u32;
    let result: u32;

    unsafe {
        asm!(
            "lahf", 
            "movzx eax, ah",
            out("eax") flags1,
            options(nostack, nomem)
        );

        asm!(
            "mov edi, 0",
            "bsf edi, edi",
            "lahf", 
            "movzx eax, ah",
            out("edi") result,
            out("eax") flags2,
            options(nostack, nomem)
        );
    }

    let flagsdiff = flags2 ^ flags1;
    let zero_flag = 1 << 6;

    println!("result={}", result);
    assert_eq!(flagsdiff, zero_flag);
}
