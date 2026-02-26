; input: rdi -> source pointer to NUL-terminated string
; output: rax -> original source pointer

section .text
  global ft_strdup
  extern malloc ; byte size into rdi, allign stack
  extern ft_strlen
  extern ft_strcpy

ft_strdup:
  push rdi ; save og ptr
  call ft_strlen

  inc rax ; ptr to NUL
  mov rdi, rax ; setup for malloc

  call malloc
  cmp rax, 0 ; err handling
  je .error

  mov rdi, rax ; setup for strcpy
  pop rsi ; get back ptr

  call ft_strcpy
  ret

.error
  ; still need to pop to keep the stack balanced
  pop rdi
  ret
