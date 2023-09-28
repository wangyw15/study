using System.ComponentModel.DataAnnotations.Schema;

[Table("c")]
public class Course
{
    [Column("kh")]
    public string ID { get; set; }

    [Column("km")]
    public string Name { get; set; }

    [Column("xf")]
    public double Credit { get; set; }

    [Column("xs")]
    public double Hour { get; set; }

    [Column("yxh")]
    public int InstituteID { get; set; }
}
