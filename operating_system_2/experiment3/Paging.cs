namespace experiment3;

public interface PagingAlgorithm
{
    public double Run(List<int> pageSequence, int physicalMemorySize);
}

public class OptPaging : PagingAlgorithm
{
    public double Run(List<int> pageSequence, int physicalMemorySize)
    {
        double interrupt = 0;
        var memory = new int[physicalMemorySize];

        // 初始化内存
        for (var i = 0; i < physicalMemorySize; i++)
        {
            memory[i] = -1;
        }

        int clock = 0;
        foreach (var instruction in pageSequence)
        {
            var found = false;
            for (var i = 0; i < physicalMemorySize; i++)
            {
                // 命中
                if (memory[i] == instruction)
                {
                    found = true;
                    break;
                }
                // 未命中但内存有空余
                else if (memory[i] == -1)
                {
                    memory[i] = instruction;
                    interrupt++;
                    found = true;
                    break;
                }
            }
            // 缺页
            if (!found)
            {
                // 计算访问间隔
                var distance = new int[physicalMemorySize];
                for (var i = 0; i < physicalMemorySize; i++)
                {
                    distance[i] = int.MaxValue;
                    for (var j = clock + 1; j < pageSequence.Count; j++)
                    {
                        if (memory[i] == pageSequence[j])
                        {
                            distance[i] = j;
                            break;
                        }
                    }
                }
                // 找到最迟访问
                var farthestIndex = -1;
                var farthestDistance = -1;
                for (var i = 0; i < physicalMemorySize; i++)
                {
                    if (distance[i] > farthestDistance)
                    {
                        farthestIndex = i;
                        farthestDistance = distance[i];
                    }
                }
                // 替换最迟访问
                memory[farthestIndex] = instruction;
                interrupt++;
            }
            clock++;
        }
        return 1.0 - interrupt / pageSequence.Count;
    }
}

public class LRUPaging : PagingAlgorithm
{
    public double Run(List<int> pageSequence, int physicalMemorySize)
    {
        double interrupt = 0;
        var memory = new int[physicalMemorySize];
        var accessTime = new int[physicalMemorySize];

        // 初始化内存
        for (var i = 0; i < physicalMemorySize; i++)
        {
            memory[i] = -1;
            accessTime[i] = -1;
        }

        int clock = 0;
        foreach (var instruction in pageSequence)
        {
            var found = false;
            for (var i = 0; i < physicalMemorySize; i++)
            {
                // 命中
                if (memory[i] == instruction)
                {
                    found = true;
                    accessTime[i] = clock;
                    break;
                }
                // 未命中但内存有空余
                else if (memory[i] == -1)
                {
                    memory[i] = instruction;
                    interrupt++;
                    found = true;
                    accessTime[i] = clock;
                    break;
                }
            }
            // 缺页
            if (!found)
            {
                // 寻找最早访问
                var earliestIndex = int.MaxValue;
                var earliestTime = int.MaxValue;
                for (var i = 0; i < physicalMemorySize; i++)
                {
                    if (accessTime[i] < earliestTime)
                    {
                        earliestIndex = i;
                        earliestTime = accessTime[i];
                    }
                }
                // 替换最早访问
                memory[earliestIndex] = instruction;
                accessTime[earliestIndex] = clock;
                interrupt++;
            }
            clock++;
        }
        return 1.0 - interrupt / pageSequence.Count;
    }
}

public class FIFOPaging : PagingAlgorithm
{
    public double Run(List<int> pageSequence, int physicalMemorySize)
    {
        double interrupt = 0;
        var memory = new Queue<int>(physicalMemorySize);
        var usedMemory = 0;

        int clock = 0;
        foreach (var instruction in pageSequence)
        {
            var found = false;
            // 命中
            if (memory.Contains(instruction))
            {
                found = true;
            }
            // 未命中但内存有空余
            else if (usedMemory != physicalMemorySize)
            {
                memory.Enqueue(instruction);
                usedMemory++;
                interrupt++;
                found = true;
            }
            // 缺页
            if (!found)
            {
                // 先进先出
                memory.Dequeue();
                // 替换
                memory.Enqueue(instruction);
                interrupt++;
            }
            clock++;
        }
        return 1.0 - interrupt / pageSequence.Count;
    }
}
