use std::io::{self, Read};

fn read_to_vec<R: Read>(r: R, v: &mut Vec<u8>) -> io::Result<usize> {
    const MINSPACE: usize = 64;
    if v.capacity() - v.len() < MINSPACE {
        if v.capacity() < 64 {
            v.reserve(64);
        } else {
            v.reserve(v.capacity());
        }
    }

    unsafe {
        let slice = v.get_unchecked_mut(v.len() .. v.capacity());
        let bytes_read = r.read(slice)?;
        v.set_len(v.len() + bytes_read);
        Ok(bytes_read)
    }
}

