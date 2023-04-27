var rain = new Rain();
rain.RainEvent += RainHandler;
rain.StartRain();

static void RainHandler(object sender, RainEventArgs e)
{
    Console.WriteLine($"Amount: {e.Amount}  Duration: {e.Duration}");
}
