BITS 64

global asm_strncasecmp

section .data
    ; declare static data here

section .text
    ; Code section
asm_strncasecmp:
    push rbp
    mov rbp, rsp
    push rcx
    push r8
    push r9
    push rdx

    xor rcx, rcx
    xor r8, r8
    xor r9, r9
    xor eax, eax
loop:
    test edx, edx
    jz end
    dec edx
    mov r8b, [rdi + rcx]
    mov r9b, [rsi + rcx]
    cmp r8b, 65
    jl check
    cmp r8b, 90
    jg check
    add r8b, 32
check:
    cmp r9b, 65
    jl cont
    cmp r9b, 90
    jg cont
    add r9b, 32
cont:
    mov eax, r8d
    sub eax, r9d
    test eax, eax
    jnz end
    test r8b, r8b
    jz end
    inc rcx
    jmp loop
end:
    pop rdx
    pop r9
    pop r8
    pop rcx
    mov rsp, rbp
    pop rbp
    ret
