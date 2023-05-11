// 实验几
#let number = "十二"
// 姓名
#let student_name = "诗和远方"
// 学号
#let student_id = "不便透露"
// 上课时间
#let time = "有空就行"
// 机位
#let seat = "随心所欲"
// 指导教师
#let teacher = "自力更生"

// 实验名称
#let name = "建立汇编指令系统"
// 实验目的
#let purpose = ("建立一个含中文助记符的汇编指令系统。", "用建立的指令系统编制一段程序，并运行之。")
// 实验原理
#let principle = [
    + 编制汇编指令：在实验三的“举例”中我们编制了一条微指令，它实现“A＋W的结果右移一位后的值输出到OUT”，本质上它是编制了这个微指令对应的24个控制信号的电平；实验五的任务2中，我们修改机器指令E8，使其成为“输出A＋W的结果左移一位后的值到OUT”指令，它本质上是编制了μEM中从E8开始的连续4个地址中的24bit值，即连续的四条微指令；实验六的背景知识2使我们知道：“汇编指令是表达机器指令功能的指令助记符，二者的对应关系由编制的汇编指令表确定”。按步完成这三个编制过程，就定义好一条全新的汇编指令，进一步也可以定义一个汇编指令系统——指令集。
      汇编环境CP226考虑到了教学上定义汇编指令系统的需求，提供了完成这三个编制任务的集成环境，只要按规定的格式送入编制的符号，系统就会生成相应的汇编指令或汇编指令系统。
    + 汇编表文件:这个文件的后缀为 .DAT,它是一个二维表格式文件，其每一行对应一条指令，这个表共有3列，如图1。第一列是指令的汇编助记符，宽度为20个半角字符。第二列是指令的16进制编码形式（机器指令），在实验箱系统就是指令的微程序在μEM中的起始地址，宽度为8个半角字符。第3列是这条指令的字节数，宽度为1个半角字符，这是本表的重要汇编信息，也是设立本表的原因之一。 
      这个文件的主要作用是：当编译（汇编）源程序时，查此表把汇编指令翻译成机器指令。即这就是汇编表。
    + 微程序型指令文件：这个文件的后缀为 .MIC,它也是一个二维表格式的文件，其每一行对应一条微指令，这个表共有11列（字段），每一列都定义好了属性和宽度，例如：图2是指令集insfile1.MIC的格式，这个指令集的全部内容见指导书103页到110页。 
      这个表的主要作用是：当系统调用此文件时把其第4列“微程序”的内容送入其第3列“微地址”指定的μEM（微程序存储器）单元。即初始化μEM。表的第一列为指令的汇编助记符,内容与表1的第1列一致。5到11列是对本行微指令的说明，内容可以省略。
    + 指令的机器码文件:这个文件的后缀为 .MAC, 也是一个二维表格式文件，每一行对应一条指令，表共有5列，如图3。第1列是汇编助记符，宽度14，与表1的第1列一致。第2列是机器码1，它是指令的微程序在μEM中起始地址的二进制表示，其最后两位是对R0～R3的选择，所以与表2的第3列一致，宽度为15。第3列是机器码2，是指令带的立即数或存储器地址。第4列是机器码3，是指令带的第二个存储器地址，宽度2。第5列是注释，宽度100，用于对指令进行说明。
      这个文件的主要作用是：解释汇编表的机器码细节，所以当编译源程序中的多字节指令时，可能要查此表。
]

// 实验内容
#let tasks = (
    (
        // 实验任务名称
        name: [编制一个汇编指令系统],
        // 实验步骤
        steps: [
            根据实验要求，包含下列助记符
            #table(
                columns: (auto, auto),
                inset: 10pt,
                align: center,
                [指令助记符], [指令意义描述],
                [LD A,\#\*], [将立即数打入累加器A],
                [A-W A,\#\*], [累加器A加立即数],
                [跳到 \*], [无条件跳转指令],
                [OUTA], [累加器A输出到OUT],
                [延时], [延长显示时间],
            )

            在CP226环境，按以下步骤操作，可建立相应文件：
            - 在下拉菜单中选择：文件→打开指令系统/微程序。
            - 在出现的对话窗中选择目录 c:\ program files\CP226计算机组成原理\data\
            - 在data目录中选择需要创建的文件（.mic; .dat 或 .mac ）的模板(一般选infile1.mic, infile1.dat, infile1.mac文件作为模板) 。
            - 系统在屏幕的“源程序”窗口中打开选中的程序。
            - 在源程序窗口按照显示出的文件格式打入自己编制的符号。
            - 删除原来程序的多余符号，以自定的文件名和正确的后缀存储新编制的文件到D盘。


            通过查询实验箱原始微指令集，从实验软件自带的模板修改并编写出如下的文件

            z12.dat
            ```
            LD A,#*             04      2
            A-W A,#*            08      2
            跳到 *              0C      2
            OUTA                10      1
            延时                14      1
            ```

            z12.mic
            ```
            _FETCH_     T0 00 CBFFFF 浮空                             浮空     A输出                 +1      
                           01 FFFFFF 浮空                             浮空     A输出                 +1      
                           02 FFFFFF 浮空                             浮空     A输出                 +1      
                           03 FFFFFF 浮空                             浮空     A输出                 +1      
            LD A,#*     T1 04 C7FFF7 浮空                             浮空     A输出                 +1      
                        T0 05 CBFFFF 浮空                             浮空     A输出                 +1      
                           06 FFFFFF 浮空                             浮空     A输出                 +1      
                           07 FFFFFF 浮空                             浮空     A输出                 +1      
            A-W A,#*    T2 08 C7FFEF 浮空                             浮空     A输出                 +1      
                        T1 09 FFFE90 浮空                             浮空     A输出                 +1      
                        T0 0A CBFFFF 浮空                             浮空     A输出                 +1      
                           0B FFFFFF 浮空                             浮空     A输出                 +1      
            跳到 *      T1 0C C6FFFF 浮空                             浮空     A输出                 写入+1  
                        T0 0D CBFFFF 浮空                             浮空     A输出                 +1      
                           0E FFFFFF 浮空                             浮空     A输出                 +1      
                           0F FFFFFF 浮空                             浮空     A输出                 +1      
            OUTA        T1 10 CBDF9F 浮空                             浮空     A输出                 +1      
                        T0 11 CBFFFF 浮空                             浮空     A输出                 +1      
                           12 FFFFFF 浮空                             浮空     A输出                 +1      
                           13 FFFFFF 浮空                             浮空     A输出                 +1      
            延时        T3 14 FFFFFF 浮空                             浮空     A输出                 +1      
                        T2 15 FFFFFF 浮空                             浮空     A输出                 +1      
                        T1 16 FFFFFF 浮空                             浮空     A输出                 +1      
                        T0 17 CBFFFF 浮空                             浮空     A输出                 +1 
            ```

            z12.mac
            ```
            _FETCH_       000000XX 00-03        
            LD A,#*       000001xx 04-07 #*     
            A-W A,#*      000010XX 08-0B #*     
            跳到 *        000011XX 0C-0F *      
            OUTA          000100XX 10-13        
            延时          000101XX 14-17        
            ```
        ],
        // 实验现象
        phenomena: [
            无
        ],
        // 数据记录、分析与处理
        data: [
            无
        ],
        // 实验结论
        conclusion: [
            得到一个包含五条指令的汇编指令系统
        ]
    ),
    (
        name: [用所编制的指令系统，写出源程序，完成OUT寄存器交替显示55，22，和55-22的值。],
        steps: [
            根据之前编写的指令系统，编写出如下代码
            ```
            LOOP: LD A,#55H
                  OUTA
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时

                  LD A,#22H
                  OUTA
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时

                  LD A,#55H
                  A-W A,#22H
                  OUTA
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时
                  延时

                  跳到 LOOP
                  END

            ```
        ],
        phenomena: [
            #figure(image("result_55.jpg", width: 100%), caption: [显示55])
            #figure(image("result_22.jpg", width: 100%), caption: [显示22])
        ],
        data: [
            交替显示55 22 和55+22的和77
        ],
        conclusion: [
            通过编写汇编指令系统，可以自定义一些汇编指令，甚至可以使用中文
        ]
    ),
)

// 建议和体会
#let experience = [
    通过编写汇编指令系统，可以自定义一些汇编指令，以后可以扩展出自己的汇编指令系统
]

// 思考题
#let thinking = [
    为什么汇编指令中可以用“中文符号”？
    
    因为中文只是助记符，最终都是要翻译成机器语言，所以可以使用中文
]