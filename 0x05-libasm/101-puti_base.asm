BITS 64

section .bss

    buf     resb        34

extern asm_putc
extern asm_strlen
global asm_puti_base

section .text

asm_puti_base:

    push rbp
    mov rbp, rsp
    push r8
    push r9
    push r10
    push rcx
    push rsi
    push rbx

    mov r8, buf
    mov r9, rsi
    mov r10, 32
    mov BYTE [r8 + 33], 0
    movsx rdi, edi
    xor sil, sil

    mov rcx, rdi
    mov rdi, r9
    call asm_strlen
    cmp eax, 2
    jl print
    mov rbx, rax
    mov rdi, rcx

    xor rcx, rcx
    cmp rdi, 0
    jl negative

continue:

    mov rax, rdi

do:

    xor rdx, rdx
    div rbx
    mov dl, BYTE [r9 + rdx]
    mov BYTE [r8 + r10], dl
    inc rcx

while:

    test rax, rax
    jz check_sign
    dec r10
    jmp do

negative:

    imul rdi, -1
    mov sil, -1
    jmp continue

check_sign:

    cmp sil, -1
    jne print
    dec r10
    mov BYTE [r8 + r10], '-' 
    inc rcx

print:

    lea r8, [r8 + r10]
    xor r9, r9

print_loop:

    mov dl, BYTE [r8 + r9]
    test dl, dl
    jz end
    movzx rdi, dl
    call asm_putc
    inc r9
    jmp print_loop

end:

    mov rax, r9

    pop rcx
    pop rbx
    pop rsi
    pop rcx
    pop r10
    pop r9
    pop r8

    mov rsp, rbp
    pop rbp

    ret
