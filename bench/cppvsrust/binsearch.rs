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
    
    let mut set = Vec::with_capacity(n);
    for s in it.by_ref().take(n) {
        set.push(s);
    }
    set.sort_unstable();

    println!("Inserted elements - {:?}", now.elapsed());
    println!("Number of elements: {}", set.len());

    let mut hits = 0u32;
    let n: usize = it.next().unwrap()
        .parse().expect("Invalid number of checks");

    for s in it.take(n) {
        let contains = set.binary_search(&s).is_ok();
        hits += contains as u32;
    }

    println!("Hits: {}", hits);
    println!("Finished ({:?})", now.elapsed());
}

