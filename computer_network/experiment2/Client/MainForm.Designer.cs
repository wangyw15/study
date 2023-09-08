namespace Client;

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
		labelPassword = new Label();
		labelUserName = new Label();
		textBoxUsername = new TextBox();
		textBoxPassword = new TextBox();
		groupBoxServer = new GroupBox();
		buttonDisconnect = new Button();
		buttonConnect = new Button();
		label1 = new Label();
		textBoxHost = new TextBox();
		label2 = new Label();
		textBoxPort = new TextBox();
		textBoxLog = new TextBox();
		buttonSend = new Button();
		textBoxMessage = new TextBox();
		groupBoxUser.SuspendLayout();
		groupBoxServer.SuspendLayout();
		SuspendLayout();
		// 
		// groupBoxUser
		// 
		groupBoxUser.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		groupBoxUser.Controls.Add(labelPassword);
		groupBoxUser.Controls.Add(labelUserName);
		groupBoxUser.Controls.Add(textBoxUsername);
		groupBoxUser.Controls.Add(textBoxPassword);
		groupBoxUser.Location = new Point(12, 205);
		groupBoxUser.Name = "groupBoxUser";
		groupBoxUser.Size = new Size(622, 109);
		groupBoxUser.TabIndex = 0;
		groupBoxUser.TabStop = false;
		groupBoxUser.Text = "登录";
		// 
		// labelPassword
		// 
		labelPassword.AutoSize = true;
		labelPassword.Location = new Point(23, 68);
		labelPassword.Name = "labelPassword";
		labelPassword.Size = new Size(46, 24);
		labelPassword.TabIndex = 4;
		labelPassword.Text = "密码";
		// 
		// labelUserName
		// 
		labelUserName.AutoSize = true;
		labelUserName.Location = new Point(6, 32);
		labelUserName.Name = "labelUserName";
		labelUserName.Size = new Size(64, 24);
		labelUserName.TabIndex = 3;
		labelUserName.Text = "用户名";
		// 
		// textBoxUsername
		// 
		textBoxUsername.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxUsername.Location = new Point(76, 29);
		textBoxUsername.Name = "textBoxUsername";
		textBoxUsername.Size = new Size(540, 30);
		textBoxUsername.TabIndex = 1;
		// 
		// textBoxPassword
		// 
		textBoxPassword.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxPassword.Location = new Point(75, 65);
		textBoxPassword.Name = "textBoxPassword";
		textBoxPassword.PasswordChar = '*';
		textBoxPassword.Size = new Size(541, 30);
		textBoxPassword.TabIndex = 2;
		// 
		// groupBoxServer
		// 
		groupBoxServer.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		groupBoxServer.Controls.Add(buttonDisconnect);
		groupBoxServer.Controls.Add(buttonConnect);
		groupBoxServer.Controls.Add(label1);
		groupBoxServer.Controls.Add(textBoxHost);
		groupBoxServer.Controls.Add(label2);
		groupBoxServer.Controls.Add(textBoxPort);
		groupBoxServer.Location = new Point(12, 12);
		groupBoxServer.Name = "groupBoxServer";
		groupBoxServer.Size = new Size(622, 187);
		groupBoxServer.TabIndex = 5;
		groupBoxServer.TabStop = false;
		groupBoxServer.Text = "服务器";
		// 
		// buttonDisconnect
		// 
		buttonDisconnect.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		buttonDisconnect.Enabled = false;
		buttonDisconnect.Location = new Point(6, 141);
		buttonDisconnect.Name = "buttonDisconnect";
		buttonDisconnect.Size = new Size(610, 34);
		buttonDisconnect.TabIndex = 10;
		buttonDisconnect.Text = "关闭连接";
		buttonDisconnect.UseVisualStyleBackColor = true;
		buttonDisconnect.Click += buttonDisconnect_Click;
		// 
		// buttonConnect
		// 
		buttonConnect.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		buttonConnect.Location = new Point(6, 101);
		buttonConnect.Name = "buttonConnect";
		buttonConnect.Size = new Size(610, 34);
		buttonConnect.TabIndex = 9;
		buttonConnect.Text = "连接";
		buttonConnect.UseVisualStyleBackColor = true;
		buttonConnect.Click += buttonConnect_Click;
		// 
		// label1
		// 
		label1.AutoSize = true;
		label1.Location = new Point(23, 68);
		label1.Name = "label1";
		label1.Size = new Size(46, 24);
		label1.TabIndex = 8;
		label1.Text = "端口";
		// 
		// textBoxHost
		// 
		textBoxHost.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxHost.Location = new Point(76, 29);
		textBoxHost.Name = "textBoxHost";
		textBoxHost.Size = new Size(540, 30);
		textBoxHost.TabIndex = 5;
		// 
		// label2
		// 
		label2.AutoSize = true;
		label2.Location = new Point(6, 32);
		label2.Name = "label2";
		label2.Size = new Size(64, 24);
		label2.TabIndex = 7;
		label2.Text = "主机名";
		// 
		// textBoxPort
		// 
		textBoxPort.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		textBoxPort.Location = new Point(75, 65);
		textBoxPort.Name = "textBoxPort";
		textBoxPort.Size = new Size(541, 30);
		textBoxPort.TabIndex = 6;
		// 
		// textBoxLog
		// 
		textBoxLog.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		textBoxLog.Location = new Point(12, 320);
		textBoxLog.Multiline = true;
		textBoxLog.Name = "textBoxLog";
		textBoxLog.ReadOnly = true;
		textBoxLog.ScrollBars = ScrollBars.Vertical;
		textBoxLog.Size = new Size(622, 284);
		textBoxLog.TabIndex = 5;
		textBoxLog.Text = "日志";
		// 
		// buttonSend
		// 
		buttonSend.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
		buttonSend.Enabled = false;
		buttonSend.Location = new Point(522, 610);
		buttonSend.Name = "buttonSend";
		buttonSend.Size = new Size(112, 30);
		buttonSend.TabIndex = 6;
		buttonSend.Text = "发送";
		buttonSend.UseVisualStyleBackColor = true;
		buttonSend.Click += buttonSend_Click;
		// 
		// textBoxMessage
		// 
		textBoxMessage.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
		textBoxMessage.Location = new Point(12, 610);
		textBoxMessage.Name = "textBoxMessage";
		textBoxMessage.Size = new Size(504, 30);
		textBoxMessage.TabIndex = 7;
		// 
		// MainForm
		// 
		AutoScaleDimensions = new SizeF(11F, 24F);
		AutoScaleMode = AutoScaleMode.Font;
		ClientSize = new Size(646, 652);
		Controls.Add(textBoxMessage);
		Controls.Add(buttonSend);
		Controls.Add(textBoxLog);
		Controls.Add(groupBoxServer);
		Controls.Add(groupBoxUser);
		Name = "MainForm";
		Text = "客户端";
		FormClosing += MainForm_FormClosing;
		groupBoxUser.ResumeLayout(false);
		groupBoxUser.PerformLayout();
		groupBoxServer.ResumeLayout(false);
		groupBoxServer.PerformLayout();
		ResumeLayout(false);
		PerformLayout();
	}

	#endregion

	private GroupBox groupBoxUser;
	private Label labelPassword;
	private Label labelUserName;
	private TextBox textBoxUsername;
	private TextBox textBoxPassword;
	private GroupBox groupBoxServer;
	private Label label1;
	private TextBox textBoxHost;
	private Label label2;
	private TextBox textBoxPort;
	private TextBox textBoxLog;
	private Button buttonSend;
	private TextBox textBoxMessage;
	private Button buttonDisconnect;
	private Button buttonConnect;
}
