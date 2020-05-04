#![feature(const_generics)]

struct Array<T, const N: usize> {
    data:   [T; N],
}

/* TODO: iters */
impl<T: PartialEq, const N: usize> PartialEq for Array<T, N> {
    fn eq(&self, other: &Self) -> bool {
        let self_iter = self.data.iter();
        let other_iter = other.data.iter();

        for (a, b) in self_iter.zip(other_iter) {
            if *a != *b { return false; }
        }

        return true;
    }
}

impl<T: Eq, const N: usize> Eq for Array<T, N> {}

impl<T: Default + Copy, const N: usize> Default for Array<T, N> {
    fn default() -> Self {
        Self {
            data: [T::default(); N],
        }
    }
}

fn main() {
    let x: Array<i32, 32> = Array::default();
    let y = x;
}

