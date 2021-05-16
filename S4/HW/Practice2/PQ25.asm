section .data
string: db "Enter 2 numbers:", 10
len: equ $ -string
newline: db 10
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
num: resw 1
temp: resb 1
count: resb 1
a: resw 1
b: resw 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .text
global _start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, string
mov edx, len
int 80h

call read_num
mov cx, word[num]
mov word[a], cx

call read_num
mov cx, word[num]
mov word[b], cx

loop:
mov dx, 0
mov ax, word[a]
div word[b]
cmp dx, 0
je end_loop
mov ax, word[b]
mov word[a], ax
mov word[b], dx
jmp loop
end_loop:

mov ax, word[b]
mov word[num], ax
call print_num

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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_num:
mov byte[count], 0
pusha

extract_no:
cmp word[num], 0
je print_no
inc byte[count]
mov dx, 0
mov ax, word[num]
mov bx, 10
div bx
push dx
mov word[num], ax
jmp extract_no

print_no:
cmp byte[count], 0
je end_print
dec byte[count]
pop dx
mov byte[temp], dl
add byte[temp], 30h
mov eax, 4
mov ebx, 1
mov ecx, temp
mov edx, 1
int 80h
jmp print_no

end_print:
mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, 1
int 80h

popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;