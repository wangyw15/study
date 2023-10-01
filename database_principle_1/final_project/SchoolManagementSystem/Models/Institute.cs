#pragma warning disable CS8618

using System.ComponentModel.DataAnnotations.Schema;

namespace SchoolManagementSystem.Models;

[Table("d")]
public class Institute
{
    [Column("yxh")]
    public int Id { get; set; }

    [Column("mc")]
    public string Name { get; set; }

    [Column("dz")]
    public string Address { get; set; }

    [Column("lxdh")]
    public string Telephone { get; set; }
}
