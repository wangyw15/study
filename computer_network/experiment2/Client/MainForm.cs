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
			_log("δ���ӵ�������");
		}
		if (string.IsNullOrEmpty(textBoxUsername.Text) || string.IsNullOrWhiteSpace(textBoxUsername.Text))
		{
			_log("�û�������Ϊ��");
			return;
		}
		if (string.IsNullOrEmpty(textBoxPassword.Text) || string.IsNullOrWhiteSpace(textBoxPassword.Text))
		{
			_log("���벻��Ϊ��");
			return;
		}
		if (string.IsNullOrEmpty(textBoxMessage.Text) || string.IsNullOrWhiteSpace(textBoxMessage.Text))
		{
			_log("��Ϣ����Ϊ��");
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
				_log(respdata["success"] ? "���ͳɹ�" : "����ʧ��");
			}
		}
		catch
		{
			_log("����ʧ��");
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
			_log("�Ѿ����ӹ���");
			return;
		}
		if (string.IsNullOrEmpty(textBoxHost.Text) || string.IsNullOrWhiteSpace(textBoxHost.Text))
		{
			_log("����������Ϊ��");
			return;
		}
		if (string.IsNullOrEmpty(textBoxPort.Text) || string.IsNullOrWhiteSpace(textBoxPort.Text))
		{
			_log("�˿ںŲ���Ϊ��");
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
			_log($"{textBoxHost.Text}:{textBoxPort.Text} ���ӳɹ�");
			buttonConnect.Enabled = false;
			buttonDisconnect.Enabled = true;
			buttonSend.Enabled = true;
			textBoxHost.ReadOnly = true;
			textBoxPort.ReadOnly = true;
		}
		else
		{
			_log($"{textBoxHost.Text}:{textBoxPort.Text} ����ʧ��");
		}
	}

	private void buttonDisconnect_Click(object sender, EventArgs e)
	{
		if (_socket != null && _socket.Connected)
		{
			_socket.Close();
			if (!_socket.Connected)
			{
				_log($"{textBoxHost.Text}:{textBoxPort.Text} �ѹر�����");
				buttonConnect.Enabled = true;
				buttonDisconnect.Enabled = false;
				buttonSend.Enabled = false;
				textBoxHost.ReadOnly = false;
				textBoxPort.ReadOnly = false;
				_socket = null;
			}
			else
			{
				_log($"{textBoxHost.Text}:{textBoxPort.Text} �ر�����ʧ��");
			}
		}
		else
		{
			_log($"δ����");
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
