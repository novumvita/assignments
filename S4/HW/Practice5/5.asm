;search and replace word
section .data
    msg_enter: db "Enter a string:", 10
    l_enter: equ $ - msg_enter
    msg_replace1: db "Enter word to be replaced: "
    l_replace1: equ $ - msg_replace1
    msg_replace2: db "Enter word to replace with: "
    l_replace2: equ $ - msg_replace2
    msg_result: db "Resultant string is:", 10
    l_result: equ $ - msg_result

section .bss
    string: resb 100
    str_len: resb 1
    word_remove: resb 50
    len_remove: resb 1
    word_replace: resb 50
    len_replace: resb 1
    string_result: resb 100

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

    movzx eax, byte[str_len]
    mov byte[string + eax], ' '
    mov byte[string + eax + 1], 0        ;append space to end of string

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_replace1
    mov edx, l_replace1
    int 80h

    push word_remove
    push len_remove
    call read_string

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_replace2
    mov edx, l_replace2
    int 80h

    push word_replace
    push len_replace
    call read_string

    mov eax, string             ;iterator
    mov ebx, string             ;pointer to word beginning
    mov ecx, string_result      ;pointer to result string
    string_replace_loop:
        cmp byte[eax], 0
        je string_replace_loop_end

        cmp byte[eax], ' '
        jne not_word_end
        ;is_word_end
            mov byte[eax], 0
            pusha
            push ebx
            push word_remove
            call string_cmp
            pop dx
            cmp dx, 1
            popa

            jne no_replace_word
            ;replace word
                movzx dx, byte[len_replace]
                pusha
                push ecx
                push word_replace
                jmp call_write_word
            no_replace_word:
                mov edx, eax
                sub edx, ebx        ;word length
                pusha
                push ecx
                push ebx

            call_write_word:
            push dx
            call write_word
            popa

            add cx, dx
            mov byte[ecx], ' '
            inc ecx

            mov ebx, eax
            inc ebx

        not_word_end:
        inc eax
        jmp string_replace_loop
    string_replace_loop_end:

    mov byte[ecx-1], 0

    mov eax, 4
    mov ebx, 1
    mov ecx, msg_result
    mov edx, l_result
    int 80h

    push string_result
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

    ;writes length [pop](word) from string [pop] into string [pop] 
    write_word:
        pop eax     ;ra
        pop bx      ;length
        pop ecx     ;string source
        pop edx     ;string destination
        push eax


        mov eax, 0
        string_write_loop:
            cmp ax, bx
            je string_write_loop_end

            push bx
            mov bl, byte[ecx+eax]
            mov byte[edx+eax], bl
            pop bx

            inc eax
            jmp string_write_loop
        string_write_loop_end:
        ret

    ;compares strings [pop](string2) and [pop](string1) and [push] 0 if string1 < string 2 , 1 if =, 2 if >  
    string_cmp:
        pop eax     ;ra
        pop ecx     ;string2
        pop ebx     ;string1
        push eax

        mov eax, 0

        string_compare_loop:
            mov dl, byte[ebx + eax]
            cmp dl, byte[ecx + eax]
            jb result_before
            ja result_after

            cmp dl, 0
            je result_equal

            inc eax
            jmp string_compare_loop
        string_compare_end:
    
        result_before:      ;string1 is before string2
        mov dx, 0
        jmp push_to_stack

        result_equal:
        mov dx, 1
        jmp push_to_stack

        result_after:
        mov dx, 2
        
        push_to_stack:
        pop eax     ;ra
        push dx
        push eax

        ret