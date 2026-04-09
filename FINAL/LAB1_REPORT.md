# PCS-II Lab: Process Memory Information in xv6

## Part A: Understanding Process Memory in xv6

1. `struct proc` definition location:
- File: `proc.h`
- It defines all per-process metadata used by the scheduler, memory management, files, and traps.

2. Field that stores process memory size:
- Field: `uint sz;`
- Meaning: total size of user virtual memory (in bytes) currently allocated for the process.

3. Where xv6 allocates memory when a process grows:
- `growproc(int n)` in `proc.c` handles process growth/shrink.
- For growth (`n > 0`), it calls `allocuvm(curproc->pgdir, sz, sz + n)`.
- For shrink (`n < 0`), it calls `deallocuvm(...)`.

4. Page-table management functions studied in `vm.c`:
- `walkpgdir()`
- `mappages()`
- `setupkvm()`
- `allocuvm()`
- `deallocuvm()`
- `copyuvm()`
- `freevm()`

5. How virtual addresses are mapped to physical pages:
- xv6 uses two-level paging (page directory + page table).
- Macros like `PDX(va)` and `PTX(va)` split a virtual address into directory/table indexes.
- PTE entries map each virtual page to a physical frame, with flags like `PTE_P`, `PTE_W`, `PTE_U`.

## Part B: Implemented System Calls

Implemented and exposed three new syscalls:
- `getmemsize()` -> returns total process memory size in bytes.
- `getvirtpages()` -> returns number of virtual pages used by process.
- `getptecount()` -> returns number of valid present user PTEs for current process address space.

Integration completed in:
- syscall numbers: `syscall.h`
- syscall dispatch table: `syscall.c`
- syscall kernel handlers: `sysproc.c`
- kernel function declarations: `defs.h`
- user-space declarations: `user.h`
- syscall stubs: `usys.S`
- implementation helpers: `proc.c` and `vm.c`

## Part C: User Program

User program:
- `memtest.c`

What it validates:
- memory size change after `sbrk(4096)`
- virtual page change after `malloc(8192)`
- valid PTE behavior across `fork()` for parent/child
- final summary using all three syscalls

## Build and Verification

Build checks run in submission folder:
- `make fs.img` (success)
- `kernel` and `xv6.img` generation succeeded
- `_memtest` user binary generation succeeded

Note:
- Runtime boot test with `make qemu-nox` could not be executed in this environment because a QEMU binary is not installed in PATH.
