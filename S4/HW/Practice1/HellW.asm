section .data
string: db "Hello World!", 0Ah
length: equ $ -string

section .text

	global _start:
	_start:

	mov eax, 4
	mov ebx, 1
	mov ecx, string
	mov edx, length
	int 80h
	
	mov eax, 1
	mov ebx, 0
	int 80h

; 	read_num:
; 	pusha
; 	mov dword[just_read],0
; 	reading:
; 		mov eax,3
; 		mov ebx,0
; 		mov ecx,temp
; 		mov edx,1
; 		int 80h

; 		cmp dword[temp],10
; 		je end_read
; 		sub dword[temp],30h
; 		mov eax,dword[just_read]
; 		mov edx,0
; 		mov ebx,10
; 		mul ebx
; 		add eax,dword[temp]
; 		mov dword[just_read],eax
; 		jmp reading
; end_read:
; 	popa
; 	ret