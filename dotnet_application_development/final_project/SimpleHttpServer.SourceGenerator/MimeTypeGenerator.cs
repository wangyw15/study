using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml.Linq;
using Microsoft.CodeAnalysis;

namespace SimpleHttpServer.SourceGenerator
{
    [Generator]
    public class MimeTypeGenerator : ISourceGenerator
    {
        public void Execute(GeneratorExecutionContext context)
		{
			var generated = new StringBuilder();
			generated.Append("namespace SimpleHttpServer.Core; public static partial class MimeType { static MimeType() { _types = new Dictionary<string, string> {");
            var appendedExt = new List<string>();
			foreach (var file in context.AdditionalFiles)
            {
                if (Path.GetExtension(file.Path) == ".csv")
                {
                    var csv = file.GetText(context.CancellationToken).ToString().Split('\n');
                    for (var i = 1; i < csv.Length; i++)
                    {
                        if (string.IsNullOrEmpty(csv[i]))
                        {
                            continue;
                        }
                        var splitted = csv[i].Split(',');
                        var name = splitted[0].Trim();
                        var template = splitted[1].Trim();
                        if (!appendedExt.Contains(name))
						{
							generated.Append("{" + "\"" + name + "\"" + "," + "\"" + template + "\"" + "},");
                            appendedExt.Add(name);
						}
					}
                }
			}
			generated.Append("}; }}");
			context.AddSource("MimeTypes.g.cs", generated.ToString());
		}

        public void Initialize(GeneratorInitializationContext context)
        {

        }
    }
}
