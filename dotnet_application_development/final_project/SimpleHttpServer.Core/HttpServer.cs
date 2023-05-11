using System.Net;
using System.Net.Sockets;
using System.Reflection.PortableExecutable;
using System.Text;

namespace SimpleHttpServer.Core;

public struct HttpRequest
{
    public string Method { get; set; }
    public string Path { get; set; }
    public string Version { get; set; }
    public Dictionary<string, string>? Headers { get; set; }

    public static HttpRequest ParseMessage(string msg)
    {
        var ret = new HttpRequest();
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

public struct HttpResponse
{
    public string Version { get; set; }
    public int StatusCode { get; set; }
    public string StatusMessage { get; set; }
    public string Content { get; set; }
    public string ContentType { get; set; }

    public HttpResponse()
    {
        Version = "HTTP/1.1";
        StatusCode = 200;
        StatusMessage = "OK";
        Content = "";
        ContentType = "text/plain";
    }

    public override string ToString()
    {
        var ret = new StringBuilder();
        ret.Append($"{Version} {StatusCode} {StatusMessage}\r\n");
        ret.Append($"Content-Length: {Content.Length}\r\n");
        ret.Append($"Content-Type: {ContentType}\r\n");
        ret.Append("\r\n");
        ret.Append(Content);
        ret.Append("\r\n\r\n");
        return ret.ToString();
    }
}

public class HttpServer
{
    public delegate HttpResponse RequestHandler(HttpRequest request);
    public event RequestHandler? OnRequest;
    
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
        while (true)
        {
            var client = _listener.AcceptTcpClient();
            var task = new Task(() => ConnectionHander(client));
            task.Start();
        }
    }

    public void Stop()
    {
        _listener.Stop();
    }

    protected void ConnectionHander(TcpClient client)
	{
        Console.WriteLine("New incoming request");
		var stream = client.GetStream();
		// read request
		Span<byte> buffer = new byte[10240];
		var length = stream.Read(buffer);
		var msg = Encoding.UTF8.GetString(buffer[0..length]);
		var request = HttpRequest.ParseMessage(msg);

		// handle request
		var response = new HttpResponse();
		if (OnRequest != null)
		{
			response = OnRequest.Invoke(request);
		}
		// write response
		var responseMsg = response.ToString();
		stream.Write(Encoding.UTF8.GetBytes(responseMsg));
		// close connection
		stream.Flush();
		client.Close();
		buffer.Clear();
	}
}
