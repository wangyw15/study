using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace YourAge
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void buttonCalculate_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                DateTime birthday;
                if (DateTime.TryParse($"{textBoxYear.Text}/{textBoxMonth.Text}/{textBoxDay.Text}", out birthday))
                {
                    if (birthday <= DateTime.Now)
                    {
                        var span = DateTime.Now - birthday;
                        textBoxAge.Text = $"{span.Days / 365}";
                    }
                    else
                    {
                        MessageBox.Show("你还没出生呢", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("请输入有效的年月日", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
    }
}
