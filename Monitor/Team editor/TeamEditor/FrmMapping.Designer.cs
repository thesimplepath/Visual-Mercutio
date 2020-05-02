namespace TeamEditor
{
    partial class FrmMapping
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMapping));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabProc = new System.Windows.Forms.TabPage();
            this.grdProc = new System.Windows.Forms.DataGridView();
            this.tabDeliv = new System.Windows.Forms.TabPage();
            this.grdDeliv = new System.Windows.Forms.DataGridView();
            this.tabUser = new System.Windows.Forms.TabPage();
            this.grdUser = new System.Windows.Forms.DataGridView();
            this.tabPrestation = new System.Windows.Forms.TabPage();
            this.grdPrestation = new System.Windows.Forms.DataGridView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboModel = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cboExternSystem = new System.Windows.Forms.ComboBox();
            this.cmdClose = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabProc.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdProc)).BeginInit();
            this.tabDeliv.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdDeliv)).BeginInit();
            this.tabUser.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdUser)).BeginInit();
            this.tabPrestation.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdPrestation)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabProc);
            this.tabControl1.Controls.Add(this.tabDeliv);
            this.tabControl1.Controls.Add(this.tabUser);
            this.tabControl1.Controls.Add(this.tabPrestation);
            this.tabControl1.Location = new System.Drawing.Point(12, 102);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(973, 480);
            this.tabControl1.TabIndex = 4;
            // 
            // tabProc
            // 
            this.tabProc.Controls.Add(this.grdProc);
            this.tabProc.Location = new System.Drawing.Point(4, 22);
            this.tabProc.Name = "tabProc";
            this.tabProc.Padding = new System.Windows.Forms.Padding(3);
            this.tabProc.Size = new System.Drawing.Size(965, 454);
            this.tabProc.TabIndex = 0;
            this.tabProc.Text = "Procédures";
            this.tabProc.UseVisualStyleBackColor = true;
            // 
            // grdProc
            // 
            this.grdProc.AllowUserToAddRows = false;
            this.grdProc.AllowUserToDeleteRows = false;
            this.grdProc.AllowUserToResizeRows = false;
            this.grdProc.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdProc.Location = new System.Drawing.Point(6, 6);
            this.grdProc.Name = "grdProc";
            this.grdProc.Size = new System.Drawing.Size(956, 441);
            this.grdProc.TabIndex = 6;
            this.grdProc.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdProc_CellValueChanged);
            // 
            // tabDeliv
            // 
            this.tabDeliv.Controls.Add(this.grdDeliv);
            this.tabDeliv.Location = new System.Drawing.Point(4, 22);
            this.tabDeliv.Name = "tabDeliv";
            this.tabDeliv.Padding = new System.Windows.Forms.Padding(3);
            this.tabDeliv.Size = new System.Drawing.Size(965, 454);
            this.tabDeliv.TabIndex = 1;
            this.tabDeliv.Text = "Livrables";
            this.tabDeliv.UseVisualStyleBackColor = true;
            // 
            // grdDeliv
            // 
            this.grdDeliv.AllowUserToAddRows = false;
            this.grdDeliv.AllowUserToDeleteRows = false;
            this.grdDeliv.AllowUserToResizeRows = false;
            this.grdDeliv.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdDeliv.Location = new System.Drawing.Point(6, 7);
            this.grdDeliv.Name = "grdDeliv";
            this.grdDeliv.Size = new System.Drawing.Size(951, 441);
            this.grdDeliv.TabIndex = 7;
            this.grdDeliv.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdDeliv_CellValueChanged);
            // 
            // tabUser
            // 
            this.tabUser.Controls.Add(this.grdUser);
            this.tabUser.Location = new System.Drawing.Point(4, 22);
            this.tabUser.Name = "tabUser";
            this.tabUser.Size = new System.Drawing.Size(965, 454);
            this.tabUser.TabIndex = 2;
            this.tabUser.Text = "Utilisateurs";
            this.tabUser.UseVisualStyleBackColor = true;
            // 
            // grdUser
            // 
            this.grdUser.AllowUserToAddRows = false;
            this.grdUser.AllowUserToDeleteRows = false;
            this.grdUser.AllowUserToResizeRows = false;
            this.grdUser.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdUser.Location = new System.Drawing.Point(7, 7);
            this.grdUser.Name = "grdUser";
            this.grdUser.Size = new System.Drawing.Size(951, 441);
            this.grdUser.TabIndex = 8;
            this.grdUser.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdUser_CellValueChanged);
            // 
            // tabPrestation
            // 
            this.tabPrestation.Controls.Add(this.grdPrestation);
            this.tabPrestation.Location = new System.Drawing.Point(4, 22);
            this.tabPrestation.Name = "tabPrestation";
            this.tabPrestation.Size = new System.Drawing.Size(965, 454);
            this.tabPrestation.TabIndex = 3;
            this.tabPrestation.Text = "Prestations";
            this.tabPrestation.UseVisualStyleBackColor = true;
            // 
            // grdPrestation
            // 
            this.grdPrestation.AllowUserToAddRows = false;
            this.grdPrestation.AllowUserToDeleteRows = false;
            this.grdPrestation.AllowUserToResizeRows = false;
            this.grdPrestation.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdPrestation.Location = new System.Drawing.Point(7, 7);
            this.grdPrestation.Name = "grdPrestation";
            this.grdPrestation.Size = new System.Drawing.Size(951, 441);
            this.grdPrestation.TabIndex = 9;
            this.grdPrestation.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdPrestation_CellValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cboModel);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cboExternSystem);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(362, 84);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Sélection";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Model Ref :";
            // 
            // cboModel
            // 
            this.cboModel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboModel.FormattingEnabled = true;
            this.cboModel.Location = new System.Drawing.Point(110, 46);
            this.cboModel.Name = "cboModel";
            this.cboModel.Size = new System.Drawing.Size(202, 21);
            this.cboModel.TabIndex = 6;
            this.cboModel.SelectedIndexChanged += new System.EventHandler(this.cboModel_SelectedIndexChanged);
            this.cboModel.SelectedValueChanged += new System.EventHandler(this.cboModel_SelectedValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Système Externe :";
            // 
            // cboExternSystem
            // 
            this.cboExternSystem.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboExternSystem.FormattingEnabled = true;
            this.cboExternSystem.Location = new System.Drawing.Point(110, 19);
            this.cboExternSystem.Name = "cboExternSystem";
            this.cboExternSystem.Size = new System.Drawing.Size(202, 21);
            this.cboExternSystem.TabIndex = 4;
            // 
            // cmdClose
            // 
            this.cmdClose.Location = new System.Drawing.Point(878, 584);
            this.cmdClose.Name = "cmdClose";
            this.cmdClose.Size = new System.Drawing.Size(75, 23);
            this.cmdClose.TabIndex = 8;
            this.cmdClose.Text = "Fermer";
            this.cmdClose.UseVisualStyleBackColor = true;
            // 
            // FrmMapping
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(985, 611);
            this.Controls.Add(this.cmdClose);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmMapping";
            this.Text = "Mapping externe";
            this.Load += new System.EventHandler(this.FrmMapping_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabProc.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdProc)).EndInit();
            this.tabDeliv.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdDeliv)).EndInit();
            this.tabUser.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdUser)).EndInit();
            this.tabPrestation.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdPrestation)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabProc;
        private System.Windows.Forms.DataGridView grdProc;
        private System.Windows.Forms.TabPage tabDeliv;
        private System.Windows.Forms.TabPage tabUser;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboModel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cboExternSystem;
        private System.Windows.Forms.DataGridView grdDeliv;
        private System.Windows.Forms.Button cmdClose;
        private System.Windows.Forms.DataGridView grdUser;
        private System.Windows.Forms.TabPage tabPrestation;
        private System.Windows.Forms.DataGridView grdPrestation;

    }
}