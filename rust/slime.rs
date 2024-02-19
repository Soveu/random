#![allow(unused_parens)]
#![feature(int_roundings)]

use std::ops::BitXor;

#[derive(Copy, Clone)]
#[repr(C)]
pub struct Rgb {
    r: u8,
    g: u8,
    b: u8,
}

impl Rgb {
    const VIOLET: Rgb = Rgb::from_bytes([0x88, 0x00, 0xFF]);
    const PUMPKIN: Rgb = Rgb::from_bytes([0xFF, 0x80, 0x00]);
    const BLACK: Rgb = Rgb::from_bytes([0, 0, 0]);

    const fn from_bytes(x: [u8; 3]) -> Self {
        Rgb { r: x[0], g: x[1], b: x[2] }
    }
}

type Seed = i64;

struct JavaUtilRandom {
    pub seed: Seed
}

impl JavaUtilRandom {
    const NUM_BITS: u8 = 48;
    const SEED_CONSTANT: Seed = 0x5DEECE66D;
    const SEED_MASK: Seed = (1 << Self::NUM_BITS) - 1;

    pub fn with_seed(seed: Seed) -> Self {
        let mut rng = Self { seed: 0 };
        rng.set_seed(seed);
        return rng;
    }

    pub fn next(&mut self, bits: u8) -> i32 {
        // https://developer.classpath.org/doc/java/util/Random-source.html
        let new_seed = self.seed
            .wrapping_mul(Self::SEED_CONSTANT)
            .wrapping_add(0xB) & Self::SEED_MASK;
        self.seed = new_seed;

        let ret = new_seed >> (Self::NUM_BITS - bits);
        return ret as i32;
    }

    pub fn set_seed(&mut self, seed: Seed) {
        self.seed = (seed ^ Self::SEED_CONSTANT) & Self::SEED_MASK;
    }

    pub fn next_int(&mut self, n: i32) -> i32 {
        // https://developer.classpath.org/doc/java/util/Random-source.html
        assert!(n > 0, "n must be positive");

        if (n as u32).is_power_of_two() {
            return (n * self.next(31)) >> 31;
        }

        let mut bits = self.next(31);
        let mut val = bits % n;
        while (bits + n) < (val + 1) {
            bits = self.next(31);
            val = bits % n;
        }

        return val;
    }
}

fn is_minecraft_slime_chunk(world_seed: Seed, chunk_x: i32, chunk_z: i32) -> bool {
    // https://minecraft.wiki/w/Chunk#Slime_chunks
    const A: i32 = 0x4c1906;
    const B: i32 = 0x5ac0db;
    const C: i64 = 0x4307a7i64;
    const D: i32 = 0x5f24f;
    const E: i64 = 0x3ad8025fi64;

    let x = chunk_x;
    let z = chunk_z;

    let p1: i32 = x.wrapping_mul(x).wrapping_mul(A);
    let p2: i32 = x.wrapping_mul(B);
    let p3: i64 = C.wrapping_mul(z.wrapping_mul(z) as i64);
    let p4: i32 = z.wrapping_mul(D);

    let seed = world_seed
        .wrapping_add(p1.into())
        .wrapping_add(p2.into())
        .wrapping_add(p3)
        .wrapping_add(p4.into())
        .bitxor(E);

    return JavaUtilRandom::with_seed(seed).next_int(10) == 0;
}

fn main() {
    let start_coord = (-944i32, -1360i32);
    let end_coord = (351i32, -49i32);
    const SEED: Seed = 5436860190769269733;

    println!("{:?} {:?}", start_coord, end_coord);

    let x_mul = (end_coord.0 - start_coord.0).abs() as usize;
    let z_mul = (end_coord.1 - start_coord.1).abs() as usize;
    println!("x_mul={}", x_mul);
    println!("z_mul={}", z_mul);
    let mut data = Vec::new();
    data.resize(z_mul * x_mul, Rgb::BLACK);

    for z in (start_coord.1 .. end_coord.1) {
        let pixel_z = (z - start_coord.1) as usize * x_mul;
        let chunk_z = z.div_floor(16);

        for x in (start_coord.0 .. end_coord.0) {
            let pixel_x = (x - start_coord.0) as usize;
            let chunk_x = x.div_floor(16);

            if is_minecraft_slime_chunk(SEED, chunk_x, chunk_z) {
                let pixel_index = pixel_z + pixel_x;
                data[pixel_index] = Rgb::VIOLET;
            }
        }
    }

    let pumpkins = [(-405i32, -631i32), (-400, -631), (-405, -626)];
    for (pumpkin_x, pumpkin_z) in pumpkins {
        let x = (pumpkin_x - start_coord.0) as usize;
        let z = (pumpkin_z - start_coord.1) as usize;
        let pixel_index = z * x_mul + x;
        data[pixel_index] = Rgb::PUMPKIN;
    }

    let raw_data = unsafe {
        let ptr = data.as_ptr() as *const u8;
        let len = data.len() * 3;
        std::slice::from_raw_parts(ptr, len)
    };

    std::fs::write("asdf2.data", raw_data).unwrap();
}
