---
marp: true
---

# 超出转移范围的解决方式

---

# 段内


```assembly
jmp short label
```

段内短转移，范围是-128~127

```assembly
jnz label_far
```

条件跳转范围同样是-128~127，如果需要跳转的距离超过了这个范围，可以使用多个跳转

```assembly
            jz label_near
            jmp label_far
label_near: ...
```

---

# 段内

```assembly
jump near ptr label
```

段内近转移，范围是-32768~32767

超出范围可进行多次跳转，或者进行段间转移

```assembly
         jmp label_a
label_a: jmp label_b
label b: jmp label_c
...
```

---

# 段间

```assembly
jmp far ptr label
```

段间转移，会改变CS和IP的值

---

# 测试

```assembly
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
```

---

# 测试

![](images/code_1.png)

![](images/code_2.png)

---

# 多重循环应该注意的问题

如果使用 `cx` 寄存器和 `loop` 指令，应在进入内层循环时使用其它寄存器，或者使用 `push` 和 `pop` 保存 `cx` 的值
