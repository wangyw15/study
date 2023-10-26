# 第九周作业

# 6.18

编写一个有主程序和子程序结构的程序模块。子程序的参数是一个 N 字节数组的首地址 `TABLE`，数 `N` 及字符 `CHAR`。要求在 N 字节数组中查找字符 `CHAR`，并记录该字符的出现次数。主程序则要求从键盘接收一串字符以建立字节数组 `TABLE`，并逐个显示从键盘输入的每个字符 `CHAR` 以及它在 `TABLE` 数组中出现的次数。(为简化起见，假设出现次数$\le15$，可以用十六进制形式把它显示出来)

```assembly
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
```

# 8.14

试编制一程序，要求测出任意程序的运行时间，并把结果打印出来。

```assembly
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
```
