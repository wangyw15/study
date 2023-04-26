// 实验几
#let number = "一？"
// 姓名
#let student_name = "某人"
// 学号
#let student_id = "某个神秘数字"
// 上课时间
#let time = "有时间就行"
// 机位
#let seat = "自由"
// 指导教师
#let teacher = "好像没有"

// 实验名称
#let name = "中断机制和应用"
// 实验目的'
#let purpose = ("学习实验箱感知中断的硬件结构和工作原理。", "学习使用中断系统。", "学习使用扩展外设。")
// 实验原理
#let principle = [
    + 程序中断：因“随机性”原因，使一个程序暂停执行，转而执行另一个程序，以处理随机事件，然后再返回原程序继续执行的过程成为“中断”。
      中断同子程序调用有共同点：执行另一个程序，然后返回。所以在调用另一个程序（中断服务子程序）时必须保存断点。
      中断与子程序调用有一个根本区别：中断发生的时间是随机的（不可预知，但发生后应该如何处理是安排好的），而子程序调用时间是安排好的，由程序员写下的调用指令决定。
      中断发生的“随机性”决定了“必须用硬件感知中断请求”、“不仅要保存断点，还必须保存现场”。
      中断发生时间与正在运行的程序的无关性，使得整个系统在运行一个程序的同时，还能感知其它事件的发生！这是实时监控的技术基础、是多用户、多任务、多线程技术的关键点，因此是操作系统工作的前提。
    + 实验箱的中断感知硬件：只有“中断返回”指令和复位操作使EINT为低电平，这个低电平作用到IREQ的SD端，使上面这个D触发器的Q端为1，作用到IACK的CD端使下面这个D触发器的Q端输出0。本课程称其为状态0。
      系统复位结束或执行其他指令时,EINT为无效的高电平，这时在时钟CK驱动下，IREQ的Q端输出D端的INT状态。当有中断请求时INT为0，则一个CK后Q端输出0，但这个0能否被CPU感知却要看①号“或门”是否允许它通过。而“非取指”微指令有IREN＝1，则②号“或门”输出1，于是IREQ的Q端无论输出0或1，①号“或门”总输出1，即不允许中断请求通过。同时这个1又送入IACK的SD端；于是下触发器的SD和CD端的输入都是无效状态，这个触发器保持稳定。
      当执行取指微指令时，IREN＝0，于是②号或门输出0，这时①号“或门”对IREQ的Q端开放，若有中断请求就会在这时被CPU感知。所以无论中断请求在何时提出，都只能在取指阶段被感知！
       当①号“或门”输出0时中断被感知，同时这个低电平使IACK的SD有效，迫使其Q端输出1，ACK灯亮，并使②号“或门”对IREN关闭并输出1；这个1又使①号“或门”对中断请求关闭并输出1，这个1又返回IACK的SD端，使IACK保持Q＝1的状态。所以系统进入中断服务子程序后，ACK灯保持亮，且不响应新的中断请求（仅一级中断）。
      直到中断服务程序执行“中断返回”指令RETI时，EINT为0，使系统再次进入状态0。
      在中断服务期间中断源若不及时撤销中断请求（使INT为1），则中断返回后系统会再次进入中断状态，造成“中断未返回”的假象。    
      ICOE向下经“与门”控制PC＋1信号，如图。当感知中断请求（ ICOE＝0）时，使PC值不变（确定断点），进入服务程序后（ ICOE＝1），PC恢复自动加1功能，保证服务程序的顺序执行。
      ICOE的另一个作用是通过③号“或门”控制EM中指令的输出，保证在输出中断指令B8H时，EM不输出。
]

// 实验内容
#let tasks = (
    (
        // 实验任务名称
        name: [用74LS08芯片搭建当电键K1和K2都为1时不产生中断请求信号的外部电路。],
        // 实验步骤
        steps: [
            任选芯片74LS08中的一个与门，K1、K2接与门的输入，与门的输出作为INT信号。
        ],
        // 实验现象
        phenomena: [
            #figure(image("result.jpg", width: 100%), caption: [接线图])
        ],
        // 数据记录、分析与处理
        data: [
            通过K1K2手动控制中断信号的产生。
        ],
        // 实验结论
        conclusion: [
            当K1K2同时为1时，74LS08的输出为1，INT信号为1，不产生中断请求信号。
        ]
    ),
    (
        name: [编制中断服务子程序使OUT交替显示AA、BB三次后返回源程序。源程序为上次实验完成的交替显示11和55的程序。],
        steps: [
            + 运行上述程序，在完成AA、BB交替显示三次之前恢复K1K2都为1的状态。记录OUT显示的现象、REQ灯和ACK灯的情况以及ST寄存器的值及改变情况。
            + 运行上述程序，在完成AA、BB交替显示时不恢复K1K2都为1的状态。记录OUT显示的现象、REQ灯和ACK灯的情况以及ST寄存器的值及改变情况。
            根据题目要求，编制中断服务子程序，使OUT交替显示AA、BB三次后返回源程序，可以编写如下代码
            ```assembly
                    ORG 00H
            LOOP:   MOV A,#11H
                    MOV R1,A
                    OUT
                    MOV A,#20H
            z1:     SUB A,#01H
                    MOV R2,A
                    JZ z2
                    JMP z1
            z2:     MOV A,#55H
                    MOV R1,A
                    OUT
                    MOV A,#20H
            z3:     SUB A,#01H
                    MOV R2,A
                    JZ z4
                    JMP z3
            z4:     JMP LOOP
                    
                    ORG 60H
                    MOV R0,#03H
            LOOP1:  MOV A,#AAH
                    OUT
                    MOV A,#10H;
            T1:     SUB A,#01H
                    JZ T2
                    JMP T1
            T2:     MOV A,#BBH
                    OUT
                    MOV A,#10H
            T3:     SUB A,#01H   
                    JZ T4
                    JMP T3
                    T4:    MOV A,R0
                    SUB A,#01H
                    JZ EXIT
                    MOV R0,A
                    JMP LOOP1
            EXIT:   MOV A,R1
                    OUT
                    MOV A,R2
                    SUB A,#00H
                    RETI
                    END
            ```

            在上述代码中，`z1`、`z3`、`T1`、`T3`程序段用来延时，`LOOP`程序段用来交替显示11和55，`LOOP1`程序段用来交替显示AA和BB，`EXIT`程序段用来退出中断服务子程序。
        ],
        phenomena: [
            #figure(image("result.jpg", width: 100%), caption: [AA与BB交替显示])
            #figure(image("result2.jpg", width: 100%), caption: [11和55交替显示])
        ],
        data: [
            - 在K1和K2都为1的状态下，不产生中断信号，实验箱的OUT在交替输出11和55，实验箱的REQ灯和ACK灯
            - 在K1和K2有一个不为1的状态下，产生硬件中断信号，实验箱交替输出AA和BB，实验箱的REQ灯和ACK灯
        ],
        conclusion: [
            硬件中断信号可以让计算机保存当前状态并强制跳转到中断处理程序，处理完成之后恢复到中断之前的状态。
        ]
    ),
)

// 建议和体会
#let experience = [
    通过硬件中断信号可以让计算机处理其他外设传入的数据，处理完成之后恢复到中断之前的状态。通过中断可以避免轮询带来的性能损耗。
]

// 思考题
#let thinking = [
    实验箱的中断服务程序中可以嵌套一般的子程序吗？

    不能，因为实验箱的ST寄存器只能存放8位二进制，仅能实现一级中断，所以不能嵌套一般的子程序。
]
