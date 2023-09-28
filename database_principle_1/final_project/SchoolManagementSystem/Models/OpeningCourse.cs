using System.ComponentModel.DataAnnotations.Schema;

[Table("o")]
public class OpeningCourse
{
    [Column("xq")]
    public string Semester { get; set; }

    [Column("kh")]
    public string CourseID { get; set; }

    [Column("gh")]
    public int TeacherID { get; set; }

    [Column("sksj")]
    public string Time { get; set; }
}
