section .data
addr: db "Address line 1, Address line 2", 10, "Address line 3, Address line 4", 10
len: equ $ -addr

section .text
global _start:
_start:

    mov eax, 4
    mov ebx, 1
    mov ecx, addr
    mov edx, len
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h