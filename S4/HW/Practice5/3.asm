;sort words in a string to lexicographic order
section .data
    msg_enter: db "Enter a string:", 10
    l_enter: equ $ - msg_enter
    msg_result: db "Resultant string is:", 10
    l_result: equ $ - msg_result

section .bss
    string: resb 100
    str_len: resb 1
    string_result: resb 100
    word_array: resd 50
    word_array_size: resb 1

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

    ;add all words to word array
    ;(not handling empty string)
    cmp byte[string], 65
    jb not_capital_init
    cmp byte[string], 90
    ja not_capital_init
    ;is_capital
    add byte[string], 32        ;to small letter
    not_capital_init:

    mov eax, string
    mov ebx, word_array
    mov dword[ebx], eax
    add ebx, 4
    mov byte[word_array_size], 1
    inc eax

    
    string_word_loop:
        cmp byte[eax], 0
        je string_word_loop_end

        cmp byte[eax], 65
        jb not_capital
        cmp byte[eax], 90
        ja not_capital
        ;is_capital
        add byte[eax], 32        ;to small letter
        not_capital:

        cmp byte[eax - 1], ' '
        jne not_word_beginning
        ;byte[eax - 1] == ' '
            mov byte[eax - 1], 0        ;separate word strings
            mov dword[ebx],eax
            add ebx, 4
            inc byte[word_array_size]
            
        not_word_beginning:
        inc eax
        jmp string_word_loop
    string_word_loop_end:

    ;sort words in word array [bubble sort]
    mov eax, 0
    word_sort_loop:
        cmp al, byte[word_array_size]
        je word_sort_loop_end
        movzx ebx, byte[word_array_size]
        sub ebx, eax

        mov ecx, 1
        mov edx, word_array
        add edx, 4
        push eax

        inner_sort_loop:
            cmp ecx, ebx
            jnb end_inner_sort_loop

            pusha
            push dword[edx]
            push dword[edx-4]
            call string_cmp     ;will push 0 to stack if string[edx] < string[edx-4]
            pop dx
            cmp dx, 0
            popa
            jne swap_complete
            ;string[edx] < string[edx-4]
                push dword[edx]
                mov eax, dword[edx-4]
                mov dword[edx], eax
                pop eax
                mov dword[edx-4], eax
            swap_complete:

            inc ecx
            add edx, 4
            jmp inner_sort_loop
        end_inner_sort_loop:

        pop eax
        inc eax
        jmp word_sort_loop
    word_sort_loop_end:

    ;write words in word_array to string_result
    mov eax, 0
    mov edx, string_result

    string_result_write_loop:
        cmp al, byte[word_array_size]
        je string_result_write_loop_end

        ;find length of word
        mov ecx, 0
        mov ebx, dword[word_array + 4*eax]

        string_length_loop:
            cmp byte[ebx+ecx], 0
            je string_length_loop_end
            inc ecx
            jmp string_length_loop
        string_length_loop_end:

        pusha
        push edx
        push ebx
        push cx
        call write_word
        popa
        add dx, cx
        mov byte[edx], ' '
        inc edx

        inc eax
        jmp string_result_write_loop
    string_result_write_loop_end:

    dec edx
    mov byte[edx], 0

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

