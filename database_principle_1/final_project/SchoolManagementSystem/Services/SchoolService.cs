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

    public string GetCourseName(string id)
    {
        var result = from x in Courses where x.Id == id select x;
        if (result.Any())
        {
            return result.First().Name;
        }
        return "";
    }

    public string GetTeacherName(int id)
    {
        var result = from x in Teachers where x.Id == id select x;
        if (result.Any())
        {
            return result.First().Name;
        }
        return "";
    }

    public string GetCourseTime(string id, string semester, int teacherId)
    {
        var result = from x in OpeningCourses 
                     where x.CourseId == id && x.Semester == semester && x.TeacherId == teacherId 
                     select x;
        if (result.Any())
        {
            return result.First().Time;
        }
        return "";
    }
}

