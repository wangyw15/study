var points = new Point[15];
var spoints = new PointStruct[15];

for (var i = 0; i < 15; i++)
{
    points[i] = new Point(i, i);
    spoints[i] = new PointStruct(i + 100, i + 100);
}

foreach (var i in points)
{
    Console.WriteLine($"{i.x}, {i.y}");
}
foreach (var i in spoints)
{
    Console.WriteLine($"{i.x}, {i.y}");
}

class Point
{
    public int x, y;
    public Point(int i, int j) 
    {
        x = i;
        y = j;
    }
}

struct PointStruct
{
    public int x, y;
    public PointStruct(int i, int j)
    {
        x = i;
        y = j;
    }
}
