; bug still exists
.model small
.stack

.data
keyword_prompt db 'Enter keyword: $'
sentence_prompt db 'Enter sentence: $'
matched_prompt_prefix db 'Match at location: $'
matched_prompt_suffix db 'H of the sentence.$'
not_matched_prompt db 'No match.$'
crlf db 0dh, 0ah, '$'
keyword_buffer db 80, '?', 80 dup('$')
sentence_buffer db 80, '?', 80 dup('$')

.code
start:
    mov ax, @data
    mov ds, ax
    mov es, ax ; for repe cmpsb

begin:
    ; get keyword
    mov dx, offset keyword_prompt
    mov ah, 9
    int 21h
    mov dx, offset keyword_buffer
    mov ah, 0ah
    int 21h
    call new_line_proc

    ; get sentence
    mov dx, offset sentence_prompt
    mov ah, 9
    int 21h
    mov dx, offset sentence_buffer
    mov ah, 0ah
    int 21h
    call new_line_proc

    ; search for keyword
    lea si, sentence_buffer + 1
    xor cx, cx
    lea bx, sentence_buffer
    inc bx
    mov dl, ds:[bx]
    xor dh, dh
    inc dx
search_loop:
    dec dx
    jz failed
    inc si
    lea di, keyword_buffer + 2
    mov cl, keyword_buffer + 1
    mov al, ds:[si]
    mov bl, ds:[di]
    repe cmpsb ; cx always -1
    cmp cx, 0
    jne search_loop

    ; check if fully matched
    cmp cx, 0
    je matched
    jmp failed

failed:
    mov dx, offset not_matched_prompt
    mov ah, 9
    int 21h
    call new_line_proc
    jmp begin

matched:
    ; print matched location
    mov dx, offset matched_prompt_prefix
    mov ah, 9
    int 21h

    mov ax, si
    lea bx, keyword_buffer
    inc bx
    mov bl, ds:[bx]
    sub ax, bx
    sub ax, offset sentence_buffer + 1
    mov cx, 2

; ignore ah (rol ax, 8)
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1

print_loop:
    ; rol ax, 4
    rol ax, 1
    rol ax, 1
    rol ax, 1
    rol ax, 1
    ; to ascii
    mov dl, al
    and dl, 0fh
    ; cmp dl, 0
    ; je continue_print_loop
    cmp dl, 9
    jbe print_digit
    add dl, 'A' - 10
    jmp print_char
print_digit:
    add dl, '0'
print_char:
    push ax
    mov ah, 2
    int 21h
    pop ax
continue_print_loop:
    dec cx
    jnz print_loop

print_matched_prompt_suffix:
    mov dx, offset matched_prompt_suffix
    mov ah, 9
    int 21h
    call new_line_proc

    jmp begin
    mov ax, 4c00h
    int 21h

new_line_proc proc near
    push ax
    push dx
    mov dx, offset crlf
    mov ah, 9
    int 21h
    pop dx
    pop ax
    ret
new_line_proc endp

end start
