# nm

A simple ELF-32/64 clone of GNU BinUtils' `nm` with limited functionality.

## Used libraries

This project only uses `libc`, as allowed in the subject. No `glibc` or POSIX
functions were used in the project, with the notable exception of `mmap` and
`fileio` (used for finding out a file descriptor from a File).

## Mandatory part

The normal program takes one or more files to analyze. The analyzing process
goes like this:

1. Open the file to check flags, size, etc (then close it).
2. Syscall `mmap` to have a pointer on the file (which is way easier than
   manually reading the file.
3. Read the symbol table header to figure out where each symbol is, and what
   they correspond to.
4. Read all symbols from their index relative to the beginning of the file, and
   construct a symbols array.
5. Sort the symbols alphanumerically (leveraging locale.h)
6. Display the address, type and name of the sorted symbols

## Bonus part

The bonus analyzing process is the same, but some flags are introduced:

- `-a`
- `-g`
- `-p`
- `-r`
- `-u`
