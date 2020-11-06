use std::time::Instant;

fn rotate_right<T>(slice: &mut [T], k: usize) {
    assert!(k <= slice.len());
    slice.reverse();
    let (front, back) = slice.split_at_mut(k);
    front.reverse();
    back.reverse();
}

fn rotate_left<T>(slice: &mut [T], k: usize) {
    let k = slice.len() - k;
    rotate_right(slice, k)
}

fn test(slice: &mut [u64], k: usize) {
    let now = Instant::now();
    slice.rotate_left(k);
    println!("slice::rotate_left = {:?}, black_box = {:?}", now.elapsed(), slice.first());

    let now = Instant::now();
    rotate_left(slice, k);
    println!("DIY rotate_left = {:?}, black_box = {:?}", now.elapsed(), slice.first());
}

fn main() {
    let pow = 10;
    let mut vec: Vec<u64> = (0..1 << (pow-1)).collect();
    vec.reserve(1 << (pow+3));

    for i in pow..pow+3 {
        let x = 1 << i;
        vec.extend(1 << (i-1) .. 1 << i);

        for j in 1..4 {
            let shift = x >> j;
            println!("2 ** {} elements, shift = {}", i, shift);
            test(&mut vec, shift);
            println!("");
        }
    }

}

