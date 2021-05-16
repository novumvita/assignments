section .data
string1: db "Enter 2 numbers:", 10
len1: equ $ -string1
newline: db 10
string2: db "The first number is a multiple of the second.", 10
len2: equ $ -string2
string3: db "The first number is not a multiple of the second.", 10
len3: equ $ -string3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
num: resw 1
temp: resb 1
count: resb 1
a: resw 1
b: resw 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .text
global _start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, string1
mov edx, len1
int 80h

call read_num
mov cx, word[num]
mov word[a], cx

call read_num
mov cx, word[num]
mov word[b], cx

mov dx, 0
mov ax, word[a]
div word[b]

cmp dx, 0
je yes

mov eax, 4
mov ebx, 1
mov ecx, string3
mov edx, len3
int 80h
jmp end

yes:
mov eax, 4
mov ebx, 1
mov ecx, string2
mov edx, len2
int 80h

end:
mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_num:

pusha
mov word[num], 0

loop_read:

mov eax, 3
mov ebx, 0
mov ecx, temp
mov edx, 1
int 80h

cmp byte[temp], 10
je end_read

mov ax, word[num]
mov bx, 10
mul bx
mov bl, byte[temp]
sub bl, 30h
mov bh, 0
add ax, bx
mov word[num], ax
jmp loop_read

end_read:
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;