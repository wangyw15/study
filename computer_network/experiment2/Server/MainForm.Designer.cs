namespace Server;

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
		groupBoxUser = new GroupBox();
		buttonDeleteUser = new Button();
		listBoxUsers = new ListBox();
		textBoxPasswordCheck = new TextBox();
		label1 = new Label();
		buttonAddUser = new Button();
		labelPassword = new Label();
		labelUserName = new Label();
		textBoxUserName = new TextBox();
		textBoxPassword = new TextBox();
		groupBoxConsole = new GroupBox();
		buttonMode = new Button();
		buttonListenToggle = new Button();
		labelPort = new Label();
		numericUpDownPort = new NumericUpDown();
		buttonCloseConnection = new Button();
		listBoxConnectedUsers = new ListBox();
		textBoxLog = new TextBox();
		groupBoxUser.SuspendLayout();
		groupBoxConsole.SuspendLayout();
		((System.ComponentModel.ISupportInitialize)numericUpDownPort).BeginInit();
		SuspendLayout();
		// 
		// groupBoxUser
		// 
		groupBoxUser.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
		groupBoxUser.Controls.Add(buttonDeleteUser);
		groupBoxUser.Controls.Add(listBoxUsers);
		groupBoxUser.Controls.Add(textBoxPasswordCheck);
		groupBoxUser.Controls.Add(label1);
		groupBoxUser.Controls.Add(buttonAddUser);
		groupBoxUser.Controls.Add(labelPassword);
		groupBoxUser.Controls.Add(labelUserName);
		groupBoxUser.Controls.Add(textBoxUserName);
		groupBoxUser.Controls.Add(textBoxPassword);
		groupBoxUser.Location = new Point(12, 12);
		groupBoxUser.Name = "groupBoxUser";
		groupBoxUser.Size = new Size(315, 619);
		groupBoxUser.TabIndex = 0;
		groupBoxUser.TabStop = false;
		groupBoxUser.Text = "用户管理";
		// 
		// buttonDeleteUser
		// 
		buttonDeleteUser.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		buttonDeleteUser.Location = new Point(6, 579);
		buttonDeleteUser.Name = "buttonDeleteUser";
		buttonDeleteUser.Size = new Size(303, 34);
		buttonDeleteUser.TabIndex = 8;
		buttonDeleteUser.Text = "删除用户";
		buttonDeleteUser.UseVisualStyleBackColor = true;
		buttonDeleteUser.Click += buttonDeleteUser_Click;
		// 
		// listBoxUsers
		// 
		listBoxUsers.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		listBoxUsers.FormattingEnabled = true;
		listBoxUsers.ItemHeight = 24;
		listBoxUsers.Location = new Point(6, 178);
		listBoxUsers.Name = "listBoxUsers";
		listBoxUsers.Size = new Size(303, 388);
		listBoxUsers.TabIndex = 1;
		// 
		// textBoxPasswordCheck
		// 
		textBoxPasswordCheck.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxPasswordCheck.Location = new Point(94, 101);
		textBoxPasswordCheck.Name = "textBoxPasswordCheck";
		textBoxPasswordCheck.PasswordChar = '*';
		textBoxPasswordCheck.Size = new Size(215, 30);
		textBoxPasswordCheck.TabIndex = 7;
		// 
		// label1
		// 
		label1.AutoSize = true;
		label1.Location = new Point(6, 104);
		label1.Name = "label1";
		label1.Size = new Size(82, 24);
		label1.TabIndex = 6;
		label1.Text = "重复密码";
		// 
		// buttonAddUser
		// 
		buttonAddUser.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		buttonAddUser.Location = new Point(6, 138);
		buttonAddUser.Name = "buttonAddUser";
		buttonAddUser.Size = new Size(303, 34);
		buttonAddUser.TabIndex = 5;
		buttonAddUser.Text = "添加用户";
		buttonAddUser.UseVisualStyleBackColor = true;
		buttonAddUser.Click += buttonAddUser_Click;
		// 
		// labelPassword
		// 
		labelPassword.AutoSize = true;
		labelPassword.Location = new Point(42, 68);
		labelPassword.Name = "labelPassword";
		labelPassword.Size = new Size(46, 24);
		labelPassword.TabIndex = 4;
		labelPassword.Text = "密码";
		// 
		// labelUserName
		// 
		labelUserName.AutoSize = true;
		labelUserName.Location = new Point(24, 32);
		labelUserName.Name = "labelUserName";
		labelUserName.Size = new Size(64, 24);
		labelUserName.TabIndex = 3;
		labelUserName.Text = "用户名";
		// 
		// textBoxUserName
		// 
		textBoxUserName.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxUserName.Location = new Point(94, 29);
		textBoxUserName.Name = "textBoxUserName";
		textBoxUserName.Size = new Size(215, 30);
		textBoxUserName.TabIndex = 1;
		// 
		// textBoxPassword
		// 
		textBoxPassword.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxPassword.Location = new Point(94, 65);
		textBoxPassword.Name = "textBoxPassword";
		textBoxPassword.PasswordChar = '*';
		textBoxPassword.Size = new Size(215, 30);
		textBoxPassword.TabIndex = 2;
		// 
		// groupBoxConsole
		// 
		groupBoxConsole.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		groupBoxConsole.Controls.Add(buttonMode);
		groupBoxConsole.Controls.Add(buttonListenToggle);
		groupBoxConsole.Controls.Add(labelPort);
		groupBoxConsole.Controls.Add(numericUpDownPort);
		groupBoxConsole.Controls.Add(buttonCloseConnection);
		groupBoxConsole.Controls.Add(listBoxConnectedUsers);
		groupBoxConsole.Controls.Add(textBoxLog);
		groupBoxConsole.Location = new Point(333, 12);
		groupBoxConsole.Name = "groupBoxConsole";
		groupBoxConsole.Size = new Size(1066, 619);
		groupBoxConsole.TabIndex = 1;
		groupBoxConsole.TabStop = false;
		groupBoxConsole.Text = "控制台";
		// 
		// buttonMode
		// 
		buttonMode.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		buttonMode.Location = new Point(6, 29);
		buttonMode.Name = "buttonMode";
		buttonMode.Size = new Size(716, 34);
		buttonMode.TabIndex = 6;
		buttonMode.Text = "TCP";
		buttonMode.UseVisualStyleBackColor = true;
		buttonMode.Click += buttonMode_Click;
		// 
		// buttonListenToggle
		// 
		buttonListenToggle.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		buttonListenToggle.Location = new Point(948, 29);
		buttonListenToggle.Name = "buttonListenToggle";
		buttonListenToggle.Size = new Size(112, 30);
		buttonListenToggle.TabIndex = 5;
		buttonListenToggle.Text = "开始";
		buttonListenToggle.UseVisualStyleBackColor = true;
		buttonListenToggle.Click += buttonListenToggle_Click;
		// 
		// labelPort
		// 
		labelPort.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		labelPort.AutoSize = true;
		labelPort.Location = new Point(728, 32);
		labelPort.Name = "labelPort";
		labelPort.Size = new Size(46, 24);
		labelPort.TabIndex = 4;
		labelPort.Text = "端口";
		// 
		// numericUpDownPort
		// 
		numericUpDownPort.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		numericUpDownPort.Location = new Point(780, 29);
		numericUpDownPort.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
		numericUpDownPort.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
		numericUpDownPort.Name = "numericUpDownPort";
		numericUpDownPort.Size = new Size(162, 30);
		numericUpDownPort.TabIndex = 3;
		numericUpDownPort.Value = new decimal(new int[] { 11451, 0, 0, 0 });
		// 
		// buttonCloseConnection
		// 
		buttonCloseConnection.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
		buttonCloseConnection.Location = new Point(728, 579);
		buttonCloseConnection.Name = "buttonCloseConnection";
		buttonCloseConnection.Size = new Size(332, 34);
		buttonCloseConnection.TabIndex = 2;
		buttonCloseConnection.Text = "关闭连接";
		buttonCloseConnection.UseVisualStyleBackColor = true;
		buttonCloseConnection.Click += buttonCloseConnection_Click;
		// 
		// listBoxConnectedUsers
		// 
		listBoxConnectedUsers.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
		listBoxConnectedUsers.FormattingEnabled = true;
		listBoxConnectedUsers.ItemHeight = 24;
		listBoxConnectedUsers.Location = new Point(728, 65);
		listBoxConnectedUsers.Name = "listBoxConnectedUsers";
		listBoxConnectedUsers.Size = new Size(332, 508);
		listBoxConnectedUsers.TabIndex = 1;
		// 
		// textBoxLog
		// 
		textBoxLog.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		textBoxLog.Location = new Point(6, 69);
		textBoxLog.Multiline = true;
		textBoxLog.Name = "textBoxLog";
		textBoxLog.ReadOnly = true;
		textBoxLog.ScrollBars = ScrollBars.Vertical;
		textBoxLog.Size = new Size(716, 544);
		textBoxLog.TabIndex = 0;
		textBoxLog.Text = "日志";
		// 
		// MainForm
		// 
		AutoScaleDimensions = new SizeF(11F, 24F);
		AutoScaleMode = AutoScaleMode.Font;
		ClientSize = new Size(1411, 643);
		Controls.Add(groupBoxConsole);
		Controls.Add(groupBoxUser);
		Name = "MainForm";
		Text = "服务端";
		groupBoxUser.ResumeLayout(false);
		groupBoxUser.PerformLayout();
		groupBoxConsole.ResumeLayout(false);
		groupBoxConsole.PerformLayout();
		((System.ComponentModel.ISupportInitialize)numericUpDownPort).EndInit();
		ResumeLayout(false);
	}

	#endregion

	private GroupBox groupBoxUser;
	private Button buttonAddUser;
	private Label labelPassword;
	private Label labelUserName;
	private TextBox textBoxUserName;
	private TextBox textBoxPassword;
	private Button buttonDeleteUser;
	private ListBox listBoxUsers;
	private TextBox textBoxPasswordCheck;
	private Label label1;
	private GroupBox groupBoxConsole;
	private TextBox textBoxLog;
	private Button buttonCloseConnection;
	private ListBox listBoxConnectedUsers;
	private Label labelPort;
	private NumericUpDown numericUpDownPort;
	private Button buttonListenToggle;
	private Button buttonMode;
}
