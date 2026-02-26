; input: rdi -> file descriptor (int)
; input: rsi -> pointer to data buffer (const void*)
; input: rdx -> count of bytes of data to read (size_t)
; output: rax -> bytes read, -1 on error (size_t)

section .text
  global ft_read
  extern __errno_location

ft_read:
  mov rax, 0 ; 0 is the syscall number for sys_read on Linux
  ; all data already in place, we just call
  syscall

  cmp rax, 0
  jl .error
  ret ; after call rax will be nbytes read

.error:
  neg rax ; invert code

  ; Because we called, stack shift is now 8, but Linux tells us it should be
  ; divisible by 16 before calling or undefined behaviors will occur.
  ; This push both saves the code to rax and alligns the stack.
  push rax
  call __errno_location
  pop rcx ; pop back the saved code into rcx

  ; Technically errno is a 32-bit int. We can move the 32-bit portion of rcx
  ; into the mem address pointed by rax. This also means we don't need to
  ; zero out the memory pointed by rax.
  mov [rax], ecx

  mov rax, -1
  ret
