设 `X`、`Y` 均为存放在 `X` 和 `Y` 单元中的 16 位操作数，先判断 $X>50$ ，如不满足，转到 `EXIT`，如满足条件则转移到 `TOO_HIGH` 去执行，然后做 `X-Y`，如溢出则转移到 `OVERFLOW` 去执行，否则计算 $|X-Y|$，并把结果存入 `RESULT` 中。

画出程序流程图，并给出程序代码。

---

```mermaid
graph TD;
    A(开始) --> B{X>50};
    B -- 是 --> TOO_HIGH[跳转至 TOO_HIGH]
    B -- 否 --> EXIT[跳转至 EXIT]
    TOO_HIGH --> C[X-Y]
    C --> D{溢出}
    D -- 是 --> OVERFLOW[跳转至 OVERFLOW]
    D -- 否 --> E{X-Y<0}
    E -- 是 --> F[X-Y 取反]
    E -- 否 --> G[保存至 RESULT]
    F --> G
```

```assembly
mov ax, X
cmp ax, 50
jle EXIT
jmp TOO_HIGH

TOO_HIGH:
mov bx, Y
sub ax, bx
jo OVERFLOW
cmp ax, 0
jge save
neg ax

save:
mov RESULT, ax

OVERFLOW:

EXIT:
```
