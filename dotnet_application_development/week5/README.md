# 第 5 周作业要求

# 实验 1：类、对象、方法、类的继承的综合练习

## 实验内容

假设您是一家银行的开发人员。请定义一个账户系统。这些账户是：
- 活期账户（checking account）
- 储蓄存款账户（savings account）

### （1）活期账户

活期账户具有以下特征：
- 账户拥有者的名字只能在创建账户时指定
- 初始存额（opening balance）必须在账户创建时指定
- 账户创建时必须分配账户号，活期账户的账号范围从 100000~499999，每个活期账户必须具有唯一的账户号。

活期账户持有者能够：
- 订购支票薄
- 检查账户余额
- 往账户中加钱
- 如果活期账户中资金充足，可以从中取钱，但不能透支。

### （2）储蓄存款账户

储蓄存款账户具有如下特征：
- 账户持有者的名字只能在创建账户时指定
- 储蓄存款账户的账户号的范围从 500000~999999
- 账户可以赚取利息，利息取决于账户的余额，余额大于 1000，年利息为6％，否则为 3％

储蓄存款账户持有者能够：
- 检查账户余额
- 往账户中加钱
- 如果账户中资金充足，可以从中取钱，但不能透支。

## 实验要求

1. 编制程序实现上述账户系统，并要求设计一个 test 程序和模拟数据，演示上述各项功能。
2. 要求先设计一个抽象类，活期账户类和储蓄存款账户类继承并实现这个抽象类。

## 实验报告

1. 将账户系统用 UML 图表示出来。
2. 说明为什么采用抽象类而不是一般的基类。

# 实验 2：接口的实现

## 实验内容和要求

本实验通过两个接口来定义 MP3 或者 MP4 播放器的功能，熟悉接口的设计，显式接口成员的实现，但是因为课程内容和实验规模的限制，方法中只能用文字来象征性地表明它们的功能。

## 设计接口

1. `IRecordable`，其中包含三个方法：
   - `void receive(string s)`表示接受了文件 s；
   - `bool checked(string f)`表示检查了文件 f 的格式，返回布尔量，表示是不是可接受的格式；
   -  `void save(string t)`表示存储了文件 t。
2. `IPlayable`，其中包含三个方法：
   - `void find(string u)`表示找到了文件 u；
   - `bool checked(string f)`表示检查了文件 f 的格式，返回布尔量，表示是不是可接受的格式；
   - `void play(string v)`表示播放文件 v。
3. 设计类 `MP3`，它继承接口 `IRecordable` 和 `IPlayable`，其中方法 `checked` 要显式接口成员来实现，`IRecordable.checked` 方法是用来检查输入文件的格式，因为除了可播放的文件以外，其他可存储的文件都是合法的；`IPlayable.checked` 方法检查文件是否可播放的多媒体文件。
4. 编制完整的可演示结果的程序。

## 实验报告

1. 小结接口的实现、显式接口成员实现的要点；
2. 小结调用显式接口成员的方式；

# 实验 3：结构的优越性和局限性

## 实验内容和步骤

1. 分析下面的类定义：
```csharp
class Point
{
    public int x, y;
    public Point(int i, int j) 
    { x = i; y = j; }
}
```
2. 将上面的类改为结构；
3. 设计一个包含 15 个 `Point` 类的对象的数组；设计一个包含 15 个 `Point` 结构的对象的数组。
4. 完成整个程序，输出上述两个数组。

## 实验报告

通过本实验可以了解结构对象数组的设计技术，本实验不能直接观察到应用结构的优越性和局限性，要求根据已有的知识进行思考和小结。

1. 列出结构的特点；
2. 讨论结构的应用价值和局限性；
3. 讨论结构对象的数组和类对象的数组之间的差别（包括在存储量、访问方式、访问速度等方面差别）。
4. 如果分别用结构对象数组和类对象数组作为某方法的参数，它们之间有什么差别和优缺点。

# 实验 4：程序分析及改错

1. 以下程序语法上是否正确？如果是正确的，那么输出是什么？如果有错误，是什么错误？请改正。
```csharp
using System;

class A
{ 
    public int i; 
    public A(int j)
    {
        i = j;
    } 
}

class B : A
{
    public B(int j)
    {
        i = j;
    } 
}

class T
{
    public static void Main()
    { 
        B b = new B(10);
        Console.WriteLine("B's i = " + b.i); 
    }
}
```
2. 指出下面程序中的错误，并给出改正的方案。
```csharp
using System;

class A
{
    int i; 
    protected string s; 
    public char c;
    public A(char d)
    {
        c = d; 
    }
}

class B : A
{
    int i; 
    string s; 
    public char ch;
    public B(int j, string t, char d) : base(t, d)
    {
        i = j; 
        s = t; 
        ch = d; 
    }
}

class T
{
    public static void Main()
    {
        A a = new A('a');
        B b = new B(11, "Here!",'f');
        Console.WriteLine(a.c + "\t" + a.s);
    }
}
```