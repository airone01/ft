	; input: rdi -> begin_list (t_list **), rsi -> data (void *)
	; output: (none) — prepends a new node to the list

	;        appendix B
	default  rel
	[warning -reloc-rel-dword]

	section .text
	global  ft_list_push_front
	extern  malloc

ft_list_push_front:
	push rbx
	push r12
	sub  rsp, 8; 2 pushes + 8 = 24 bytes total: (8+24)%16=0, aligned for call

	mov rbx, rdi; rbx = begin_list
	mov r12, rsi; r12 = data

	mov  rdi, 16; sizeof(t_list)
	call malloc WRT ..plt

	add  rsp, 8
	test rax, rax
	jz   .done

	mov rcx, [rbx]; rcx = old *begin_list
	mov [rax + 8], rcx; new->next = old head
	mov [rax], r12; new->data = data
	mov [rbx], rax; *begin_list = new node

.done:
	pop r12
	pop rbx
	ret
