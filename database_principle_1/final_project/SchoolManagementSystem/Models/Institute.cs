using System.ComponentModel.DataAnnotations.Schema;

[Table("d")]
public class Institute
{
    [Column("yxh")]
    public int ID { get; set; }

    [Column("mc")]
    public string Name { get; set; }

    [Column("dz")]
    public string Address { get; set; }

    [Column("lxdh")]
    public string Telephone { get; set; }
}
