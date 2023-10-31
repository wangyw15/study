.model small
.stack

.data
    frequency dw 524
              dw 588
              dw 660
              dw 698
              dw 784
              dw 880
              dw 988
              dw 1048

.code
start:
    mov ax, @data
    mov ds, ax

main_loop:
    ; read key
    mov ah, 1
    int 21h
    ; detect if the key is valid
    cmp al, '1'
    jb main_loop
    cmp al, '8'
    ja main_loop
    sub al, '1'

    ; get frequency
    xor ah, ah
    add ax, ax
    mov si, ax
    mov bx, frequency[si]
    mov cx, 500
    call play_sound

    jmp main_loop

exit: ; properly exit
    mov ax, 4c00h
    int 21h

play_sound proc near
; bx: frequency
; cx: duration
    push ax
    push dx

    mov dx, cx ; dx as duration
    in al, 61h ; read port 61h
    and al, 11111100b ; turn off lower 2 bits
play:
    xor al, 2 ; toggle bit 1
    out 61h, al ; write to port 61h
    push ax
    push dx
    ; 1193180 / frequency
    mov dx, 0012h
    mov ax, 34dch
    div bx
    mov cx, ax ; set output duration
    pop dx
    pop ax
duration:
    loop duration
    dec dx
    jnz play

    pop dx
    pop ax
    ret
play_sound endp

end
