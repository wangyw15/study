using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleHttpServer.Core;

public static class MimeTypes
{
	private static Dictionary<string, string> _types;

	static MimeTypes()
	{
		_types = new Dictionary<string, string>
		{
			{ "html", "text/html" },
			{ "css", "text/css" },
			{ "png", "image/png" }
		};
	}

	public static string GetMimeType(string name)
	{
		return _types[name];
	}
}
