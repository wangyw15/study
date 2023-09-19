data segment
    letter        db 0
    digit         db 0
    other         db 0
    enter_prompt  db 'Enter: $'
    letter_prompt db 0dh, 0ah, 'Letters: $'
    digit_prompt  db ' Digits: $'
    other_prompt  db ' Others: $'
data ends

code segment
    assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    ; prompt
    lea dx, enter_prompt
    mov ah, 09h
    int 21h

    mov cx, -1
    ; read chars
    read:
        inc cx
        ; no more than 80 chars
        cmp cx, 80
        je end_read

        mov ah, 01h
        int 21h
        ; check for enter
        cmp al, 0dh
        je end_read
        ; lower check
        cmp al, 'a'
        jb upper_letter
        cmp al, 'z'
        ja other_char
        ; increment letter
        inc letter
        jmp read

    upper_letter:
        ; upper check
        cmp al, 'A'
        jb digit_char
        cmp al, 'Z'
        ja other_char
        ; increment letter
        inc letter
        jmp read

    digit_char:
        ; digit check
        cmp al, '0'
        jb other_char
        cmp al, '9'
        ja other_char
        ; increment digit
        inc digit
        jmp read

    other_char:
        inc other
        jmp read
    
    end_read:
        ; prompt
        lea dx, letter_prompt
        mov ah, 09h
        int 21h
        ; print number
        mov al, letter
        call print_number
        call print_new_line

        ; prompt
        lea dx, digit_prompt
        mov ah, 09h
        int 21h
        ; print number
        mov al, digit
        call print_number
        call print_new_line

        ; prompt
        lea dx, other_prompt
        mov ah, 09h
        int 21h
        ; print number
        mov al, other
        call print_number
        call print_new_line
    
    ; quit to dos
    xor al, al
    mov ah, 4ch
    int 21h

; print number in al
print_number proc near
    push ax
    push bx
    push cx
    push dx

    xor ah, ah
    mov bx, 10
    xor cx, cx
    get_digit_loop:
        div bl
        push ax
        xor ah, ah
        inc cx
        cmp al, 0
        jne get_digit_loop

    print_digit_loop:
        pop ax
        mov dl, ah
        add dl, '0'
        mov ah, 02h
        int 21h
        loop print_digit_loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_number endp

print_new_line proc near
    push ax
    push dx

    mov dl, 0ah
    mov ah, 02h
    int 21h
    mov dl, 0dh
    mov ah, 02h
    int 21h

    pop dx
    pop ax
    ret
print_new_line endp

code ends
end start
