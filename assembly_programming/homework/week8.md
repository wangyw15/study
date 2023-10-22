# 第八周作业

# 3.34 试分析下列程序段

```assembly
ADD AX, BX
JNO L1
JNC L2
SUB AX, BX
JNC L3
JNO L4
JMP SHORT L5
```

如果 AX 和 BX的内容给定如下

| 序号 | AX | BX |
| :-: | :-: | :-: |
| 1 | `147B` | `80DC` |
| 2 | `B568` | `54B7` |
| 3 | `42C8` | `608D` |
| 4 | `D023` | `9FD0` |
| 5 | `94B7` | `B568` |

问该程序执行完后，程序转向哪里？

## (1)

`147B+80DC=9557`，未溢出，未进位

执行 `JNO L1`，转向 `L1`

## (2)

`B568+54B7=10A1F`，未溢出，产生进位

执行 `JNO L1`，转向 `L1`

## (3)

`42C8+608D=A355`，产生溢出，未进位

`42C8-608D=E23B`，未溢出，有进位

执行 `JNO L4`，转向 `L4`

## (4)

`D023+9FD0=16FF3`，产生溢出，产生进位

执行 `JNC L2`，转向 `L2`

## (5)

`94B7+B568=14A1F`，产生溢出，产生进位

`94B7-B568=DF4F`，产生溢出，产生进位

执行 `JMP SHORT L5`，转向 `L5`

# 3.36 假设 `X` 和 `X+2` 单元的内容为双精度数 $p$，`Y` 和 `Y+2` 单元的内容为双精度数 $q$，`X` 和 `Y` 为低位字，试说明下列程序段做什么工作？

```assembly
        MOV  DX, X+2
        MOV  AX, X
        ADD  AX, X
        ADC  DX, X+2
        CMP  DX, Y+2
        JL   L2
        JG   L1
        CMP  AX, Y
        JBE  L2
L1:     MOV  AX, 1
        JMP  SHORT EXIT
L2      MOV  AX, 2
EXIT:   INT  20H
```

这段程序比较 $2X$ 与 $Y$ 的大小

$2X>Y$ 时，`AX=1`

$2X\le Y$ 时，`AX=2`

# 5.12 有一个首地址为 `MEM` 的 `100D` 字数组，试编制序删除数组中所有为零的项，并将后续项向前压缩，最后将数组的剩余部分补上零。

```assembly
    lea bx, MEM
    mov si, 0 ; for array index
    mov di, -1 ; for none-zero index
move_loop:
    mov ax, bx[si]
    cmp ax, 0 ; compare if current number is zero
    je continue
    inc di
    mov bx[di], ax
continue:
    inc si
    cmp si, 100d
    jne move_loop

fill_loop:
    inc di
    mov bx[di], 0
    cmp di, 100d
    jne fill_loop
```
