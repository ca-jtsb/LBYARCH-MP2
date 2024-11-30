section .data
var1 dd 1000.0
var2 dd 3600.0

section .text
bits 64
default rel
global acc

acc:
    xor r10, r10

calculate:
    cmp r10, rcx
    jge done

    mov rax, r10
    imul rax, 3

    movss xmm0, [rdx + rax * 4]
    movss xmm1, [rdx + rax * 4 + 4]
    movss xmm2, [rdx + rax * 4 + 8]

    mulss xmm0, dword [var1]
    divss xmm0, dword [var2]

    mulss xmm1, dword [var1]
    divss xmm1, dword [var2]

    subss xmm1, xmm0
    divss xmm1, xmm2

    cvtss2si eax, xmm1
    mov [r8 + r10 * 4], eax
    inc r10

    jmp calculate

done:
    ret