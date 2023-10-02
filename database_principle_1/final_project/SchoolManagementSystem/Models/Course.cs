using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("c")]
public class Course
{
    [Required]
    [Column("kh")]
    public string Id { get; set; } = "";

    [Required]
    [Column("km")]
    public string Name { get; set; } = "";

    [Required]
    [Column("xf")]
    public double Credit { get; set; }

    [Required]
    [Column("xs")]
    public double Hour { get; set; }

    [Required]
    [Column("yxh")]
    public int InstituteId { get; set; }
}
