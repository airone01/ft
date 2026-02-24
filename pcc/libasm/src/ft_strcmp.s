; input: rdi -> s1 pointer of NUL-terminated string
; input: rsi -> s2 pointer of NUL-terminated string
; output: rax -> int difference between data in pointers
; note: NULL pointer segfaults

section .text
  global ft_strcmp

ft_strcmp:
  mov rax, 0 ; init rax

.find_loop:
  ; calculate diff
  add al, byte [rdi]
  sub al, byte [rsi]

  ; check if either str ends
  cmp byte[rdi], 0
  je .done
  cmp byte[rsi], 0
  je .done

  ; move to next dest and src bytes
  inc rdi
  inc rsi
  jmp .find_loop

.done:
  ret ; rax has output result

