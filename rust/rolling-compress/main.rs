#[repr(C)]
#[derive(Clone, Copy, Debug)]
struct RollingInfo {
    repeat: u8,
    byte:   u8,
}

fn rolling_compress(slice: &[u8]) -> Vec<RollingInfo> {
    let mut vec = Vec::new();

    if slice.len() == 0 {
        return vec;
    }

    let mut it = slice.iter();
    let mut info = RollingInfo{
        repeat: 1,
        byte: it.next().copied().unwrap(),
    };

    for &x in it {
        if x == info.byte {
            info.repeat = info.repeat.wrapping_add(1);
            if info.repeat != 0 { continue; }
            info.repeat = info.repeat.wrapping_sub(1);
        }

        vec.push(info);
        info.byte = x;
        info.repeat = 1;
    }

    vec.push(info);
    return vec;
}

fn main() {
    let bytes = [0u8; 300];
    println!("{:?}", rolling_compress(&bytes));
}

