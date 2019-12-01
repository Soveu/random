extern crate rand;
use rand::{Rng, SeedableRng};
use rand::rngs::SmallRng;
use rand::seq::SliceRandom;

use std::time;

fn is_list_correct(v: &Vec<usize>) -> bool {
    for (i, item) in v.iter().enumerate() {
        if *item == i {
            return false;
        }
    }

    return true;
}

fn secret_santa(n: usize) -> Vec<usize> {
    let mut rng = SmallRng::seed_from_u64(0);
    let mut people: Vec<usize> = (0..n).collect();

    for i in 0..n-1 {
        let mut j = rng.gen_range(i, n);

        while people[j] == i {
            j = rng.gen_range(i, n);
        }

        let tmp = people[i];
        people[i] = people[j];
        people[j] = tmp;
    }

    /* Does it change the probability of a certain permutation? */
    if people[n-1] == n-1 {
        let i = rng.gen_range(0, n-1);
        let tmp = people[n-1];
        people[n-1] = people[i];
        people[i] = tmp;
    }

    return people;
}

fn main() {
    let start = time::Instant::now();
    let _result = secret_santa(1024);
    println!("{}", start.elapsed().as_millis())
}

