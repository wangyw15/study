using Microsoft.VisualBasic.ApplicationServices;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Server;

public partial class MainForm : Form
{
	public MainForm()
	{
		InitializeComponent();
		// load users
		if (File.Exists("users.json"))
		{
			_users = JsonSerializer.Deserialize<Dictionary<string, string>>(File.ReadAllText("users.json"))
				?? new();
		}
		foreach (var user in _users)
		{
			listBoxUsers.Items.Add(user.Key);
		}
		Task.Run(() =>
		{
			while (true)
			{
				if (!_listening)
				{
					continue;
				}
				var connect = _server.Accept();
				_connections.Add(connect.RemoteEndPoint.ToString(), connect);
				listBoxConnectedUsers.Invoke(() =>
				{
					listBoxConnectedUsers.Items.Add(connect.RemoteEndPoint.ToString());
				});
				Task.Run(() =>
				{
					var remote = connect.RemoteEndPoint as IPEndPoint;
					if (connect.Connected)
					{
						_log($"�ѽ������� {remote.Address.MapToIPv4()}:{remote.Port} ������");
					}
					else
					{
						_log($"���� {remote.Address.MapToIPv4()}:{remote.Port} ʧ��");
						return;
					}
					while (!connect.Poll(1000, SelectMode.SelectRead))
					{
						byte[] bytesBuffer = new byte[256];
						try
						{
							int bytesReceived = connect.Receive(bytesBuffer);
							if (bytesReceived != 0)
							{
								var data = JsonSerializer.Deserialize<Dictionary<string, string>>(Encoding.UTF8.GetString(bytesBuffer, 0, bytesReceived));
								var success = false;
								if (_users.ContainsKey(data["username"]))
								{
									if (_users[data["username"]] == data["password"])
									{
										_log(data["username"] + ": " + data["message"]);
										success = true;
									}
								}
								int sentBytes = 0;
								var respdata = Encoding.UTF8.GetBytes(JsonSerializer.Serialize(new
								{
									success
								}));
								while (sentBytes < respdata.Length)
								{
									sentBytes += connect.Send(respdata, sentBytes, respdata.Length - sentBytes, SocketFlags.None);
								}
								if (!success)
								{
									_log("�û������������");
								}
							}
						}
						catch
						{
							break;
						}
					}
					connect.Close();
					_log($"�ѶϿ����� {remote.Address}:{remote.Port} ������");
				});
			}
		});
	}

	Dictionary<string, Socket> _connections = new();
	Socket _server = new Socket(SocketType.Stream, ProtocolType.Tcp);
	Dictionary<string, string> _users = new();
	bool _listening = false;

	private void buttonAddUser_Click(object sender, EventArgs e)
	{
		if (string.IsNullOrEmpty(textBoxUserName.Text) || string.IsNullOrWhiteSpace(textBoxUserName.Text))
		{
			MessageBox.Show("�û�������Ϊ��", "����");
			return;
		}
		if (!_users.ContainsKey(textBoxUserName.Text))
		{
			if (textBoxPassword.Text == textBoxPasswordCheck.Text)
			{
				_users.Add(textBoxUserName.Text, textBoxPassword.Text);
				using (var writer = new StreamWriter("users.json"))
				{
					writer.WriteLine(JsonSerializer.Serialize(_users));
				}
				listBoxUsers.Items.Add(textBoxUserName.Text);
			}
			else
			{
				MessageBox.Show("�����������벻һ��", "����");
			}
		}
		else
		{
			MessageBox.Show("�û����Ѵ���", "����");
		}
	}

	private void buttonDeleteUser_Click(object sender, EventArgs e)
	{
		if (listBoxUsers.SelectedItem != null)
		{
			var selected = listBoxUsers.SelectedItem.ToString() ?? "";
			if (_users.ContainsKey(selected))
			{
				_users.Remove(selected);
				using (var writer = new StreamWriter("users.json"))
				{
					writer.WriteLine(JsonSerializer.Serialize(_users));
				}
				listBoxUsers.Items.Remove(selected);
			}
		}
	}

	private void buttonCloseConnection_Click(object sender, EventArgs e)
	{
		if (listBoxConnectedUsers.SelectedItem != null)
		{
			var selected = listBoxConnectedUsers.SelectedItem.ToString() ?? "";
			if (_connections.ContainsKey(selected))
			{
				_connections[selected].Close();
				_connections.Remove(selected);
				listBoxConnectedUsers.Items.Remove(selected);
			}
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

	private void buttonListenToggle_Click(object sender, EventArgs e)
	{
		if (buttonListenToggle.Text == "��ʼ")
		{
			_server.Bind(new IPEndPoint(IPAddress.Any, (int)numericUpDownPort.Value));
			_server.Listen();
			_log("��ʼ����", false);
			buttonListenToggle.Enabled = false;
			_listening = true;
		}
	}
}
