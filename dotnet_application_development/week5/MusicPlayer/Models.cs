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

    }

    public bool IRecordable.Checked(string f)
    {

    }

    public void Save()
    {

    }

    public void Find(string u)
    {

    }

    public bool IPlayable.Checked(string f)
    {

    }

    public void Play(string v)
    {

    }
}
