#pragma warning disable CS8618

using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("e")]
[PrimaryKey(nameof(StudentId), nameof(Semester), nameof(CourseId))]
public class SelectedCourse
{
    [Column("xh")]
    public int StudentId { get; set; }

    [Column("xq")]
    public string Semester { get; set; }

    [Column("kh")]
    public string CourseId { get; set; }

    [Column("gh")]
    public int TeacherId { get; set; }

    [Column("pscj")]
    public double Grade { get; set; }

    [Column("kscj")]
    public double Test { get; set; }

    [Column("zpcj")]
    public double TotalGrade { get; set; }
}
