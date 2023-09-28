using System.ComponentModel.DataAnnotations.Schema;

[Table("e")]
public class SelectedCourse
{
    [Column("xh")]
    public int StudentID { get; set; }

    [Column("xq")]
    public string Semester { get; set; }

    [Column("kh")]
    public string CourseID { get; set; }

    [Column("gh")]
    public int TeacherID { get; set; }

    [Column("pscj")]
    public double Grade { get; set; }

    [Column("kscj")]
    public double Test { get; set; }

    [Column("zpcj")]
    public double TotalGrade { get; set; }
}
