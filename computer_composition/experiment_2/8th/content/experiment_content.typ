// exp 1
#heading(level: 2, numbering: none)[1. 手动方式把立即数`33H`写入内存`D1H`单元]
#heading(level: 3, numbering: none)[(1) 实验步骤]

对于这一实验来说，需要手动对各个信号进行连接和取值，需要控制的信号列表如下：

#table(
    columns: (1fr, 1fr),
    inset: 10pt,
    [信号名称], [信号作用],
    [MAREN], [地址寄存器MAR写允许],
    [MAROE], [地址寄存器MAR输出允许],
    [EMEN], [存储器EM与数据总线连通],
    [EMRD], [存储器EM的数据读出到数据总线],
    [EMWR], [数据总线的数据写入到存储器EM],
    [X#sub[2]X#sub[1]X#sub[0]], [存储器选择],
    [STEN], [允许写入ST寄存器]
)

+ 由于本实验中，我们需要手动对各个信号进行连接和取值，因此需要将`MAREN`、`MAROE`、`EMEN`、`EMRD`、`EMWR`、`X2X1X0`、`STEN`这些信号连接好。
+ 将实验箱的模式调整为手动模式
+ 设置立即数`D1=1101 0001`，然后将`MAREN`、`X2X1X0`这两个信号设置为0，并按下STEP键。作用是选择内存，并且设置操作地址为`D1`。
+ 设置立即数`33=0011 0011`，然后将`EMEN`、`EMWR`、`MAROE`这三个信号设置为0，`X2X1X0`仍然保持为`000`，并按下STEP键。作用是将`33`写入内存`D1`单元。

#heading(level: 3, numbering: none)[(2)	实验现象]

#figure(image("img/exp1_1.jpg", width: 100%), caption: [第一次按下STEP键之后，`MAR=D1`], numbering: none)
#figure(image("img/exp1_2.jpg", width: 100%), caption: [第二次按下STEP键之后，`EM=33`], numbering: none)

#heading(level: 3, numbering: none)[(3)	数据记录、分析与处理]

- `MAREN=0 X2X1X0=0`，其余都为1时，`MAR=D1`
- `EMEN=0 EMWR=0 MAROE=0 X2X1X0=0`，其余都为1时，`EM=33`

#heading(level: 3, numbering: none)[(4)	实验结论]

通过手动方式，我们可以将立即数`33H`写入内存`D1H`单元。

// exp 2
#heading(level: 2, numbering: none)[2. 手动方式把`D1H`单元的内容读出，再送入`E1H`单元]
#heading(level: 3, numbering: none)[(1) 实验步骤]

- 准备步骤如前一个实验相同
+ 设置立即数`D1=1101 0001`，然后将`MAREN`、`MAROE`、`X2X1X0`这三个信号设置为0，并按下STEP键。作用是选择内存，并且设置操作地址为`D1`，并读出其中的数据送入数据总线，按下`STEP`。
+ 设置立即数`E1=1110 0001`，`MAROE`、`EMEN`、`EMRD`、`STEN`这四个信号设置为0，`X2X1X0`为`111`，并按下STEP键。作用是将`D1`读取的数据写入内存`E1`单元，按下`STEP`。

#heading(level: 3, numbering: none)[(2)	实验现象]

#figure(image("img/exp2.jpg", width: 100%), caption: [按下STEP键之后，最终`ST=33`], numbering: none)

#heading(level: 3, numbering: none)[(3)	数据记录、分析与处理]

最终`ST=33`

#heading(level: 3, numbering: none)[(4)	实验结论]

通过手动方式，我们可以将内存中`D1H`地址存储的数据写入内存`E1H`单元。

// exp 3
#heading(level: 2, numbering: none)[3. 在CP226汇编语言程序集成开发环境下编写程序，调试和单微步（跟踪）运行，完成下面任务，观察数据走向及寄存器的输入输出状态。将初始值05H赋予累加器A，每次减1，到0时，OUT寄存器输出FFH。]
#heading(level: 3, numbering: none)[(1) 实验步骤]

+ 将所有的手动开关拨到高电平位置，避免影响汇编程序的运行。
+ 在电脑上打开实验箱配套程序
+ 通过分析要求，我们可以知道，程序的功能是将`A`的值递减到0，最终变为`FF`，代码如下
+ 将汇编程序编译并下载到实验箱中，然后单步运行程序

```asm
      MOV A, #05H
loop: SUB A, #01H
      JZ end
      JMP loop
end:  MOV OUT, #FFH
      OUT
      END
```

#heading(level: 3, numbering: none)[(2)	实验现象]

#figure(image("img/exp3.jpg", width: 100%), caption: [随着程序运行，`A`的值递减到0，最终变为`FF`], numbering: none)

#heading(level: 3, numbering: none)[(3)	数据记录、分析与处理]

我们也可以通过汇编程序的运行，观察到`A`的值递减到0，最终变为`FF`

#heading(level: 3, numbering: none)[(4)	实验结论]

可以通过汇编来控制内存读写
