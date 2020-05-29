use std::ffi::*;

/*
fn f1() {
    let s = "Hello World!\0".to_string();
    assert!(s.chars().last().unwrap() == '\0');
    println!("{:?}", CString::new(s));
    println!("{:?}", s);
}
*/

fn main() {
    println!("{:?}", CStr::from_bytes_with_nul(b"Hello World!\0"));
    println!("{:?}", CStr::from_bytes_with_nul(b"Hello World!\0\0\0\0"));

    let s = "Hell\0 World!".to_string();
    println!("{:?}", OsString::from(s));
}
