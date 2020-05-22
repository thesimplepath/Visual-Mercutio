namespace Visual_Mercutio_Reports_Manager.Forms
{
    partial class ModifyCase
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
            this.lblCaseTable = new System.Windows.Forms.Label();
            this.dgvCase = new System.Windows.Forms.DataGridView();
            ( (System.ComponentModel.ISupportInitialize)( this.dgvCase ) ).BeginInit();
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
            // lblCaseTable
            // 
            this.lblCaseTable.AutoSize = true;
            this.lblCaseTable.Location = new System.Drawing.Point( 11, 7 );
            this.lblCaseTable.Name = "lblCaseTable";
            this.lblCaseTable.Size = new System.Drawing.Size( 57, 13 );
            this.lblCaseTable.TabIndex = 5;
            this.lblCaseTable.Text = "Case table";
            // 
            // dgvCase
            // 
            this.dgvCase.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.dgvCase.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvCase.Location = new System.Drawing.Point( 14, 23 );
            this.dgvCase.Name = "dgvCase";
            this.dgvCase.Size = new System.Drawing.Size( 608, 387 );
            this.dgvCase.TabIndex = 4;
            this.dgvCase.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler( this.dgvCase_DataError );
            // 
            // ModifyCase
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 632, 446 );
            this.Controls.Add( this.btnCancel );
            this.Controls.Add( this.btnOk );
            this.Controls.Add( this.lblCaseTable );
            this.Controls.Add( this.dgvCase );
            this.Name = "ModifyCase";
            this.Text = "Modify Case Table";
            ( (System.ComponentModel.ISupportInitialize)( this.dgvCase ) ).EndInit();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Label lblCaseTable;
        private System.Windows.Forms.DataGridView dgvCase;
    }
}