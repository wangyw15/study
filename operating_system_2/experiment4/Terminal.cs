using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace experiment4;

public class Terminal
{
    private string _User = "";
    private readonly Dictionary<string, Action<string, string[]>> _Commands = [];

    public void RegisterCommand(string name, Action<string, string[]> action)
    {
        _Commands[name] = action;
    }

    public void Run()
    {
        Console.ForegroundColor = ConsoleColor.White;
        while (true)
        {
            Console.Write("> ");
            var line = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(line))
            {
                continue;
            }
            var arguments = (from x in line.Split(' ') select x.Trim()).ToArray();
            if (arguments[0] == "login")
            {
                if (arguments.Length != 2 || string.IsNullOrEmpty(arguments[1]))
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("login command requires 1 argument");
                    Console.ForegroundColor = ConsoleColor.White;
                }
                else
                {
                    _User = arguments[1];
                    Console.WriteLine($"Logged as {_User}");
                }
            }
            else if (arguments[0] == "exit")
            {
                break;
            }
            else
            {
                if (string.IsNullOrEmpty(_User))
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("You must login first");
                    Console.ForegroundColor = ConsoleColor.White;
                    continue;
                }
                
                if (_Commands.TryGetValue(arguments[0], out var action))
                {
                    action(_User, arguments);
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Invalid command");
                    Console.ForegroundColor = ConsoleColor.White;
                }
            }
        }
    }
}
