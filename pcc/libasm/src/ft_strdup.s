; input: rdi -> source pointer to NUL-terminated string
; output: rax -> original source pointer

; appendix B
default rel

section .text
  global ft_strdup
  extern malloc ; byte size into rdi, allign stack
  extern ft_strlen
  extern ft_strcpy

ft_strdup:
  push rdi ; save original ptr
  call ft_strlen WRT ..plt

  inc rax ; ptr to NUL
  mov rdi, rax ; setup for malloc

  call malloc WRT ..plt
  cmp rax, 0 ; err handling
  je .lerror

  mov rdi, rax ; setup for strcpy
  pop rsi ; get back ptr

  call ft_strcpy WRT ..plt
  ret

.lerror:
  pop rdi ; appendix A
  ret
