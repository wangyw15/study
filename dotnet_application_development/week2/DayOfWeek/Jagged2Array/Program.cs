using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jagged2Array
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter 7 words: ");
            var words = Console.ReadLine().Split(' ');
            
            var strJaggedArray = new string[2][];
            strJaggedArray[0] = new string[] { words[0], words[1], words[2], words[3] };
            strJaggedArray[1] = new string[] { words[4], words[5], words[6] };

            var strArray = new List<string>();
            for (int i = 0; i < strJaggedArray[0].Length; i++)
            {
                for (int j = 0; j < strJaggedArray[1].Length; j++)
                {
                    strArray.Add(strJaggedArray[0][i] + "&" + strJaggedArray[1][j]);
                }
            }

            foreach (var item in strArray)
            {
                Console.WriteLine(item);
            }
            
            Console.ReadLine();
        }
    }
}
