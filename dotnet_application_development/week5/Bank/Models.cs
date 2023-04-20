abstract class Account
{
    public string OwnerName { get; protected set; }
    public decimal Balance { get; protected set; }
    public int ID { get; protected set; }

    public Account(string name, int id)
    {
        OwnerName = name;
        ID = id;
    }

    public virtual void Deposit(int balance)
    {
        if (balance >= 0)
        {
            Balance += balance;
        }
    }

    public virtual void Withdraw(int balance)
    {
        if (Balance >= balance)
        {
            Balance -= balance;
        }
    }
}

class CheckingAccount : Account
{
    public CheckingAccount(string name, int id, int openingBalance) : base(name, id)
    {
        Balance = openingBalance;
    }

    public void OrderCheckBook()
    {
        
    }
}

class SavingAccount : Account
{
    public SavingAccount(string name, int id) : base(name, id)
    {
    }

    public decimal GetInterests()
    {
        return (Balance > 1000) ? (decimal)0.06 : (decimal)0.03;
    }
}
