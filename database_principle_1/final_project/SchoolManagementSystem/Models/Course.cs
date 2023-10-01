#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("c")]
public class Course
{
    [Column("kh")]
    public string Id { get; set; }

    [Column("km")]
    public string Name { get; set; }

    [Column("xf")]
    public double Credit { get; set; }

    [Column("xs")]
    public double Hour { get; set; }

    [Column("yxh")]
    public int InstituteId { get; set; }
}
