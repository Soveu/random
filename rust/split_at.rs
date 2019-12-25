fn main() {
    let s = "asdfg";
    let (a, b) = s.split_at(2);
    println!("{}:{}", a, b);
}
