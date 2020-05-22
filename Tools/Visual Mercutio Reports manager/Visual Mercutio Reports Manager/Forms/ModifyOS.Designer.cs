namespace Visual_Mercutio_Reports_Manager.Forms
{
    partial class ModifyOS
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if ( disposing && ( components != null ) )
            {
                components.Dispose();
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dgvOS = new System.Windows.Forms.DataGridView();
            this.lblOSTable = new System.Windows.Forms.Label();
            this.btnOk = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            ( (System.ComponentModel.ISupportInitialize)( this.dgvOS ) ).BeginInit();
            this.SuspendLayout();
            // 
            // dgvOS
            // 
            this.dgvOS.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.dgvOS.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvOS.Location = new System.Drawing.Point( 12, 25 );
            this.dgvOS.Name = "dgvOS";
            this.dgvOS.Size = new System.Drawing.Size( 608, 387 );
            this.dgvOS.TabIndex = 0;
            this.dgvOS.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler( this.dgvOS_DataError );
            // 
            // lblOSTable
            // 
            this.lblOSTable.AutoSize = true;
            this.lblOSTable.Location = new System.Drawing.Point( 9, 9 );
            this.lblOSTable.Name = "lblOSTable";
            this.lblOSTable.Size = new System.Drawing.Size( 119, 13 );
            this.lblOSTable.TabIndex = 1;
            this.lblOSTable.Text = "Operating systems table";
            // 
            // btnOk
            // 
            this.btnOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.btnOk.Location = new System.Drawing.Point( 545, 418 );
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size( 75, 23 );
            this.btnOk.TabIndex = 2;
            this.btnOk.Text = "Ok";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Click += new System.EventHandler( this.btnOk_Click );
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
            this.btnCancel.Location = new System.Drawing.Point( 12, 418 );
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
            // 
            // ModifyOS
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 632, 446 );
            this.Controls.Add( this.btnCancel );
            this.Controls.Add( this.btnOk );
            this.Controls.Add( this.lblOSTable );
            this.Controls.Add( this.dgvOS );
            this.MinimumSize = new System.Drawing.Size( 300, 300 );
            this.Name = "ModifyOS";
            this.Text = "Operating Systems Modifier";
            ( (System.ComponentModel.ISupportInitialize)( this.dgvOS ) ).EndInit();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvOS;
        private System.Windows.Forms.Label lblOSTable;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Button btnCancel;
    }
}