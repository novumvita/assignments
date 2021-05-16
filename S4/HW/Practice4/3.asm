section .data
msg1: db  "Enter the first string:", 10
len1: equ $ -msg1
msg2: db  "Enter the second string:", 10
len2: equ $ -msg2
msg3: db  "The concatenated string is:", 10
len3: equ $ -msg3
newline: db 10
msgdeb: db "Here", 10
lendeb: equ $ -msgdeb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
temp: resb 1
string_len: resw 1
string: resb 100
string1: resb 100
stringconc: resb 200
stringlen1: resw 1
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
mov ax, word[string_len]
mov word[stringlen1], ax

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

mov ebx, string1
call read_string

mov eax, string
mov ebx, stringconc

loop:
cmp byte[eax], 0
je firstover
mov cl, byte[eax]
mov byte[ebx], cl
inc eax
inc ebx
jmp loop
firstover:
mov byte[ebx], 32
inc ebx
mov eax, string1
loop2:
cmp byte[eax], 0
je over
mov cl, byte[eax]
mov byte[ebx], cl
inc eax
inc ebx
jmp loop2
over:

mov byte[ebx], 0

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

mov ebx, stringconc
call print_string

mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, 1
int 80h

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
mov ebx, string
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_string:           ;string in ebx
pusha

loop_string_print:
mov al, byte[ebx]
mov byte[temp], al
cmp byte[temp], 0
je end_string_print

push ebx
mov eax, 4
mov ebx, 1
mov ecx, temp
mov edx, 1
int 80h
pop ebx
inc ebx
jmp loop_string_print

end_string_print:
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;