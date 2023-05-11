namespace Calculator;

partial class MainForm
{
	/// <summary>
	///  Required designer variable.
	/// </summary>
	private System.ComponentModel.IContainer components = null;

	/// <summary>
	///  Clean up any resources being used.
	/// </summary>
	/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
	protected override void Dispose(bool disposing)
	{
		if (disposing && (components != null))
		{
			components.Dispose();
		}
		base.Dispose(disposing);
	}

	#region Windows Form Designer generated code

	/// <summary>
	///  Required method for Designer support - do not modify
	///  the contents of this method with the code editor.
	/// </summary>
	private void InitializeComponent()
	{
		tabControl = new TabControl();
		calculatorTab = new TabPage();
		calculateButton = new Button();
		label1 = new Label();
		formulaTextBox = new TextBox();
		exerciseTab = new TabPage();
		nextButton = new Button();
		exerciseTextBox = new TextBox();
		answerTextBox = new TextBox();
		label2 = new Label();
		label3 = new Label();
		tabControl.SuspendLayout();
		calculatorTab.SuspendLayout();
		exerciseTab.SuspendLayout();
		SuspendLayout();
		// 
		// tabControl
		// 
		tabControl.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		tabControl.Controls.Add(calculatorTab);
		tabControl.Controls.Add(exerciseTab);
		tabControl.Location = new Point(12, 12);
		tabControl.Name = "tabControl";
		tabControl.SelectedIndex = 0;
		tabControl.Size = new Size(431, 573);
		tabControl.TabIndex = 0;
		// 
		// calculatorTab
		// 
		calculatorTab.Controls.Add(calculateButton);
		calculatorTab.Controls.Add(label1);
		calculatorTab.Controls.Add(formulaTextBox);
		calculatorTab.Location = new Point(4, 33);
		calculatorTab.Name = "calculatorTab";
		calculatorTab.Padding = new Padding(3);
		calculatorTab.Size = new Size(423, 536);
		calculatorTab.TabIndex = 0;
		calculatorTab.Text = "计算器";
		calculatorTab.UseVisualStyleBackColor = true;
		// 
		// calculateButton
		// 
		calculateButton.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		calculateButton.Location = new Point(6, 66);
		calculateButton.Name = "calculateButton";
		calculateButton.Size = new Size(411, 34);
		calculateButton.TabIndex = 2;
		calculateButton.Text = "计算";
		calculateButton.UseVisualStyleBackColor = true;
		calculateButton.MouseClick += calculateButton_MouseClick;
		// 
		// label1
		// 
		label1.AutoSize = true;
		label1.Location = new Point(6, 3);
		label1.Name = "label1";
		label1.Size = new Size(46, 24);
		label1.TabIndex = 1;
		label1.Text = "算式";
		// 
		// formulaTextBox
		// 
		formulaTextBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		formulaTextBox.Location = new Point(6, 30);
		formulaTextBox.Name = "formulaTextBox";
		formulaTextBox.Size = new Size(411, 30);
		formulaTextBox.TabIndex = 0;
		// 
		// exerciseTab
		// 
		exerciseTab.Controls.Add(label3);
		exerciseTab.Controls.Add(label2);
		exerciseTab.Controls.Add(answerTextBox);
		exerciseTab.Controls.Add(nextButton);
		exerciseTab.Controls.Add(exerciseTextBox);
		exerciseTab.Location = new Point(4, 33);
		exerciseTab.Name = "exerciseTab";
		exerciseTab.Padding = new Padding(3);
		exerciseTab.Size = new Size(423, 536);
		exerciseTab.TabIndex = 1;
		exerciseTab.Text = "小学生算术练习器";
		exerciseTab.UseVisualStyleBackColor = true;
		// 
		// nextButton
		// 
		nextButton.Location = new Point(3, 126);
		nextButton.Name = "nextButton";
		nextButton.Size = new Size(411, 34);
		nextButton.TabIndex = 1;
		nextButton.Text = "下一题";
		nextButton.UseVisualStyleBackColor = true;
		nextButton.MouseClick += nextButton_MouseClick;
		// 
		// exerciseTextBox
		// 
		exerciseTextBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		exerciseTextBox.Location = new Point(6, 30);
		exerciseTextBox.Name = "exerciseTextBox";
		exerciseTextBox.ReadOnly = true;
		exerciseTextBox.Size = new Size(411, 30);
		exerciseTextBox.TabIndex = 0;
		// 
		// answerTextBox
		// 
		answerTextBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		answerTextBox.Location = new Point(6, 90);
		answerTextBox.Name = "answerTextBox";
		answerTextBox.Size = new Size(411, 30);
		answerTextBox.TabIndex = 2;
		// 
		// label2
		// 
		label2.AutoSize = true;
		label2.Location = new Point(6, 3);
		label2.Name = "label2";
		label2.Size = new Size(46, 24);
		label2.TabIndex = 3;
		label2.Text = "题目";
		// 
		// label3
		// 
		label3.AutoSize = true;
		label3.Location = new Point(6, 63);
		label3.Name = "label3";
		label3.Size = new Size(46, 24);
		label3.TabIndex = 4;
		label3.Text = "答案";
		// 
		// MainForm
		// 
		AutoScaleDimensions = new SizeF(11F, 24F);
		AutoScaleMode = AutoScaleMode.Font;
		ClientSize = new Size(455, 597);
		Controls.Add(tabControl);
		Name = "MainForm";
		Text = "计算器";
		tabControl.ResumeLayout(false);
		calculatorTab.ResumeLayout(false);
		calculatorTab.PerformLayout();
		exerciseTab.ResumeLayout(false);
		exerciseTab.PerformLayout();
		ResumeLayout(false);
	}

	#endregion

	private TabControl tabControl;
	private TabPage calculatorTab;
	private Label label1;
	private TextBox formulaTextBox;
	private TabPage exerciseTab;
	private Button calculateButton;
	private Button nextButton;
	private TextBox exerciseTextBox;
	private Label label3;
	private Label label2;
	private TextBox answerTextBox;
}
