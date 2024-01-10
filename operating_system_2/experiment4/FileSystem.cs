using System.Text.Json;
using System.Text.Json.Serialization;

namespace experiment4;

public enum FileType
{
    File,
    Directory
}

public struct FileEntry
{
    public string Path;
    public uint Permission;
}

public class FileManager(int maxFiles = 100, int maxOpenedFiles = 1)
{
    private readonly FileEntry?[] _Files = new FileEntry?[maxFiles];
    public Dictionary<string, Dictionary<string, int>> _UserFileDirectory = []; // [user, [path, index]]
    private readonly List<KeyValuePair<string, string>> _OpenedFiles = []; // [user, path]
    private readonly int _MaxOpenedFiles = maxOpenedFiles;

    public void CreateFile(string user, string path, uint permission)
    {
        // check user fs
        if (!_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
        {
            userfs = ([]);
            _UserFileDirectory.Add(user, userfs);
        }
        // find empty block
        for (var i = 0; i < _Files.Length; i++)
        {
            if (!_Files[i].HasValue)
            {
                _Files[i] = new FileEntry
                {
                    Path = path,
                    Permission = permission
                };
                userfs.Add(path, i);
                Console.WriteLine($"{path} created");
                return;
            }
        }
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("File system full");
        Console.ForegroundColor = ConsoleColor.White;
    }

    public void DeleteFile(string user, string path)
    {
        if (_OpenedFiles.Any(x => x.Key == user && x.Value == path))
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"{path} opened");
            Console.ForegroundColor = ConsoleColor.White;
            return;
        }

        if (_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
        {
            if (userfs.TryGetValue(path, out int index))
            {
                var entry = _Files[index];
                if (entry.HasValue)
                {
                    var perm = entry.Value.Permission;
                    if ((perm & (uint)Permission.Write) == 0)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine($"{path} permission denied");
                        Console.ForegroundColor = ConsoleColor.White;
                    }
                    else
                    {
                        userfs.Remove(path);
                        _Files[index] = null;
                        Console.WriteLine($"{path} deleted");
                    }
                }
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"{path} not found");
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        else
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("Empty");
            Console.ForegroundColor = ConsoleColor.White;
        }
    }

    public void OpenFile(string user, string path)
    {
        if (_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
        {
            if (userfs.TryGetValue(path, out int index))
            {
                var entry = _Files[index];
                if (entry.HasValue)
                {
                    _OpenedFiles.Add(new KeyValuePair<string, string>(user, path));
                    Console.WriteLine($"{path} opened");
                }
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"{path} not found");
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        else
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("Empty");
            Console.ForegroundColor = ConsoleColor.White;
        }
    }

    public void CloseFile(string user, string path)
    {
        if (!_OpenedFiles.Any(x => x.Key == user && x.Value == path))
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"{path} not opened");
            Console.ForegroundColor = ConsoleColor.White;
        }
        else
        {
            _OpenedFiles.Remove(_OpenedFiles.Find(x => x.Key == user && x.Value == path));
            Console.WriteLine($"{path} closed");
        }
    }

    public void ReadFile(string user, string path)
    {
        if (!_OpenedFiles.Any(x => x.Key == user && x.Value == path))
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"{path} not opened");
            Console.ForegroundColor = ConsoleColor.White;
        }
        else
        {
            if (_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
            {
                if (userfs.TryGetValue(path, out int index))
                {
                    var entry = _Files[index];
                    if (entry.HasValue)
                    {
                        var perm = entry.Value.Permission;
                        if ((perm & (uint)Permission.Read) == 0)
                        {
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine($"{path} permission denied");
                            Console.ForegroundColor = ConsoleColor.White;
                        }
                        else
                        {
                            Console.WriteLine($"{path} read");
                        }
                    }
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"{path} not found");
                    Console.ForegroundColor = ConsoleColor.White;
                }
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Empty");
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
    }

    public void WriteFile(string user, string path)
    {
        if (!_OpenedFiles.Any(x => x.Key == user && x.Value == path))
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"{path} not opened");
            Console.ForegroundColor = ConsoleColor.White;
        }
        else
        {
            if (_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
            {
                if (userfs.TryGetValue(path, out int index))
                {
                    var entry = _Files[index];
                    if (entry.HasValue)
                    {
                        var perm = entry.Value.Permission;
                        if ((perm & (uint)Permission.Write) == 0)
                        {
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine($"{path} permission denied");
                            Console.ForegroundColor = ConsoleColor.White;
                        }
                        else
                        {
                            Console.WriteLine($"{path} wrote");
                        }
                    }
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"{path} not found");
                    Console.ForegroundColor = ConsoleColor.White;
                }
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Empty");
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
    }

    public void ListFiles(string user)
    {
        Console.WriteLine("File Permission");
        if (_UserFileDirectory.TryGetValue(user, out Dictionary<string, int>? userfs))
        {
            if (userfs != null)
            {
                foreach (var i in userfs)
                {
                    var entry = _Files[i.Value];
                    if (entry.HasValue)
                    {
                        Console.WriteLine($"{i.Key} {entry.Value.Permission}");
                    }
                }
            }
        }
    }

    public void Dump()
    {
        var option = new JsonSerializerOptions
        {
            Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping
        };
        Console.WriteLine(JsonSerializer.Serialize(_Files, option));
        Console.WriteLine(JsonSerializer.Serialize(_UserFileDirectory, option));
        Console.WriteLine(JsonSerializer.Serialize(_OpenedFiles, option));
    }
}
