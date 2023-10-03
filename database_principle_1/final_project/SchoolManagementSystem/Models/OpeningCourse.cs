#pragma warning disable CS8618

using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("o")]
[PrimaryKey(nameof(Semester), nameof(CourseId), nameof(TeacherId))]
public class OpeningCourse
{
    [Required]
    [Column("xq")]
    public string Semester { get; set; }

    [Required]
    [Column("kh")]
    public string CourseId { get; set; }

    [Required]
    [Column("gh")]
    public int TeacherId { get; set; }

    [Required]
    [Column("sksj")]
    public string Time { get; set; }
}
