namespace experiment1;

class Program
{
    static void Main()
    {
        Console.Write("Process amount: ");
        var amount = int.Parse(Console.ReadLine() ?? throw new InvalidOperationException());
        var processes = new List<Process>();
        // use random number to initialize processes
        var random = new Random();
        for (var i = 0; i < amount; i++)
        {
            processes.Add(new Process(i, random.Next(1, 10), 0, random.Next(1, 10)));
        }
        var scheduler = new HighPriorityFirst(processes);
        scheduler.Schedule();
        scheduler.Print();
    }
}
