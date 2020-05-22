namespace RichTextEditor.RichTextEditorForms
{
    partial class FindAndReplace
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
            this.btnReplaceAll = new System.Windows.Forms.Button();
            this.btnReplace = new System.Windows.Forms.Button();
            this.btnFindNext = new System.Windows.Forms.Button();
            this.btnFind = new System.Windows.Forms.Button();
            this.cbxCaseSensitive = new System.Windows.Forms.CheckBox();
            this.tbReplaceBy = new System.Windows.Forms.TextBox();
            this.lblReplaceBy = new System.Windows.Forms.Label();
            this.tbSearch = new System.Windows.Forms.TextBox();
            this.lblSearch = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnReplaceAll
            // 
            this.btnReplaceAll.Location = new System.Drawing.Point( 258, 140 );
            this.btnReplaceAll.Name = "btnReplaceAll";
            this.btnReplaceAll.Size = new System.Drawing.Size( 75, 21 );
            this.btnReplaceAll.TabIndex = 26;
            this.btnReplaceAll.Text = "Replace &All";
            this.btnReplaceAll.UseVisualStyleBackColor = true;
            this.btnReplaceAll.Click += new System.EventHandler( this.btnReplaceAll_Click );
            // 
            // btnReplace
            // 
            this.btnReplace.Location = new System.Drawing.Point( 177, 140 );
            this.btnReplace.Name = "btnReplace";
            this.btnReplace.Size = new System.Drawing.Size( 75, 21 );
            this.btnReplace.TabIndex = 25;
            this.btnReplace.Text = "&Replace";
            this.btnReplace.UseVisualStyleBackColor = true;
            this.btnReplace.Click += new System.EventHandler( this.btnReplace_Click );
            // 
            // btnFindNext
            // 
            this.btnFindNext.Enabled = false;
            this.btnFindNext.Location = new System.Drawing.Point( 96, 140 );
            this.btnFindNext.Name = "btnFindNext";
            this.btnFindNext.Size = new System.Drawing.Size( 75, 21 );
            this.btnFindNext.TabIndex = 24;
            this.btnFindNext.Text = "Find &Next";
            this.btnFindNext.UseVisualStyleBackColor = true;
            this.btnFindNext.Click += new System.EventHandler( this.btnFindNext_Click );
            // 
            // btnFind
            // 
            this.btnFind.Location = new System.Drawing.Point( 15, 140 );
            this.btnFind.Name = "btnFind";
            this.btnFind.Size = new System.Drawing.Size( 75, 21 );
            this.btnFind.TabIndex = 23;
            this.btnFind.Text = "&Find";
            this.btnFind.UseVisualStyleBackColor = true;
            this.btnFind.Click += new System.EventHandler( this.btnFind_Click );
            // 
            // cbxCaseSensitive
            // 
            this.cbxCaseSensitive.AutoSize = true;
            this.cbxCaseSensitive.Location = new System.Drawing.Point( 14, 104 );
            this.cbxCaseSensitive.Name = "cbxCaseSensitive";
            this.cbxCaseSensitive.Size = new System.Drawing.Size( 94, 17 );
            this.cbxCaseSensitive.TabIndex = 22;
            this.cbxCaseSensitive.Text = "Case sensitive";
            this.cbxCaseSensitive.UseVisualStyleBackColor = true;
            // 
            // tbReplaceBy
            // 
            this.tbReplaceBy.Location = new System.Drawing.Point( 14, 78 );
            this.tbReplaceBy.Name = "tbReplaceBy";
            this.tbReplaceBy.Size = new System.Drawing.Size( 320, 20 );
            this.tbReplaceBy.TabIndex = 21;
            // 
            // lblReplaceBy
            // 
            this.lblReplaceBy.AutoSize = true;
            this.lblReplaceBy.Location = new System.Drawing.Point( 12, 62 );
            this.lblReplaceBy.Name = "lblReplaceBy";
            this.lblReplaceBy.Size = new System.Drawing.Size( 61, 13 );
            this.lblReplaceBy.TabIndex = 20;
            this.lblReplaceBy.Text = "Replace by";
            // 
            // tbSearch
            // 
            this.tbSearch.Location = new System.Drawing.Point( 14, 25 );
            this.tbSearch.Name = "tbSearch";
            this.tbSearch.Size = new System.Drawing.Size( 321, 20 );
            this.tbSearch.TabIndex = 19;
            this.tbSearch.TextChanged += new System.EventHandler( this.tbSearch_TextChanged );
            // 
            // lblSearch
            // 
            this.lblSearch.AutoSize = true;
            this.lblSearch.Location = new System.Drawing.Point( 12, 9 );
            this.lblSearch.Name = "lblSearch";
            this.lblSearch.Size = new System.Drawing.Size( 41, 13 );
            this.lblSearch.TabIndex = 18;
            this.lblSearch.Text = "Search";
            // 
            // FindAndReplace
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 348, 175 );
            this.Controls.Add( this.btnReplaceAll );
            this.Controls.Add( this.btnReplace );
            this.Controls.Add( this.btnFindNext );
            this.Controls.Add( this.btnFind );
            this.Controls.Add( this.cbxCaseSensitive );
            this.Controls.Add( this.tbReplaceBy );
            this.Controls.Add( this.lblReplaceBy );
            this.Controls.Add( this.tbSearch );
            this.Controls.Add( this.lblSearch );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FindAndReplace";
            this.Text = "Find and Replace";
            this.TopMost = true;
            this.Load += new System.EventHandler( this.FindAndReplace_Load );
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.Button btnReplaceAll;
        internal System.Windows.Forms.Button btnReplace;
        internal System.Windows.Forms.Button btnFindNext;
        internal System.Windows.Forms.Button btnFind;
        internal System.Windows.Forms.CheckBox cbxCaseSensitive;
        internal System.Windows.Forms.TextBox tbReplaceBy;
        internal System.Windows.Forms.Label lblReplaceBy;
        internal System.Windows.Forms.TextBox tbSearch;
        internal System.Windows.Forms.Label lblSearch;
    }
}