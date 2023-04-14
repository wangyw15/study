#let exp_name = "内存系统实验"
#let purpose = ("学习内存访问机制", "理解代码和数据的分区存放原理和技术")
#let principle = [

+ 模型机的程序存储器结构：`PC`的自动 +1 功能保证了指令的顺序执行，决定了程序在内存中必须连续存放。而`PC`的可赋值性决定了程序可以分段存放——程序存储器是分段连续的。
+ 模型机的数据存储器结构：当`MAROE`有效时 574 输出数据成为内存的地址，配合 6116 的读/写控制，实现对该地址单元的数据存取操作。因`MAR`无自动 +1 功能，数据存储器是随机的。
+ 模型机的内存储器结构：在模型机中,程序和数据共用一个物理存储器（分区使用）。所以，`MAROE`和`PCOE`不能同时有效，否则`ABUS`上出现`MAR`和`PC`两个输出的“与”值。

实验六中我们学习了汇编语言程序的编写和运行，体会到人工编译汇编源程序到目标程序的过程就是：通过查表把汇编指令一对一的翻译成机器指令的简单过程。显然，只要把指令对照表存放在 PC 中，计算机做这种简单工作比人更快、更准确。鉴于 PC 机的强大功能，围绕着程序编译工作，PC 还提供了一系列辅助功能，如：源程序的输入和编辑、目标程序的下载和运行控制、运行过程跟踪等等，这些辅助功能使汇编语言程序的编制、运行和调制工作变得非常简单和人性化。所有这些功能被打包成一个软件，称为汇编语言程序集成开发环境。由于机器语言是针对 CPU 的，所以这个开发环境也是针对 CPU 的。

本实验箱的汇编语言程序集成开发环境是 CP226 软件，它是一个 Windows 应用程序，所以其工作界面上包含有下拉菜单、操作快捷键等“视窗”基本元素，使用方法也与其他 windows 程序相似。

伪指令：不在目标程序中生成机器指令的汇编助记符（汇编命令）。其作用是通知汇编软件如何进行“汇编操作”。不同的汇编系统伪指令不一样。本实验系统有伪指令：`END`和`ORG xx`。`END`的功能：通知汇编软件程序段“到此结束”。所以，当汇编软件遇到这条伪指令时，就不再理睬后边的任何“汇编指令”。所以，任何交给汇编软件的源程序最后一句必须是`END`，如果忘记了它，汇编软件就会无止境的汇编下去……，永远不会最后生成完整的目标程序。`ORG xx`的功能：通知汇编软件程序段的起始地址。所以，当汇编软件遇到这条伪指令时，就会把后边的地址值赋给“程序计数器”（PC），以便下一条“汇编指令”能够正确的翻译成机器指令。所以，任何交给汇编软件的源程序第一句必须是`ORG xx`，如果忘记了它，汇编软件就会把第一条“汇编指令”翻译成机器指令后，把它放在内存的地址 0 处，这显然是不对的。
]
