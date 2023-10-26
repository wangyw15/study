.model small
.stack
.data
    start_prompt db 'start now$'
    end_prompt db 'duration: $'

.code
mov ax, @data
mov ds, ax

; print start prompt
mov ah, 9
mov dx, offset start_prompt
int 21h

; get start time
call proc_get_seconds
push ax

; code goes here

; get end time
call proc_get_seconds
pop bx
sub ax, bx

; print duration
mov ah, 9
mov dx, offset end_prompt
int 21h
call proc_print_number

; exit
mov ax, 4c00h
int 21h

proc_print_number proc near ; print number in ax
    ; protect registers
    push ax
    push bx
    push cx
    push dx
    ; start
    xor cx, cx ; clear cx and use it as counter
    mov bx, 10 ; use bx as divider
loop_calculate:
    div bl ; divide ax by bx
    push ax ; push result to stack
    xor ah, ah ; clear ah
    inc cx ; increase counter
    cmp al, 0 ; check if result is zero
    jne loop_calculate ; if not, repeat loop

loop_print:
    pop dx ; pop result from stack
    mov dl, dh ; dl is the digit
    xor dh, dh ; clear dh
    add dl, '0' ; convert number to char
    mov ah, 2 ; print char
    int 21h
    loop loop_print
    ; return
    pop dx
    pop cx
    pop bx
    pop ax
    ret
proc_print_number endp

proc_get_seconds proc near
; get current seconds in one hour
; result in ax
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
    
    pop dx
    pop cx
    pop bx
    ret
proc_get_seconds endp

end
