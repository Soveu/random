use std::env::args;
use rand_pcg::Pcg32;
use rand::Rng;
use std::io::{self, Write, BufWriter};

const ALPHABET: &str = 
    "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";

fn make_random_str(mut s: String, n: usize, rng: &mut Pcg32, alphabet: &[char]) -> String {
    s.clear();

    for _ in 0..n {
        let n = rng.gen_range(0, alphabet.len());
        s.push(alphabet[n]);
    }

    return s;
}

fn get_args() -> [usize; 3] {
    let mut ret = [0; 3];
    let args: Vec<_> = args().skip(1).take(3).collect();
    assert!(args.len() == 3, "Usage: ./exe ENTRIES TESTS STRLEN");

    for i in 0..3 {
        ret[i] = args[i].parse().expect("argument is not a number");
    }

    return ret;
}

fn main() {
    let stdout = io::stdout();
    let stdout = stdout.lock();
    let mut stdout = BufWriter::new(stdout);

    let [entries, tests, strlen] = get_args();
    let alphabet: Vec<char> = ALPHABET.chars().collect();
    let mut s = String::with_capacity(65536 * 4);
    let mut rng = [Pcg32::new(0xcafef00dd15ea5e5, 0xa02bdbf7bb3c0a7), Pcg32::new(0xDEADBEEF, 0xC0FFEE)];

    writeln!(&mut stdout, "{}", entries).expect("IO Error");
    for _ in 0..entries {
        let n: usize = rng[0].gen_range(1, strlen);
        s = make_random_str(s, n, &mut rng[0], &alphabet);
        writeln!(&mut stdout, "{}", s).expect("IO Error");
    }

    rng[0] = Pcg32::new(0xcafef00dd15ea5e5, 0xa02bdbf7bb3c0a7);
    writeln!(&mut stdout, "{}", tests).expect("IO Error");
    for _ in 0..tests {
        let r = rng[1].gen_range(0, 2);
        let n: usize = rng[r].gen_range(1, strlen);
        s = make_random_str(s, n, &mut rng[r], &alphabet);
        writeln!(&mut stdout, "{}", s).expect("IO Error");
    }
}

