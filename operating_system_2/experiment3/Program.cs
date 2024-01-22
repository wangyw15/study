namespace experiment3;

class Program
{
    static void Main()
    {
        var virtualSize = 32;
        var pages = Instruction.GeneratePageSequence(virtualSize);

        for (var i = 4; i < 33; i++)
        {
            var physicalSize = i;

            Console.WriteLine($"Physical size: {physicalSize}");

            var opt = new OptPaging();
            Console.WriteLine($"OPT: {opt.Run(pages, physicalSize)}");

            var lru = new LRUPaging();
            Console.WriteLine($"LRU: {lru.Run(pages, physicalSize)}");

            var fifo = new FIFOPaging();
            Console.WriteLine($"FIFO: {fifo.Run(pages, physicalSize)}");
            
            Console.WriteLine();
        }
    }
}
