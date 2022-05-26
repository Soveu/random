use std::process::{Command, Child};
use std::error::Error;
use std::fmt::Write;
use std::fs::File;
use std::io::Read;

fn main() -> Result<(), Box<dyn Error>> {
    let mut child = Command::new("xxd")
        .args(&["-"])
        .spawn()?;

    let pid = child.id();

    let mut sbuf = String::with_capacity(4096);

    write!(sbuf, "/proc/{}/maps", pid)?;
    let mut maps = File::open(&sbuf)?;

    sbuf.clear();
    write!(sbuf, "/proc/{}/mem", pid)?;
    let mem = File::open(&sbuf)?;

    sbuf.clear();
    maps.read_to_string(&mut sbuf)?;
    println!("{}", sbuf);

    let _ = child.kill();

    Ok(())
}
