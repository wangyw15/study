using System.Net;
using System.Net.Sockets;

namespace SimpleHttpServer.Core;

public struct HttpRequestMessage
{
    public string Method { get; set; }
    public string Path { get; set; }
    public string Version { get; set; }
    public Dictionary<string, string> Headers { get; set; }

    public static HttpRequestMessage ParseMessage(string msg)
    {
        var ret = new HttpRequestMessage();
        ret.Headers = new Dictionary<string, string>();

        var lines = msg.Split("\r\n");

        // parse http basic info
        var splitedFirstLine = lines[0].Split(' ');
        ret.Method = splitedFirstLine[0];
        ret.Path = splitedFirstLine[1];
        ret.Version = splitedFirstLine[2][5..];

        foreach (var line in lines[1..])
        {
            var splittedLine = line.Split(':');
            var key = splittedLine[0].Trim();
            var value = splittedLine[1].Trim();
            if (ret.Headers.ContainsKey(key))
            {
                ret.Headers[key] = value;
            }
            else
            {
                ret.Headers.Add(key, value);
            }
        }

        return ret;
    }
}

public struct HttpResponseMessage
{
    public string Version { get; set; }
    public int StatusCode { get; set; }
    public string StatusMessage { get; set; }
    public Dictionary<string, string> Headers { get; set; }
}

public class HttpServer
{
    protected TcpListener _listener;
    protected string _wwwroot;

    public HttpServer(string wwwroot, IPAddress addr, int port)
    {
        _wwwroot = wwwroot;
        _listener = new TcpListener(addr, port);
    }

    public HttpServer(string wwwroot, IPEndPoint ep)
    {
        _wwwroot = wwwroot;
        _listener = new TcpListener(ep);
    }

    public void Start()
    {
        _listener.Start();
        //_listener.AcceptTcpClient()
    }

    public void Stop()
    {
        _listener.Stop();
    }
}
