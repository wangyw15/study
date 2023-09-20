# 第四周作业

# 3.14 设(DS)=1B00H，(ES)=2B00H，有关存储单元的内容如图所示。请写出两条指令把字变量 X 装入 AX 寄存器。

| 地址 | 内容 |
| :-: | :-: |
| `1B00:2000` | 8000 |
| `1B00:2002` | 2B00 |
| ... | ... |
| `2B00:8000` | X |
| ... | ... |

```assembly
mov bx, 2000H
mov ax, es:[bx]
```

# 3.15 求出以下各十六进制数与十六进制数 62A0 之和，并根据结果设置标志位 `SF`，`ZF`，`CF` 和 `OF` 的值。

| 数 | 和 | `SF` | `ZF` | `CF` | `OF` |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 1234 | 74D4 | 0 | 0 | 0 | 0 |
| 4321 | A5C1 | 1 | 0 | 0 | 1 |
| CFA0 | 3240 | 0 | 0 | 1 | 0 |
| 9D60 | 0000 | 0 | 1 | 1 | 0 |

# 3.16 求出以下各十六进制数与十六进制数 4AEO 的差值，并根据结果设置标志位 `SF`，`ZF`，`CF` 和 `OF` 的值。

| 数 | 差 | `SF` | `ZF` | `CF` | `OF` |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 1234 | C754 | 1 | 0 | 1 | 0 |
| 5D90 | 12B0 | 0 | 0 | 0 | 0 |
| 9090 | 45B0 | 0 | 0 | 0 | 1 |
| EA04 | 9F24 | 1 | 0 | 0 | 0 |

# 3.17 写出执行以下计算的指令序列，其中 X，Y，Z，R 和 Z 均为存放 16 位带符号数单元的地址。

## (1) $Z \leftarrow W+(Z-X)$

```assembly
mov ax, Z
mov bx, X
sub ax, bx
mov bx, W
adc ax, bx
mov Z, ax
```

## (2) $Z \leftarrow W-(X+6)-(R+9)$

```assembly
mov ax, X
mov bx, 6
add ax, bx
mov cx, R
mov dx, 9
add cx, dx
mov bx, W
sub bx, ax
sbc bx, cx
mov Z, bx
```

## (3) $Z \leftarrow (W \times X) \div (Y+6)$, $R \leftarrow 余数$

```assembly
mov ax, W
mov dx, X
imul dx
mov bx, Y
mov cx, 6
add bx, cx
idiv bx
mov R, dx
mov Z, ax
```

## (4) $Z \leftarrow ((W-X) \div 5 \times Y) \times 2$

```assembly
mov ax, W
mov bx, X
sub ax, bx
mov bx, 5
idiv bx
mov ah, 0
mov bx, Y
imul bx
shl ax, 1
rcl dx, 1
mov Z, ax
mov Z+1, dx
```

# 3.23 假设 (BX)=0E3H，变量 VALUE 中存放的内容为 79H，确定下列各条指令单独执行后的结果。

| 指令 | BX | SF | ZF | PF | CF | OF |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| `XOR BX, VALUE` | 9AH | 1 | 0 | 1 | 0 | 0 |
| `AND BX, VALUE` | 61H | 0 | 0 | 0 | 0 | 0 |
| `OR BX, VALUE` | 0FBH | 1 | 0 | 0 | 0 | 0 |
| `XOR BX, 0FFH` | 1CH | 0 | 0 | 0 | 0 | 0 |
| `AND BX, 0` | 00H | 0 | 1 | 1 | 0 | 0 |
| `TEST BX, 01H` | 0E3H | 0 | 0 | 0 | 0 | 0 |

# 3.26 试分析下面的程序段完成什么功能?

```assembly
MOV CL, 04
SHL DX, CL
MOV BL, AH
SHL AX, CL
SHR BL, CL
OR  DL, BL
```

将`((DX), (AX))`的双字左移四位，即乘以16
