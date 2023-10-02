#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("t")]
public class Teacher
{
    [Required]
    [Column("gh")]
    public int Id { get; set; }

    [Required]
    [Column("xm")]
    public string Name { get; set; }

    [Required]
    [Column("xb")]
    public string Gender { get; set; }
    
    [Column("csrq")]
    public string DateOfBirth { get; set; }

    [Required]
    [Column("xl")]
    public string Degree { get; set; }

    [Required]
    [Column("jbgz")]
    public double Salary { get; set; }

    [Required]
    [Column("yxh")]
    public int InstituteId { get; set; }
}
