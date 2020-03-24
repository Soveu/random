use std::collections::VecDeque;

fn main() {
    let mut q = VecDeque::<i32>::new();

    for i in 0..4 {
        q.push_back(2*i);
        q.push_front(2*i + 1);
        println!("{:?}", q.as_slices());
        println!("{:?}\n", q);
    }

    for i in 0..4 {
        match q.pop_front() {
            Some(x) => {},
            None => break,
        }

        println!("{:?}", q.as_slices());
        println!("{:?}\n", q);
    }

    q.push_back(42);
    println!("{:?}", q.as_slices());
    println!("{:?}\n", q);

    q.pop_back();
    println!("{:?}", q.as_slices());
    println!("{:?}\n", q);
}

