use std::io::{self, Read};
use std::process::{Command, Stdio};
use std::thread;

fn main() -> io::Result<()> {
    let mut child = Command::new("./test")
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .stdin(Stdio::piped())
        .spawn()?;

    let mut outbuf = String::new();
    let mut errbuf = String::new();

    thread::sleep_ms(1000);

    if let Some(err) = child.stderr.as_mut() {
        err.read_to_string(&mut errbuf)?;
    }
    if let Some(out) = child.stdout.as_mut() {
        out.read_to_string(&mut outbuf)?;
    }

    println!("out={:?} err={:?}", outbuf, errbuf);

    println!("exit status {:?}", child.wait()?);
    Ok(())
}

