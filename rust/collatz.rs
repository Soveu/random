const STEPS: usize = 8;
const N: usize = 1 << STEPS;

fn step(x: [usize; 2]) -> [usize; 2] {
    return if x[1] % 2 == 0 {
        if x[0] % 2 != 0 {
            eprintln!("Error: {:?}", x);
            panic!();
        }
        [x[0] / 2, x[1] / 2]
    } else {
        [x[0] * 3, x[1] * 3 + 1]
    };
}

fn main() {
    for i in 1..N {
        let mut x = [N, i];
        print!("{:?}", x);

        for _ in 0..STEPS {
            x = step(x);
        }

        println!(" -> {:?}", x);
    }
}

