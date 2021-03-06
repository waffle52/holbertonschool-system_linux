BITS 64

global asm_strncmp

section .data
    ; declare static data here

section .text
    ; Code section

asm_strncmp:
    push rbp
    mov rbp, rsp
    push rcx

    xor rcx, rcx
loop:
    cmp rcx, rdx
    je compare
    mov al, [rdi + rcx]
    mov bl, [rsi + rcx]
    test al, al
    jz compare
    test bl, bl
    jz compare
    cmp al, bl
    jne compare
    inc rcx
    jmp loop
compare:
	cmp al, bl
	je equal
	jl less
	jg greater
equal:
	mov rax, 0
	jmp end
less:
	mov rax, -1
	jmp end
greater:
	mov rax, 1
	jmp end
end:
	pop rcx
	mov rsp, rbp
	pop rbp
	ret
