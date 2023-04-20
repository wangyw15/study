namespace Code1;
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
    public B(int j) : base(j)
    {
        i = j;
    } 
}

class T
{
    public static void TMain()
    { 
        B b = new B(10);
        Console.WriteLine("B's i = " + b.i); 
    }
}