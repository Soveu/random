use std::collections::HashSet;
use std::io::{self, Read};
use std::time::{Instant};

fn read_all_input() -> String {
    let mut buffer = Vec::new();
    io::stdin().read_to_end(&mut buffer).expect("failed to read stdin");
    return unsafe { String::from_utf8_unchecked(buffer) };
}

fn main() {
    let now = Instant::now();
    let input = read_all_input();
    let mut it = input.split_ascii_whitespace();

    let n: usize = it.next().unwrap()
        .parse().expect("Invalid number of elements");

    println!("Inserting entries ({:?})", now.elapsed());
    let mut set = HashSet::new();
    for _ in 0..n {
        let s = it.next().expect("Unexpected EOF");
        set.insert(s);
    }

    println!("Number of elements: {}", set.len());
    println!("Checking entries ({:?})", now.elapsed());

    let mut hits = 0u32;
    let mut misses = 0u32;
    let n: usize = it.next().unwrap()
        .parse().expect("Invalid number of checks");

    for _ in 0..n {
        let s = it.next().expect("Unexpected EOF");
        let contains = set.contains(s);
        hits += contains as u32;
        misses += !contains as u32;
    }

    println!("Hits: {}, Misses: {}", hits, misses);
    println!("Finished ({:?})", now.elapsed());
}

