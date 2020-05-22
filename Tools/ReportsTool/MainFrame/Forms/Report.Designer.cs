namespace ReportsTool.Forms
{
    partial class Report
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Report));
            this.fbd_ChangePubFolder = new System.Windows.Forms.FolderBrowserDialog();
            this.btn_ChangeFolder = new System.Windows.Forms.Button();
            this.tb_PubFolder = new System.Windows.Forms.TextBox();
            this.gbx_PubFolder = new System.Windows.Forms.GroupBox();
            this.gbx_Report = new System.Windows.Forms.GroupBox();
            this.lbx_Files = new System.Windows.Forms.ListBox();
            this.lbl_Files = new System.Windows.Forms.Label();
            this.cbx_ReportType = new System.Windows.Forms.ComboBox();
            this.lbl_ReportType = new System.Windows.Forms.Label();
            this.btn_Cancel = new System.Windows.Forms.Button();
            this.btn_Open = new System.Windows.Forms.Button();
            this.gbx_PubFolder.SuspendLayout();
            this.gbx_Report.SuspendLayout();
            this.SuspendLayout();
            // 
            // fbd_ChangePubFolder
            // 
            resources.ApplyResources(this.fbd_ChangePubFolder, "fbd_ChangePubFolder");
            // 
            // btn_ChangeFolder
            // 
            this.btn_ChangeFolder.AccessibleDescription = null;
            this.btn_ChangeFolder.AccessibleName = null;
            resources.ApplyResources(this.btn_ChangeFolder, "btn_ChangeFolder");
            this.btn_ChangeFolder.BackgroundImage = null;
            this.btn_ChangeFolder.Font = null;
            this.btn_ChangeFolder.Name = "btn_ChangeFolder";
            this.btn_ChangeFolder.UseVisualStyleBackColor = true;
            this.btn_ChangeFolder.Click += new System.EventHandler(this.btn_ChangeFolder_Click);
            // 
            // tb_PubFolder
            // 
            this.tb_PubFolder.AccessibleDescription = null;
            this.tb_PubFolder.AccessibleName = null;
            resources.ApplyResources(this.tb_PubFolder, "tb_PubFolder");
            this.tb_PubFolder.BackgroundImage = null;
            this.tb_PubFolder.Font = null;
            this.tb_PubFolder.Name = "tb_PubFolder";
            this.tb_PubFolder.ReadOnly = true;
            this.tb_PubFolder.TextChanged += new System.EventHandler(this.tb_PubFolder_TextChanged);
            // 
            // gbx_PubFolder
            // 
            this.gbx_PubFolder.AccessibleDescription = null;
            this.gbx_PubFolder.AccessibleName = null;
            resources.ApplyResources(this.gbx_PubFolder, "gbx_PubFolder");
            this.gbx_PubFolder.BackgroundImage = null;
            this.gbx_PubFolder.Controls.Add(this.btn_ChangeFolder);
            this.gbx_PubFolder.Controls.Add(this.tb_PubFolder);
            this.gbx_PubFolder.Font = null;
            this.gbx_PubFolder.Name = "gbx_PubFolder";
            this.gbx_PubFolder.TabStop = false;
            // 
            // gbx_Report
            // 
            this.gbx_Report.AccessibleDescription = null;
            this.gbx_Report.AccessibleName = null;
            resources.ApplyResources(this.gbx_Report, "gbx_Report");
            this.gbx_Report.BackgroundImage = null;
            this.gbx_Report.Controls.Add(this.lbx_Files);
            this.gbx_Report.Controls.Add(this.lbl_Files);
            this.gbx_Report.Controls.Add(this.cbx_ReportType);
            this.gbx_Report.Controls.Add(this.lbl_ReportType);
            this.gbx_Report.Font = null;
            this.gbx_Report.Name = "gbx_Report";
            this.gbx_Report.TabStop = false;
            // 
            // lbx_Files
            // 
            this.lbx_Files.AccessibleDescription = null;
            this.lbx_Files.AccessibleName = null;
            resources.ApplyResources(this.lbx_Files, "lbx_Files");
            this.lbx_Files.BackgroundImage = null;
            this.lbx_Files.Font = null;
            this.lbx_Files.FormattingEnabled = true;
            this.lbx_Files.Name = "lbx_Files";
            // 
            // lbl_Files
            // 
            this.lbl_Files.AccessibleDescription = null;
            this.lbl_Files.AccessibleName = null;
            resources.ApplyResources(this.lbl_Files, "lbl_Files");
            this.lbl_Files.Font = null;
            this.lbl_Files.Name = "lbl_Files";
            // 
            // cbx_ReportType
            // 
            this.cbx_ReportType.AccessibleDescription = null;
            this.cbx_ReportType.AccessibleName = null;
            resources.ApplyResources(this.cbx_ReportType, "cbx_ReportType");
            this.cbx_ReportType.BackgroundImage = null;
            this.cbx_ReportType.Font = null;
            this.cbx_ReportType.FormattingEnabled = true;
            this.cbx_ReportType.Items.AddRange(new object[] {
            resources.GetString("cbx_ReportType.Items"),
            resources.GetString("cbx_ReportType.Items1"),
            resources.GetString("cbx_ReportType.Items2")});
            this.cbx_ReportType.Name = "cbx_ReportType";
            this.cbx_ReportType.SelectedIndexChanged += new System.EventHandler(this.cbx_ReportType_SelectedIndexChanged);
            // 
            // lbl_ReportType
            // 
            this.lbl_ReportType.AccessibleDescription = null;
            this.lbl_ReportType.AccessibleName = null;
            resources.ApplyResources(this.lbl_ReportType, "lbl_ReportType");
            this.lbl_ReportType.Font = null;
            this.lbl_ReportType.Name = "lbl_ReportType";
            // 
            // btn_Cancel
            // 
            this.btn_Cancel.AccessibleDescription = null;
            this.btn_Cancel.AccessibleName = null;
            resources.ApplyResources(this.btn_Cancel, "btn_Cancel");
            this.btn_Cancel.BackgroundImage = null;
            this.btn_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btn_Cancel.Font = null;
            this.btn_Cancel.Name = "btn_Cancel";
            this.btn_Cancel.UseVisualStyleBackColor = true;
            this.btn_Cancel.Click += new System.EventHandler(this.btn_Cancel_Click);
            // 
            // btn_Open
            // 
            this.btn_Open.AccessibleDescription = null;
            this.btn_Open.AccessibleName = null;
            resources.ApplyResources(this.btn_Open, "btn_Open");
            this.btn_Open.BackgroundImage = null;
            this.btn_Open.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btn_Open.Font = null;
            this.btn_Open.Name = "btn_Open";
            this.btn_Open.UseVisualStyleBackColor = true;
            this.btn_Open.Click += new System.EventHandler(this.btn_Open_Click);
            // 
            // Report
            // 
            this.AcceptButton = this.btn_Open;
            this.AccessibleDescription = null;
            this.AccessibleName = null;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = null;
            this.CancelButton = this.btn_Cancel;
            this.Controls.Add(this.btn_Open);
            this.Controls.Add(this.btn_Cancel);
            this.Controls.Add(this.gbx_Report);
            this.Controls.Add(this.gbx_PubFolder);
            this.Font = null;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Report";
            this.ShowInTaskbar = false;
            this.gbx_PubFolder.ResumeLayout(false);
            this.gbx_PubFolder.PerformLayout();
            this.gbx_Report.ResumeLayout(false);
            this.gbx_Report.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FolderBrowserDialog fbd_ChangePubFolder;
        private System.Windows.Forms.Button btn_ChangeFolder;
        private System.Windows.Forms.TextBox tb_PubFolder;
        private System.Windows.Forms.GroupBox gbx_PubFolder;
        private System.Windows.Forms.GroupBox gbx_Report;
        private System.Windows.Forms.ComboBox cbx_ReportType;
        private System.Windows.Forms.Label lbl_ReportType;
        private System.Windows.Forms.ListBox lbx_Files;
        private System.Windows.Forms.Label lbl_Files;
        private System.Windows.Forms.Button btn_Cancel;
        private System.Windows.Forms.Button btn_Open;
    }
}