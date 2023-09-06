data segment
    input_prompt db 'Enter a string: ', '$'
    too_long_prompt db 'String too long', '$'
    empty_line_prompt db 'Empty line', '$'
    crlf db 0dh, 0ah, '$'
    buffer db 50
           db ?
           db 50 dup('$')
data ends

code segment
assume ds:data, cs:code

start:
    mov ax, data
    mov ds, ax

    ; prompt
    lea dx, input_prompt
    mov ah, 09h
    int 21h

    ; get the input
    lea dx, buffer
    mov ah, 0ah
    int 21h

    call newline

    cmp buffer+1, 48 ; buffer-2 is the max length of the string
    ja too_long
    cmp buffer+1, 0
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

    ; return to dos
    exit:
        mov al, 0
        mov ah, 4ch
        int 21h

newline proc near ; new line
    lea dx, crlf
    mov ah, 09h
    int 21h
    ret
newline endp

code ends
end start
