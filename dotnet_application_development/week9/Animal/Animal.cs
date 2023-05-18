namespace Animal;

class Animal
{
    public string Gender { get; set; } = "";
    public int Age { get; set; }

    public override string ToString()
    {
        return $"Animal, gender: {Gender}, age: {Age}";
    }
    
    public override bool Equals(object? obj)
    {
        if (obj != null && obj is Animal)
        {
            return (obj as Animal).Gender == Gender && (obj as Animal).Age == Age;
        }
        return false;
    }
}

class Tiger : Animal
{
    public string Color { get; set; } = "";
    public double Weight { get; set; }

    public override string ToString()
    {
        return $"Tiger, gender: {Gender}, age: {Age}, color: {Color}, weight: {Weight}";
    }

    public override bool Equals(object? obj)
    {
        if (obj != null)
        {
            if (obj is Cat)
            {
                return base.Equals(obj) && (obj as Cat).Color == Color && (obj as Cat).Weight == Weight;
            }
            else if (obj is Tiger)
            {
                return base.Equals(obj) && (obj as Tiger).Color == Color && (obj as Tiger).Weight == Weight;
            }
        }
        return false;
    }
}

class Cat : Animal
{
    public string Color { get; set; } = "";
    public double Weight { get; set; }

    public override string ToString()
    {
        return $"Cat, gender: {Gender}, age: {Age}, color: {Color}, weight: {Weight}";
    }

    public override bool Equals(object? obj)
    {
        if (obj != null)
        {
            if (obj is Cat)
            {
                return base.Equals(obj) && (obj as Cat).Color == Color && (obj as Cat).Weight == Weight;
            }
            else if (obj is Tiger)
            {
                return true;
            }
        }
        return false;
    }
}
