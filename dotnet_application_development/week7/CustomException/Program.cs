using System;

int errorCount = 0;
bool b = true;
while (b == true)
{
    try
    {
        if (errorCount < 5)
        {
            Console.WriteLine("请输入一个整数：");
            int x = int.Parse(Console.ReadLine());
            if (x == 100)
            {
                throw new HundredException("您输入了100", new Exception("原始错误"));
            }
            Console.WriteLine($"您输入的数字为{x}");
        }
        else
        {
            throw new Exception("错误的输入次数超过限制，您被怀疑为故意捣乱，我们有权把您踢出本系统！");
        }
    }
    catch (FormatException)
    {
        Console.WriteLine("输入不正确，请重新输入");
        errorCount++;
    }
    catch (HundredException e)
    {
        Exception? i = e;
        while (i != null)
        {
            Console.WriteLine(i);
            i = i.InnerException;
        }
    }
    catch (Exception e)
    {
        Console.WriteLine(e.Message);
        b = false;
    }
    finally
    {
        if (b)
        {
            Console.WriteLine("继续输入（y/n）？");
            string ch = Console.ReadLine();
            if (ch == "N" || ch == "n")
                goto leave;
            else
                goto here;
            leave: b = false;
        here:;
        }
    }
}

[Serializable]
class HundredException : Exception
{
    public HundredException() { }
    public HundredException(string message) : base(message) { }
    public HundredException(string message, Exception inner) : base(message, inner) { }
}
