section .data
msg1: db  "Enter the number of elements in the array:", 10
len1: equ $ -msg1
msg2: db  "Enter the numbers:", 10
len2: equ $ -msg2
msg3: db  "The sum is:", 10
len3: equ $ -msg3
msg4: db  "The average is:", 10
len4: equ $ -msg4
newline: db 10
msgdeb: db "Here", 10
lendeb: equ $ -msgdeb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
num: resw 1
temp: resb 1
count: resb 1
size: resw 1
array: resw 100
sum: resb 1
avg: resb 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .text
global _start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, msg1
mov edx, len1
int 80h

call read_num
mov cx, word[num]
mov word[size], cx

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

call read_array

mov ecx, 0
mov ebx, array
mov word[sum], 0


loop_count:

cmp cx, word[size]
je end_loop

mov ax, word[ebx + 2*ecx]
add word[sum], ax
inc cx
jmp loop_count

end_loop:

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

mov ax, word[sum]
mov word[num], ax
call print_num

mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h

mov ax, word[sum]
mov dx, 0
div word[size]
mov word[num], ax
call print_num

mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_array:

pusha
mov eax, 0
mov ebx, array

loop_array:

cmp ax, word[size]
je end_array
call read_num
mov cx, word[num]
mov word[ebx + 2*eax], cx
inc eax
jmp loop_array

end_array:
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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