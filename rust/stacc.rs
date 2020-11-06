const K: usize = 2;

struct HPRec<T> {
    hp: AtomicPtr<T>,
}

struct Node<T> {
    data: T,
    next: AtomicPtr<T>,
}

struct Stacc<T> {
    top: AtomicPtr<T>,
}

impl Stacc<T> {
    fn push(&self, x: T) {
        let node = Node {
            data: x,
            next: AtomicPtr::new(0),
        };
        let mut node = Box::into_raw(Box::new(node));
    
        loop {
            let top = self.top.load(Ordering::Acquire);
            node.next = top;
            if self.top.compare_exchange(top, node, Ordering::Acquire).is_ok() {
                return;
            }
        }
    }

    fn pop(&self) -> Option<T> {
        loop {
            let top = self.top.load(Ordering::Acquire);
            if top.is_null() {
                return None;
            }

            *hp = top;
            if top != self.top.load(Ordering::Acquire) {
                continue;
            }

            let next = unsafe { (*top).next };
            if self.top.compare_exchange(top, next).is_ok() {
                let data = unsafe { (*top).data };
                retire_node(t);
                return Some(data);
            }
        }
    }
}

