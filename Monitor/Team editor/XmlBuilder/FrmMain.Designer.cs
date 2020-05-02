namespace XmlBuilder
{
    partial class frmMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.cmdProcess = new System.Windows.Forms.Button();
            this.openFileDlgExcel = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radStep5 = new System.Windows.Forms.RadioButton();
            this.prgBarProcess = new System.Windows.Forms.ProgressBar();
            this.radStep3 = new System.Windows.Forms.RadioButton();
            this.radStep2 = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cmdParcourirXml = new System.Windows.Forms.Button();
            this.txtXmlPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cmdParcourirExcel = new System.Windows.Forms.Button();
            this.txtExcelPath = new System.Windows.Forms.TextBox();
            this.openFileDlgXml = new System.Windows.Forms.OpenFileDialog();
            this.cmdQuitter = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdProcess
            // 
            this.cmdProcess.Enabled = false;
            this.cmdProcess.Location = new System.Drawing.Point(224, 97);
            this.cmdProcess.Name = "cmdProcess";
            this.cmdProcess.Size = new System.Drawing.Size(75, 23);
            this.cmdProcess.TabIndex = 0;
            this.cmdProcess.Text = "&Génération";
            this.cmdProcess.UseVisualStyleBackColor = true;
            this.cmdProcess.Click += new System.EventHandler(this.cmdProcess_Click);
            // 
            // openFileDlgExcel
            // 
            this.openFileDlgExcel.Filter = "Documents Excel (*.xls)|*.xls";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radStep5);
            this.groupBox1.Controls.Add(this.prgBarProcess);
            this.groupBox1.Controls.Add(this.radStep3);
            this.groupBox1.Controls.Add(this.radStep2);
            this.groupBox1.Location = new System.Drawing.Point(12, 153);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(512, 120);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Avancement";
            // 
            // radStep5
            // 
            this.radStep5.AutoSize = true;
            this.radStep5.Enabled = false;
            this.radStep5.Location = new System.Drawing.Point(6, 97);
            this.radStep5.Name = "radStep5";
            this.radStep5.Size = new System.Drawing.Size(120, 17);
            this.radStep5.TabIndex = 13;
            this.radStep5.TabStop = true;
            this.radStep5.Text = "Génération terminée";
            this.radStep5.UseVisualStyleBackColor = true;
            // 
            // prgBarProcess
            // 
            this.prgBarProcess.Enabled = false;
            this.prgBarProcess.Location = new System.Drawing.Point(23, 68);
            this.prgBarProcess.Name = "prgBarProcess";
            this.prgBarProcess.Size = new System.Drawing.Size(483, 23);
            this.prgBarProcess.TabIndex = 11;
            // 
            // radStep3
            // 
            this.radStep3.AutoSize = true;
            this.radStep3.Enabled = false;
            this.radStep3.Location = new System.Drawing.Point(6, 45);
            this.radStep3.Name = "radStep3";
            this.radStep3.Size = new System.Drawing.Size(150, 17);
            this.radStep3.TabIndex = 10;
            this.radStep3.TabStop = true;
            this.radStep3.Text = "Traitement du fichier Excel";
            this.radStep3.UseVisualStyleBackColor = true;
            // 
            // radStep2
            // 
            this.radStep2.AutoSize = true;
            this.radStep2.Enabled = false;
            this.radStep2.Location = new System.Drawing.Point(6, 22);
            this.radStep2.Name = "radStep2";
            this.radStep2.Size = new System.Drawing.Size(186, 17);
            this.radStep2.TabIndex = 9;
            this.radStep2.TabStop = true;
            this.radStep2.Text = "Chargement des données sources";
            this.radStep2.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.cmdParcourirXml);
            this.groupBox2.Controls.Add(this.cmdProcess);
            this.groupBox2.Controls.Add(this.txtXmlPath);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.cmdParcourirExcel);
            this.groupBox2.Controls.Add(this.txtExcelPath);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(512, 135);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Sélection des fichiers";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Fichier XML :";
            // 
            // cmdParcourirXml
            // 
            this.cmdParcourirXml.Location = new System.Drawing.Point(458, 60);
            this.cmdParcourirXml.Name = "cmdParcourirXml";
            this.cmdParcourirXml.Size = new System.Drawing.Size(35, 23);
            this.cmdParcourirXml.TabIndex = 8;
            this.cmdParcourirXml.Text = "...";
            this.cmdParcourirXml.UseVisualStyleBackColor = true;
            this.cmdParcourirXml.Click += new System.EventHandler(this.cmdParcourirXml_Click);
            // 
            // txtXmlPath
            // 
            this.txtXmlPath.Location = new System.Drawing.Point(136, 62);
            this.txtXmlPath.Name = "txtXmlPath";
            this.txtXmlPath.Size = new System.Drawing.Size(318, 20);
            this.txtXmlPath.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(110, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Fichier Source Excel :";
            // 
            // cmdParcourirExcel
            // 
            this.cmdParcourirExcel.Location = new System.Drawing.Point(458, 22);
            this.cmdParcourirExcel.Name = "cmdParcourirExcel";
            this.cmdParcourirExcel.Size = new System.Drawing.Size(35, 23);
            this.cmdParcourirExcel.TabIndex = 5;
            this.cmdParcourirExcel.Text = "...";
            this.cmdParcourirExcel.UseVisualStyleBackColor = true;
            this.cmdParcourirExcel.Click += new System.EventHandler(this.cmdParcourirExcel_Click);
            // 
            // txtExcelPath
            // 
            this.txtExcelPath.Location = new System.Drawing.Point(136, 24);
            this.txtExcelPath.Name = "txtExcelPath";
            this.txtExcelPath.Size = new System.Drawing.Size(318, 20);
            this.txtExcelPath.TabIndex = 4;
            // 
            // openFileDlgXml
            // 
            this.openFileDlgXml.CheckFileExists = false;
            this.openFileDlgXml.Filter = "Documents XML (*.xml)|*.xml";
            // 
            // cmdQuitter
            // 
            this.cmdQuitter.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdQuitter.Location = new System.Drawing.Point(449, 291);
            this.cmdQuitter.Name = "cmdQuitter";
            this.cmdQuitter.Size = new System.Drawing.Size(75, 23);
            this.cmdQuitter.TabIndex = 10;
            this.cmdQuitter.Text = "Quitter";
            this.cmdQuitter.UseVisualStyleBackColor = true;
            this.cmdQuitter.Click += new System.EventHandler(this.cmdQuitter_Click);
            // 
            // frmMain
            // 
            this.AcceptButton = this.cmdProcess;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cmdQuitter;
            this.ClientSize = new System.Drawing.Size(533, 326);
            this.Controls.Add(this.cmdQuitter);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "frmMain";
            this.Text = "Processsoft XML Builder";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button cmdProcess;
        private System.Windows.Forms.OpenFileDialog openFileDlgExcel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar prgBarProcess;
        private System.Windows.Forms.RadioButton radStep3;
        private System.Windows.Forms.RadioButton radStep2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button cmdParcourirXml;
        private System.Windows.Forms.TextBox txtXmlPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button cmdParcourirExcel;
        private System.Windows.Forms.TextBox txtExcelPath;
        private System.Windows.Forms.OpenFileDialog openFileDlgXml;
        private System.Windows.Forms.Button cmdQuitter;
        private System.Windows.Forms.RadioButton radStep5;
    }
}

