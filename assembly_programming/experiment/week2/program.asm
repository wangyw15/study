data segment
    input_prompt      db ' Enter: $'
    too_long_prompt   db 'String too long$'
    empty_line_prompt db 'Empty line$'
    length_prompt     db 'Length: $'
    duration_prompt   db 'Execution time (in seconds): $'
    crlf              db 0dh, 0ah, '$'
    buffer            db 50
                      db ?
                      db 50 dup('$')
data ends

code segment
assume ds:data, cs:code

start:
    mov ax, data
    mov ds, ax

    ; get start time
    call proc_get_seconds
    push ax

    ; prompt
    lea dx, input_prompt
    mov ah, 09h
    int 21h

    ; get the input
    lea dx, buffer
    mov ah, 0ah
    int 21h

    call proc_new_line

    cmp buffer+1, 48 ; buffer-2 is the max length of the string
    ja too_long ; useless
    cmp buffer+1, 0 ; detect empty line
    je empty_line
    jmp upper_case_process
    empty_line:
        lea dx, empty_line_prompt
        mov ah, 09h
        int 21h
        jmp exit
    too_long:
        lea dx, too_long_prompt
        mov ah, 09h
        int 21h
        jmp exit
    
    upper_case_process:
    ; print length prompt
    lea dx, length_prompt
    mov ah, 09h
    int 21h
    ; print length
    mov al, buffer+1
    call proc_print_number

    call proc_new_line

    ; to upper case
    lea si, buffer+2
    mov cl, buffer+1
    upper_case_loop:
        mov al, [si]
        ; and al, 11011111b
        cmp al, 'a'
        ja next
        jmp final
        next:
            cmp al, 'z'
            jb next2
        next2:
            sub al, 20h
        final:
        mov [si], al
        inc si
        loop upper_case_loop

    ; write the string
    lea dx, buffer+2
    mov ah, 09h
    int 21h

    call proc_new_line

    ; executing duration
    lea dx, duration_prompt
    mov ah, 09h
    int 21h

    call proc_get_seconds
    mov bx, ax
    pop ax
    sub bx, ax
    mov ax, bx
    call proc_print_number

    ; return to dos
    exit:
        mov al, 0
        mov ah, 4ch
        int 21h

proc_new_line proc near ; new line
    push ax
    push dx

    lea dx, crlf
    mov ah, 09h
    int 21h

    pop ax
    pop dx
    ret
proc_new_line endp

proc_print_char proc near ; print char
    push ax
    mov ah, 02h
    int 21h
    pop ax
    ret
proc_print_char endp

proc_print_number proc near ; print number in al
    ; protect registers
    push bx
    push cx
    push dx

    mov ah, 0 ; reset high byte
    mov cx, 0 ; count count of digits
    mov bl, 10 ; print decimal
    calculate_loop: ; get digits
        inc cx
        div bl
        push ax
        mov ah, 0
        cmp al, 0
        jne calculate_loop
    
    print_number_loop: ; print digits
        pop ax
        mov dl, ah
        add dl, 30h
        call proc_print_char
        loop print_number_loop
    
    pop bx
    pop cx
    pop dx
    ret
proc_print_number endp

proc_get_seconds proc near ; get current seconds in one day
    ; protect
    push bx
    push cx
    push dx

    ; get time
    mov ah, 2ch
    int 21h
    ; init
    mov bx, 0
    ; seconds
    mov dl, dh
    ; dx as result/temp
    mov dh, 0
    ; minutes
    mov ax, 0
    mov al, cl
    mov bl, 60
    mul bl
    add dx, ax
    ; hours
    ; mov ax, 0
    ; mov al, ch
    ; mov bx, 3600
    ; mul bx
    ; add dx, ax

    mov ax, dx
    
    pop bx
    pop cx
    pop dx
    ret
proc_get_seconds endp

code ends
end start
