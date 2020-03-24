use std::borrow::Cow;

fn main() {
    let mut x1: Cow<str> = Cow::Owned("asdf".to_string());
    let x2: Cow<str> = Cow::Borrowed(&x1);

    println!("{:?} {:?}", x1, x2);

    x1.to_mut().push_str("qwerty");
    println!("{:?} {:?}", x1, x2);
}

