using System;
using System.Diagnostics;

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
        Exception? e1 = e;
        while (e1 != null)
        {
            Console.WriteLine(e1);
			e1 = e1.InnerException;
		}
		StackTrace st = new StackTrace(true);
		for (int i = 0; i < st.FrameCount; i++)
		{
			StackFrame sf = st.GetFrame(i);
			Console.WriteLine($"Method: {sf.GetMethod()}, Line Number: {sf.GetFileLineNumber()}");
		}
		b = false;
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
