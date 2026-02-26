; input: rdi -> file descriptor (int)
; input: rsi -> pointer to data buffer (const void*)
; input: rdx -> count of bytes of data to read (size_t)
; output: rax -> bytes read, -1 on error (size_t)

; appendix B
default rel
[warning -reloc-rel-dword]

section .text
  global ft_read
  extern __errno_location

ft_read:
  mov rax, 0 ; 0 is syscall no. for sys_read on Linux
  ; all data already in place, we just call
  syscall

  cmp rax, 0
  jl .lerror
  ret ; after call rax will be nbytes read

.lerror:
  neg rax ; invert code

  push rax ; appendix A
  call __errno_location WRT ..plt ; appendix B
  pop rcx ; pop back the saved code into rcx

  mov [rax], ecx ; appendix C

  mov rax, -1 ; libc errors out with -1
  ret
