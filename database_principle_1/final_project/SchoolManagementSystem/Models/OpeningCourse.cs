#pragma warning disable CS8618

using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("o")]
[PrimaryKey(nameof(Semester), nameof(CourseId), nameof(TeacherId))]
public class OpeningCourse
{
    [Column("xq")]
    public string Semester { get; set; }

    [Column("kh")]
    public string CourseId { get; set; }

    [Column("gh")]
    public int TeacherId { get; set; }

    [Column("sksj")]
    public string Time { get; set; }
}
