.model small
.stack
.data
    enter_table_prompt db 'Enter a string: $'
    enter_char_prompt db 'Enter a character: $'
    crlf db 0dh, 0ah, '$'
    table db 100 dup('$')
    n db 0
    char db 0

.code
    mov ax, @data
    mov ds, ax

    ; enter table
    call enter_table
    call new_line

main_loop:
    ; print char prompt
    lea dx, enter_char_prompt
    mov ah, 9
    int 21h
    mov ah, 1
    int 21h
    mov char, al
    call new_line

    ; count char
    call count_char

    ; print result
    mov dl, n
    xor dh, dh
    cmp n, '9'
    jle number
number:
    add dl, '0'
    jmp print_digit
letter:
    add dl, 'A' - 10
print_digit:
    mov ah, 2
    int 21h

    call new_line
    jmp main_loop

exit:
    mov ax, 4c00h
    int 21h

count_char proc near
    push ax
    push dx
    push si

    ; search in table
    xor si, si
    mov al, char
    mov ah, 0 ; ah for counter
count_loop:
    cmp table[si], '$'
    je count_end
    cmp al, table[si]
    jne not_found
    inc ah
not_found:
    inc si
    jmp count_loop

count_end:
    mov n, ah

    pop si
    pop dx
    pop ax
    ret
count_char endp

enter_table proc near
    push ax
    push dx
    push si

    ; print prompt
    lea dx, enter_table_prompt
    mov ah, 9
    int 21h

    ; enter table
    xor si, si
    mov ah, 1
input_loop:
    int 21h
    cmp al, 0dh
    je input_end
    mov table[si], al
    inc si
    jmp input_loop

input_end:
    pop si
    pop dx
    pop ax
    ret
enter_table endp

new_line proc near
    push ax
    push dx

    lea dx, crlf
    mov ah, 9
    int 21h

    pop dx
    pop ax
    ret
new_line endp

end
