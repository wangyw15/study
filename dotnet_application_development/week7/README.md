# 第7周作业要求

# 作业1 异常处理和使用`throw`语句抛出异常

## 实验内容和要求

(1)分析下面的程序，试找出并改正其中的错误，如果没有错误，则写出程序的运行结果;

代码1：
```csharp
class Class1
{
    static void Main(string[] args)
    {
        bool b = true;
        while (b == true)
        {
            try
            {
                Console.WriteLine("请输入一个整数：");
                int x = int.Parse(Console.ReadLine());
            }
            catch (FormatException)
            {
                Console.WriteLine("输入不正确，请重新输入");
            }
            finally
            {
                Console.WriteLine("继续输入（y/n）？");
                string ch = Console.ReadLine();
                if (ch == "N" || ch == "n")
                    break;
                    //return;
                    //continue;
                    //goto leave;
                else
                    goto here;
                leave:b = false;
                here:;
            }
        }
    }
}
```

代码2：
```csharp
class Class1{
    static void Main(string[] args)
    {
        Console.WriteLine("请输入五个整数：");
        int count = 0;
        int []a = new int[5];
        string []b = new string[10];
        for(int i = 0; i < 5; i++)
        {
            try
            {
                b[count] = Console.ReadLine();
                a[i] = int.Parse(b[count]);
            } //1
            catch (FormatException)
            {
                Console.WriteLine("输入不正确，请重新输入");
                i--;
                continue;
            } //2
            finally
            {
                count++;
            }
        } // end of for
        for (int i = 0; i < count; i++)
            Console.Write("第{0}个输入为：{1}；", i, b[i]);
        Console.WriteLine();
        Console.WriteLine("其中不合法的输入有{0}个", count-5);
    }
}
```
(2)根据代码1内容，结合代码2的设计思路，控制用户的输入次数。

要求：当用户5次输入不正确时，即输入错误的次数超过了限制，就抛出一个`Exception`异常，并利用传递给`Exception`对象的构造函数的字符串参数对异常进行如下描述：“错误的输入次数超过限制，您被怀疑为故意捣乱，我们有权把您踢出本系统！”。

## 实验报告

1. 小结`throw`语句的作用和用法。
2. 如何在构造`Exception`对象时，传递用户自定义的信息，如异常信息等。
3. 如何捕捉由于5次输入错误而引发的异常？
4. `throw`语句产生的异常会如何处理？

# 作业2 自定义异常类的使用

## 实验内容和要求

对实验1的内容进行改进，控制用户的输入内容。

要求：即使用户输入正确，但是当用户输入整数100时，抛出一个自定义的异常类对象。并且捕捉到异常后，显示引发异常的异常链中的每一个对象的名字和信息。

## 实验报告

1. 小结自定义异常类的步骤和注意事项。
2. 如何找到异常链中的每一个对象。
3. 如何捕捉自定义异常类对象？

# 作业3 课程项目作业

在组长的带领下设计本课程的大作业项目方案，并明确指出自己在其中所要承担的具体任务和模块。

具体要求如下：

1. 用word文档撰写；
2. 注明自己是第几组的，这一组由哪些同学组成的，组长是哪位；
3. 自己在课程项目中承担的模块在本周的计划是什么？具体推进情况如何？（请将具体推进的源代码以附件形式放入作业压缩包内！）
4. 每个同学都需要将此文档提交在自己这一周的作业压缩包内。
