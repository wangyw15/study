using System;
using System.Windows.Forms;

namespace DayOfWeek
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxYear = new System.Windows.Forms.TextBox();
            this.buttonCalculate = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxDay = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxMonth = new System.Windows.Forms.TextBox();
            this.textBoxDayOfWeek = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 20F);
            this.label1.Location = new System.Drawing.Point(146, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(217, 40);
            this.label1.TabIndex = 0;
            this.label1.Text = "请输入日期";
            // 
            // textBoxYear
            // 
            this.textBoxYear.Font = new System.Drawing.Font("宋体", 20F);
            this.textBoxYear.Location = new System.Drawing.Point(19, 52);
            this.textBoxYear.Name = "textBoxYear";
            this.textBoxYear.Size = new System.Drawing.Size(100, 53);
            this.textBoxYear.TabIndex = 1;
            // 
            // buttonCalculate
            // 
            this.buttonCalculate.Font = new System.Drawing.Font("宋体", 20F);
            this.buttonCalculate.Location = new System.Drawing.Point(157, 111);
            this.buttonCalculate.Name = "buttonCalculate";
            this.buttonCalculate.Size = new System.Drawing.Size(213, 78);
            this.buttonCalculate.TabIndex = 4;
            this.buttonCalculate.Text = "Day";
            this.buttonCalculate.UseVisualStyleBackColor = true;
            this.buttonCalculate.MouseClick += new System.Windows.Forms.MouseEventHandler(this.buttonCalculate_MouseClick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 20F);
            this.label2.Location = new System.Drawing.Point(125, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 40);
            this.label2.TabIndex = 0;
            this.label2.Text = "年";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 20F);
            this.label3.Location = new System.Drawing.Point(463, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 40);
            this.label3.TabIndex = 0;
            this.label3.Text = "日";
            // 
            // textBoxDay
            // 
            this.textBoxDay.Font = new System.Drawing.Font("宋体", 20F);
            this.textBoxDay.Location = new System.Drawing.Point(357, 52);
            this.textBoxDay.Name = "textBoxDay";
            this.textBoxDay.Size = new System.Drawing.Size(100, 53);
            this.textBoxDay.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 20F);
            this.label4.Location = new System.Drawing.Point(294, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 40);
            this.label4.TabIndex = 0;
            this.label4.Text = "月";
            // 
            // textBoxMonth
            // 
            this.textBoxMonth.Font = new System.Drawing.Font("宋体", 20F);
            this.textBoxMonth.Location = new System.Drawing.Point(188, 52);
            this.textBoxMonth.Name = "textBoxMonth";
            this.textBoxMonth.Size = new System.Drawing.Size(100, 53);
            this.textBoxMonth.TabIndex = 2;
            // 
            // textBoxDayOfWeek
            // 
            this.textBoxDayOfWeek.Font = new System.Drawing.Font("宋体", 20F);
            this.textBoxDayOfWeek.Location = new System.Drawing.Point(188, 195);
            this.textBoxDayOfWeek.Name = "textBoxDayOfWeek";
            this.textBoxDayOfWeek.ReadOnly = true;
            this.textBoxDayOfWeek.Size = new System.Drawing.Size(163, 53);
            this.textBoxDayOfWeek.TabIndex = 5;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(514, 262);
            this.Controls.Add(this.textBoxDayOfWeek);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxMonth);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxDay);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonCalculate);
            this.Controls.Add(this.textBoxYear);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "YourAge";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxYear;
        private System.Windows.Forms.Button buttonCalculate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxDay;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxMonth;
        private System.Windows.Forms.TextBox textBoxDayOfWeek;
    }
}

