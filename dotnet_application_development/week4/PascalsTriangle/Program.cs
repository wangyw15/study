Console.Write("Input n: ");
var line = Console.ReadLine();
var n = 0;
if (line != null)
{
    n = int.Parse(line);
}
// 1d array
var factorial = (int n) => {
    var ret = 1;
    for (var i = 1; i <= n; i++)
    {
        ret *= i;
    }
    return ret;
};
var c = (int n, int r) => {
    return factorial(n) / factorial(r) / factorial(n - r);
};
var arrayTriangle = new int[(n + 1) * n / 2];
for (var i = 0; i < n; i++)
{
    for (var j = 0; j < i + 1; j++)
    {
        arrayTriangle[(i + 1) * i / 2 + j] = c(i, j);
    }
}
for (var i = 0; i < n; i++)
{
    for (var j = 0; j < i + 1; j++)
    {
        Console.Write($"{arrayTriangle[(i + 1) * i / 2 + j]} ");
    }
    Console.WriteLine();
}

// jagged array
int[][] jaggedTriangle = new int[n][];
jaggedTriangle[0] = new int[1]{ 1 };
for (var i = 1; i < n; i++)
{
    jaggedTriangle[i] = new int[i + 1];
    jaggedTriangle[i][0] = jaggedTriangle[i][i] = 1;
    for (var j = 1; j < i; j++)
    {
        jaggedTriangle[i][j] = jaggedTriangle[i - 1][j - 1] + jaggedTriangle[i - 1][j];
    }
}
foreach(var row in jaggedTriangle)
{
    foreach(var col in row)
    {
        Console.Write($"{col} ");
    }
    Console.WriteLine();
}
