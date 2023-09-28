using System.ComponentModel.DataAnnotations.Schema;

[Table("t")]
public class Teacher
{
    [Column("gh")]
    public int ID { get; set; }

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
    public int InstituteID { get; set; }
}
