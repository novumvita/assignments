;interchange i and n-i th words in n word string
section .data
    msg_enter: db "Enter a string:", 10
    l_enter: equ $ - msg_enter
    msg_result: db "Resultant string is:", 10
    l_result: equ $ - msg_result

section .bss
    string: resb 100
    str_len: resb 1
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

    movzx eax, byte[str_len]        ;string backward indexing
    mov ebx, string_result          ;string_result forward indexing
    mov cx, 0                       ;length of word
    

    ;iterate through string and write to result string in reverse
    string_wreverse_loop:
        cmp al, 0 
        je string_wreverse_loop_end

        cmp byte[string + eax - 1], ' '
        jne not_word_beginning
        ;is_word_beginning
            pusha

            mov edx, string
            add edx, eax
            
            push ebx        ;string destination
            push edx        ;string source
            push cx         ;write length
            call write_word
            
            popa

            add bx, cx
            mov byte[ebx], ' '
            inc ebx

            mov cx, 0
            jmp check_end

        not_word_beginning:
            inc cx
        
        check_end:
        dec eax
        jmp string_wreverse_loop
    string_wreverse_loop_end:
    
    ;write first word to end of string_result
                
    push ebx        ;string destination
    push string        ;string source
    push cx         ;write length
    call write_word

    add bx, cx
    mov byte[ebx], 0

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