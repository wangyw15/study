using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DayOfWeek
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
                if (int.TryParse(textBoxYear.Text, out int year))
                {
                    if (year == DateTime.Now.Year)
                    {
                        if (DateTime.TryParse($"{textBoxYear.Text}/{textBoxMonth.Text}/{textBoxDay.Text}", out birthday))
                        {
                            textBoxDayOfWeek.Text = birthday.ToString("dddd");
                        }
                        else
                        {
                            MessageBox.Show("请输入有效的年月日", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else
                    {
                        MessageBox.Show("只能输入今年的日期", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
