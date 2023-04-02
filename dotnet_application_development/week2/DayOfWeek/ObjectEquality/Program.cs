using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectEquality
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 1;
            float f = 1.0f;
            Console.WriteLine($"a == b: {a == b}");
            Console.WriteLine($"Object.Equals(a, b): {Object.Equals(a, b)}");
            
            Console.WriteLine($"a == f: {a == f}");
            Console.WriteLine($"Object.Equals(a, f): {Object.Equals(a, f)}");

            object t1 = new object(), t2 = new object();
            Console.WriteLine($"t1 == t2: {t1 == t2}");
            Console.WriteLine($"Object.Equals(t1, t2): {Object.Equals(t1, t2)}");

            Console.ReadLine();
        }
    }
}
