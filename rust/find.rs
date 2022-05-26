#![feature(array_windows)]

use std::arch::asm;
use std::ffi::{CString, CStr};

unsafe fn close(fd: i32) {
    let output: isize;
    asm!("
        push rcx
        push r11
        syscall
        push r11
        popf
        pop r11
        pop rcx",
        inout("rax") 3usize => output,
        in("rdi") fd,
        options(preserves_flags, nomem)
    );
    assert_eq!(output, 0);
}

unsafe fn open(path: *const i8, flags: usize, mode: usize) -> isize {
    let output;
    asm!("
        push rcx
        push r11
        syscall
        push r11
        popf
        pop r11
        pop rcx",
        inout("rax") 2usize => output,
        in("rdi") path,
        in("rsi") flags,
        in("rdx") mode,
        options(preserves_flags, readonly)
    );
    return output;
}

unsafe fn _getdents64(fd: i32, dirp: *mut u64, count: usize) -> isize {
    let output;
    asm!("
        push rcx
        push r11
        syscall
        push r11
        popf
        pop r11
        pop rcx",
        inout("rax") 217usize => output,
        in("rdi") fd,
        in("rsi") dirp,
        in("rdx") count,
        options(preserves_flags)
    );
    return output;
}

#[derive(Clone, Copy)]
pub enum DirentType {
    Unknown = 0,
    Fifo = 1,
    Character = 2,
    Directory = 4,
    Block = 6,
    RegularFile = 8,
    Link = 10,
    Socket = 12,
    Wht = 14,
}

#[derive(Debug)]
#[repr(C)]
pub struct Dirent64 {
    inode: u64,
    offset: u64,
    reclen: u16,
    typ: u8,
    filename: CStr,
}

fn getdents64(fd: i32, dirp: &mut [u64]) -> (DirentIter, &mut [u64]) {
    let status = unsafe { _getdents64(fd, dirp.as_mut_ptr(), dirp.len() * 8) };
    assert!(status >= 0 && status % 8 == 0, "Error code = {}, fd = {}", -status, fd);
    let (dirents, rest) = dirp.split_at_mut(status as usize / 8);
    return (DirentIter(dirents), rest);
}

pub struct DirentIter<'a>(&'a [u64]);

impl<'a> Iterator for DirentIter<'a> {
    type Item = &'a Dirent64;

    fn next(&mut self) -> Option<Self::Item> {
        let base_dirent = self.0.get(..3)?;
        let base_dirent = std::ptr::slice_from_raw_parts(base_dirent.as_ptr(), 0);
        let base_dirent = base_dirent as *const Dirent64;
        let base_dirent = unsafe { &*base_dirent };

        let reclen = base_dirent.reclen as usize;
        let size_in_u64s = reclen / 8;
        let last_word_idx = size_in_u64s.checked_sub(1)?;
        assert!(reclen % 8 == 0 && reclen >= 24, "reclen={}", reclen);
        let last_word = self.0[last_word_idx];

        // Sometimes the filename will be so short, the last u64 will also contain
        // the contents of `reclen` and `type`, so we need to force them to
        // not have null bytes.
        let last_word = if last_word_idx == 2 { last_word | 0xFFFFFF } else { last_word };

        let ignore = 7 - last_word.to_le_bytes()
            .into_iter()
            .enumerate()
            .find(|(_, x)| *x == 0u8)
            .unwrap()
            .0;

        let dirent_size = 8 + 8 + 2 + 1;
        let filename_len = reclen - dirent_size - ignore;
        let (dirent, rest) = self.0.split_at(size_in_u64s);
        let dirent = std::ptr::slice_from_raw_parts(dirent.as_ptr(), filename_len);
        let dirent = dirent as *const Dirent64;
        let dirent = unsafe { &*dirent };

        self.0 = rest;
        return Some(dirent);
    }
}

fn walk(mut path: CString, buf: &mut [u64], f: &mut impl FnMut(&CStr, &Dirent64)) -> CString {
    const O_DIRECTORY: usize = 0o200_000;
    const O_RDONLY: usize = 0;
    let fd = unsafe { open(path.as_ptr(), O_DIRECTORY | O_RDONLY, 0) };
    if fd < 0 {
        return path;
    }

    let (dents, rest) = getdents64(fd as i32, buf);

    for dent in dents
        .filter(|d| d.filename.to_bytes() != b".")
        .filter(|d| d.filename.to_bytes() != b"..")
    {
        (f)(&path, &dent);

        if dent.typ != DirentType::Directory as u8 {
            continue;
        }

        let mut name = path.into_bytes();
        name.extend_from_slice(dent.filename.to_bytes());
        name.extend_from_slice(b"/\0");
        path = unsafe { CString::from_vec_with_nul_unchecked(name) };

        path = walk(path, rest, f);

        let mut name = path.into_bytes_with_nul();
        name.truncate(name.len() - dent.filename.to_bytes_with_nul().len() - 1);
        name.push(0u8);
        path = unsafe { CString::from_vec_with_nul_unchecked(name) };
    }

    unsafe { close(fd as i32); }
    return path;
}

pub fn find_png(current_dir: &CStr, d: &Dirent64) {
    if d.typ == DirentType::RegularFile as u8 && d.filename.to_bytes().ends_with(b".png") {
        let path = unsafe { std::str::from_utf8_unchecked(current_dir.to_bytes()) };
        let filename = unsafe { std::str::from_utf8_unchecked(d.filename.to_bytes()) };
        println!("{}{}", path, filename);
    }
}

fn main() {
    let mut buf = vec![0u64; 1024 * 128];
    let start_path = CString::new("/home/").unwrap();

    // let mut counter = 0usize;
    // let mut f = |_: &CStr| counter += 1;

    walk(start_path, &mut buf, &mut find_png);

    // println!("{}", counter);
}
