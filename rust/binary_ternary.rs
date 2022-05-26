#![feature(bench_black_box)]

fn xorshift(mut x: u32) -> u32 {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

fn generate_input(mut preallocated_vec: Vec<u32>, mut seed: u32) -> Vec<u32> {
    let iter = std::iter::repeat_with(move || { seed = xorshift(seed); seed });
    let capacity = preallocated_vec.capacity();

    preallocated_vec.clear();
    preallocated_vec.extend(iter.take(capacity));

    return preallocated_vec;
}

fn main() {
    let mut seed = 0xDEADBEEF;

    let start = std::time::Instant::now();
    let vec = Vec::with_capacity(1_000_000);
    println!("Allocating {:?}", start.elapsed());

    let start = std::time::Instant::now();
    let mut input = generate_input(vec, seed);
    println!("Generating random numbers {:?}", start.elapsed());

    let start = std::time::Instant::now();
    input.sort_unstable();
    println!("Sorting {:?}", start.elapsed());

    let start = std::time::Instant::now();
    for _ in 0..100 {
        std::hint::black_box(input.binary_search(&seed));
        seed = xorshift(seed);
    }
    println!("Doing binary search 100 times {:?}", start.elapsed());
}
