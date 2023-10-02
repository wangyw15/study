using Microsoft.EntityFrameworkCore;
using SchoolManagementSystem.Models;

namespace SchoolManagementSystem.Services;

public class SchoolContext : DbContext
{
    public DbSet<Student> Students { get; set; }
    public DbSet<Institute> Institutes { get; set; }
    public DbSet<Teacher> Teachers { get; set; }
    public DbSet<Course> Courses { get; set; }
    public DbSet<OpeningCourse> OpeningCourses { get; set; }
    public DbSet<SelectedCourse> SelectedCourses { get; set; }

    public string DbPath { get; }

    public SchoolContext()
    {
        DbPath = "school.db";
    }

    protected override void OnConfiguring(DbContextOptionsBuilder options)
        => options.UseSqlite($"Data Source={DbPath}");
    
    public string GetInstituteName(int id)
    {
        var result = from x in Institutes where x.Id == id select x;
        if (result.Any())
        {
            return result.First().Name;
        }
        return "未知学院";
    }
}

