data segment
    crlf db 0dh, 0ah, '$'
data ends

code segment
assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    ; code starts here
    mov bl, 0 ; for row
    mov dl, 10h ; for char
    display:
    ; display character
    mov ah, 2
    int 21h
    ; new line
    cmp bl, 10h
    je newline
    jmp without_newline
    newline:
    push dx ; save dx
    lea dx, crlf
    mov ah, 9
    int 21h
    mov bl, 0 ; reset row counter
    pop dx ; restore dx
    without_newline:
    inc bl ; increase row counter
    ; compare
    inc dl
    cmp dl, 80h
    jne display
    ; return to dos
    mov al, 0
    mov ah, 4ch
    int 21h
code ends
end start
