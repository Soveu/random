use std::collections::BTreeMap;
use std::io::{self, Write, BufRead, BufReader};

#[derive(Debug)]
enum ArgsplitError {
    UnexpectedEnd,
    InvalidSequence,
}

fn is_quote(c: char) -> bool {
    ['"', '\''].contains(&c)
}

fn skip_first_char<'a>(s: &'a str) -> &'a str {
    let mut chars = s.chars();
    chars.next();
    return chars.as_str();
}

fn get_arg<'a>(mut s: &'a str) -> Result<(&'a str, &'a str), ArgsplitError> {
    s = s.trim_start();

    let c = match s.chars().next() {
        None => return Ok((s, "")),
        Some(x) => x,
    };

    if c == ';' {
        let (arg, rest) = s.split_at(1);
        return Ok((rest, arg));
    }

    if is_quote(c) {
        s = skip_first_char(s);
        let n = match s.find(c) {
            None => return Err(ArgsplitError::UnexpectedEnd),
            Some(x) => x,
        };

        let (arg, rest) = s.split_at(n);
        s = skip_first_char(rest);

        return Ok((s, arg));
    }

    let next_whitespace = match s.find(char::is_whitespace) {
        None => s.len(),
        Some(x) => x,
    };
    if let Some(n) = s.find(is_quote) {
        if n < next_whitespace {
            return Err(ArgsplitError::InvalidSequence);
        }
    }

    let (arg, rest) = s.split_at(next_whitespace);
    s = rest;

    return Ok((s, arg));
}

fn argsplit<'a>(mut s: &'a str, mut args: Vec<&'a str>) -> 
    Result<(&'a str, &'a str, Vec<&'a str>), ArgsplitError> 
{
    let cmd = {
        let (_s, _arg) = get_arg(s.trim_end())?;
        s = _s;
        _arg
    };

    if cmd == ";" {
        return Ok((s, cmd, args));
    }

    while s.len() != 0 {
        let arg = {
            let (_s, _arg) = get_arg(s)?;
            s = _s;
            _arg
        };

        if arg == ";" {
            break;
        }

        args.push(arg);
    }

    return Ok((s, cmd, args));
}

type ConsoleFunction = fn(&[&str]) -> String;

fn setpos(args: &[&str]) -> String {
    if args.len() != 3 {
        return "Invalid number of arguments".to_string();
    }

    return format!("Your position has been set to {} {} {}", args[0], args[1], args[2]);
}

fn setdifficulty(args: &[&str]) -> String {
    if args.len() != 1 {
        return "Invalid number of arguments".to_string();
    }

    return format!("Difficulty has been set to {}", args[0]);
}

fn yeet(args: &[&str]) -> String {
    return format!("Yeeted {:?}", args);
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();
    let mut stdin_buf = BufReader::new(handle);
    let mut text_buffer = String::new();
    let mut commands: BTreeMap<&'static str, ConsoleFunction> = BTreeMap::new();
    commands.insert("setpos", setpos);
    commands.insert("setdifficulty", setdifficulty);
    commands.insert("yeet", yeet);

    loop {
        print!("> ");
        io::stdout().flush();

        let line = match stdin_buf.read_line(&mut text_buffer) {
            Ok(0) => break,
            Ok(n) => &text_buffer[text_buffer.len() - n ..],
            Err(e)=> {
                println!("ERROR {:?}", e);
                return;
            },
        };

        let (rest, cmd, args) = match argsplit(line, Vec::new()) {
            Ok(x) => x,
            Err(e) => {
                println!("ERROR {:?}", e);
                continue;
            },
        };

        if cmd.ends_with("?") {
            let subcmd = &cmd[..cmd.len()-1];
            for (key, _) in commands.range(subcmd..).take_while(|(key, _)| key.starts_with(subcmd)) {
                println!("{}", key);
            }
            continue;
        }

        match commands.get(cmd) {
            Some(f) => println!("{}", f(&args)),
            None => println!("No function named {:?}", cmd),
        }
    }
}

