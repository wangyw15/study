using System.Numerics;

// 1. zeros in 1000!
// use BigInteger
var zeros1 = () => {
    var result = new BigInteger(1);
    for (int i = 1; i <= 1000; i++)
    {
        result *= i;
    }

    var count = 0;
    while (result % 10 == 0)
    {
        count++;
        result /= 10;
    }

    Console.WriteLine(count);
};
zeros1();

// count 5
var zeros2 = () => {
    var n = 1000;
    var count = 0;
    while (n != 0)
    {
        count += (n /= 5);
    }
    Console.WriteLine(count);
};
zeros2();

Console.WriteLine();

// 2. magic square
var magicSquare = () => {
    var n = 3;
    var square = new int[3,3];
    int i = n / 2, j = n - 1;

    for (var num = 1; num <= n * n;)
    {
        if (i == -1 && j == n)
        {
            j = n - 2;
            i = 0;
        }
        else
        {
            if (j == n)
            {
                j = 0;
            }
            if (i < 0)
            {
                i = n - 1;
            }
        }
        if (j >= 0)
        {
            if (square[i, j] != 0)
            {
                j -= 2;
                i++;
                continue;
            }
            else
            {
                square[i, j] = num++;
            }
        }
        j++;
        i--;
    }
    for (var a = 0; a < square.GetLength(0); a++)
    {
        for (var b = 0; b < square.GetLength(1); b++)
        {
            Console.Write(square[a, b]);
        }
        Console.WriteLine();    
    }
};
magicSquare();
