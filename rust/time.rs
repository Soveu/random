use std::time::{Duration, Instant};

fn main() {
    let mut v = Vec::new();
    v.resize(1024 * 1024 * 256, Instant::now());

    for x in v.iter_mut() {
        *x = Instant::now();
    }

    let mut results: Vec<_> = v.windows(2)
        .map(|w| w[1] - w[0])
        .filter(|&t| t > Duration::from_nanos(100))
        .collect();

    results.sort();
    results.truncate(results.len() * 19 / 20);
    println!("{:?}", &results[0..10]);
    println!("{:?}", &results[results.len()-10 .. results.len()]);
    println!("Median {:?}", results[results.len() / 2]);
    let sum = results.iter()
        .fold(Duration::new(0, 0), |acc, &val| acc + val);
    println!("Average {}ns", sum.as_nanos() / results.len() as u128);
}

