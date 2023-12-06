namespace experiment2;

class Program
{
    static void Main(string[] args)
    {
        var processAmount = 5;
        var resourceAmount = 3;
        var scale = 3;

        var max = new int[resourceAmount];
        for (var i = 0; i < resourceAmount; i++)
        {
            max[i] = RandomNumber(processAmount, processAmount * scale);
        }

        var available = new int[resourceAmount];
        for (var i = 0; i < resourceAmount; i++)
        {
            available[i] = max[i];
        }

        var allocation = new int[processAmount, resourceAmount];
        for (var i = 0; i < processAmount; i++)
        {
            for (var j = 0; j < resourceAmount; j++)
            {
                allocation[i, j] = RandomNumber(0, available[j] / 2);
                available[j] -= allocation[i, j];
            }
        }

        var need = new int[processAmount, resourceAmount];
        for (var i = 0; i < processAmount; i++)
        {
            for (var j = 0; j < resourceAmount; j++)
            {
                need[i, j] = RandomNumber(0, max[j]);
            }
        }

        Console.WriteLine("Max");
        Print(max);
        Console.WriteLine();

        Console.WriteLine("Available");
        Print(available);
        Console.WriteLine();

        Console.WriteLine("Allocation");
        Print(allocation);
        Console.WriteLine();

        Console.WriteLine("Need");
        Print(need);
        Console.WriteLine();

        // test if the system is in a safe state
        var sequence = new List<int>();
        var satisfied = new bool[processAmount];
        while (satisfied.Any(x => !x))
        {
            var satisfiedCount = satisfied.Count(x => x);
            for (var i = 0; i < processAmount; i++)
            {
                if (satisfied[i])
                {
                    continue;
                }

                var canSatisfy = true;
                for (var j = 0; j < resourceAmount; j++)
                {
                    if (need[i, j] > available[j])
                    {
                        canSatisfy = false;
                        break;
                    }
                }

                if (canSatisfy)
                {
                    satisfied[i] = true;
                    sequence.Add(i);
                    for (var j = 0; j < resourceAmount; j++)
                    {
                        available[j] += allocation[i, j];
                    }
                }

                i = (i + 1) % processAmount;
            }
            if (satisfiedCount == satisfied.Count(x => x))
            {
                break;
            }
        }

        if (satisfied.All(x => x))
        {
            foreach (var i in sequence)
            {
                Console.Write($"{i} ");
            }
            Console.WriteLine();
        }
        else
        {
            Console.WriteLine("The system is not in a safe state.");
        }
    }

    private static int RandomNumber(int min, int max)
    {
        var random = new Random();
        return random.Next(min, max);
    }

    private static void Print(int[,] data)
    {
        var rows = data.GetLength(0);
        var columns = data.GetLength(1);

        for (var i = 0; i < rows; i++)
        {
            for (var j = 0; j < columns; j++)
            {
                Console.Write($"{data[i, j]} ");
            }
            Console.WriteLine();
        }
    }

    private static void Print(IReadOnlyList<int> data)
    {
        var rows = data.Count;

        for (var i = 0; i < rows; i++)
        {
            Console.Write($"{data[i]} ");
        }
        Console.WriteLine();
    }
}
