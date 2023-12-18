namespace experiment3;

class Program
{
    static void Main()
    {
        var virtualSize = 32;
        var physicalSize = 8;
        
        var pages = Instruction.GeneratePageSequence(virtualSize);

        var opt = new OptPaging();
        Console.WriteLine($"OPT: {opt.Run(pages, physicalSize)}");

        var lru = new LRUPaging();
        Console.WriteLine($"LRU: {lru.Run(pages, physicalSize)}");
    }
}
