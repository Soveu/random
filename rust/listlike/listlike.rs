use std::io::{self, Read};

#[derive(Copy, Debug, Clone)]
struct SliceInfo {
    begin:  usize,
    len:    usize,
}

fn find_index(slices: &Vec::<SliceInfo>, i: &mut usize) -> usize {
    for (n, si) in slices.iter().enumerate() {
        if si.len >= *i {
            return n;
        }

        *i -= si.len;
    }

    return 0;
}

fn split_sliceinfo(s: SliceInfo, n: usize) -> (SliceInfo, SliceInfo) {
    return (
        SliceInfo{begin: s.begin, len: n},
        SliceInfo{begin: s.begin+n, len: s.len-n},
    );
}

fn main() {
    let mut buffer = String::new();
    io::stdin().read_to_string(&mut buffer).expect("Error reading data");

    let mut cache = Vec::<i32>::new();
    let mut slices = Vec::<SliceInfo>::new();
    slices.push(SliceInfo{begin:0, len:0});

    for line in buffer.lines() {
        let mut words = line.split_whitespace();
        match words.next() {
            Some("insert") => {
                let mut index: usize = words.next().unwrap().parse().unwrap();
                let mut items: Vec::<i32> = words.map(|s| s.parse().unwrap()).collect();
                let n = find_index(&slices, &mut index);
                let (prev, next) = split_sliceinfo(slices[n], index);

                slices[n] = prev;
                slices.insert(n+1, SliceInfo{ begin: cache.len(), len: items.len() });
                slices.insert(n+2, next);
                cache.append(&mut items);
            },
            Some("delete") => {
                let index: usize = words.next().unwrap().parse().unwrap();
            },
            Some("print")  => {
                let mut t = Vec::<i32>::new();
                for s in &slices {
                    t.extend_from_slice(&cache[s.begin .. s.begin+s.len]);
                }
                println!("{:?}", t);
                cache = t;
                slices.clear();
                slices.push(SliceInfo{begin: 0, len: cache.len()});
            },
            _ => panic!("Invalid command"),
        }
    }
}

