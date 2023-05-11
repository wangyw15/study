using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Reflection.PortableExecutable;
using System.Runtime.InteropServices;
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
    public byte[] Content { get; set; }
    public string ContentType { get; set; }

    public HttpResponse()
    {
        Version = "HTTP/1.1";
        StatusCode = 200;
        StatusMessage = "OK";
        Content = new byte[0];
        ContentType = "text/plain";
    }

    public override string ToString()
    {
        var ret = new StringBuilder();
        ret.Append($"{Version} {StatusCode} {StatusMessage}\r\n");
        ret.Append($"Content-Length: {Content.Length}\r\n");
        ret.Append($"Content-Type: {ContentType}\r\n");
        ret.Append("\r\n");
        ret.Append(Encoding.UTF8.GetString(Content));
        ret.Append("\r\n\r\n");
        return ret.ToString();
    }

    public static implicit operator byte[](HttpResponse resp)
    {
        var ret = new List<byte>();
        ret.AddRange(Encoding.UTF8.GetBytes($"{resp.Version} {resp.StatusCode} {resp.StatusMessage}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes($"Content-Length: {resp.Content.Length}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes($"Content-Type: {resp.ContentType}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes("\r\n"));
		ret.AddRange(resp.Content);
		ret.AddRange(Encoding.UTF8.GetBytes("\r\n\r\n"));
		return ret.ToArray();
    }

	public static implicit operator ReadOnlySpan<byte>(HttpResponse resp)
	{
		var ret = new List<byte>();
		ret.AddRange(Encoding.UTF8.GetBytes($"{resp.Version} {resp.StatusCode} {resp.StatusMessage}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes($"Content-Length: {resp.Content.Length}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes($"Content-Type: {resp.ContentType}\r\n"));
		ret.AddRange(Encoding.UTF8.GetBytes("\r\n"));
		ret.AddRange(resp.Content);
		ret.AddRange(Encoding.UTF8.GetBytes("\r\n\r\n"));
        return CollectionsMarshal.AsSpan(ret);
	}
}

public class HttpServer
{
    public delegate HttpResponse RequestHandler(HttpRequest request);
    public event RequestHandler? OnRequest;
    
    protected TcpListener _listener;

    public HttpServer(IPAddress addr, int port)
    {
        _listener = new TcpListener(addr, port);
    }

    public HttpServer(IPEndPoint ep)
    {
        _listener = new TcpListener(ep);
    }

    public void Start()
    {
        _listener.Start();
        while (true)
        {
            var client = _listener.AcceptTcpClient();
            Task.Run(() => ConnectionHander(client));
        }
    }

    public void Stop()
    {
        _listener.Stop();
    }

    protected void ConnectionHander(TcpClient client)
	{
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
		stream.Write(response);
		// close connection
		stream.Flush();
		client.Close();
		buffer.Clear();
	}
}
