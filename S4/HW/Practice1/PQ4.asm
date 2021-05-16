section .data
string: db "Enter two numbers", 10
len: equ $ -string

section .bss
var1: resb 1
var2: resb 1
junk: resb 1

section .text
global _start:
_start:

    mov eax, 4
    mov ebx, 1
    mov ecx, string
    mov edx, len
    int 80h

    mov eax, 3
    mov ebx, 0
    mov ecx, var1
    mov edx, 1
    int 80h

    mov eax, 3
    mov ebx, 0
    mov ecx, junk
    mov edx, 1
    int 80h

    mov eax, 3
    mov ebx, 0
    mov ecx, var2
    mov edx, 1
    int 80h

    sub byte[var1], 30h
    sub byte[var2], 30h

    mov ax, word[var1]
    add ax, word[var2]

    mov bl, 10
    mov ah, 0
    div bl

    mov byte[var1], al
    add byte[var1], 30h
    mov byte[var2], ah
    add byte[var2], 30h

    mov eax, 4
    mov ebx, 1
    mov ecx, var1
    mov edx, 1
    int 80h
    mov eax, 4
    mov ebx, 1
    mov ecx, var2
    mov edx, 1
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h