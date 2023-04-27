class RainEventArgs : EventArgs
{
    public double Amount { get; set; }
    public TimeSpan Duration { get; set; }

    public RainEventArgs()
    {
        Amount = 0;
        Duration = TimeSpan.Zero;
    }

    public RainEventArgs(double amount, TimeSpan duration)
    {
        Amount = amount;
        Duration = duration;
    }
}

class Rain
{
    public delegate void RainHandler(object sender, RainEventArgs e);

    private RainHandler _rainEvent;

    public event RainHandler RainEvent
    {
        add
        {
            _rainEvent += value;
        }
        remove
        {
            if (_rainEvent != null)
            {
                _rainEvent -= value;
            }
        }
    }

    public Rain()
    {
        _rainEvent += (object sender, RainEventArgs e) => {};
    }

    public void StartRain()
    {
        _rainEvent.Invoke(this, new RainEventArgs(100, TimeSpan.FromHours(2)));
    }
}
