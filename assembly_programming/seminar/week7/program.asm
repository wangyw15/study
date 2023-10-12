.model small
.code
start:
test_short:
    jmp short test_near
    jmp test_near
test_near:
    jmp near ptr test_far
    jmp test_far
    db 500 dup(0)
test_far:
    jmp far ptr exit
    jmp exit
    db 50000 dup(0)
exit:
    mov ax, 4c00h
    int 21h
end start
