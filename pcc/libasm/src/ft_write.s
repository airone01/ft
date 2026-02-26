; input: rdi -> file descriptor (int)
; input: rsi -> pointer to data buffer (const void*)
; input: rdx -> count of bytes of data to write (size_t)
; output: rax -> bytes written, -1 on error (size_t)

; appendix B
default rel
[warning -reloc-rel-dword]

section .text
  global ft_write
  extern __errno_location

ft_write:
  mov rax, 1 ; 1 is syscall no. for sys_write on Linux
  ; all data already in place, we just call
  syscall

  cmp rax, 0
  jl .lerror
  ret ; after call rax will be nbytes written

.lerror:
  neg rax ; invert code

  push rax ; appendix A
  call __errno_location WRT ..plt ; appendix B
  pop rcx ; pop back the saved code into rcx

  mov [rax], ecx ; appendix C

  mov rax, -1
  ret
