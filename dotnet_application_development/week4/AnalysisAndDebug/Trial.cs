struct Trial
{
    public int x;
    public string y;
    public Trial() { }
    public Trial(int p1, string p2)
    {
        x = p1;
        y = p2;
    }
}

class TrialProgram
{
    public static void TrialMain()
    {
        Trial myTrial = new Trial();
        Trial yourTrial = new Trial(10, "Oh, I see.");
        Trial hisTrial;
        hisTrial.x = 88;
        hisTrial.y = "";
        Console.WriteLine("x = {0}, y = {1}", myTrial.x, yourTrial.y);
        Console.WriteLine(hisTrial.x + "\t" + hisTrial.y);
    }
}
