section .data
msg1: db  "Enter the string:", 10
len1: equ $ -msg1
msg2: db  "The number of a's is:", 10
len2: equ $ -msg2
msg3: db  "The number of e's is:", 10
len3: equ $ -msg3
msg4: db  "The number of i's is:", 10
len4: equ $ -msg4
msg5: db  "The number of o's is:", 10
len5: equ $ -msg5
msg6: db  "The number of u's is:", 10
len6: equ $ -msg6
newline: db 10
msgdeb: db "Here", 10
lendeb: equ $ -msgdeb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
temp: resb 1
string_len: resw 1
string: resb 100
count: resb 1
num: resw 1
counta: resb 1
counte: resb 1
counti: resb 1
counto: resb 1
countu: resb 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .text
global _start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, msg1
mov edx, len1
int 80h

mov ebx, string
call read_string
mov ebx, string
dec ebx

mov byte[count], 0

loop:
inc ebx
cmp byte[ebx], 0
je end_loop
cmp byte[ebx], 65
je inccounta
cmp byte[ebx], 69
je inccounte
cmp byte[ebx], 73
je inccounti
cmp byte[ebx], 79
je inccounto
cmp byte[ebx], 85
je inccountu
cmp byte[ebx], 97
je inccounta
cmp byte[ebx], 101
je inccounte
cmp byte[ebx], 105
je inccounti
cmp byte[ebx], 111
je inccounto
cmp byte[ebx], 117
je inccountu
jmp loop

inccounta:
inc byte[counta]
jmp loop

inccounte:
inc byte[counte]
jmp loop

inccounti:
inc byte[counti]
jmp loop

inccounto:
inc byte[counto]
jmp loop

inccountu:
inc byte[countu]
jmp loop

end_loop:

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

movzx ax, byte[counta]
mov word[num], ax
call print_num

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

movzx ax, byte[counte]
mov word[num], ax
call print_num

mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h

movzx ax, byte[counti]
mov word[num], ax
call print_num

mov eax, 4
mov ebx, 1
mov ecx, msg5
mov edx, len5
int 80h

movzx ax, byte[counto]
mov word[num], ax
call print_num

mov eax, 4
mov ebx, 1
mov ecx, msg6
mov edx, len6
int 80h

movzx ax, byte[countu]
mov word[num], ax
call print_num

mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_string:    ;string in ebx

pusha
mov word[string_len], 0

loop_string_read:
push ebx
mov eax, 3
mov ebx, 0
mov ecx, temp
mov edx, 1
int 80h
pop ebx
cmp byte[temp], 10
je end_string_read

inc word[string_len]
mov al, byte[temp]
mov byte[ebx], al
inc ebx
jmp loop_string_read

end_string_read:
mov byte[ebx], 0

popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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