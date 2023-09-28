using System.ComponentModel.DataAnnotations.Schema;

[Table("s")]
public class Student
{
    [Column("xh")]
    public int ID { get; set; }

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
    public int InstituteID { get; set; }
}
