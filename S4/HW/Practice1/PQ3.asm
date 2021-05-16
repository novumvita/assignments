section .data
string: db "Enter a number", 10
len: equ $ -string
linebreak: db 10

section .bss
number: resb 1
counter: resb 1

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
    mov ecx, number
    mov edx, 1
    int 80h
    sub byte[number], 30h
    mov byte[counter], 0

    loop:
        add byte[counter], 30h
        mov eax, 4
        mov ebx, 1
        mov ecx, counter
        mov edx, 1
        int 80h

        mov eax, 4
        mov ebx, 1
        mov ecx, linebreak
        mov edx, 1
        int 80h

        sub byte[counter], 30h
        add byte[counter], 1
        mov al, byte[counter]
        cmp al, byte[number]
        jna loop

    mov eax, 1
    mov ebx, 0
    int 80h