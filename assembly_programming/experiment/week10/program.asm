.model small
.stack

.data
    frequency dw 415
              dw 524
              dw 588
              dw 660
              dw 698
              dw 784
              dw 880
              dw 988
              dw 1048
    sheet db '1 2 3 1   1 2 3 1   3 4 5   3 4 5   56543 1   56543 1   2 0 1   2 0 1 $'

.code
start:
    mov ax, @data
    mov ds, ax

    mov si, 0; si for sheet

main_loop:
    mov dl, sheet[si] ; dl for note
    ; print note
    mov ah, 2
    int 21h

    ; space for wait
    cmp sheet[si], ' '
    jne play_note
    mov cx, 65535
    call delay
    inc si
    jmp continue

play_note:
    ; get duration
    xor cx, cx
    inc si
    cmp sheet[si], ' '
    jne short_note
    add cx, 500
short_note:
    add cx, 500

    ; play note
    ; get frequency
    sub dl, '0'
    xor dh, dh
    add dx, dx ; because frequency is 2 bytes
    mov di, dx
    mov bx, frequency[di]
    call play_sound

    ; sub note (if exists)
    cmp sheet[si], ' '
    je continue
    ; get frequency
    mov cx, 500
    mov dl, sheet[si]
    mov ah, 2
    int 21h
    sub dl, '0'
    xor dh, dh
    add dx, dx ; because frequency is 2 bytes
    mov di, dx
    mov bx, frequency[di]
    call play_sound

continue:
    inc si
    cmp sheet[si], '$'
    jne main_loop

exit: ; properly exit
    mov ax, 4c00h
    int 21h

delay proc near
; cx: duration
delay_loop:
    nop
    loop delay_loop
    ret
delay endp

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
