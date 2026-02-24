; input: rdi -> s1 pointer of NUL-terminated string
; input: rsi -> s2 pointer of NUL-terminated string
; output: rax -> int difference between data in pointers
; note: NULL pointer segfaults

section .text
  global ft_strcmp

ft_strcmp:
  ; xor is a fast way to bzero a reg
  xor rax, rax
  xor rcx, rcx

.find_loop:
  mov al, byte [rdi]
  mov cl, byte [rsi]

  ; early stop when any char diff
  cmp al, cl
  jne .done

  ; just check rsi's because the previous check made sure they are the same
  cmp al, 0
  je .done

  inc rdi
  inc rsi
  jmp .find_loop

.done:
  ; because rax and rcx were bzero'd, they hold only the exact positive
  ; unsigned value of the characters, meaning subbing them correctly here
  ; handles neg results as intended
  sub rax, rcx
  ret

