using SimpleHttpServer.Core;
using System.Net;
using HttpRequest = SimpleHttpServer.Core.HttpRequest;
using HttpResponseMessage = SimpleHttpServer.Core.HttpResponse;

var server = new HttpServer(IPAddress.Loopback, 8080);
var wwwroot = "wwwroot/";
Console.WriteLine("Listening at http://localhost:8080");
server.OnGet += (HttpRequest request) =>
{
    var ret = new HttpResponseMessage();
    var path = Path.Combine(wwwroot, request.Path[1..]);
    Console.WriteLine(request.Path);
    foreach (var item in request.Parameters)
    {
        Console.WriteLine($"{item.Key}: {item.Value}");
    }
    if (Directory.Exists(path) && File.Exists(Path.Combine(path, "index.html")))
    {
        path = Path.Combine(path, "index.html");
        ret.StatusCode = 200;
        ret.StatusMessage = "OK";
        ret.Content = File.ReadAllBytes(path);
        ret.ContentType = MimeType.GetMimeType(Path.GetExtension(path)[1..]);
    }
    else if (File.Exists(path))
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
