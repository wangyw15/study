using Microsoft.EntityFrameworkCore;

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
}

