using Microsoft.AspNetCore.Components.Authorization;
using Microsoft.AspNetCore.Components.Server.ProtectedBrowserStorage;
using System.Security.Claims;

namespace SchoolManagementSystem.Services;

public class Role
{
    public const string Administrator = "ADMINISTRATOR";
    public const string Teacher = "TEACHER";
    public const string Student = "STUDENT";
}

public struct User
{
    public int Id;
    public string Role;
}

public struct LoginResult
{
    public string Token;
    public User User;
}

public class TokenService
{
    private Dictionary<string, User> _tokens;

    public TokenService()
    {
        _tokens = new Dictionary<string, User>();
    }

    public bool Validate(string token) => _tokens.ContainsKey(token);

    public void Add(string token, User user) => _tokens.Add(token, user);

    public void Remove(string token) => _tokens.Remove(token);

    public User this[string token]
    {
        get => _tokens[token];
    }
}

public class SchoolStateProvider : AuthenticationStateProvider
{
    private readonly ProtectedLocalStorage _storage;
    private readonly SchoolContext _context;
    private readonly TokenService _tokens;

    public SchoolStateProvider(ProtectedLocalStorage storage, SchoolContext context, TokenService tokens)
    {
        this._storage = storage;
        _tokens = tokens;
        _context = context;
    }

    public User CurrentUser
    {
        get;
        private set;
    }
    
    public override async Task<AuthenticationState> GetAuthenticationStateAsync()
    {
        try
        {
            var result = await _storage.GetAsync<string>("token");
            var token = result.Success ? result.Value : null;
            if (_tokens.Validate(token ?? ""))
            {
                CurrentUser = _tokens[token];
            }
            return new AuthenticationState(CreateIdentity(token));
        }
        catch
        {
            return new AuthenticationState(new ClaimsPrincipal());
        }
    }

    private ClaimsPrincipal CreateIdentity(string? token)
    {
        if (!string.IsNullOrEmpty(token))
        {
            if (_tokens.Validate(token))
            {
                var user = _tokens[token];
                var identity = new ClaimsIdentity();
                identity.AddClaim(new Claim(ClaimTypes.Name, user.Id.ToString()));
                identity.AddClaim(new Claim(ClaimTypes.Role, user.Role));
                return new ClaimsPrincipal(identity);
            }
        }
        return new ClaimsPrincipal();
    }

    public async Task<bool> Login(string username, string password)
    {
        var token = Guid.NewGuid().ToString("N");
        var user = new User();
        var result = new LoginResult();
        var success = false;
        if (username == "admin")
        {
            user.Id = 0;
            user.Role = Role.Administrator;
            result.Token = token;
            result.User = user;
            success = true;
        }
        else
        {
            var teacherResult = from x in _context.Teachers where x.Id.ToString() == username select x;
            if (teacherResult != null && teacherResult.Any())
            {
                var teacher = teacherResult.First();
                user.Id = teacher.Id;
                user.Role = Role.Teacher;
                result.Token = token;
                result.User = user;
                success = true;
            }
            else
            {
                var studentResult = from x in _context.Students where x.Id.ToString() == username select x;
                if (studentResult != null && studentResult.Any())
                {
                    var student = studentResult.First();
                    user.Id = student.Id;
                    user.Role = Role.Student;
                    result.Token = token;
                    result.User = user;
                    success = true;
                }
            }
        }

        if (success)
        {
            await _storage.SetAsync("token", token);
            _tokens.Add(token, user);
            NotifyAuthenticationStateChanged(Task.FromResult(new AuthenticationState(CreateIdentity(token))));
            return true;
        }
        return false;
    }
    
    public async Task<bool> Logout(string token)
    {
        if (!string.IsNullOrEmpty(token))
        {
            if (_tokens.Validate(token))
            {
                await _storage.DeleteAsync("token");
                _tokens.Remove(token);
                NotifyAuthenticationStateChanged(Task.FromResult(new AuthenticationState(CreateIdentity(token))));
                return true;
            }
        }
        return false;
    }
}
