// intialize data
var winner = new Winner();
winner.Add("男子100米", "刘庆平", "四川");
winner.Add("女子800米", "王安新", "北京");
winner.Add("男子跳高", "胡颖", "云南");
winner.Add("女子铅球", "丁丰岚", "辽宁");
winner.Add("男子10000米", "李铭钧", "上海");

Console.WriteLine(winner[1]);
Console.WriteLine(winner["项目", "女子800米"]);
Console.WriteLine(winner["选手", "王安新"]);
Console.WriteLine(winner[false, "王安新"]);

class Winner
{
    private List<(string sport, string name, string region)> _winners;

    public Winner()
    {
        _winners = new ();
    }

    public void Add(string sport, string name, string region)
    {
        _winners.Add((sport, name, region));
    }

    public string this[int n]
    {
        get
        {
            if (0 <= n && n < _winners.Count)
            {
                return $"{_winners[n].sport}冠军：{_winners[n].region}选手{_winners[n].name}";
            }
            return "";
        }
    }

    public string this[string field, string query]
    {
        get
        {
            (string sport, string name, string region)? item = null;
            if (field == "项目")
            {
                var result = from x in _winners where x.sport == query select x;
                if (result.Any())
                {
                    item = result.First();
                }
            }
            else if (field == "选手")
            {
                var result = from x in _winners where x.name == query select x;
                if (result.Any())
                {
                    item = result.First();
                }
            }

            if (item.HasValue)
            {
                return $"{item.Value.sport}冠军：{item.Value.region}选手{item.Value.name}";
            }
            return "";
        }
    }

    public string this[bool is_sport, string query]
    {
        get
        {
            (string sport, string name, string region)? item = null;
            if (is_sport)
            {
                var result = from x in _winners where x.sport == query select x;
                if (result.Any())
                {
                    item = result.First();
                }
            }
            else
            {
                var result = from x in _winners where x.name == query select x;
                if (result.Any())
                {
                    item = result.First();
                }
            }

            if (item.HasValue)
            {
                return $"{item.Value.sport}冠军：{item.Value.region}选手{item.Value.name}";
            }
            return "";
        }
    }
}
