.model small
.stack

.data
    split_line            db '*********************************************************', 0dh, 0ah, '$'
    menu_1                db 'Please input', 0dh, 0ah, '$'
    menu_2                db '1 print "hello world!"', 0dh, 0ah, '$'
    menu_3                db '2 adder', 0dh, 0ah, '$'
    menu_4                db '3 display current time', 0dh, 0ah, '$'
    menu_5                db '4 quit', 0dh, 0ah, '$'
    hello_world           db 'hello world!', 0dh, 0ah, '$'
    num1_prompt           db 'Enter first number:  $'
    num2_prompt           db 'Enter second number: $'
    crlf                  db 0dh, 0ah, '$'
    invalid_choice_prompt db 'Invalid choice!', 0dh, 0ah, '$'
    transfer_table        dw selection_1
                          dw selection_2
                          dw selection_3
                          dw selection_4

.code
start:
    mov ax, @data
    mov ds, ax

loop_main:
    call proc_print_menu
    mov ah, 1
    int 21h ; get choice
    call proc_newline
    ; check if choice is valid
    cmp al, '1'
    jb invalid_choice
    cmp al, '4'
    ja invalid_choice
    sub al, '1' ; get index
    xor ah, ah ; clear ah
    mov bx, 2
    mul bl ; ax *= 2
    mov si, ax ; si = ax
    jmp transfer_table[si]
selection_1:
    call proc_print_hello_world
    jmp loop_main
selection_2:
    call proc_adder
    jmp loop_main
selection_3:
    call proc_print_time
    jmp loop_main
selection_4:
    jmp exit
invalid_choice:
    lea dx, invalid_choice_prompt
    mov ah, 9
    int 21h
    jmp loop_main
exit:
    ; properly exit
    mov ax, 4c00h
    int 21h

proc_newline proc near
    push ax
    push dx
    lea dx, crlf
    mov ah, 9
    int 21h
    pop dx
    pop ax
    ret
proc_newline endp

proc_print_menu proc near
    push ax
    push dx
    lea dx, split_line
    mov ah, 9
    int 21h
    lea dx, menu_1
    int 21h
    lea dx, menu_2
    int 21h
    lea dx, menu_3
    int 21h
    lea dx, menu_4
    int 21h
    lea dx, menu_5
    int 21h
    lea dx, split_line
    int 21h
    pop dx
    pop ax
    ret
proc_print_menu endp

proc_print_hello_world proc near
    push ax
    push dx
    lea dx, hello_world
    mov ah, 9
    int 21h
    pop dx
    pop ax
    ret
proc_print_hello_world endp

; read number from keyboard and return it in ax
proc_read_number proc near
    push bx
    push cx
    push dx
    ; start
    xor cx, cx ; clear cx
    xor dx, dx ; clear dx and use it as result
    mov bx, 10 ; use bx as multiplier
read_number_loop:
    mov ah, 1
    int 21h ; read char from keyboard
    cmp al, 0dh ; check if enter pressed
    je read_number_done ; if yes, exit loop
    mov cl, al ; copy char to cl
    mov ax, dx ; move result to ax
    mul bl ; multiply result by 10
    mov dx, ax ; move result back to dx
    sub cl, '0' ; convert char to number
    add dx, cx ; add number to result
    jmp read_number_loop

read_number_done:
    mov ax, dx ; move result to ax
    pop dx
    pop cx
    pop bx
    ret
proc_read_number endp

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

proc_adder proc near
    push ax
    push bx
    push cx
    push dx
    ; read first number
    lea dx, num1_prompt
    mov ah, 9
    int 21h
    call proc_read_number
    mov bx, ax
    ; read second number
    lea dx, num2_prompt
    mov ah, 9
    int 21h
    call proc_read_number
    add ax, bx

    ; print result
    call proc_print_number
    call proc_newline
    ; return
    pop dx
    pop cx
    pop bx
    pop ax
    ret
proc_adder endp

proc_print_time proc near
    push ax
    push cx
    push dx
    ; start
    mov ah, 2ch
    int 21h ; get time

    xor ah, ah ; reset ah
    mov al, ch ; print hours
    call proc_print_number
    mov ah, 2
    mov dl, ':'
    int 21h
    xor ah, ah ; reset ah
    mov al, cl ; print minutes
    call proc_print_number
    mov ah, 2
    mov dl, ':'
    int 21h
    xor ah, ah ; reset ah
    mov al, dh ; print seconds
    call proc_print_number
    call proc_newline
    ; return
    pop dx
    pop cx
    pop ax
    ret
proc_print_time endp

end start
