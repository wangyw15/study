namespace experiment3;

public class Instruction
{
    public static List<int> GeneratePageSequence(int virtualMemorySize, int count = 1000)
    {
        var ret = new List<int>();
        var random = new Random();
        for (var i = 0; i < count / 2; i++)
        {
            ret.Add(i % virtualMemorySize);
        }
        for (var i = 0; i < count / 4; i++)
        {
            ret.Add(random.Next(0, virtualMemorySize / 2));
        }
        for (var i = 0; i < count / 4; i++)
        {
            ret.Add(random.Next(virtualMemorySize / 2, virtualMemorySize));
        }
        return ret;
    }
}
