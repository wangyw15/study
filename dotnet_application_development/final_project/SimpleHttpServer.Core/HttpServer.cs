using System.Net;
using System.Net.Sockets;
using System.Reflection.PortableExecutable;
using System.Text;

namespace SimpleHttpServer.Core;

public struct HttpRequestMessage
{
    public string Method { get; set; }
    public string Path { get; set; }
    public string Version { get; set; }
    public Dictionary<string, string>? Headers { get; set; }

    public static HttpRequestMessage ParseMessage(string msg)
    {
        var ret = new HttpRequestMessage();
        ret.Headers = new Dictionary<string, string>();

        var lines = msg.Split("\r\n");

        // parse http basic info
        var splitedFirstLine = lines[0].Split(' ');
        ret.Method = splitedFirstLine[0];
        ret.Path = splitedFirstLine[1];
        ret.Version = splitedFirstLine[2];

        foreach (var line in lines[1..])
        {
			if (string.IsNullOrEmpty(line))
			{
				continue;
			}
            var splittedLine = line.Split(':');
			if (splittedLine.Length != 2)
			{
				continue;
			}
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

	public override string ToString()
	{
		var builder = new StringBuilder();
		builder.Append($"{Method} {Path} {Version}\r\n");
		if (Headers != null)
		{
			foreach(var header in Headers)
			{
				builder.Append($"{header.Key}: {header.Value}\r\n");
			}
		}
		builder.Append("\r\n");
		return builder.ToString();
	}
}

public struct HttpResponseMessage
{
    public string Version { get; set; }
    public int StatusCode { get; set; }
    public string StatusMessage { get; set; }
    public Dictionary<string, string>? Headers { get; set; }
    public string Content { get; set; }

	public HttpResponseMessage()
	{
		Version = "HTTP/1.1";
		StatusCode = 200;
		StatusMessage = "OK";
		Headers = new Dictionary<string, string>();
		Headers.Add("Content-Type", "text/html; charset=utf-8");
		Headers.Add("Server", "SimpleHttpServer/0.1");
		Headers.Add("Connection", "close");
		Content = "";
	}

	public override string ToString()
	{
		var ret = new StringBuilder();
		ret.Append($"{Version} {StatusCode} {StatusMessage}\r\n");
        if (Headers == null)
		{
			Headers = new Dictionary<string, string>();
		}
		if (!Headers.ContainsKey("Content-Length"))
		{
			Headers.Add("Content-Length", Encoding.UTF8.GetByteCount(Content).ToString());
		}
		foreach (var header in Headers)
		{
			ret.Append($"{header.Key}: {header.Value}\r\n");
		}
		ret.Append("\r\n");
        ret.Append(Content);
		ret.Append("\r\n");

		return ret.ToString();
	}
}

public class HttpServer
{
	public delegate HttpResponseMessage RequestHandler(HttpRequestMessage request);
	public event RequestHandler OnRequest;
    
	protected TcpListener _listener;
    protected string _wwwroot;

	public HttpServer(string wwwroot, IPAddress addr, int port)
    {
        _wwwroot = wwwroot;
        _listener = new TcpListener(addr, port);
        // OnRequest += _DefaultHandler;
	}

    public HttpServer(string wwwroot, IPEndPoint ep)
    {
        _wwwroot = wwwroot;
        _listener = new TcpListener(ep);
		// OnRequest += _DefaultHandler;
	}

    protected HttpResponseMessage _DefaultHandler(HttpRequestMessage request)
    {
		var ret = new HttpResponseMessage();
		ret.Version = "HTTP/1.1";
		ret.StatusCode = 200;
		ret.StatusMessage = "OK";
		ret.Headers = new Dictionary<string, string>();
		ret.Headers.Add("Content-Type", "text/html; charset=utf-8");
		ret.Headers.Add("Server", "SimpleHttpServer/0.1");

		return ret;
	}

	public void Start()
    {
        _listener.Start();
        while (true)
		{
			var client = _listener.AcceptTcpClient();
			var stream = client.GetStream();
			
			// read request
			Span<byte> buffer = new byte[1024];
			stream.Read(buffer);
			var msg = Encoding.UTF8.GetString(buffer);
			var request = HttpRequestMessage.ParseMessage(msg);

			// handle request
			var response = OnRequest.Invoke(request);
			// write response
			var responseMsg = response.ToString();
			Console.WriteLine(response);
			var responseBytes = Encoding.UTF8.GetBytes(responseMsg);
			stream.Write(responseBytes);
			// close connection
			stream.Flush();
			client.Close();
            buffer.Clear();
		}
    }

    public void Stop()
    {
        _listener.Stop();
    }
}
