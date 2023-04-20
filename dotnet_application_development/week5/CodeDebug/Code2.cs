namespace Code2;

class A
{
    int i; 
    public string s; 
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
    public B(int j, string t, char d) : base(d)
    {
        i = j; 
        s = t; 
        ch = d; 
    }
}

class T
{
    public static void TMain()
    {
        A a = new A('a');
        B b = new B(11, "Here!",'f');
        Console.WriteLine(a.c + "\t" + a.s);
    }
}