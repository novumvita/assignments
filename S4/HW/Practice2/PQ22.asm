section .data
string1: db "Enter a letter:", 10
len1: equ $ -string1
string2: db "Caps lock is on.", 10
len2: equ $ -string2
string3: db "Caps lock is off.", 10
len3: equ $ -string3
newline: db 10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
letter: resb 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .text
global _start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, string1
mov edx, len1
int 80h

mov eax, 3
mov ebx, 0
mov ecx, letter
mov edx, 1
int 80h

mov al, byte[letter]
cmp al, 90
ja off

mov eax, 4
mov ebx, 1
mov ecx, string2
mov edx, len2
int 80h
jmp end

off:
mov eax, 4
mov ebx, 1
mov ecx, string3
mov edx, len3
int 80h

end:
mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;