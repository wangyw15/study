using SimpleHttpServer.Core;
using System;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using HttpRequest = SimpleHttpServer.Core.HttpRequest;
using HttpResponseMessage = SimpleHttpServer.Core.HttpResponse;

namespace WebTodo
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
			var html = "<html>\r\n<head>\r\n<title>WebTodo</title>\r\n</head>\r\n<body>\r\n<p>\r\n<textarea cols=\"100\" rows=\"20\" id=\"content\" onchange=\"setContent()\"></textarea>\r\n</p>\r\n<script>\r\nvar content = document.querySelector(\"#content\");\r\nfetch('/get').then(resp => resp.text()).then(text => content.value = text);\r\nfunction setContent(){\r\nfetch('/set?content=' + content.value);\r\n}\r\n</script>\r\n</body>\r\n</html>";
			_server = new HttpServer(new IPEndPoint(IPAddress.Any, 8080));
			_server.OnGet += (HttpRequest request) =>
			{
				var ret = new HttpResponseMessage();
				if (request.Path == "/set")
				{
					Application.Current.Dispatcher.Invoke(() =>
					{
						textContent.Text = request.Parameters["content"];
					});
					_content = request.Parameters["content"];
					ret.StatusCode = 200;
					ret.StatusMessage = "OK";
					ret.Content = new byte[0];
					ret.ContentType = MimeType.GetMimeType("html");
				}
				else if (request.Path == "/get")
				{
					ret.StatusCode = 200;
					ret.StatusMessage = "OK";
					ret.Content = Encoding.UTF8.GetBytes(_content);
					ret.ContentType = MimeType.GetMimeType("html");
				}
				else
				{
					ret.StatusCode = 200;
					ret.StatusMessage = "OK";
					ret.Content = Encoding.UTF8.GetBytes(html);
					ret.ContentType = MimeType.GetMimeType("html");
				}
				return ret;
			};
			Task.Run(_server.Start);
		}

		private HttpServer _server;
		private string _content= "";

		private void SetContent(object sender, EventArgs e)
		{
			_content = textContent.Text;
		}
	}
}
