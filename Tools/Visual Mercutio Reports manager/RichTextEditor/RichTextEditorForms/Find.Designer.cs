namespace RichTextEditor.RichTextEditorForms
{
    partial class Find
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
            this.btnFindNext = new System.Windows.Forms.Button();
            this.btnFind = new System.Windows.Forms.Button();
            this.cbxCaseSensitive = new System.Windows.Forms.CheckBox();
            this.tbSearch = new System.Windows.Forms.TextBox();
            this.lblSearch = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnFindNext
            // 
            this.btnFindNext.Enabled = false;
            this.btnFindNext.Location = new System.Drawing.Point( 300, 56 );
            this.btnFindNext.Name = "btnFindNext";
            this.btnFindNext.Size = new System.Drawing.Size( 75, 21 );
            this.btnFindNext.TabIndex = 4;
            this.btnFindNext.Text = "Find &Next";
            this.btnFindNext.UseVisualStyleBackColor = true;
            this.btnFindNext.Click += new System.EventHandler( this.btnFindNext_Click );
            // 
            // btnFind
            // 
            this.btnFind.Location = new System.Drawing.Point( 300, 25 );
            this.btnFind.Name = "btnFind";
            this.btnFind.Size = new System.Drawing.Size( 75, 21 );
            this.btnFind.TabIndex = 3;
            this.btnFind.Text = "&Find";
            this.btnFind.UseVisualStyleBackColor = true;
            this.btnFind.Click += new System.EventHandler( this.btnFind_Click );
            // 
            // cbxCaseSensitive
            // 
            this.cbxCaseSensitive.AutoSize = true;
            this.cbxCaseSensitive.Location = new System.Drawing.Point( 15, 56 );
            this.cbxCaseSensitive.Name = "cbxCaseSensitive";
            this.cbxCaseSensitive.Size = new System.Drawing.Size( 94, 17 );
            this.cbxCaseSensitive.TabIndex = 2;
            this.cbxCaseSensitive.Text = "Case sensitive";
            this.cbxCaseSensitive.UseVisualStyleBackColor = true;
            // 
            // tbSearch
            // 
            this.tbSearch.Location = new System.Drawing.Point( 15, 25 );
            this.tbSearch.Name = "tbSearch";
            this.tbSearch.Size = new System.Drawing.Size( 252, 20 );
            this.tbSearch.TabIndex = 1;
            this.tbSearch.TextChanged += new System.EventHandler( this.tbSearch_TextChanged );
            // 
            // lblSearch
            // 
            this.lblSearch.AutoSize = true;
            this.lblSearch.Location = new System.Drawing.Point( 12, 9 );
            this.lblSearch.Name = "lblSearch";
            this.lblSearch.Size = new System.Drawing.Size( 41, 13 );
            this.lblSearch.TabIndex = 0;
            this.lblSearch.Text = "Search";
            // 
            // Find
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 387, 88 );
            this.Controls.Add( this.btnFindNext );
            this.Controls.Add( this.btnFind );
            this.Controls.Add( this.cbxCaseSensitive );
            this.Controls.Add( this.tbSearch );
            this.Controls.Add( this.lblSearch );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Find";
            this.Text = "Find Text";
            this.TopMost = true;
            this.Load += new System.EventHandler( this.Find_Load );
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.Button btnFindNext;
        internal System.Windows.Forms.Button btnFind;
        internal System.Windows.Forms.CheckBox cbxCaseSensitive;
        internal System.Windows.Forms.TextBox tbSearch;
        internal System.Windows.Forms.Label lblSearch;
    }
}