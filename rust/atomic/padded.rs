use std::sync::{Arc, Barrier};
use std::thread;
use std::sync::atomic::{Ordering, AtomicU64};

#[repr(align(64))]
#[derive(Debug)]
struct PaddedAtomicU64 {
    value: AtomicU64,
}

impl PaddedAtomicU64 {
    fn new(x: u64) -> Self {
        Self{value: AtomicU64::new(x)}
    }
}

unsafe impl Send for PaddedAtomicU64 {}
unsafe impl Sync for PaddedAtomicU64 {}

const THREADS: usize = 8;
const ITERATIONS: usize = 40_000_000;

fn main() {
    let counters = Arc::new([PaddedAtomicU64::new(0), PaddedAtomicU64::new(0)]);
    let mut handles = Vec::with_capacity(THREADS);
    let barrier = Arc::new(Barrier::new(THREADS));

    for _ in 0..THREADS {
        let b = barrier.clone();
        let c = counters.clone();

        handles.push(thread::spawn(move || {
            b.wait();

            for _ in 0..ITERATIONS {
                c[0].value.fetch_add(1, Ordering::Relaxed);
                c[1].value.fetch_add(1, Ordering::Relaxed);
            }
        }));
    }

    // Wait for other threads to finish.
    for handle in handles {
        handle.join().unwrap();
    }

    println!("{} {}", counters[0].value.load(Ordering::SeqCst), counters[1].value.load(Ordering::SeqCst));
}

