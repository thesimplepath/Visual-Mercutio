namespace Visual_Mercutio_Reports_Manager.Forms
{
    partial class ModifyPriority
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
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOk = new System.Windows.Forms.Button();
            this.lblPriorityTable = new System.Windows.Forms.Label();
            this.dgvPriority = new System.Windows.Forms.DataGridView();
            ( (System.ComponentModel.ISupportInitialize)( this.dgvPriority ) ).BeginInit();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
            this.btnCancel.Location = new System.Drawing.Point( 14, 416 );
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
            this.btnCancel.TabIndex = 7;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
            // 
            // btnOk
            // 
            this.btnOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.btnOk.Location = new System.Drawing.Point( 547, 416 );
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size( 75, 23 );
            this.btnOk.TabIndex = 6;
            this.btnOk.Text = "Ok";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Click += new System.EventHandler( this.btnOk_Click );
            // 
            // lblPriorityTable
            // 
            this.lblPriorityTable.AutoSize = true;
            this.lblPriorityTable.Location = new System.Drawing.Point( 11, 7 );
            this.lblPriorityTable.Name = "lblPriorityTable";
            this.lblPriorityTable.Size = new System.Drawing.Size( 64, 13 );
            this.lblPriorityTable.TabIndex = 5;
            this.lblPriorityTable.Text = "Priority table";
            // 
            // dgvPriority
            // 
            this.dgvPriority.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.dgvPriority.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvPriority.Location = new System.Drawing.Point( 14, 23 );
            this.dgvPriority.Name = "dgvPriority";
            this.dgvPriority.Size = new System.Drawing.Size( 608, 387 );
            this.dgvPriority.TabIndex = 4;
            this.dgvPriority.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler( this.dgvPriority_DataError );
            // 
            // ModifyPriority
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 632, 446 );
            this.Controls.Add( this.btnCancel );
            this.Controls.Add( this.btnOk );
            this.Controls.Add( this.lblPriorityTable );
            this.Controls.Add( this.dgvPriority );
            this.MinimumSize = new System.Drawing.Size( 300, 300 );
            this.Name = "ModifyPriority";
            this.Text = "Modify Priority table";
            ( (System.ComponentModel.ISupportInitialize)( this.dgvPriority ) ).EndInit();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Label lblPriorityTable;
        private System.Windows.Forms.DataGridView dgvPriority;
    }
}