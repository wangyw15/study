// 实验几
#let number = "八"
// 姓名
#let student_name = "someone"
// 学号
#let student_id = "some digits"
// 上课时间
#let time = "sometimes"
// 机位
#let seat = "somewhere"
// 指导教师
#let teacher = "teacher"

// 实验名称
#let name = "内存系统实验"
// 实验目的
#let purpose = ("学习内存访问机制", "理解代码和数据的分区存放原理和技术")
// 实验原理
#let principle = [
    + 模型机的程序存储器结构：`PC`的自动 +1 功能保证了指令的顺序执行，决定了程序在内存中必须连续存放。而`PC`的可赋值性决定了程序可以分段存放——程序存储器是分段连续的。
    + 模型机的数据存储器结构：当`MAROE`有效时 574 输出数据成为内存的地址，配合 6116 的读/写控制，实现对该地址单元的数据存取操作。因`MAR`无自动 +1 功能，数据存储器是随机的。
    + 模型机的内存储器结构：在模型机中,程序和数据共用一个物理存储器（分区使用）。所以，`MAROE`和`PCOE`不能同时有效，否则`ABUS`上出现`MAR`和`PC`两个输出的“与”值。

    实验六中我们学习了汇编语言程序的编写和运行，体会到人工编译汇编源程序到目标程序的过程就是：通过查表把汇编指令一对一的翻译成机器指令的简单过程。显然，只要把指令对照表存放在 PC 中，计算机做这种简单工作比人更快、更准确。鉴于 PC 机的强大功能，围绕着程序编译工作，PC 还提供了一系列辅助功能，如：源程序的输入和编辑、目标程序的下载和运行控制、运行过程跟踪等等，这些辅助功能使汇编语言程序的编制、运行和调制工作变得非常简单和人性化。所有这些功能被打包成一个软件，称为汇编语言程序集成开发环境。由于机器语言是针对 CPU 的，所以这个开发环境也是针对 CPU 的。

    本实验箱的汇编语言程序集成开发环境是 CP226 软件，它是一个 Windows 应用程序，所以其工作界面上包含有下拉菜单、操作快捷键等“视窗”基本元素，使用方法也与其他 windows 程序相似。

    伪指令：不在目标程序中生成机器指令的汇编助记符（汇编命令）。其作用是通知汇编软件如何进行“汇编操作”。不同的汇编系统伪指令不一样。本实验系统有伪指令：`END`和`ORG xx`。`END`的功能：通知汇编软件程序段“到此结束”。所以，当汇编软件遇到这条伪指令时，就不再理睬后边的任何“汇编指令”。所以，任何交给汇编软件的源程序最后一句必须是`END`，如果忘记了它，汇编软件就会无止境的汇编下去……，永远不会最后生成完整的目标程序。`ORG xx`的功能：通知汇编软件程序段的起始地址。所以，当汇编软件遇到这条伪指令时，就会把后边的地址值赋给“程序计数器”（PC），以便下一条“汇编指令”能够正确的翻译成机器指令。所以，任何交给汇编软件的源程序第一句必须是`ORG xx`，如果忘记了它，汇编软件就会把第一条“汇编指令”翻译成机器指令后，把它放在内存的地址 0 处，这显然是不对的。
]

// 实验内容
#let tasks = (
    (
        name: [手动方式把立即数`33H`写入内存`D1H`单元],
        steps: [
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
        ],
        phenomena: [
            #figure(image("img/exp1_1.jpg", width: 100%), caption: [第一次按下STEP键之后，`MAR=D1`], numbering: none)
            #figure(image("img/exp1_2.jpg", width: 100%), caption: [第二次按下STEP键之后，`EM=33`], numbering: none)
        ],
        data: [
            - `MAREN=0 X2X1X0=0`，其余都为1时，`MAR=D1`
            - `EMEN=0 EMWR=0 MAROE=0 X2X1X0=0`，其余都为1时，`EM=33`
        ],
        conclusion: [
            通过手动方式，我们可以将立即数`33H`写入内存`D1H`单元。
        ]
    ),
    (
        name: [手动方式把`D1H`单元的内容读出，再送入`E1H`单元],
        steps: [
            - 准备步骤如前一个实验相同
            + 设置立即数`D1=1101 0001`，然后将`MAREN`、`MAROE`、`X2X1X0`这三个信号设置为0，并按下STEP键。作用是选择内存，并且设置操作地址为`D1`，并读出其中的数据送入数据总线，按下`STEP`。
            + 设置立即数`E1=1110 0001`，`MAROE`、`EMEN`、`EMRD`、`STEN`这四个信号设置为0，`X2X1X0`为`111`，并按下STEP键。作用是将`D1`读取的数据写入内存`E1`单元，按下`STEP`。
        ],
        phenomena: [
            #figure(image("img/exp2.jpg", width: 100%), caption: [按下STEP键之后，最终`ST=33`], numbering: none)
        ],
        data: [
            最终`ST=33`
        ],
        conclusion: [
            通过手动方式，我们可以将内存中`D1H`地址存储的数据写入内存`E1H`单元。
        ]
    ),
    (
        name: [在CP226汇编语言程序集成开发环境下编写程序，调试和单微步（跟踪）运行，完成下面任务，观察数据走向及寄存器的输入输出状态。将初始值05H赋予累加器A，每次减1，到0时，OUT寄存器输出FFH。],
        steps: [
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
        ],
        phenomena: [
            #figure(image("img/exp3.jpg", width: 100%), caption: [随着程序运行，`A`的值递减到0，最终变为`FF`], numbering: none)
        ],
        data: [
            我们也可以通过汇编程序的运行，观察到`A`的值递减到0，最终变为`FF`
        ],
        conclusion: [
            可以通过汇编来控制内存读写
        ]
    )
)

// 建议和体会
#let experience = [
  通过手动控制实验箱上的各个信号，可以将特定的数值送入指定的内存空间，从而实现对内存的读写操作。
  也可以通过汇编语言的方式，对内存进行读写操作。
]

// 思考题
#let thinking = [
  _既然有 `ORG` 伪指令，为什么集成开发环境下载到实验箱的目标程序的第一条执行语句最好存放在 0 号地址？_

  集成开发环境下载到实验箱的目标程序的第一条执行语句最好存放在 0 号地址，是因为实验箱的 CPU 在上电复位后会将程序计数器 PC 的值初始化为 0，即从 0 号地址开始执行程序。如果将第一条执行语句存放在其他地址，需要手动修改 PC 的值，才能使程序从正确的地址开始执行。而将第一条执行语句存放在 0 号地址，可以避免这种手动修改 PC 的操作，使程序的执行更加方便和自然。
]