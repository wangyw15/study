using SimpleHttpServer.Core;
using System.Net;
using System.Web;
using HttpRequest = SimpleHttpServer.Core.HttpRequest;
using HttpResponseMessage = SimpleHttpServer.Core.HttpResponse;

var server = new HttpServer(IPAddress.Loopback, 8080);
Console.WriteLine("Listening at http://localhost:8080");
server.OnRequest += (HttpRequest request) =>
{
    var ret = new HttpResponseMessage();
    var path = Path.Combine("wwwroot/", request.Path[1..]);
	Console.WriteLine(path);
    foreach (var item in request.Parameters)
	{
		Console.WriteLine($"{item.Key}: {item.Value}");
	}
    if (File.Exists(path))
    {
        ret.StatusCode = 200;
        ret.StatusMessage = "OK";
        ret.Content = File.ReadAllBytes(path);
        ret.ContentType = MimeType.GetMimeType(Path.GetExtension(path)[1..]);
	}
    else
	{
		ret.StatusCode = 404;
		ret.StatusMessage = "NOT FOUND";
	}
    return ret;
};
server.Start();
Console.ReadLine();
