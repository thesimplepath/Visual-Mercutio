namespace TeamEditor
{
    partial class FrmAIP
    {
        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false</param>
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmAIP));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtTaux = new System.Windows.Forms.MaskedTextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtDateFin = new System.Windows.Forms.DateTimePicker();
            this.label4 = new System.Windows.Forms.Label();
            this.txtDateDebut = new System.Windows.Forms.DateTimePicker();
            this.txtMotif = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cboCritereAIP = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtEmploye = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cmdSauver = new System.Windows.Forms.Button();
            this.cmdAnnuler = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtTaux);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txtDateFin);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.txtDateDebut);
            this.groupBox1.Controls.Add(this.txtMotif);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cboCritereAIP);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtEmploye);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(523, 208);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Détail de la configuration AIP";
            // 
            // txtTaux
            // 
            this.txtTaux.Location = new System.Drawing.Point(106, 105);
            this.txtTaux.Mask = "9.99";
            this.txtTaux.Name = "txtTaux";
            this.txtTaux.Size = new System.Drawing.Size(39, 20);
            this.txtTaux.TabIndex = 22;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 108);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(37, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Taux :";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 161);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 13);
            this.label5.TabIndex = 19;
            this.label5.Text = "Date fin :";
            // 
            // txtDateFin
            // 
            this.txtDateFin.Location = new System.Drawing.Point(106, 157);
            this.txtDateFin.Name = "txtDateFin";
            this.txtDateFin.Size = new System.Drawing.Size(200, 20);
            this.txtDateFin.TabIndex = 18;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 135);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Date début :";
            // 
            // txtDateDebut
            // 
            this.txtDateDebut.Location = new System.Drawing.Point(106, 131);
            this.txtDateDebut.Name = "txtDateDebut";
            this.txtDateDebut.Size = new System.Drawing.Size(200, 20);
            this.txtDateDebut.TabIndex = 16;
            // 
            // txtMotif
            // 
            this.txtMotif.Location = new System.Drawing.Point(106, 79);
            this.txtMotif.Name = "txtMotif";
            this.txtMotif.Size = new System.Drawing.Size(308, 20);
            this.txtMotif.TabIndex = 15;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 14;
            this.label3.Text = "Motif :";
            // 
            // cboCritereAIP
            // 
            this.cboCritereAIP.FormattingEnabled = true;
            this.cboCritereAIP.Location = new System.Drawing.Point(106, 52);
            this.cboCritereAIP.Name = "cboCritereAIP";
            this.cboCritereAIP.Size = new System.Drawing.Size(190, 21);
            this.cboCritereAIP.TabIndex = 13;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "Critère :";
            // 
            // txtEmploye
            // 
            this.txtEmploye.Enabled = false;
            this.txtEmploye.Location = new System.Drawing.Point(106, 26);
            this.txtEmploye.Name = "txtEmploye";
            this.txtEmploye.Size = new System.Drawing.Size(190, 20);
            this.txtEmploye.TabIndex = 11;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Employé :";
            // 
            // cmdSauver
            // 
            this.cmdSauver.Location = new System.Drawing.Point(460, 226);
            this.cmdSauver.Name = "cmdSauver";
            this.cmdSauver.Size = new System.Drawing.Size(75, 23);
            this.cmdSauver.TabIndex = 11;
            this.cmdSauver.Text = "Sauver";
            this.cmdSauver.UseVisualStyleBackColor = true;
            this.cmdSauver.Click += new System.EventHandler(this.cmdSauver_Click);
            // 
            // cmdAnnuler
            // 
            this.cmdAnnuler.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdAnnuler.Location = new System.Drawing.Point(379, 226);
            this.cmdAnnuler.Name = "cmdAnnuler";
            this.cmdAnnuler.Size = new System.Drawing.Size(75, 23);
            this.cmdAnnuler.TabIndex = 12;
            this.cmdAnnuler.Text = "Annuler";
            this.cmdAnnuler.UseVisualStyleBackColor = true;
            this.cmdAnnuler.Click += new System.EventHandler(this.cmdAnnuler_Click);
            // 
            // FrmAIP
            // 
            this.AcceptButton = this.cmdSauver;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cmdAnnuler;
            this.ClientSize = new System.Drawing.Size(548, 269);
            this.Controls.Add(this.cmdAnnuler);
            this.Controls.Add(this.cmdSauver);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmAIP";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Configuration AIP";
            this.Load += new System.EventHandler(this.FrmAIP_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker txtDateFin;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DateTimePicker txtDateDebut;
        private System.Windows.Forms.TextBox txtMotif;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cboCritereAIP;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtEmploye;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button cmdSauver;
        private System.Windows.Forms.Button cmdAnnuler;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.MaskedTextBox txtTaux;

    }
}