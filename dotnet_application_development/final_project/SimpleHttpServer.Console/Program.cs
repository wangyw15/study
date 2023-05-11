using SimpleHttpServer.Core;
using System.Net;
using HttpRequestMessage = SimpleHttpServer.Core.HttpRequestMessage;
using HttpResponseMessage = SimpleHttpServer.Core.HttpResponseMessage;

var server = new HttpServer("./wwwroot", IPAddress.Loopback, 8080);
server.OnRequest += (HttpRequestMessage request) =>
{
	var ret = new HttpResponseMessage()
	{
		StatusCode = 200,
		Content = "<html><body><h1>Hello World</h1></body></html>"
	};
	// Console.WriteLine(ret);
	return ret;
};
server.Start();
Console.ReadLine();
