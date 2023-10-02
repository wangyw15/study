#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("s")]
public class Student
{
    [Required]
    [Column("xh")]
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
    [Column("jg")]
    public string BirthPlace { get; set; }

    [Required]
    [Column("sjhm")]
    public string Phone { get; set; }

    [Required]
    [Column("yxh")]
    public int InstituteId { get; set; }
}
