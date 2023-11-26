namespace experiment1;

class Program
{
    static void Main()
    {
        Console.Write("Process amount: ");
        var amount = int.Parse(Console.ReadLine() ?? "5");
        var hpfProcesses = new List<Process>();
        var rrProcesses = new List<Process>();
        var fbProcesses = new List<Process>();

        // use random number to initialize processes
        var random = new Random();
        for (var i = 0; i < amount; i++)
        {
            var priority = random.Next(1, 10);
            var arrivalTime = 0;
            var totalCpuTime = random.Next(1, 10);

            hpfProcesses.Add(new Process(i, priority, arrivalTime, totalCpuTime));
            rrProcesses.Add(new Process(i, priority, arrivalTime, totalCpuTime));
            fbProcesses.Add(new Process(i, priority, arrivalTime, totalCpuTime));
        }

        Console.WriteLine("Processes:");
        foreach (var process in hpfProcesses)
        {
            Console.WriteLine(process);
        }

        // HPF
        Console.WriteLine(Environment.NewLine + "HPF:");
        IScheduler scheduler = new HighPriorityFirst(hpfProcesses);
        scheduler.Schedule();
        scheduler.PrintFinishTime();

        // RR
        Console.WriteLine(Environment.NewLine + "RR:");
        scheduler = new RoundRobin(rrProcesses);
        scheduler.Schedule();
        scheduler.PrintFinishTime();

        // FB
        Console.WriteLine(Environment.NewLine + "FB:");
        scheduler = new FeedbackQueue(fbProcesses);
        scheduler.Schedule();
        scheduler.PrintFinishTime();
    }
}
