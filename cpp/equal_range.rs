fn equal_range(slice: &[i32], val: &'_ i32) -> &[i32] {
    let mut len = slice.len();

    while len > 0 {
        let middle = len / 2;
        let item = slice.get(middle).unwrap();

        match item.cmp(val) {
            Ordering::Less    => {
                slice = slice.get(middle+1..).unwrap();
            }
            Ordering::Greater => {
                len = middle;
            }
            Ordering::Equal   => {
                let left = slice.get(.. middle).binary_search(val);
                let right = slice.get(middle+1 .. len).upper_bound(val);
                return slice.get(left .. right).unwrap();
            }
        }
    }

    return &[];
}

