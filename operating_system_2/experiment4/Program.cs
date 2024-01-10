using experiment4;

var fm = new FileManager();

var terminal = new Terminal();
terminal.RegisterCommand("create", (user, arguments) =>
{
    if (arguments.Length != 3)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("create command requires 2 arguments");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }
    
    fm.CreateFile(user, arguments[1], uint.Parse(arguments[2]));
});
terminal.RegisterCommand("delete", (user, arguments) =>
{
    if (arguments.Length != 2)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("delete command requires 1 argument");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }

    fm.DeleteFile(user, arguments[1]);
});
terminal.RegisterCommand("open", (user, arguments) =>
{
    if (arguments.Length != 2)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("open command requires 1 argument");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }

    fm.OpenFile(user, arguments[1]);
});
terminal.RegisterCommand("close", (user, arguments) =>
{
    if (arguments.Length != 2)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("close command requires 1 argument");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }

    fm.CloseFile(user, arguments[1]);
});
terminal.RegisterCommand("read", (user, arguments) =>
{
    if (arguments.Length != 2)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("read command requires 1 arguments");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }

    fm.ReadFile(user, arguments[1]);
});
terminal.RegisterCommand("write", (user, arguments) =>
{
    if (arguments.Length != 2)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("write command requires 1 arguments");
        Console.ForegroundColor = ConsoleColor.White;
        return;
    }

    fm.WriteFile(user, arguments[1]);
});
terminal.RegisterCommand("ls", (user, arguments) =>
{
    fm.ListFiles(user);
});
terminal.RegisterCommand("dump", (user, arguments) =>
{
    fm.Dump();
});

terminal.Run();
