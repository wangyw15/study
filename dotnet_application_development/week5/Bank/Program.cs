var accounts = new List<Account>();
var generateID = (int min, int max) => {
    var r = new Random();
    var id = -1;
    while (id == -1 || (from x in accounts where x.ID == id select x).Any())
    {
        id = r.Next(min, max);
    }
    return id;
};
var printAllAccounts = () => {
    foreach (var i in accounts)
    {
        var accountType = i is SavingAccount ? "活期账户" : "储蓄存款账户";
        Console.WriteLine($"{i.ID} - {accountType} - {i.OwnerName}");
    }
};

while (true)
{
    Console.WriteLine("1. 查看所有账户\n2. 新建账户\n3. 取款\n4. 存款\n5. 订购支票簿\n6. 查询存款\n7. 查询利率\nq. 退出");
    var choice = Console.ReadLine();
    if (choice == "q")
    {
        break;
    }
    else if (choice == "1")
    {
        printAllAccounts();
    }
    else if (choice == "2")
    {
        Console.Write("1. 活期账户\n2. 储蓄存款账户\n请选择账户类型: ");
        choice = Console.ReadLine();
        if (choice == "1")
        {
            Console.Write("请输入姓名: ");
            var name = Console.ReadLine();
            Console.Write("请输入初始存额: ");
            var balance = int.Parse(Console.ReadLine());
            accounts.Add(new CheckingAccount(name, generateID(100000, 499999), balance));
        }
        else if (choice == "2")
        {
            Console.Write("请输入姓名: ");
            var name = Console.ReadLine();
            accounts.Add(new SavingAccount(name, generateID(500000, 999999)));
        }
    }
    else if (choice == "3")
    {
        printAllAccounts();
        Console.Write("请输入账户ID: ");
        var id = int.Parse(Console.ReadLine());
        var account = (from x in accounts where x.ID == id select x).First();
        Console.WriteLine("请输入取款金额: ");
        var amount = int.Parse(Console.ReadLine());
        if (amount <= account.Balance)
        {
            account.Withdraw(amount);
            Console.WriteLine($"当前账户余额: {account.Balance}");
        }
        else
        {
            Console.WriteLine("不能透支");
        }
    }
    else if (choice == "4")
    {
        printAllAccounts();
        Console.Write("请输入账户ID: ");
        var id = int.Parse(Console.ReadLine());
        var account = (from x in accounts where x.ID == id select x).First();
        Console.WriteLine("请输入存款金额: ");
        var amount = int.Parse(Console.ReadLine());
        account.Deposit(amount);
        Console.WriteLine($"当前账户余额: {account.Balance}");
    }
    else if (choice == "5")
    {
        var savingAccounts = (from x in accounts where x is SavingAccount select x);
        foreach (var i in savingAccounts)
        {
            Console.WriteLine($"{i.ID} - 储蓄存款账户 - {i.OwnerName}");
        }
        Console.Write("请输入账户ID: ");
        var id = int.Parse(Console.ReadLine());
        var account = (from x in accounts where x.ID == id select x).First() as SavingAccount;
        Console.WriteLine("订购成功");
    }
    else if (choice == "6")
    {
        printAllAccounts();
        Console.Write("请输入账户ID: ");
        var id = int.Parse(Console.ReadLine());
        var account = (from x in accounts where x.ID == id select x).First();
        Console.WriteLine($"账户余额为: {account.Balance}");
    }
    else if (choice == "7")
    {
        var savingAccounts = (from x in accounts where x is SavingAccount select x);
        foreach (var i in savingAccounts)
        {
            Console.WriteLine($"{i.ID} - 储蓄存款账户 - {i.OwnerName}");
        }
        Console.Write("请输入账户ID: ");
        var id = int.Parse(Console.ReadLine());
        var account = (from x in accounts where x.ID == id select x).First() as SavingAccount;
        Console.WriteLine($"年利率为{account.GetInterests() * 100}%");
    }
}
