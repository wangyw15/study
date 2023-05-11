using System;
abstract class A
    {
    int i;
    abstract public void Print(string content);
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
    public override void Print(string w)
    { 
        Console.WriteLine(w); 
    }

    public void Print(char ch)
    {
        Console.WriteLine(ch); 
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
