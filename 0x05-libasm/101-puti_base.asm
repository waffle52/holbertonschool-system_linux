BITS 64
	global asm_puti_base
	extern asm_putc
	extern asm_strlen
	section .text

asm_puti_base:
	push rbp
	mov rbp, rsp
	push r15
 	push r14
	push r13
	push r12

	xor r15, r15
	xor r14, r14
	movsx r15, edi
	xor rax, rax

	cmp r15, 0
	jge after_negative
	imul r15, -1
	mov r13, 1
	mov rdi, 45
	push rbx
	push rsi
	call asm_putc
	pop rsi
	pop rbx

after_negative:
	mov rdi, rsi
	call asm_strlen
	mov rbx, rax
	cmp rbx, 1
	jnz test_zero
	mov r14, r15
	loop_unary:
	test r15, r15
	jz done_loop_unary
	xor rax, rax
	mov al, BYTE [rsi]
	push rax
	dec r15
	jmp loop_unary
	done_loop_unary:
	xor rax, rax
	jmp while_n

test_zero:
	test r15, r15
	jnz while_n
	movzx rdi, BYTE [rsi]
	call asm_putc
	mov r13, 1

while_n:
	test rbx, rbx
	jz while_n_nobase
	xor rdx, rdx
	test r15, r15
	jz done_while_n
	mov rax, r15
	div rbx
	mov r15, rax
	xor rax, rax
	mov al, BYTE [rsi + rdx]
	push rax
	inc r14
	jmp while_n
done_while_n:
	jmp done_both_while

while_n_nobase:
	xor rdx, rdx
	test r15, r15
	jz done_while_n_nobase
	mov rax, r15
	mov rbx, 10
	div rbx
	mov r15, rax
	xor rax, rax
	mov rax, rdx
	add rax, 48
	push rax
	inc r14
	jmp while_n_nobase
done_while_n_nobase:

done_both_while:
	mov r15, r14
print_loop:
	test r15, r15
	jz done_print_loop
	pop rdi
	after_pop:
	call asm_putc
	dec r15
	jmp print_loop

done_print_loop:

	cmp r13, 1
	jne end
	inc r14

end:
	mov rax, r14
	pop r12
	pop r13
	pop r14
	pop r15
	mov rsp, rbp
	pop rbp
	ret
