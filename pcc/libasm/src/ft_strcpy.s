; input: rdi -> destination pointer
; input: rdi -> source pointer to NUL-terminated string
; output: rax -> original dest pointer

section .text
  global ft_strcpy

ft_strcpy:
  mov rax, rdi ; dest ptr in rax

.find_loop:
  ; copy data byte
  mov cl, byte [rsi]
  mov byte [rdi], cl

  ; check if str end
  cmp cl, 0
  je .done

  ; move to next dest and src bytes
  inc rdi
  inc rsi
  jmp .find_loop

.done:
  ret ; rax still has original ptr

