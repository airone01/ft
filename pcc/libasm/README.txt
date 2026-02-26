libasm
======

A library of basic functions, written in assembly.

Project specifications
======================

This project is programmed for baseline AMD64 with the System V AMD64 convention, for the GNU/Linux ABI.
The Intel syntax is the one used, as required by the subject.
My implementation is vanilla, as in it is not programmed with AVX or any AMD64 extension in mind.
It should therefore be portable on AMD64 Linux.

Provided functions
------------------

The functions provided by this project are the following:

- ft_strlen (strlen.3)
- ft_strcpy (strcpy.3)
- ft_strcmp (strcmp.3)
- ft_write (write.2)
- ft_read (read.2)
- ft_strdup (strdup.3, call to malloc allowed)

And the bonus functions are as follow:

- ft_atoi_base
  - `int ft_atoi_base(char *str, char *base);`
- ft_list_push_front
  - `void ft_list_push_front(t_list **begin_list, void *data);`
- ft_list_size
  - `int ft_list_size(t_list *begin_list);`
- ft_list_sort
  - `void ft_list_sort(t_list **begin_list, int (*cmp)());`
  - The function pointed to by cmp will be used as:
    - `(*cmp)(list_ptr->data, list_other_ptr->data);`
- ft_list_remove_if
  - `void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));`
  - The functions pointed to by cmp will be used respectively as:
    - `(*cmp)(list_ptr->data, data_ref);`
    - `(*free_fct)(list_ptr->data);`

Appendix
========

Appendix A
----------

"Why align the stack?"
Before executing a 'call' instruction, the stack pointer (rsp) must be 16-byte aligned.
When a function is entered, the 'call' instruction pushes an 8-byte return address onto the stack, leaving it misaligned.
To fix this before calling another C function, we must adjust rsp by 8 bytes.
Pushing a dummy register (or saving a register we need) offsets that 8-byte imbalance. 
Failing to do this causes modern C library functions (which use strict SSE/AVX instructions) to segfault.

Appendix B
----------

"With Respect to the Procedure Linking Table"
Modern Linux enforces PIE (Position Independent Executables).
Memory addresses for external C library functions (like malloc or __errno_location) are randomized at runtime and cannot be reached via a static 32-bit relative jump.
Appending 'WRT ..plt' (With Respect To Procedure Linkage Table) forces the assembler to generate an R_X86_64_PLT32 relocation.
This routes our call through the PLT trampoline, which dynamically resolves the true memory address via the GOT (Global Offset Table) at runtime.

The 'default rel' line is used to indicate to the assembler that we are purposely writing position independent code.
AFAIK, 'WRT ..plt' does route the call, but '-Wall' still warns, and we cannot compile because of '-Werror'. Hence, using '[warning -reloc-rel-dword]' to suppress the NASM warning.

Appendix C
----------

Technically errno is a 32-bit integer.
We can move the 32-bit portion of a register someplace else by leveraging the last 32 bits out of the 64 bits of a register.
We can use the convenient 32-bit version of the 64-bit integer for that. For example, EAX for RAX.
We don't need to zero out RAX in this example.

Resources
=========

"AMD 64-Bit Technology: The AMD64 x86-64™ Architecture Programmers Overview" by AMD
https://refspecs.linuxbase.org/x86_64-overview.pdf

"Linux ABI description"
https://docs.kernel.org/admin-guide/abi.html
