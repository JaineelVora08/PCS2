# Process Memory Information in xv6

## Project Overview

This project extends the **xv6 operating system** (an x86 emulator running on QEMU) by implementing new system calls that expose detailed memory usage information about the currently running process. 

In xv6, each process has a dedicated virtual address space mapped through a two-level page table, which holds memory segments like code, data, heap, and stack. The goal of this project is to explore the xv6 kernel's memory management mechanisms (`proc.c`, `vm.c`, `sysproc.c`) and extract the following runtime metrics:

1. **Total Size of Memory**: The total memory size (in bytes) used by the process.
2. **Virtual Pages Count**: The number of virtual pages currently utilized by the process.
3. **Valid PTE Count**: The number of valid, allocated page table entries (PTEs) present in the process's page table.

## Components Implemented

### 1. New System Calls

Three new system calls have been added to the xv6 kernel:

- `getmemsize()` (Syscall 22): Returns the total size of memory (in bytes) utilized by the current process. This looks at the `sz` field of `struct proc` in `proc.c`.
- `getvirtpages()` (Syscall 23): Returns the number of virtual pages currently used by the process. Calculated by stepping through the process size by `PGSIZE` (4096 bytes).
- `getptecount()` (Syscall 24): Iterates through the process's page directory and page tables, counting all entries mapped with the `PTE_P` (present) flag within the user's address space.

These are linked through `syscall.h`, `syscall.c`, and exposed to the user space via `user.h` and `usys.S`.

### 2. User Program: `memtest`

A user program, `memtest.c`, was developed and added to the `Makefile` to empirically test and observe these system calls under different memory allocation scenarios:
- **Immediate Evaluation**: Records baseline memory metrics immediately upon startup.
- **Dynamic Allocation via `sbrk()`**: Allocates an additional 4096 bytes and verifies the corresponding growth in memory size.
- **Dynamic Allocation via `malloc()`**: Allocates an additional 8192 bytes and observes changes in virtual page counts.
- **Process Forking (`fork()`)**: Checks and compares the PTE counts for both parent and child processes to verify successful copying of page structures.

## Build and Run Instructions

Ensure you have the QEMU emulator and xv6 build tools installed in your environment.

1. **Compile the Kernel and User Programs**:
   ```bash
   make
   ```
2. **Start the xv6 Emulator**:
   ```bash
   make qemu
   # or for terminal-only output:
   make qemu-nox
   ```
3. **Run the Memory Test Program** inside xv6:
   ```bash
   $ memtest
   ```
   You will see the output detailing memory sizes, page counts, and PTE valid entries updating across `sbrk`, `malloc`, and `fork` scenarios.
