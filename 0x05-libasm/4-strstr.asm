BITS 64

global asm_strstr

section .data
    ; declare static data here

section .text
    ; Code section

asm_strstr:
    push rbp
    mov rbp, rsp
    push rcx
    push rbx
    push rdx
    push r8
    push r9
    xor  rax, rax
    xor rcx, rcx
    xor r8, r8
    xor r9, r9
loop:
    mov rdx, rcx		; store pos before match
    xor rbx, rbx
loop_match:
	mov r8b, [rdi + rcx]
	mov r9b, [rsi + rbx]
	test r9b, r9b
	jz match
	cmp r8b, r9b
	jne break
	inc rcx
	inc rbx
	jmp loop_match
break:
	mov r8b, [rdi + rcx]
	test r8b, r8b
	jz end
	inc rcx
	jmp loop
match:
	mov rax, rdi
	add rax, rdx
end:
	pop r9
	pop r8
	pop rdx
	pop rbx
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
