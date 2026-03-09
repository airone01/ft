; input: rdi -> pointer to NUL-terminated string
; output: rax -> length (size_t)

section .text
  global ft_strlen

ft_strlen:
  mov rax, rdi ; save str ptr in rax

.find_loop:
  cmp byte [rdi],  0
  je .done
  inc rdi
  jmp .find_loop

.done:
  ; rdi now points to NUL terminator
  sub rdi, rax ; calc ptrs diff
  mov rax, rdi ; ret len in rax
  ret

