namespace experiment1;

public interface IScheduler
{
    public void Schedule();
    public void Print();
}

public class HighPriorityFirst(List<Process> processes) : IScheduler
{
    private Dictionary<int, int> _finishTime = new();
    private int _currentTime = 0;

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

    private IEnumerable<Process> GetReadyChain()
    {
        return from x in processes
               where x.PCB.State != ProcessState.Finish
               orderby x.PCB.Priority descending
               select x;
    }

    public void Print()
    {
        foreach (var (pid, finishTime) in _finishTime)
        {
            Console.WriteLine($"PID: {pid}, finish time: {finishTime}");
        }
    }
}

public class RoundRobin(List<Process> processes) : IScheduler
{
    private Dictionary<int, int> _finishTime = new();
    private int _currentTime = 0;

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

    public void Print()
    {
        foreach (var (pid, finishTime) in _finishTime)
        {
            Console.WriteLine($"PID: {pid}, finish time: {finishTime}");
        }
    }
}
