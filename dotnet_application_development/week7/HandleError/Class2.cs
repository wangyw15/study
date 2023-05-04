class Class2
{
    public static void Main2()
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
            } // 1
            catch (FormatException)
            {
                Console.WriteLine("输入不正确，请重新输入");
                i--;
                continue;
            } // 2
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
