	; input: rdi -> str, rsi -> base
	; output: rax -> integer value, sets g_invalid_base or g_no_match on error

	; Callee-saved layout:
	; rbx = current str pointer
	; r12 = base pointer
	; r13d = base length
	; r14d = sign (+1 or -1)
	; r15d = accumulated result

	default  rel
	[warning -reloc-rel-dword]

	section .bss
	global  g_invalid_base
	global  g_no_match
	g_invalid_base: resd 1
	g_no_match: resd 1

	section .text
	global  ft_atoi_base

ft_atoi_base:
	push rbx
	push r12
	push r13
	push r14
	push r15

	mov rbx, rdi
	mov r12, rsi

	;   --- count base length, reject '+', '-', ' ' ---
	xor r13d, r13d

.count_base:
	movzx eax, byte [r12 + r13]
	test  al, al
	jz    .check_len
	cmp   al, '+'
	je    .invalid_base
	cmp   al, '-'
	je    .invalid_base
	;     whitespace: 9-13 (\t \n \v \f \r)
	lea   ecx, [eax - 9]
	je    .invalid_base
	cmp   al, ' '
	je    .invalid_base
	inc   r13d
	jmp   .count_base

.check_len:
	cmp r13d, 2
	jl  .invalid_base

	;   --- reject duplicate chars in base ---
	xor r14d, r14d; i = 0

.dup_outer:
	cmp   r14d, r13d
	jge   .no_dups
	movzx ecx, byte [r12 + r14]; cl = base[i]
	lea   r15d, [r14d + 1]; j = i + 1

.dup_inner:
	cmp   r15d, r13d
	jge   .dup_next
	movzx eax, byte [r12 + r15]
	cmp   al, cl
	je    .invalid_base
	inc   r15d
	jmp   .dup_inner

.dup_next:
	inc r14d
	jmp .dup_outer

.no_dups:
	;   --- skip leading whitespace and parse sign ---
	mov r14d, 1

.skip_prefix:
	movzx eax, byte [rbx]
	;     whitespace: 9-13 (\t \n \v \f \r)
	lea   ecx, [eax - 9]
	cmp   ecx, 4
	jbe   .advance_prefix
	cmp   al, ' '
	je    .advance_prefix
	cmp   al, '+'
	je    .advance_prefix
	cmp   al, '-'
	jne   .prefix_done
	neg   r14d

.advance_prefix:
	inc rbx
	jmp .skip_prefix

.prefix_done:
	;   --- convert each digit ---
	xor r15d, r15d

.digit_loop:
	movzx eax, byte [rbx]
	test  al, al
	jz    .apply_sign
	;     find al in base
	xor   ecx, ecx

.find_digit:
	cmp   ecx, r13d
	jge   .no_match
	movzx edx, byte [r12 + rcx]
	cmp   al, dl
	je    .digit_found
	inc   ecx
	jmp   .find_digit

.digit_found:
	imul r15d, r13d
	add  r15d, ecx
	inc  rbx
	jmp  .digit_loop

.apply_sign:
	imul r15d, r14d
	mov  eax, r15d
	jmp  .return

.invalid_base:
	mov dword [rel g_invalid_base], 1
	xor eax, eax
	jmp .return

.no_match:
	mov dword [rel g_no_match], 1
	xor eax, eax

.return:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
