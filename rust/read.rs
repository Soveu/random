use std::io::{self, Read};
use std::{thread, time};

fn main() {
    let stdin = io::stdin();
    let mut stdin_handle = stdin.lock();
    let mut buffer = vec![0 as u8; 8192];
    let mut input = String::new();
    
    let second = time::Duration::from_secs(1);
    loop {
        match stdin_handle.read_to_string(&mut input) {
            Ok(n) => println!("Read {} bytes", n),
            Err(e) => {},
        }
        thread::sleep(second);
    }
}

