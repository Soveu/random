use std::collections::BTreeSet;
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

    println!("Read input - {:?}", now.elapsed());

    let mut set = BTreeSet::new();
    for _ in 0..n {
        let s = it.next().expect("Unexpected EOF");
        set.insert(s);
    }

    println!("Inserted elements - {:?}", now.elapsed());
    println!("Number of elements: {}", set.len());

    let mut hits = 0u32;
    let n: usize = it.next().unwrap()
        .parse().expect("Invalid number of checks");

    for _ in 0..n {
        let s = it.next().expect("Unexpected EOF");
        let contains = set.contains(s);
        hits += contains as u32;
    }

    println!("Hits: {}", hits);
    println!("Finished ({:?})", now.elapsed());
}

