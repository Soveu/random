#[derive(Debug, PartialEq, Eq, Clone, Copy)]
struct Fraction {
    num: i32,
    denum: i32,
}

use std::cmp::Ordering;

impl PartialOrd for Fraction {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        /* a/b - c/d = (ad - bc) / bd */
        /* a/b > c/d => (ad - bc) / bd > 0 */
        /* a/b < c/d => (ad - bc) / bd < 0 */

        let a = self.num as i64;
        let b = self.denum as i64;
        let c = other.num as i64;
        let d = other.denum as i64;

        let ad = a.wrapping_mul(d);
        let bc = b.wrapping_mul(c);
        let bd = b.wrapping_mul(d);
        let adbc = ad - bc;
        
        let x = adbc.signum() * bd.signum();
        return x.cmp(&0);
    }
}

fn calkin_wilf(mut n: u32) -> [u32; 2] {
    let mut ret = [1, 1];

    while n != 0 {
        let a = n & 1;
        let b = a ^ 1;
        ret[a as usize] += ret[b as usize];
        n = (n-1) >> 1;
    }

    return ret;
}

fn main() {
    for i in 0..10 {
        println!("{}: {:?}", i, calkin_wilf(i));
    }
}
