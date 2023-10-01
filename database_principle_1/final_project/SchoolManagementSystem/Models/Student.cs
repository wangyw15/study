#pragma warning disable CS8618

using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("s")]
public class Student
{
    [Column("xh")]
    public int Id { get; set; }

    [Column("xm")]
    public string Name { get; set; }

    [Column("xb")]
    public string Gender { get; set; }

    [Column("csrq")]
    public string DateOfBirth { get; set; }

    [Column("jg")]
    public string BirthPlace { get; set; }

    [Column("sjhm")]
    public string Phone { get; set; }

    [Column("yxh")]
    public int InstituteId { get; set; }
}
