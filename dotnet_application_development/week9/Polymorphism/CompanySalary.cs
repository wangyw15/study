namespace CompanySalary;

enum EmployeePosition
{
    Normal,
    Manager,
    DecisionMaker,
}

abstract class Employee
{
    public string Name { get; set; } = "";

    public string Gender { get; set; } = "";

    public DateTime Birthday { get; set; }

    public string ID { get; set; } = "";

    public DateTime EntryDate { get; set; }

    public EmployeePosition Position { get; set; }

    public double LevelCoefficient { get; set; }

    public string Title { get; set; } = "";

    public string Assessment { get; set; } = "";

    public double BaseSalary { get; set; }

    public double PerfSalary { get; set; }

    public double PositionSalary
    {
        get
        {
            return (int)Position * 1000;
        }
    }

    public double YearSalary
    {
        get
        {
            return (DateTime.Now - EntryDate).Days / 365.0 * 50;
        }
    }

    public Employee(string name, string gender, DateTime birthday, string id, DateTime entry, EmployeePosition position, double baseSalary)
    {
        Name = name;
        Gender = gender;
        Birthday = birthday;
        ID = id;
        EntryDate = entry;
        Position = position;
        BaseSalary = baseSalary;
    }

    public abstract double GetSalary();
}

class Normal : Employee
{
    public Normal(string name, string gender, DateTime birthday, string id, DateTime entry, EmployeePosition position, double baseSalary) : 
        base(name, gender, birthday, id, entry, position, baseSalary)
    { }

    public override double GetSalary()
    {
        return BaseSalary + YearSalary + PerfSalary;
    }
}

class Manager : Employee
{
    public Manager(string name, string gender, DateTime birthday, string id, DateTime entry, EmployeePosition position, double baseSalary) : 
        base(name, gender, birthday, id, entry, position, baseSalary)
    { }

    public override double GetSalary()
    {
        return BaseSalary + PositionSalary + YearSalary + PerfSalary;
    }
}

class DecisionMaker : Employee
{
    public double SmoothSalary { get; set; }

    public int Class { get; set; }

    public DecisionMaker(string name, string gender, DateTime birthday, string id, DateTime entry, EmployeePosition position, double baseSalary, int cls) : 
        base(name, gender, birthday, id, entry, position, baseSalary)
    {
        Class = cls;
    }
    
    public override double GetSalary()
    {
        return BaseSalary + PerfSalary * Class + SmoothSalary + YearSalary;
    }
}
