// create graph
int[,] graph = new int[7, 7]{
    { int.MaxValue , 6            , 7            , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue } ,
    { int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , 6            , 3            , int.MaxValue },
    { int.MaxValue , int.MaxValue , int.MaxValue , 2            , int.MaxValue , int.MaxValue , int.MaxValue },
    { int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , 10           , 3            , int.MaxValue },
    { int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , 11           },
    { int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , 4            },
    { int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue , int.MaxValue }
};

var FirstVertex = (int n) =>
{
    for (var i = 0; i < 7; i++)
    {
        if (graph[n, i] != int.MaxValue)
        {
            return i;
        }
    }
    return -1;
};

var NextVertex = (int n1, int n2) =>
{
    for (var i = n2 + 1; i < 7; i++)
    {
        if (graph[n1, i] != int.MaxValue)
        {
            return i;
        }
    }
    return -1;
};

var Dijkstra = (int start, int end) =>
{
    // intialize data
    int[] distance = new int[7], path = new int[7];
    bool[] visited = new bool[7];
    for (var i = 0; i < 7; i++)
    {
        distance[i] = graph[start, i];
        if (distance[i] == int.MaxValue)
        {
            path[i] = -1;
        }
        else
        {
            path[i] = start;
        }
    }
    visited[start] = true; // U={start}

    // Dijkstra
    for (var i = 0; i < 7; i++)
    {
        int shortest = int.MaxValue;
        int u = start;
        for (var j = 0; j < 7; j++)
        {
            if (!visited[j] && distance[j] < shortest)
            {
                u = j;
                shortest = distance[j];
            }
        }
        visited[u] = true;

        for (var j = FirstVertex(u); j != -1; j = NextVertex(u, j))
        {
            if (!visited[j] && shortest + graph[u, j] < distance[j])
            {
                distance[j] = shortest + graph[u, j];
                path[j] = u;
            }
        }
    }

    var ret = new List<int>();
    int v = end;
    while (v != -1)
    {
        ret.Insert(0, v);
        v = path[v];
    }
    return ret.ToArray();
};

while (true)
{
    Console.Write("start end: ");
    var line = Console.ReadLine();
    if (string.IsNullOrEmpty(line))
    {
        break;
    }
    var points = (from x in line.Split(" ") select x[0] - 'A').ToArray();
    var path = Dijkstra(points[0], points[1]);
    Console.Write((char)('A' + path[0]));
    for (var i = 1; i < path.Length; i++)
    {
        Console.Write($" --{graph[path[i - 1], path[i]]}-> {(char)('A' + path[i])}");
    }
    Console.WriteLine();
}
