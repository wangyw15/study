.model small
.stack

.data
    name_prompt           db 'Enter name: $'
    phone_prompt          db 'Enter number: $'
    complete_prompt       db 'Enter complete! $'
    crlf                  db 0dh, 0ah, '$'
    name_buffer           db 15, '?', 15 dup('$')
    phone_buffer          db 15, '?', 15 dup('$')
    table_buffer          db 300 dup('$')

.code
start:
    mov ax, @data
    mov ds, ax

    call add_data_proc
    call print_table_proc
query_loop:
    call search_phone_by_name_proc
    call new_line_proc
    jmp query_loop

exit:
    ; properly exit
    mov ax, 4c00h
    int 21h

add_data_proc proc near
    push ax
    push bx
    push cx
    push dx
    push di

    ; get table pointer
    lea di, table_buffer ; di = table_buffer

enter_data:
    ; input name
    lea dx, name_prompt
    call print_string_proc
    lea dx, name_buffer
    call input_string_proc
    call new_line_proc
    ; empty name means end of input
    mov al, [name_buffer + 1]
    cmp al, 0
    je enter_complete

    ; input phone
    lea dx, phone_prompt
    call print_string_proc
    lea dx, phone_buffer
    call input_string_proc
    call new_line_proc

    ; add name to table
    lea bx, name_buffer
    add bx, 2
    mov cx, 15
copy_name:
    mov al, [bx]
    mov [di], al
    inc bx
    inc di
    loop copy_name

    ; add phone to table
    lea bx, phone_buffer
    add bx, 2
    mov cx, 15
copy_phone:
    mov al, [bx]
    mov [di], al
    inc bx
    inc di
    loop copy_phone

    jmp enter_data

enter_complete:
    lea dx, complete_prompt
    call print_string_proc
    call new_line_proc

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret
add_data_proc endp

search_phone_by_name_proc proc near
    push ax
    push bx
    push cx
    push dx

    ; input name
    lea dx, name_prompt
    call print_string_proc
    lea dx, name_buffer
    call input_string_proc
    call new_line_proc

    ; compare name
    lea bx, table_buffer ; bx = table_buffer
    mov cx, 10 ; max 10 rows
search_phone_loop:
    push cx
    xor cx, cx
    lea si, name_buffer ; si = name_buffer
    add si, 2 ; skip length
    mov di, bx
compare_name_loop:
    mov al, [si]
    cmp al, [di]
    jne compare_complete
    inc si
    inc di
    inc cx
    cmp cx, 15
    jne compare_name_loop
compare_complete:
    cmp cx, 15
    jne compare_fail
    ; print phone
    mov dx, bx
    add dx, 15 ; skip name
    call print_string_proc
compare_fail:
    pop cx
    add bx, 30 ; next name
    loop search_phone_loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret
search_phone_by_name_proc endp

print_table_proc proc near
    push cx
    push dx

    ; get table pointer
    lea dx, table_buffer ; dx = table_buffer
    mov cx, 20 ; 300 / 15 = 20

print_table_loop:
    ; print cell
    call print_string_proc
    call new_line_proc
    add dx, 15
    loop print_table_loop

    pop dx
    pop cx
    ret
print_table_proc endp

new_line_proc proc near
    push ax
    push dx
    mov dx, offset crlf
    call print_string_proc
    pop dx
    pop ax
    ret
new_line_proc endp

print_string_proc proc near ; print string at ds:dx
    push ax
    mov ah, 9
    int 21h
    pop ax
    ret
print_string_proc endp

input_string_proc proc near
    push ax
    mov ah, 0ah
    int 21h
    pop ax
    ret
input_string_proc endp

end start
