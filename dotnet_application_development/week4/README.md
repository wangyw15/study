# 第 4 周编程作业

# 实验1：索引器的重载技术

## 实验内容

设类 `Winner` 中有一个 `string` 类型数组，其数据如下所示：

| 项目 | 姓名 | 省份 |
| :-: | :-: | :-: |
| 男子 100 米 | 刘庆平 | 四川 |
| 女子 800 米 | 王安新 | 北京 |
| 男子跳高 | 胡颖 | 云南 |
| 女子铅球 | 丁丰岚 | 辽宁 |
| 男子 10000 米 | 李铭钧 | 上海 |

要求设计若干个索引器，设W 为对象名，索引器使用方式的例子：

| 代码 | 作用 |
| :-: | :-: |
| `W[1]` | 已知数组的索引，返回一个包含全部信息的字符串。 
| `W["项目", "女子800 米"]` | 已知项目名称，返回一个包含全部信息的字符串 
| `W["选手", "王安新"]` | 已知选手的名字，返回一个包含全部信息的字符串 

上面例子都返回如下字符串： 

 “女子800 米冠军：北京选手王安新。” 

## 实验要求
1. 程序完整，能够演示。
2. 程序应该具有通用性，所以绝对不能用穷举法解决。 

## 实验报告

1. 本实验目标在于寻找一个途径，解决签名冲突的问题，我们用项目名作为参数，和用选手名作为参数，将发生冲突，因为它们都只有一个string 类型的参数。本实验已经提示了一种技术来化解这个问题。请详细介绍您的解决方案。 
2. 讨论这种技术的适应性、可推广的场合、局限性和注意事项。

# 实验2：程序设计题

打印下列杨辉三角形的前 `n` 行，`n` 由键盘输入。请分别使用一维数组和交错数组来实现，并对两种实现进行比较分析。

```
             1
           1   1
        1    2   1
      1   3    3    1
    1   4    6    4   1
  1   5   10   10   5   1
............................
```

# 实验3：程序分析及改错

## （1）以下程序语法上是否正确？如果是正确的，那么输出是什么？如果有错误，是什么错误？请改正。

```csharp
using System;
public struct Trial
{
    public int x; public string y;
    public Trial() {}
    public Trial(int p1, string p2)
    { x = p1; y = p2; }
}
class MainCls
{
    public static void Main()
    {
        Trial myTrial = new Trial();
        Trial yourTrial = new Trial(10, "Oh, I see.");
        Trial hisTrial;
        hisTrial.x = 88;
        hisTrial.y = "";
        Console.WriteLine("x = {0}, y = {1}", myTrial.x, yourTrial.y);
        Console.WriteLine(hisTrial.x + "\t" + hisTrial.y);
    }
}
```

## （2）指出下面程序中的错误，并给出改正的方案。

```csharp
using System;
interface IIs { float Ls(); }
interface IHs { float Ms(); }
class IH : IIs, IHs
{ 
    float l, m;
    float IIs.Ls() { return l; }
    float Ms() { return m; }
}
class MainCls
{
    public static void Main()
    {
        IH ih = new IH();
        Console.WriteLine(ih.Ls());
    }
}
```

## （3）指出下面程序中的错误，并给出改正的方案。

```csharp
using System;
interface ICountable
{
    double Compute (double i, double j);
}
struct ball : ICountable
{
    public double Radius;  public double Weight;
    const double pi = 3.14;
    public override double Compute(double i, double j)
    { return pi*i*i*i/j; }
}
class MainCls
{
    public static void Main()
    {
        ball bl;
        bl.Radius=16;
        Console.WriteLine(bl.Radius);
        Console.WriteLine(bl.Compute(bl.Radius, bl.Weight + 1));
    }
}
```
