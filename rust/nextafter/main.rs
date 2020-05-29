fn step_f64(x: f64, step: i32) -> f64 {
    if x.is_nan() || x.is_infinite() {
        return x;
    }

    let bits = x.to_bits();
    let step = step as i64;
    let bits = bits as i64 + step;
    f64::from_bits(bits as u64)
}

fn step_f32(x: f32, step: i32) -> f32 {
    if x.is_nan() || x.is_infinite() {
        return x;
    }

    let bits = x.to_bits();
    let bits = bits as i32 + step;
    f32::from_bits(bits as u32)
}

fn main() {
    let mut x: f32 = 1.0;
    x = step_f32(x, 1 << 24 - 1);

    for i in 0..10 {
        println!("{}: {:.16}", i, x);
        x = step_f32(x, 1);
    }
}

