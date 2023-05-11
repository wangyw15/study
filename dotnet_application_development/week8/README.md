# 第 8 周作业要求

# 作业 1：Windows 应用程序的开发与设计 1

实验内容和要求

1. 设计并实现一个具备基本的加减乘除功能的 Windows 界面计算器。
2. 在以上计算器基础上尝试设计一个小学生算术计算练习器，具体形式和功能不限。

# 作业 2：程序分析及改错

以下程序语法上是否正确？如果是正确的，那么输出是什么？如果有错误，是什么错误？请改正。

```csharp
using System;
abstract class A
    {
    int i;
    abstract public void Print(string ){};
}
class B:A
{
    int i;
    protected string s;
    public char ch;
    public B(int j, string t, char d)
    { 
        i=j;
        s=t; 
        ch=d; 
    }
    public new void Print(string w)
    { 
        Console.WriteLine(w); 
    }
}
class T
{
    public static void Main()
    { 
        B b=new B(11,"Here!",'f');
        b.Print(b.ch); 
    }
}
```
