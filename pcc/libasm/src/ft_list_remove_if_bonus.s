	; input: rdi -> begin_list (t_list **), rsi -> data_ref (void *)
	; rdx -> cmp (fn ptr), rcx -> free_fct (fn ptr)
	; output: (none) — removes all nodes where cmp(node->data, data_ref) == 0

	;        appendix B
	default  rel
	[warning -reloc-rel-dword]

	section .text
	global  ft_list_remove_if
	extern  free

ft_list_remove_if:
	push rbx
	push r12
	push r13
	push r14
	push r15; 5 pushes = 40 bytes: (8+40)%16=0, aligned for call

	mov rbx, rdi; rbx = cursor (t_list **), walks &(*node)->next
	mov r12, rsi; r12 = data_ref
	mov r13, rdx; r13 = cmp
	mov r14, rcx; r14 = free_fct

.loop:
	mov  rax, [rbx]; rax = current node
	test rax, rax
	jz   .done

	mov  rdi, [rax]; cmp(node->data, data_ref)
	mov  rsi, r12
	call r13

	test eax, eax
	jnz  .skip

	;   match: unlink then free data then free node
	mov r15, [rbx]; r15 = node to remove
	mov rax, [r15 + 8]
	mov [rbx], rax; *cursor = node->next

	mov  rdi, [r15]
	call r14; free_fct(node->data)

	mov  rdi, r15
	call free WRT ..plt; free(node)
	jmp  .loop; re-check new *cursor without advancing

.skip:
	mov rax, [rbx]; advance cursor to &(node->next)
	lea rbx, [rax + 8]
	jmp .loop

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
