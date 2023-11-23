namespace experiment1;

public interface IScheduler
{
    public void Schedule();
}

public class Util
{
    private const int NumberWidth = 4;

    public static void PrintProcesses(List<Process> processes, bool compact = false)
    {
        if (compact)
        {
            SimplePrinter(processes);
        }
        else
        {
            DetailedPrinter(processes);
        }
    }

    private static void SimplePrinter(List<Process> processes)
    {
        foreach (var process in processes)
        {
            Console.WriteLine(process);
        }
    }

    private static void DetailedPrinter(List<Process> processes)
    {
        Console.WriteLine("=============================");
        Console.WriteLine("RUNNING PROC");
        Console.WriteLine((from x in processes
            where x.PCB.State == ProcessState.Run
            select x.PCB.PID).FirstOrDefault());
        Console.WriteLine("WAITING QUEUE");
        foreach (var process in processes)
        {
            if (process.PCB.State == ProcessState.Wait)
            {
                Console.Write(process.PCB.PID.ToString().PadRight(NumberWidth));
            }
        }
        Console.WriteLine();
        Console.WriteLine("=============================");
        Console.Write("ID".PadRight(10));
        foreach (var process in processes)
        {
            Console.Write(process.PCB.PID.ToString().PadRight(NumberWidth));
        }
        Console.WriteLine();
        Console.Write("PRIORITY".PadRight(10));
        foreach (var process in processes)
        {
            Console.Write(process.PCB.Priority.ToString().PadRight(NumberWidth));
        }
        Console.WriteLine();
        Console.Write("CPUTIME".PadRight(10));
        foreach (var process in processes)
        {
            Console.Write(process.PCB.UsedCPUTime.ToString().PadRight(NumberWidth));
        }
        Console.WriteLine();
        Console.Write("ALLTIME".PadRight(10));
        foreach (var process in processes)
        {
            Console.Write(process.PCB.TotalCPUTime.ToString().PadRight(NumberWidth));
        }
        Console.WriteLine();
        Console.Write("STATE".PadRight(10));
        foreach (var process in processes)
        {
            Console.Write($"{process.PCB.State.ToString()[0]}".PadRight(NumberWidth));
        }
        Console.WriteLine();
    }
}

public class HighPriorityFirst(List<Process> processes) : IScheduler
{
    private Dictionary<int, int> _finishTime = new();
    private int _currentTime;

    public void Schedule()
    {
        while (true)
        {
            var chain = GetReadyChain().ToList();
            if (chain.Count == 0)
            {
                break;
            }
            var process = chain.First();
            process.Run();
            Util.PrintProcesses(processes);
            process.Update();
            _currentTime++;
            if (process.Finished)
            {
                _finishTime[process.PCB.PID] = _currentTime;
            }
            else
            {
                process.Wait();
                process.PCB.Priority -= processes.Count;
            }
        }
    }

    private IEnumerable<Process> GetReadyChain()
    {
        return from x in processes
               where x.PCB.State != ProcessState.Finish
               orderby x.PCB.Priority descending
               select x;
    }
}

public class RoundRobin(List<Process> processes) : IScheduler
{
    private Dictionary<int, int> _finishTime = new();
    private int _currentTime;

    public void Schedule()
    {
        while (true)
        {
            if (processes.All(process => process.PCB.State == ProcessState.Finish))
            {
                break;
            }
            foreach (var process in processes)
            {
                if (process.PCB.State == ProcessState.Finish)
                {
                    continue;
                }
                process.Run();
                Util.PrintProcesses(processes);
                process.Update();
                _currentTime++;
                if (process.Finished)
                {
                    _finishTime[process.PCB.PID] = _currentTime;
                }
                else
                {
                    process.Wait();
                }
            }
        }
    }
}
