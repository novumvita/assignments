section .data
msg1: db  "Enter the number of elements in the first array:", 10
len1: equ $ -msg1
msg2: db  "Enter the numbers in the first array:", 10
len2: equ $ -msg2
msg3: db  "Enter the number of elements in the second array:", 10
len3: equ $ -msg3
msg4: db  "Enter the numbers in the second array:", 10
len4: equ $ -msg4
msg5: db  "The common elements are:", 10
len5: equ $ -msg5
newline: db 10
msgdeb: db "Here", 10
lendeb: equ $ -msgdeb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
num: resw 1
temp: resb 1
count: resb 1
size1: resw 1
array1: resw 100
size2: resw 1
array2: resw 100
size: resw 1
array: resd 1
number: resw 1
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
mov word[size1], cx

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

mov ebx, array1
mov eax, 0
mov ax, word[size1]
mov word[size], ax
call read_array

call sort_array

;call print_array

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

call read_num
mov cx, word[num]
mov word[size2], cx

mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h

mov ebx, array2
mov eax, 0
mov ax, word[size2]
mov word[size], ax
call read_array

call sort_array

mov eax, 4
mov ebx, 1
mov ecx, msg5
mov edx, len5
int 80h

mov eax, array1
mov ebx, array2
mov ecx, 0
mov edx, 0

loop:
cmp cx, word[size1]
je end_loop
cmp dx, word[size2]
je end_loop
push ebx
mov bx, word[eax + 2*ecx]
mov word[num], bx
pop ebx
push eax
mov ax, word[ebx + 2*edx]
cmp ax, word[num]
pop eax
je equal
ja ba
jb ab
equal:
push eax
mov ax, word[ebx + 2*edx]
mov word[num], ax
call print_num
pop eax
inc ecx
inc edx
jmp loop
ba:
inc ecx
jmp loop
ab:
inc edx
jmp loop
end_loop:

mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_array:

mov eax, 0

loop_array_read:

cmp ax, word[size]
je end_array_read
call read_num
mov cx, word[num]
mov word[ebx + 2*eax], cx
inc eax
jmp loop_array_read

end_array_read:
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_array:

mov eax, 0
mov ecx, 0
loop_array_print:

cmp cx, word[size]
je end_array_print

mov ax, word[ebx + 2*ecx]
mov word[num], ax
call print_num
inc cx
jmp loop_array_print

end_array_print:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
sort_array:

mov eax, 1

outer_loop:

mov ecx, eax
cmp ax, word[size]
je outer_loop_end

inner_loop:
mov edx, ecx
sub edx, 1
cmp ecx, 1
push eax
jb inner_loop_end
mov ax, word[ebx + 2*edx]
cmp word[ebx + 2*ecx], ax
ja inner_loop_end
call bubble_swap
mov word[ebx + 2*edx], ax
dec ecx
pop eax
jmp inner_loop
inner_loop_end:
pop eax
inc eax
jmp outer_loop
outer_loop_end:
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bubble_swap:
push edx
mov dx, ax
mov ax, word[ebx + 2*ecx]
mov word[ebx + 2*ecx], dx
pop edx
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;