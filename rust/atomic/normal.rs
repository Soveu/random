use std::sync::{Arc, Barrier};
use std::thread;
use std::sync::atomic::{Ordering, AtomicU64};

const THREADS: usize = 8;
const ITERATIONS: usize = 40_000_000;

fn main() {
    let counters = Arc::new([AtomicU64::new(0), AtomicU64::new(0)]);
    let mut handles = Vec::with_capacity(THREADS);
    let barrier = Arc::new(Barrier::new(THREADS));

    for _ in 0..THREADS {
        let b = barrier.clone();
        let c = counters.clone();

        handles.push(thread::spawn(move || {
            b.wait();

            for _ in 0..ITERATIONS {
                c[0].fetch_add(1, Ordering::Relaxed);
                c[1].fetch_add(1, Ordering::Relaxed);
            }
        }));
    }

    // Wait for other threads to finish.
    for handle in handles {
        handle.join().unwrap();
    }

    println!("{} {}", counters[0].load(Ordering::SeqCst), counters[1].load(Ordering::SeqCst));
}

