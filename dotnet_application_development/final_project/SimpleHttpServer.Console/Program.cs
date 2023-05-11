using SimpleHttpServer.Core;
using HttpRequestMessage = SimpleHttpServer.Core.HttpRequestMessage;

var msg = "GET / HTTP/1.1\nHost: developer.mozilla.org\nAccept-Language: cn";
var parsed = HttpRequestMessage.ParseMessage(msg);
Console.WriteLine(parsed.Method);
Console.WriteLine(parsed.Path);
Console.WriteLine(parsed.Version);
foreach (var item in parsed.Headers)
{
	Console.WriteLine($"{item.Key} {item.Value}");
}
