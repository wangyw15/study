using SimpleHttpServer.Core;
using System.Net;
using HttpRequest = SimpleHttpServer.Core.HttpRequest;
using HttpResponseMessage = SimpleHttpServer.Core.HttpResponse;

var server = new HttpServer("./wwwroot", IPAddress.Loopback, 8080);
server.OnRequest += (HttpRequest request) =>
{
	var ret = new HttpResponseMessage()
	{
		StatusCode = 200,
		Content = "<html><body><h1>Hello World</h1></body></html>",
		ContentType = "text/html"
	};
	return ret;
};
server.Start();
Console.ReadLine();
