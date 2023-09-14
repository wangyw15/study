data segment
array db 10 dup(0)
      db '$'
data ends

code segment
assume cs:code, ds:data
start:
    mov cx, 0 ; count for chars
    mov di, 0
    ; lea bx, array
    read_char: ; read char from keyboard
        mov ah, 01h
        int 21h
        ; check if the char is enter
        cmp al, 0dh
        je exit
        ; find position
        mov di, 0 ; di is the position, cx is current count - 1
        find_position:
            cmp al, array[di]
            jbe move_start
            inc di
            cmp di, 9
            jne find_position

        move_start:
        mov dx, di ; dx is the position
        mov di, 9
        push ax
        move:
            dec di
            mov al, array[di]
            inc di
            mov array[di], al
            dec di
            cmp di, dx
            jne move
        pop ax

        mov array[di], al
        inc cx
        cmp cx, 10
        jb read_char

    ; new line
    mov dl, 0ah
    mov ah, 02h
    int 21h
    mov dl, 0dh
    int 21h

    mov di, 0
    print:
        mov ah, 02h
        mov dl, array[di]
        int 21h
        inc di
        cmp di, 10
        jne print

    exit:
    mov al, 0
    mov ah, 4ch
    int 21h
code ends
end start
