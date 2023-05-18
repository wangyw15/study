using CompanySalary;

var n = new Normal("John", "male", new DateTime(1970, 1, 1), "3", new DateTime(2012, 1, 1), EmployeePosition.Normal, 4000);
n.PerfSalary = 1000;
var m = new Manager("Alice", "female", new DateTime(1980, 1, 1), "3", new DateTime(2020, 1, 1), EmployeePosition.Manager, 4000);
m.PerfSalary = 2000;
var d = new DecisionMaker("Emily", "female", new DateTime(1990, 1, 1), "3", new DateTime(2020, 1, 1), EmployeePosition.DecisionMaker, 4000, 2);
m.PerfSalary = 5000;
d.SmoothSalary = 10000;

Console.WriteLine($"John normal {n.GetSalary()}");
Console.WriteLine($"Alice manager {m.GetSalary()}");
Console.WriteLine($"Emily decision maker {d.GetSalary()}");
