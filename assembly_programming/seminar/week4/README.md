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
