use std::pin::Pin;

trait PinDrop {
    fn drop(self: Pin<&mut Self>);
}

impl PinDrop for () {
    fn drop(self: Pin<&mut Self>) {
        fn unpin_drop(self: &mut ()) {
        }

        unpin_drop(Pin::into_inner(self))
    }
}

fn main() {}
