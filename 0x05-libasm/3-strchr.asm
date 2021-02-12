BITS 64

global asm_strchr

section .data
    ; declare static data here

section .text
    ; Code section
asm_strchr:
    push rbp
    mov rbp, rsp

loop:
    mov al, [rdi]
    cmp al , sil
    je match
    test al, al
    jz null
    inc rdi
    jmp loop
null:
	xor rax, rax
	jmp end
match:
	mov rax, rdi
end:
	mov rsp, rbp
	pop rbp
	ret
