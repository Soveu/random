#![feature(iter_partition_in_place)]

fn main() {
    let mut v: Vec<i64> = Vec::new();
    for _ in 0..10000 {
        v.resize(1000, 0);
        for (i, x) in v.iter_mut().enumerate() {
            *x = i as _;
        }

        let x = v.iter_mut().partition_in_place(|x| x%4 != 0);
        v.truncate(x);
    }
    println!("{:?}", v);
}

