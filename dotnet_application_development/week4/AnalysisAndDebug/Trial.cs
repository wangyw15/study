struct Trial
{
    public int x;
    public int y;
    public Trial() { }
    /*public Trial(int p1, string p2)
    {
        x = p1;
        y = p2;
    }*/
    public Trial(int p1, int p2)
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
        // Trial yourTrial = new Trial(10, "Oh, I see.");
        Trial yourTrial = new Trial(10, 20);
        Trial hisTrial;
        hisTrial.x = 88;
        // hisTrial.y = "";
        hisTrial.y = 0;
        Console.WriteLine("x = {0}, y = {1}", myTrial.x, yourTrial.y);
        Console.WriteLine(hisTrial.x + "\t" + hisTrial.y);
    }
}
