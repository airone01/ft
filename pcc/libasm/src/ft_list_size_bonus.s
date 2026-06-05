	; input: rdi -> begin_list (t_list *)
	; output: eax -> number of elements (int)

	section .text
	global  ft_list_size

ft_list_size:
	xor eax, eax

.loop:
	test rdi, rdi
	jz   .done
	inc  eax
	mov  rdi, [rdi + 8]; node = node->next
	jmp  .loop

.done:
	ret
