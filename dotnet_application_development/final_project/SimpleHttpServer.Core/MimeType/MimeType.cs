using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleHttpServer.Core;

public static partial class MimeType
{
	private static Dictionary<string, string> _types;
	
	public static string GetMimeType(string name)
	{
		return _types[name];
	}
}
