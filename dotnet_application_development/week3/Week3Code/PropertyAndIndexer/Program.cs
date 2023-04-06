var names = new Names();

while (true)
{
    Console.WriteLine("1. Add name");
    Console.WriteLine("2. Get name by last name");
    Console.WriteLine("q. exit");
    Console.WriteLine("Enter choice:");
    var line = Console.ReadLine();
    if (line == "1")
    {
        Console.Write("Enter name(3 parts): ");
        var splitted = Console.ReadLine().Split(" ");
        names.Add(splitted[0], splitted[1], splitted[2]);
    }
    else if (line == "2")
    {
        Console.Write("Enter last name: ");
        var name = names[Console.ReadLine()];
        Console.WriteLine(name);
    }
    else if (line == "q")
    {
        break;
    }
}

// ---

struct Name
{
    public string FirstName = "";
    public string MiddleName = "";
    public string LastName = "";

    public Name()
    {
        FirstName = "";
        MiddleName = "";
        LastName = "";
    }

    public Name(string firstName, string middleName, string lastName)
    {
        FirstName = firstName;
        MiddleName = middleName;
        LastName = lastName;
    }

    public override string ToString()
    {
        var middle = string.IsNullOrEmpty(MiddleName) ? "" : MiddleName.FirstOrDefault().ToString().ToUpper();
        return $"{FirstName} {middle} {LastName}";
    }
}

class Names
{
    private List<Name> _names;

    public Names() => _names = new List<Name>();

    public Names(List<Name> names)
    {
        _names = new List<Name>();
        foreach (var name in names)
        {
            _names.Add(name);
        }
    }

    public void Add(Name name) => _names.Add(name);

    public void Add(string firstName, string middleName, string lastName) => _names.Add(new Name(firstName, middleName, lastName));

    public void Remove(Name name) => _names.Remove(name);

    public void RemoveAt(int index) => _names.RemoveAt(index);

    public Name this[string lastName]
    {
        get
        {
            var ret = from x in _names where x.LastName.ToLower() == lastName.ToLower() select x;
            return ret.FirstOrDefault();
        }
        set
        {
            for (var i = 0; i < _names.Count; i++)
            {
                if (_names[i].LastName == lastName)
                {
                    _names[i] = value;
                    break;
                }
            }
        }
    }
}