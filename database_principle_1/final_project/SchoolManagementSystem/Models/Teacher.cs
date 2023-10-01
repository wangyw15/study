#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("t")]
public class Teacher
{
    [Column("gh")]
    public int Id { get; set; }

    [Column("xm")]
    public string Name { get; set; }

    [Column("xb")]
    public string Gender { get; set; }

    [Column("csrq")]
    public string DateOfBirth { get; set; }

    [Column("xl")]
    public string Degree { get; set; }

    [Column("jbgz")]
    public double Salary { get; set; }

    [Column("yxh")]
    public int InstituteId { get; set; }
}
