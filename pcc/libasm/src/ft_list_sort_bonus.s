	; input: rdi -> begin_list (t_list **), rsi -> cmp (fn ptr)
	; output: (none) — sorts list ascending via cmp, swapping data pointers

	section .text
	global  ft_list_sort

ft_list_sort:
	push rbx
	push r12
	push r13
	push r14
	push r15; 5 pushes = 40 bytes: (8+40)%16=0, aligned for call

	mov rbx, rdi; rbx = begin_list
	mov r12, rsi; r12 = cmp function pointer

.outer:
	xor r14d, r14d; swapped = 0
	mov r13, [rbx]; r13 = curr = *begin_list

.inner:
	test r13, r13
	jz   .check
	mov  r15, [r13 + 8]; r15 = next = curr->next (save before call clobbers rax)
	test r15, r15
	jz   .check

	mov  rdi, [r13]; cmp(curr->data, next->data)
	mov  rsi, [r15]
	call r12; rax = return value; r13 (curr) and r15 (next) survive

	cmp eax, 0
	jle .advance

	mov rdi, [r13]; swap data pointers
	mov rsi, [r15]; r15 still holds next (callee-saved)
	mov [r13], rsi
	mov [r15], rdi
	mov r14d, 1; swapped = 1

.advance:
	mov r13, [r13 + 8]; curr = curr->next (r13 still holds old curr)
	jmp .inner

.check:
	test r14d, r14d
	jnz  .outer

	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
