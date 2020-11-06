fn main() {
    let v = [-123, -3, 0, 1, 4, 7, 12, 21];
    
    for i in -3i32..26 {
        let n = v.binary_search_by(|p| match p.cmp(&i) {
            Ordering::Less    => Ordering::Less,
            Ordering::Equal   => Ordering::Less,
            Ordering::Greater => Ordering::Greater,
        });

        let n = n.unwrap_err();

        println!("{:?} {:?} {:?}", i, v[n], v);
    }
}
