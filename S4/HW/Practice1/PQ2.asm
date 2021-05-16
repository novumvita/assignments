section .data
query: db "Enter your name", 10
lenq: equ $ -query
string: db "Your name is: "
len: equ $ -string

section .bss
name: resb 1
name_len: resb 1

section .text
global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, query
    mov edx, lenq
    int 80h

    mov eax, 3
    mov ebx, 0
    mov ecx, name
    mov edx, name_len
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, string
    mov edx, len
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, name
    mov edx, name_len
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h