use std::sync::atomic::{Ordering, AtomicBool, AtomicU64};
use std::thread;
use std::time::Duration;

const THREADS: u64 = 1;
static HAS_PANICED: AtomicBool = AtomicBool::new(false);
static COUNTER: AtomicU64 = AtomicU64::new(0);

fn thread_start() {
    while !HAS_PANICED.load(Ordering::Relaxed) {
        COUNTER.fetch_add(1, Ordering::Relaxed);
        std::hint::spin_loop();
    }
}

fn main() {
    let threads: Vec<_> = (0..THREADS)
        .map(|_| thread::spawn(thread_start))
        .collect();

    thread::sleep(Duration::from_secs(2));
    HAS_PANICED.store(true, Ordering::Relaxed);

    threads.into_iter().for_each(|t| t.join().unwrap());

    /*
    let sum: u64 = threads
        .into_iter()
        .map(thread::JoinHandle::join)
        .map(Result::unwrap)
        .map(|x| x / THREADS / 1024 / 1024)
        .sum();

    println!("{:?}", sum);
    */
    println!("{:?}", COUNTER.load(Ordering::Relaxed) / 1024 / 1024);
}
