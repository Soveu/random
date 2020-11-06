
fn main() {
    let x = cfg!(target_has_atomic = "64");
    println!("{}", x);
}
