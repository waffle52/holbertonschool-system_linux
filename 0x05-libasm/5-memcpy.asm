BITS 64

global asm_memcpy

section .data
    ; declare static data here

section .text
    ; Code section

asm_memcpy:
    push rbp
    mov rbp, rsp
    push rbx
loop:
    test rdx, rdx
    jz end
    mov bl, [rsi]
    mov [rdi], bl
    inc rdi
    inc rsi
    dec rdx
    jmp loop
end:
    pop rbx
    mov rsp, rbp
    pop rbp
    ret
