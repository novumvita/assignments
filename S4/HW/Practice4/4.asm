section .data
msg1: db  "Enter the first string:", 10
len1: equ $ -msg1
msg2: db  "Enter the second string:", 10
len2: equ $ -msg2
msg3: db  "The strings are the same.", 10
len3: equ $ -msg3
msg4: db  "The strings are not the same. They differ at this position:", 10
len4: equ $ -msg4
newline: db 10
msgdeb: db "Here", 10
lendeb: equ $ -msgdeb
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .bss
temp: resb 1
string_len: resw 1
string: resb 100
string2: resb 100
stringlen1: resw 1
count: resb 1
num: resw 1
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

mov ebx, string2
call read_string

mov eax, string
mov ebx, string2

; mov cx, word[stringlen1]
; cmp cx, word[string_len]
; jne noteq
mov ecx, string
add cx, word[string_len]
mov edx, string2
add dx, word[stringlen1]

loop:

cmp eax, ecx
je endoffirst
cmp ebx, edx
je endofsec
push edx
mov dl, byte[ebx]
cmp byte[eax], dl
pop edx
jne noteq
inc eax
inc ebx
jmp loop

endoffirst:
cmp ebx, edx
je eq
jmp noteq

endofsec:
cmp eax, ecx
je eq
jmp noteq

eq:
mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h
jmp end

noteq:
push eax
mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h
pop eax

sub eax, string
inc eax
mov word[num], ax
call print_num

end:
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
mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, 1
int 80h
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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