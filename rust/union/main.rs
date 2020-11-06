#[derive(Clone, Copy)]
union U {
    a: [u8; 8],
    b: u64,
}

impl U {
    fn get_a(self) -> [u8; 8] {
        unsafe { self.a }
    }

    fn get_b(self) -> u64 {
        unsafe { self.b }
    }
}

fn main() {
    let u: U = U { a: [0, 1, 2, 3, 4, 5, 6, 7] };
    println!("{:?}", u.get_a());
    println!("{:?}", u.get_b());
}
