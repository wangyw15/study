interface ICountable
{
    double Compute(double i, double j);
}

struct Ball : ICountable
{
    public double Radius;
    public double Weight;
    const double pi = 3.14;
    // public override double Compute(double i, double j)
    public double Compute(double i, double j)
    {
        return pi * i * i * i / j;
    }
}

class ICountableProgram
{
    public static void ICountableMain()
    {
        // Ball bl;
        Ball bl = new Ball();
        bl.Radius = 16;
        Console.WriteLine(bl.Radius);
        Console.WriteLine(bl.Compute(bl.Radius, bl.Weight + 1));
    }
}
