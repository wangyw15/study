# 第三周作业

# 3.2 试根据以下要求写出相应的汇编语言指令

## (1) 把 BX 寄存器和 DX 寄存器的内容相加，结果存入 DX 寄存器中

```assembly
add dx, bx
```

## (2) 用寄存器 BX 和 SI 的基址变址寻址方式把存储器中的一个字节与 AL 寄存器的内容相加，并把结果送到 AL 寄存器中。

```assembly
add al, [bx+si]
```

## (3) 用寄存器 BX 和位移量 0B2H 的寄存器相对寻址方式把存储器中的一个字和 (CX) 相加，并把结果送回存储器中。

```assembly
add cx, [bx+0b2h]
mov [bx+0b2h], cx
```

## (4) 用位移量为 0524H 的直接寻址方式把存储器中的一个字与数 2A59H 相加，并把结果送回该存储单元中。

```assembly
mov ax, [0524h]
add ax, 2a59h
mov [0524h], ax
```

## (5) 把数 0B5H 与 (AL) 相加，并把结果送回 AL 中。

```assembly
add al, 0b5h
```

# 3.3 写出把首地址为 BLOCK 的字数组的第 6 个字送到 DX 寄存器的指令。要求使用以下几种寻址方式:

## (1) 寄存器间接寻址

```assembly
lea bx, BLOCK
add bx, 6
mov dx, [bx]
```

## (2) 寄存器相对寻址

```assembly
lea bx, BLOCK
mov dx, [bx+6]
```

## (3) 基址变址寻址

```assembly
lea bx, BLOCK
mov si, 6
mov dx, [bx+si]
```

# 3.4 现有(DS)=2000H，(BX)=0100H，(SI)=0002H，(20100)=12H，(20101)=34H，(20102)=56H，(20103)=78H，(21200)=2AH，(21201)=4CH，(21202)=B7H，(21203)=65H,试说明下列各条指令执行完后 AX 寄存器的内容。

## (1) `MOV AX, 1200H`

`AX=1200H`

## (2) `MOV AX, BX`

`AX=0100H`

## (3) `MOV AX, [1200H]`

`AX=2AH`

## (4) `MOV AX, [BX]`

`AX=12H`

## (5) `MOV AX, 1100[BX]`

`AX=2AH`

## (6) `MOV AX, [BX][SI]`

`AX=56H`

## (7) `MOV AX, 1100[BX][SI]`

`AX=B7H`

# 3.8 假定(DS)=2000H, (ES)=2100H, (SS)=1500H, (SI)=00A0H, (BX)=0100H, (BP)=0010H，数据段中变量名 VAL 的偏移地址值为 0050H，试指出下列源操作数字段的寻址方式是什么？其物理地址值是多少？

| 指令 | 寻址方式 | 物理地址 |
| :-: | :-: | :-: |
| `MOV AX, 0ABH` | 立即数寻址 | 没有物理地址 |
| `MOV AX, BX` | 寄存器寻址 | AX |
| `MOV AX, [100H]` | 直接寻址 | 20100H |
| `MOV AX, VAL` | 直接寻址 | 20050H |
| `MOV AX, [BX]` | 寄存器间接寻址 | 20010H |
| `MOV AX, ES:[BX]` | 寄存器间接寻址 | 21100H |
| `MOV AX, [BP]` | 寄存器间接寻址 | 20010H |
| `MOV AX, [SI]` | 寄存器间接寻址 | 200A0H |
| `MOV AX, [BX+10]` | 相对基址寻址 | 20110H |
| `MOV AX, VAL[BX]` | 寄存器相对寻址 | 20150H |
| `MOV AX, [BX][SI]` | 基址变址寻址 | 201A0H |
| `MOV AX, VAL[BX][SI]` | 相对基址变址寻址 | 201F0H |

# 3.9 在 ARRAY 数组中依次存储了七个字数据，紧接着是名为 ZERO 的字单元，表示如下

```assembly
ARRAY DW 23, 36, 2, 100, 32000, 54, 0
ZERO  DW ?
```

## (1) 如果 BX 包含数组 ARRAY 的初始地址，请编写指令将数据 0 传送给 ZERO 单元。

```assembly
mov [bx+7], 0
```

## (2) 如果 BX 包含数据 0 在数组中的位移量，请编写指令将数据 0 传送给 ZERO 单元。

```assembly
mov si, 1
mov ARRAY[bx][si], 0
```

# 3.10 如 TABLE 为数据段中 0032 单元的符号名，其中存放的内容为 1234H，试问以下两条指令有什么区别？指令执行完后 AX 寄存器的内容是什么？

```assembly
MOV AX, TABLE
```

`MOV` 为传送数据，会读取内存内容，`AX` 为 `TABLE` 数据段的第一个数据

```assembly
LEA AX, TABLE
```

`LEA` 为加载有效地址，`AX=0032H`

# 3.11 执行下列指令后，AX 寄存器中的内容是什么？

```assembly
TABLE DW 10、20，30、40，50
ENTRY DW 3
...
MOV BX, OFFSET TABLE
ADD BX, ENTRY
MOV AX, [BX]
```

`AX=40`

# 3.12 下列ASCII码串（包括空格符）依次存储在起始地址为 CSTRING 的字节单元中

```assembly
CSTRING DB 'BASED ADDRESSING'
```

请编写指令将字符串中的第 1 个和第 7 个字符传送给 DX 寄存器

```assembly
lea bx, CSTRING
mov dh, [bx]
mov dl, [bx+6]
```
