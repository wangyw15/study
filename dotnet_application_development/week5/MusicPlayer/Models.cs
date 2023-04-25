interface IRecordable
{
    void Receive(string s);
    bool Checked(string f);
    void Save(string s);
}

interface IPlayable
{
    void Find(string u);
    bool Checked(string f);
    void Play(string v);
}

class MP3 : IRecordable, IPlayable
{
    public void Receive(string s)
    {
        if ((this as IRecordable).Checked(s))
        {
            Console.WriteLine($"Received file {s}");
            // do something...
        }
    }

    bool IRecordable.Checked(string f)
    {
        if (!File.Exists(f))
        {
            return f.EndsWith(".mp3") || f.EndsWith(".wav") || f.EndsWith(".flac") || f.EndsWith(".ogg");
        }
        return false;
    }

    public void Save(string s)
    {
        if ((this as IRecordable).Checked(s))
        {
            Console.WriteLine($"Saved file {s}");
            // do something...
        }
    }

    public void Find(string u)
    {
        if ((this as IPlayable).Checked(u))
        {
            Console.WriteLine($"Found file {u}");
            // do something...
        }
    }

    bool IPlayable.Checked(string f)
    {
        if (File.Exists(f))
        {
            return f.EndsWith(".mp3") || f.EndsWith(".wav") || f.EndsWith(".flac") || f.EndsWith(".ogg");
        }
        return false;
    }

    public void Play(string v)
    {
        if ((this as IPlayable).Checked(v))
        {
            Console.WriteLine($"Playing file {v}");
            // do something...
        }
    }
}
