interface IIs
{
    float Ls();
}

interface IHs
{
    float Ms();
}

class IH : IIs, IHs
{
    float l, m;

    // float IIs.Ls()
    public float Ls()
    {
        return l;
    }

    // float Ms()
    float IHs.Ms()
    {
        return m;
    }
}

class InterfaceProgram
{
    public static void InterfaceMain()
    {
        IH ih = new IH();
        Console.WriteLine(ih.Ls());
    }
}
