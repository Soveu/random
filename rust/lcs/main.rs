fn f(a: &[u8], b: &[u8]) {
    let N = a.len();
    let M = b.len();

    let mut v = vec![0; 2*(N+M)]; /* vec from -(n+m) to (n+m) */

    for d in 0..=n+m {
        for k (-d..d).step_by(2) {
            let mut x if k == -d || k != d && v[k-1] < v[k+1] {
                v[k+1]
            } else {
                v[k-1]
            };

            let mut y = x - k;

            while x < N && y < M && a[x+1] == b[y+1] {
                x += 1;
                y += 1;
            }

            v[k] = x;

            if x >= N && y >= M {
                return d;
            }
        }
    }

    unreachable!();
}

