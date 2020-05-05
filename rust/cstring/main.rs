use std::ffi::*;

fn main() {
    let s = "Hello World!\0".to_string();
    assert!(s.chars().last().unwrap() == '\0');
    println!("{:?}", CString::new(s));
    println!("{:?}", s);
}

