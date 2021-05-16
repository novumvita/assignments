;find largest and smallest word in string
section .data
    msg_enter: db "Enter a string:", 10
    l_enter: equ $ - msg_enter
    msg_largest: db "Largest word is "
    l_largest: equ $ - msg_largest
    msg_smallest: db 10, "Smallest word is "
    l_smallest: equ $ - msg_smallest

section .bss
    string: resb 100
    str_len: resb 1
    largest: resd 1
    smallest: resd 1

section .text
    global _start
    _start:

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_enter
    mov edx, l_enter
    int 80h

    push string
    push str_len
    call read_string

    mov ch, 0           ;count highest
    mov cl, 101         ;count lowest

    movzx eax, byte[str_len]
    mov byte[string + eax], ' '
    mov byte[string + eax + 1], 0        ;append space to end of string

    mov eax, string
    mov bl, 0           ;word size count
    mov edx, string     ;pointer to current word

    string_check_loop:
        cmp byte[eax], 0
        je string_check_loop_end

        cmp byte[eax], ' '
        jne not_word_end
        ;is_word_end
            cmp bl, cl
            jnb not_smallest
            ;is_smallest
                mov dword[smallest], edx
                mov cl, bl
            not_smallest:
            cmp bl, ch
            jna not_biggest
            ;is_biggest
                mov dword[largest], edx
                mov ch, bl
            not_biggest:
            
            mov byte[eax], 0
            mov edx, eax
            inc edx
            mov bl, 0

        not_word_end:
        inc eax
        inc bl
        jmp string_check_loop
    string_check_loop_end:

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_largest
    mov edx, l_largest
    int 80h

    push dword[largest]
    call print_string

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_smallest
    mov edx, l_smallest
    int 80h

    push dword[smallest]
    call print_string

    mov eax, 1
    mov ebx, 0
    int 80h

    ;reads string into length [pop] and array [pop] 
    read_string:
        pop eax     ;return address
        pop ecx     ;length
        pop ebx     ;array
        push eax

        mov eax, 0  ;iterator

        string_input_loop:
            pusha
            mov ecx, ebx
            add ecx, eax    ;ecx ebx + eax
            mov eax, 3
            mov ebx, 0
            mov edx, 1
            int 80h
            popa

            cmp byte[ebx + eax], 10
            je string_input_loop_end

            inc eax
            jmp string_input_loop
        string_input_loop_end:
        
        mov byte[ebx + eax], 0      ;string end
        mov byte[ecx], al           ;length
        ret

    ;prints string in array [pop]
    print_string:
        pop eax     ;return address
        pop ebx     ;array
        push eax

        mov eax, 0

        string_print_loop:
            cmp byte[ebx + eax], 0
            je string_print_loop_end

            pusha
            mov ecx, ebx
            add ecx, eax    ;ecx = ebx+eax
            mov eax, 4
            mov ebx, 1
            mov edx, 1
            int 80h
            popa

            inc eax
            jmp string_print_loop
        string_print_loop_end:
        ret
