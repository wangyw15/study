using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Client;

public partial class MainForm : Form
{
	public MainForm()
	{
		InitializeComponent();
	}

	Socket? _socket;

	private void buttonSend_Click(object sender, EventArgs e)
	{
		if (_socket == null || !_socket.Connected)
		{
			_log("未连接到服务器");
		}
		if (string.IsNullOrEmpty(textBoxUsername.Text) || string.IsNullOrWhiteSpace(textBoxUsername.Text))
		{
			_log("用户名不能为空");
			return;
		}
		if (string.IsNullOrEmpty(textBoxPassword.Text) || string.IsNullOrWhiteSpace(textBoxPassword.Text))
		{
			_log("密码不能为空");
			return;
		}
		if (string.IsNullOrEmpty(textBoxMessage.Text) || string.IsNullOrWhiteSpace(textBoxMessage.Text))
		{
			_log("消息不能为空");
			return;
		}
		int sentBytes = 0;
		var data = Encoding.UTF8.GetBytes(JsonSerializer.Serialize(new
		{
			username = textBoxUsername.Text,
			password = textBoxPassword.Text,
			message = textBoxMessage.Text
		}));
		while (sentBytes < data.Length)
		{
			sentBytes += _socket.Send(data, sentBytes, data.Length - sentBytes, SocketFlags.None);
		}
		// response
		byte[] bytesBuffer = new byte[256];
		try
		{
			int bytesReceived = _socket.Receive(bytesBuffer);
			if (bytesReceived != 0)
			{
				var respdata = JsonSerializer.Deserialize<Dictionary<string, bool>>(Encoding.UTF8.GetString(bytesBuffer, 0, bytesReceived));
				_log(respdata["success"] ? "发送成功" : "发送失败");
			}
		}
		catch
		{
			_log("发送失败");
		}
	}

	private void _log(string content, bool invoke = true)
	{
		if (invoke)
		{
			textBoxLog.Invoke(() =>
			{
				textBoxLog.Text += Environment.NewLine + DateTime.Now.ToLongTimeString() + ": " + content;
			});
		}
		else
		{
			textBoxLog.Text += Environment.NewLine + DateTime.Now.ToLongTimeString() + ": " + content;
		}
	}

	private void buttonConnect_Click(object sender, EventArgs e)
	{
		if (_socket != null && _socket.Connected)
		{
			_log("已经连接过了");
			return;
		}
		if (string.IsNullOrEmpty(textBoxHost.Text) || string.IsNullOrWhiteSpace(textBoxHost.Text))
		{
			_log("主机名不能为空");
			return;
		}
		if (string.IsNullOrEmpty(textBoxPort.Text) || string.IsNullOrWhiteSpace(textBoxPort.Text))
		{
			_log("端口号不能为空");
			return;
		}
		// connect
		if (_socket != null)
		{
			_socket.Close();
		}
		_socket = new(SocketType.Stream, ProtocolType.Tcp);
		_socket.Connect(new IPEndPoint(IPAddress.Parse(textBoxHost.Text), int.Parse(textBoxPort.Text)));
		if (_socket.Connected)
		{
			_log($"{textBoxHost.Text}:{textBoxPort.Text} 连接成功");
			buttonConnect.Enabled = false;
			buttonDisconnect.Enabled = true;
			buttonSend.Enabled = true;
			textBoxHost.ReadOnly = true;
			textBoxPort.ReadOnly = true;
		}
		else
		{
			_log($"{textBoxHost.Text}:{textBoxPort.Text} 连接失败");
		}
	}

	private void buttonDisconnect_Click(object sender, EventArgs e)
	{
		if (_socket != null && _socket.Connected)
		{
			_socket.Close();
			if (!_socket.Connected)
			{
				_log($"{textBoxHost.Text}:{textBoxPort.Text} 已关闭连接");
				buttonConnect.Enabled = true;
				buttonDisconnect.Enabled = false;
				buttonSend.Enabled = false;
				textBoxHost.ReadOnly = false;
				textBoxPort.ReadOnly = false;
				_socket = null;
			}
			else
			{
				_log($"{textBoxHost.Text}:{textBoxPort.Text} 关闭连接失败");
			}
		}
		else
		{
			_log($"未连接");
		}
	}

	private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
	{
		if (_socket != null)
		{
			_socket.Close();
			_socket.Dispose();
		}
	}
}
