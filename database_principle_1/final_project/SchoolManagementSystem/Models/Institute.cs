#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("d")]
public class Institute
{
    [Required]
    [Column("yxh")]
    public int Id { get; set; }

    [Required]
    [Column("mc")]
    public string Name { get; set; }

    [Required]
    [Column("dz")]
    public string Address { get; set; }

    [Required]
    [Column("lxdh")]
    public string Telephone { get; set; }
}
