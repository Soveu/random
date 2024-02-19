#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>

typedef _Atomic(uint32_t) AtomicU32;

long futex_wait(AtomicU32* uaddr, const uint32_t val) {
    return syscall(SYS_futex, uaddr, FUTEX_WAIT, val);
}

long futex_wake(AtomicU32* uaddr) {
    const uint32_t threads_to_wake = 1;
    return syscall(SYS_futex, uaddr, FUTEX_WAKE, threads_to_wake);
}

#define MUTEX_LOCKED (1)
#define MUTEX_UNLOCKED (0)

void mutex_acquire(AtomicU32* addr) {
    if (atomic_exchange(addr, MUTEX_LOCKED) == MUTEX_UNLOCKED) {
        // Quick path, the lock was free.
        return;
    }

    // TODO: what if EAGAIN?
    const long ret = futex_wait(addr, MUTEX_LOCKED);
    if (ret == -1) {
        perror("mutex_acquire");
        abort();
    }

    // Both in the case with spurious and actual wake-up, try acquiring the lock again.
    return mutex_acquire(addr);
}

void mutex_release(AtomicU32* addr) {
    atomic_store(addr, MUTEX_UNLOCKED);
    const long woken_threads = futex_wake(addr);

    if (woken_threads == -1) {
        perror("mutex_release");
        abort();
    }
}
