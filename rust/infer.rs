#![feature(const_generics_defaults)]

struct Array<const N: usize = 1>([u32; N]);

impl<const N: usize> Array<N> {
    fn from_slice(_s: &[u32]) -> &Self {
        todo!();
    }
}

fn main() {
    let slice = [1u32, 2, 3, 4];
    let arr = Array::from_slice(&slice);
}
