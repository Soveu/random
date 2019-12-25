#![allow(non_snake_case)]

struct PrimeSieve {
    primes: Vec::<u128>,
    currentPrime: u128,
}

impl PrimeSieve {
    fn new() -> PrimeSieve {
        return PrimeSieve{currentPrime: 2, primes: Vec::new()};
    }
    fn with_capacity(n: usize) -> PrimeSieve {
        return PrimeSieve{currentPrime: 2, primes: Vec::with_capacity(n)};
    }
}

fn __helper_isPrime(x: u128, primes: &Vec::<u128>) -> bool {
    for prime in primes {
        if x % prime == 0 {
            return false;
        }
    }

    return true;
}

impl Iterator for PrimeSieve {
    type Item = u128;
    fn next(self: &mut Self) -> Option::<Self::Item> {
        let res = self.currentPrime;
        self.primes.push(res);
        let mut num = res;

        loop {
            num += 1;
            if __helper_isPrime(num, &self.primes) {
                self.currentPrime = num;
                return Some(res);
            }
        }
    }
}

struct TwinPrimeSieve {
    primeIterator: PrimeSieve,
    prevPrime: u128,
}

impl TwinPrimeSieve {
    fn new() -> TwinPrimeSieve {
        return TwinPrimeSieve{primeIterator: PrimeSieve::new(), prevPrime: 1};
    }
}

impl Iterator for TwinPrimeSieve {
    type Item = (u128, u128);
    fn next(self: &mut Self) -> Option::<Self::Item> {
        for p in &mut self.primeIterator {
            let t = self.prevPrime;
            self.prevPrime = p;
            if p - t == 2 {
                return Some((t, p));
            }
        }

        return None;
    }
}

fn main() {
    /*
    let mut ps = PrimeSieve::new();
    for p in ps.take(20) {
        println!("{}", p);
    }
*/

    let mut tps = TwinPrimeSieve::new();
    for (a, _) in tps.take(999) {
        println!("{}", a);
    }
}

