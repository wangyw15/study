using System.Data;

namespace Calculator;

public partial class MainForm : Form
{
	private DataTable _table;
	private Random _random;
	private string[] _operators = { "+", "-" };

	public MainForm()
	{
		InitializeComponent();
		_table = new DataTable();
		_random = new Random();
	}

	private void calculateButton_MouseClick(object sender, MouseEventArgs e)
	{
		if (e.Button == MouseButtons.Left)
		{
			// Calculate the result
			try
			{
				var result = _table.Compute(formulaTextBox.Text, "");
				formulaTextBox.Text += "=" + result.ToString();
			}
			catch (Exception ex)
			{
				formulaTextBox.Text = ex.Message;
			}
		}
	}

	private string GenerateFormula()
	{
		var a = _random.Next(0, 100);
		var o = _operators[_random.Next(0, _operators.Length)];
		var b = _random.Next(0, 100);
		if (o == "-")
		{
			b = _random.Next(0, a);
		}
		return a + o + b;
	}

	private void nextButton_MouseClick(object sender, MouseEventArgs e)
	{
		if (string.IsNullOrEmpty(exerciseTextBox.Text))
		{
			exerciseTextBox.Text = GenerateFormula();
		}
		else if (e.Button == MouseButtons.Left)
		{
			var result = _table.Compute(exerciseTextBox.Text, "").ToString();
			if (result == answerTextBox.Text)
			{
				MessageBox.Show("正确，你真棒！");
				exerciseTextBox.Text = GenerateFormula();
				answerTextBox.Text = "";
			}
			else
			{
				MessageBox.Show("错了，再试试吧！");
			}
		}
	}
}
