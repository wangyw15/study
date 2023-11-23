namespace experiment1;

public enum ProcessState
{
    Run,
    Wait,
    Finish
}

public struct ProcessControlBlock
{
    public int PID;
    public int Priority;
    public int ArrivalTime;
    public int UsedCPUTime;
    public int TotalCPUTime;
    public ProcessState State;
}

public class Process
{
    public ProcessControlBlock PCB;

    public Process(int pid, int priority, int arrivalTime, int totalCpuTime)
    {
        PCB.PID = pid;
        PCB.Priority = priority;
        PCB.ArrivalTime = arrivalTime;
        PCB.UsedCPUTime = 0;
        PCB.TotalCPUTime = totalCpuTime;
        PCB.State = ProcessState.Wait;
    }

    public bool Finished => PCB.State == ProcessState.Finish;

    public void Run()
    {
        if (PCB.State != ProcessState.Finish)
        {
            PCB.State = ProcessState.Run;
        }
    }

    public void Update()
    {
        if (PCB.State == ProcessState.Run)
        {
            PCB.UsedCPUTime++;
        }
        if (PCB.UsedCPUTime == PCB.TotalCPUTime)
        {
            PCB.State = ProcessState.Finish;
        }
    }

    public void Wait()
    {
        if (PCB.State != ProcessState.Finish)
        {
            PCB.State = ProcessState.Wait;
        }
    }

    public override string ToString()
    {
        return $"PID: {PCB.PID}, Priority: {PCB.Priority}, ArrivalTime: {PCB.ArrivalTime}, UsedCPUTime: {PCB.UsedCPUTime}, CPUTimeNeeded: {PCB.TotalCPUTime}, State: {PCB.State}";
    }
}
