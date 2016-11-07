namespace kaosbox_loader
{
    partial class loaderForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxCharSelect = new System.Windows.Forms.GroupBox();
            this.buttonGo = new System.Windows.Forms.Button();
            this.comboBoxCharnames = new System.Windows.Forms.ComboBox();
            this.groupBoxCharSelect.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxCharSelect
            // 
            this.groupBoxCharSelect.Controls.Add(this.buttonGo);
            this.groupBoxCharSelect.Controls.Add(this.comboBoxCharnames);
            this.groupBoxCharSelect.Location = new System.Drawing.Point(12, 12);
            this.groupBoxCharSelect.Name = "groupBoxCharSelect";
            this.groupBoxCharSelect.Size = new System.Drawing.Size(271, 49);
            this.groupBoxCharSelect.TabIndex = 0;
            this.groupBoxCharSelect.TabStop = false;
            this.groupBoxCharSelect.Text = "Select Character...";
            // 
            // buttonGo
            // 
            this.buttonGo.Location = new System.Drawing.Point(184, 19);
            this.buttonGo.Name = "buttonGo";
            this.buttonGo.Size = new System.Drawing.Size(75, 21);
            this.buttonGo.TabIndex = 1;
            this.buttonGo.Text = "Launch";
            this.buttonGo.UseVisualStyleBackColor = true;
            this.buttonGo.Click += new System.EventHandler(this.buttonGo_Click);
            // 
            // comboBoxCharnames
            // 
            this.comboBoxCharnames.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCharnames.FormattingEnabled = true;
            this.comboBoxCharnames.Location = new System.Drawing.Point(6, 19);
            this.comboBoxCharnames.Name = "comboBoxCharnames";
            this.comboBoxCharnames.Size = new System.Drawing.Size(172, 21);
            this.comboBoxCharnames.TabIndex = 0;
            // 
            // loaderForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 73);
            this.Controls.Add(this.groupBoxCharSelect);
            this.Name = "loaderForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GWSplit Loader";
            this.Load += new System.EventHandler(this.loaderForm_Load);
            this.groupBoxCharSelect.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxCharSelect;
        private System.Windows.Forms.Button buttonGo;
        private System.Windows.Forms.ComboBox comboBoxCharnames;
    }
}

