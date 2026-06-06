	; input: rdi -> source pointer to NUL-terminated string
	; output: rax -> original source pointer

	extern   __errno_location
	;        appendix B
	default  rel
	[warning -reloc-rel-dword]

	section .text
	global  ft_strdup
	extern  malloc; byte size into rdi, allign stack
	extern  ft_strlen
	extern  ft_strcpy

ft_strdup:
	push rdi; save original ptr
	call ft_strlen WRT ..plt

	inc rax; ptr to NUL
	mov rdi, rax; setup for malloc

	call malloc WRT ..plt
	cmp  rax, 0; err handling
	je   .lerror

	mov rdi, rax; setup for strcpy
	pop rsi; get back ptr

	call ft_strcpy WRT ..plt
	ret

.lerror:
	;    RSP is 16-byte aligned here (one push rdi at entry, one call ft_strlen
	;    one call malloc — net effect: aligned), so we can call directly.
	call __errno_location WRT ..plt
	mov  dword [rax], 12; ENOMEM = 12
	xor  eax, eax; return NULL
	pop  rdi; balance the initial push rdi
	ret
