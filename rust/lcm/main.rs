use std::time::Instant;

/*
struct Pcg32 {
    state:  u64,
    inc:    u64,
}

impl Pcg32 {
    fn new() -> Self {
        Pcg32{state: 0, inc: 0}
    }
    fn random_u32(self: &mut Self) -> u32 {
        let oldstate: u64 = self.state;
        self.state = oldstate.wrapping_mul(6364136223846793005).wrapping_add(self.inc | 1);
        let xorshifted: u32 = (oldstate.rotate_right(18) ^ oldstate).rotate_right(27) as u32;
        let rot: u32 = oldstate.rotate_right(59) as u32;
        return xorshifted.rotate_right(rot) | xorshifted.rotate_left(((!rot).wrapping_add(1)) & 31);
    }
}

fn make_rand_vec(n: usize) -> Vec::<i64> {
    let mut rng = Pcg32::new();
    let mut ret = Vec::new();

    ret.resize(n, 0);
    
    for x in ret.iter_mut() {
        *x = (rng.random_u32() & 0xFF) as i64;
        *x += 1;
    }

    return ret;
}
*/

fn gcd2(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let c = b;
        b = a % b;
        a = c
    }

    return a;
}        

fn lcm2(a: i64, b: i64) -> i64 {
    return (a / gcd2(a, b)) * b;
}

fn lcm_it(v: &[i64]) -> i64 {
    let mut it = v.iter();
    let mut ret = *it.next().unwrap();

    for x in it {
        ret = lcm2(ret, *x);
    }

    return ret;
}

fn lcm_rec(v: &[i64]) -> i64 {
    match v.len() {
        0 => panic!("v.len() == 0"),
        1 => v[0],
        2 => lcm2(v[0], v[1]),
        _ => {
            let (first, second) = v.split_at(v.len() / 2);
            lcm2(lcm_rec(first), lcm_rec(second))
        }
    }
}

fn make_nonrand_vec(n: usize) -> Vec::<i64> {
    let mut ret = Vec::new();
    ret.resize(n, 17);
    return ret;
}

fn main() {
    let x = make_nonrand_vec(1 << 26);

    let now = Instant::now();
    println!("lcm_it  {}, time elapsed: {}", lcm_it(&x), now.elapsed().as_millis());
    let now = Instant::now();
    println!("lcm_rec {}, time elapsed: {}", lcm_rec(&x), now.elapsed().as_millis());
}

