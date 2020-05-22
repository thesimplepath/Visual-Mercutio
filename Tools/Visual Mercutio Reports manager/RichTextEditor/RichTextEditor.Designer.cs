namespace RichTextEditor
{
    partial class RichTextEditor
    {
        /// <summary> 
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose( bool disposing )
        {
            if ( disposing && ( components != null ) )
            {
                components.Dispose();
            }
            base.Dispose( disposing );
        }

        #region Code généré par le Concepteur de composants

        /// <summary> 
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas 
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( RichTextEditor ) );
            this.mnuMain = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFile_New = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFile_Open = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFile_Save = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFile_SaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFile_PageSetup = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFile_Preview = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFile_Print = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit_Undo = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit_Redo = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuEdit_Find = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit_FindAndReplace = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuEdit_SelectAll = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem5 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuEdit_Copy = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit_Cut = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit_Paste = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem8 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuEdit_InsertImage = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFont = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFont_SelectFont = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem6 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFont_ColorFont = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFont_Bold = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFont_Italic = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFont_Underline = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFont_Normal = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem7 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFont_PageColor = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent_None = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent_5Pts = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent_10Pts = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent_15Pts = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Indent_20Pts = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Align = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Align_Left = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Align_Center = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuParagraph_Align_Right = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuBullets = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuBullets_AddBullets = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuBullets_RemoveBullets = new System.Windows.Forms.ToolStripMenuItem();
            this.tosToolbar = new System.Windows.Forms.ToolStrip();
            this.tbrNew = new System.Windows.Forms.ToolStripButton();
            this.tbrOpen = new System.Windows.Forms.ToolStripButton();
            this.tbrSave = new System.Windows.Forms.ToolStripButton();
            this.ToolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tbrFont = new System.Windows.Forms.ToolStripButton();
            this.tbrColor = new System.Windows.Forms.ToolStripButton();
            this.ToolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.tbrLeft = new System.Windows.Forms.ToolStripButton();
            this.tbrCenter = new System.Windows.Forms.ToolStripButton();
            this.tbrRight = new System.Windows.Forms.ToolStripButton();
            this.ToolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tbrBold = new System.Windows.Forms.ToolStripButton();
            this.tbrItalic = new System.Windows.Forms.ToolStripButton();
            this.tbrUnderline = new System.Windows.Forms.ToolStripButton();
            this.ToolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tbrFind = new System.Windows.Forms.ToolStripButton();
            this.rtbDocument = new ExtendedRichTextBox.RichTextBoxPrintCtrl();
            this.ofdDocument = new System.Windows.Forms.OpenFileDialog();
            this.sfdDocument = new System.Windows.Forms.SaveFileDialog();
            this.psdDocument = new System.Windows.Forms.PageSetupDialog();
            this.prdDocument = new System.Drawing.Printing.PrintDocument();
            this.ppdDocument = new System.Windows.Forms.PrintPreviewDialog();
            this.prdDocumentDialog = new System.Windows.Forms.PrintDialog();
            this.ftdDocument = new System.Windows.Forms.FontDialog();
            this.cldDocument = new System.Windows.Forms.ColorDialog();
            this.mnuMain.SuspendLayout();
            this.tosToolbar.SuspendLayout();
            this.SuspendLayout();
            // 
            // mnuMain
            // 
            this.mnuMain.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuEdit,
            this.mnuFont,
            this.mnuParagraph,
            this.mnuBullets} );
            this.mnuMain.Location = new System.Drawing.Point( 0, 0 );
            this.mnuMain.Name = "mnuMain";
            this.mnuMain.Size = new System.Drawing.Size( 640, 24 );
            this.mnuMain.TabIndex = 1;
            this.mnuMain.Text = "MenuStrip1";
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile_New,
            this.ToolStripMenuItem1,
            this.mnuFile_Open,
            this.mnuFile_Save,
            this.mnuFile_SaveAs,
            this.ToolStripMenuItem2,
            this.mnuFile_PageSetup,
            this.mnuFile_Preview,
            this.mnuFile_Print} );
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size( 35, 20 );
            this.mnuFile.Text = "&File";
            // 
            // mnuFile_New
            // 
            this.mnuFile_New.Name = "mnuFile_New";
            this.mnuFile_New.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_New.Text = "&New";
            this.mnuFile_New.Click += new System.EventHandler( this.mnuFile_New_Click );
            // 
            // ToolStripMenuItem1
            // 
            this.ToolStripMenuItem1.Name = "ToolStripMenuItem1";
            this.ToolStripMenuItem1.Size = new System.Drawing.Size( 149, 6 );
            // 
            // mnuFile_Open
            // 
            this.mnuFile_Open.Name = "mnuFile_Open";
            this.mnuFile_Open.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_Open.Text = "&Open...";
            this.mnuFile_Open.Click += new System.EventHandler( this.mnuFile_Open_Click );
            // 
            // mnuFile_Save
            // 
            this.mnuFile_Save.Name = "mnuFile_Save";
            this.mnuFile_Save.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_Save.Text = "&Save...";
            this.mnuFile_Save.Click += new System.EventHandler( this.mnuFile_Save_Click );
            // 
            // mnuFile_SaveAs
            // 
            this.mnuFile_SaveAs.Name = "mnuFile_SaveAs";
            this.mnuFile_SaveAs.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_SaveAs.Text = "Save &As...";
            this.mnuFile_SaveAs.Click += new System.EventHandler( this.mnuFile_SaveAs_Click );
            // 
            // ToolStripMenuItem2
            // 
            this.ToolStripMenuItem2.Name = "ToolStripMenuItem2";
            this.ToolStripMenuItem2.Size = new System.Drawing.Size( 149, 6 );
            // 
            // mnuFile_PageSetup
            // 
            this.mnuFile_PageSetup.Name = "mnuFile_PageSetup";
            this.mnuFile_PageSetup.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_PageSetup.Text = "Page Setup...";
            this.mnuFile_PageSetup.Click += new System.EventHandler( this.mnuFile_PageSetup_Click );
            // 
            // mnuFile_Preview
            // 
            this.mnuFile_Preview.Name = "mnuFile_Preview";
            this.mnuFile_Preview.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_Preview.Text = "Pre&view...";
            this.mnuFile_Preview.Click += new System.EventHandler( this.mnuFile_Preview_Click );
            // 
            // mnuFile_Print
            // 
            this.mnuFile_Print.Name = "mnuFile_Print";
            this.mnuFile_Print.Size = new System.Drawing.Size( 152, 22 );
            this.mnuFile_Print.Text = "&Print...";
            this.mnuFile_Print.Click += new System.EventHandler( this.mnuFile_Print_Click );
            // 
            // mnuEdit
            // 
            this.mnuEdit.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuEdit_Undo,
            this.mnuEdit_Redo,
            this.ToolStripSeparator6,
            this.mnuEdit_Find,
            this.mnuEdit_FindAndReplace,
            this.ToolStripMenuItem4,
            this.mnuEdit_SelectAll,
            this.ToolStripMenuItem5,
            this.mnuEdit_Copy,
            this.mnuEdit_Cut,
            this.mnuEdit_Paste,
            this.ToolStripMenuItem8,
            this.mnuEdit_InsertImage} );
            this.mnuEdit.Name = "mnuEdit";
            this.mnuEdit.Size = new System.Drawing.Size( 37, 20 );
            this.mnuEdit.Text = "&Edit";
            // 
            // mnuEdit_Undo
            // 
            this.mnuEdit_Undo.Name = "mnuEdit_Undo";
            this.mnuEdit_Undo.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Undo.Text = "&Undo";
            this.mnuEdit_Undo.Click += new System.EventHandler( this.mnuEdit_Undo_Click );
            // 
            // mnuEdit_Redo
            // 
            this.mnuEdit_Redo.Name = "mnuEdit_Redo";
            this.mnuEdit_Redo.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Redo.Text = "&Redo";
            this.mnuEdit_Redo.Click += new System.EventHandler( this.mnuEdit_Redo_Click );
            // 
            // ToolStripSeparator6
            // 
            this.ToolStripSeparator6.Name = "ToolStripSeparator6";
            this.ToolStripSeparator6.Size = new System.Drawing.Size( 176, 6 );
            // 
            // mnuEdit_Find
            // 
            this.mnuEdit_Find.Name = "mnuEdit_Find";
            this.mnuEdit_Find.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Find.Text = "Fi&nd...";
            this.mnuEdit_Find.Click += new System.EventHandler( this.mnuEdit_Find_Click );
            // 
            // mnuEdit_FindAndReplace
            // 
            this.mnuEdit_FindAndReplace.Name = "mnuEdit_FindAndReplace";
            this.mnuEdit_FindAndReplace.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_FindAndReplace.Text = "Find and &Replace...";
            this.mnuEdit_FindAndReplace.Click += new System.EventHandler( this.mnuEdit_FindAndReplace_Click );
            // 
            // ToolStripMenuItem4
            // 
            this.ToolStripMenuItem4.Name = "ToolStripMenuItem4";
            this.ToolStripMenuItem4.Size = new System.Drawing.Size( 176, 6 );
            // 
            // mnuEdit_SelectAll
            // 
            this.mnuEdit_SelectAll.Name = "mnuEdit_SelectAll";
            this.mnuEdit_SelectAll.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_SelectAll.Text = "Select &All";
            this.mnuEdit_SelectAll.Click += new System.EventHandler( this.mnuEdit_SelectAll_Click );
            // 
            // ToolStripMenuItem5
            // 
            this.ToolStripMenuItem5.Name = "ToolStripMenuItem5";
            this.ToolStripMenuItem5.Size = new System.Drawing.Size( 176, 6 );
            // 
            // mnuEdit_Copy
            // 
            this.mnuEdit_Copy.Name = "mnuEdit_Copy";
            this.mnuEdit_Copy.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Copy.Text = "&Copy";
            this.mnuEdit_Copy.Click += new System.EventHandler( this.mnuEdit_Copy_Click );
            // 
            // mnuEdit_Cut
            // 
            this.mnuEdit_Cut.Name = "mnuEdit_Cut";
            this.mnuEdit_Cut.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Cut.Text = "C&ut";
            this.mnuEdit_Cut.Click += new System.EventHandler( this.mnuEdit_Cut_Click );
            // 
            // mnuEdit_Paste
            // 
            this.mnuEdit_Paste.Name = "mnuEdit_Paste";
            this.mnuEdit_Paste.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_Paste.Text = "Pas&te";
            this.mnuEdit_Paste.Click += new System.EventHandler( this.mnuEdit_Paste_Click );
            // 
            // ToolStripMenuItem8
            // 
            this.ToolStripMenuItem8.Name = "ToolStripMenuItem8";
            this.ToolStripMenuItem8.Size = new System.Drawing.Size( 176, 6 );
            // 
            // mnuEdit_InsertImage
            // 
            this.mnuEdit_InsertImage.Name = "mnuEdit_InsertImage";
            this.mnuEdit_InsertImage.Size = new System.Drawing.Size( 179, 22 );
            this.mnuEdit_InsertImage.Text = "Insert Image...";
            this.mnuEdit_InsertImage.Click += new System.EventHandler( this.mnuEdit_InsertImage_Click );
            // 
            // mnuFont
            // 
            this.mnuFont.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuFont_SelectFont,
            this.ToolStripMenuItem6,
            this.mnuFont_ColorFont,
            this.ToolStripSeparator5,
            this.mnuFont_Bold,
            this.mnuFont_Italic,
            this.mnuFont_Underline,
            this.mnuFont_Normal,
            this.ToolStripMenuItem7,
            this.mnuFont_PageColor} );
            this.mnuFont.Name = "mnuFont";
            this.mnuFont.Size = new System.Drawing.Size( 41, 20 );
            this.mnuFont.Text = "F&ont";
            // 
            // mnuFont_SelectFont
            // 
            this.mnuFont_SelectFont.Name = "mnuFont_SelectFont";
            this.mnuFont_SelectFont.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_SelectFont.Text = "Se&lect Font...";
            this.mnuFont_SelectFont.Click += new System.EventHandler( this.mnuFont_SelectFont_Click );
            // 
            // ToolStripMenuItem6
            // 
            this.ToolStripMenuItem6.Name = "ToolStripMenuItem6";
            this.ToolStripMenuItem6.Size = new System.Drawing.Size( 148, 6 );
            // 
            // mnuFont_ColorFont
            // 
            this.mnuFont_ColorFont.Name = "mnuFont_ColorFont";
            this.mnuFont_ColorFont.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_ColorFont.Text = "Font &Color...";
            this.mnuFont_ColorFont.Click += new System.EventHandler( this.mnuFont_ColorFont_Click );
            // 
            // ToolStripSeparator5
            // 
            this.ToolStripSeparator5.Name = "ToolStripSeparator5";
            this.ToolStripSeparator5.Size = new System.Drawing.Size( 148, 6 );
            // 
            // mnuFont_Bold
            // 
            this.mnuFont_Bold.Name = "mnuFont_Bold";
            this.mnuFont_Bold.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_Bold.Text = "&Bold";
            this.mnuFont_Bold.Click += new System.EventHandler( this.mnuFont_Bold_Click );
            // 
            // mnuFont_Italic
            // 
            this.mnuFont_Italic.Name = "mnuFont_Italic";
            this.mnuFont_Italic.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_Italic.Text = "&Italic";
            this.mnuFont_Italic.Click += new System.EventHandler( this.mnuFont_Italic_Click );
            // 
            // mnuFont_Underline
            // 
            this.mnuFont_Underline.Name = "mnuFont_Underline";
            this.mnuFont_Underline.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_Underline.Text = "&Underline";
            this.mnuFont_Underline.Click += new System.EventHandler( this.mnuFont_Underline_Click );
            // 
            // mnuFont_Normal
            // 
            this.mnuFont_Normal.Checked = true;
            this.mnuFont_Normal.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuFont_Normal.Name = "mnuFont_Normal";
            this.mnuFont_Normal.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_Normal.Text = "&Normal";
            this.mnuFont_Normal.Click += new System.EventHandler( this.mnuFont_Normal_Click );
            // 
            // ToolStripMenuItem7
            // 
            this.ToolStripMenuItem7.Name = "ToolStripMenuItem7";
            this.ToolStripMenuItem7.Size = new System.Drawing.Size( 148, 6 );
            // 
            // mnuFont_PageColor
            // 
            this.mnuFont_PageColor.Name = "mnuFont_PageColor";
            this.mnuFont_PageColor.Size = new System.Drawing.Size( 151, 22 );
            this.mnuFont_PageColor.Text = "&Page Color...";
            this.mnuFont_PageColor.Click += new System.EventHandler( this.mnuFont_PageColor_Click );
            // 
            // mnuParagraph
            // 
            this.mnuParagraph.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuParagraph_Indent,
            this.mnuParagraph_Align} );
            this.mnuParagraph.Name = "mnuParagraph";
            this.mnuParagraph.Size = new System.Drawing.Size( 69, 20 );
            this.mnuParagraph.Text = "P&aragraph";
            // 
            // mnuParagraph_Indent
            // 
            this.mnuParagraph_Indent.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuParagraph_Indent_None,
            this.mnuParagraph_Indent_5Pts,
            this.mnuParagraph_Indent_10Pts,
            this.mnuParagraph_Indent_15Pts,
            this.mnuParagraph_Indent_20Pts} );
            this.mnuParagraph_Indent.Name = "mnuParagraph_Indent";
            this.mnuParagraph_Indent.Size = new System.Drawing.Size( 117, 22 );
            this.mnuParagraph_Indent.Text = "&Indent";
            // 
            // mnuParagraph_Indent_None
            // 
            this.mnuParagraph_Indent_None.Checked = true;
            this.mnuParagraph_Indent_None.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuParagraph_Indent_None.Name = "mnuParagraph_Indent_None";
            this.mnuParagraph_Indent_None.Size = new System.Drawing.Size( 115, 22 );
            this.mnuParagraph_Indent_None.Text = "None";
            this.mnuParagraph_Indent_None.Click += new System.EventHandler( this.mnuParagraph_Indent_None_Click );
            // 
            // mnuParagraph_Indent_5Pts
            // 
            this.mnuParagraph_Indent_5Pts.Name = "mnuParagraph_Indent_5Pts";
            this.mnuParagraph_Indent_5Pts.Size = new System.Drawing.Size( 115, 22 );
            this.mnuParagraph_Indent_5Pts.Text = "5 pts";
            this.mnuParagraph_Indent_5Pts.Click += new System.EventHandler( this.mnuParagraph_Indent_5Pts_Click );
            // 
            // mnuParagraph_Indent_10Pts
            // 
            this.mnuParagraph_Indent_10Pts.Name = "mnuParagraph_Indent_10Pts";
            this.mnuParagraph_Indent_10Pts.Size = new System.Drawing.Size( 115, 22 );
            this.mnuParagraph_Indent_10Pts.Text = "10 pts";
            this.mnuParagraph_Indent_10Pts.Click += new System.EventHandler( this.mnuParagraph_Indent_10Pts_Click );
            // 
            // mnuParagraph_Indent_15Pts
            // 
            this.mnuParagraph_Indent_15Pts.Name = "mnuParagraph_Indent_15Pts";
            this.mnuParagraph_Indent_15Pts.Size = new System.Drawing.Size( 115, 22 );
            this.mnuParagraph_Indent_15Pts.Text = "15 pts";
            this.mnuParagraph_Indent_15Pts.Click += new System.EventHandler( this.mnuParagraph_Indent_15Pts_Click );
            // 
            // mnuParagraph_Indent_20Pts
            // 
            this.mnuParagraph_Indent_20Pts.Name = "mnuParagraph_Indent_20Pts";
            this.mnuParagraph_Indent_20Pts.Size = new System.Drawing.Size( 115, 22 );
            this.mnuParagraph_Indent_20Pts.Text = "20 pts";
            this.mnuParagraph_Indent_20Pts.Click += new System.EventHandler( this.mnuParagraph_Indent_20Pts_Click );
            // 
            // mnuParagraph_Align
            // 
            this.mnuParagraph_Align.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuParagraph_Align_Left,
            this.mnuParagraph_Align_Center,
            this.mnuParagraph_Align_Right} );
            this.mnuParagraph_Align.Name = "mnuParagraph_Align";
            this.mnuParagraph_Align.Size = new System.Drawing.Size( 117, 22 );
            this.mnuParagraph_Align.Text = "&Align";
            // 
            // mnuParagraph_Align_Left
            // 
            this.mnuParagraph_Align_Left.Checked = true;
            this.mnuParagraph_Align_Left.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuParagraph_Align_Left.Name = "mnuParagraph_Align_Left";
            this.mnuParagraph_Align_Left.Size = new System.Drawing.Size( 118, 22 );
            this.mnuParagraph_Align_Left.Text = "Left";
            this.mnuParagraph_Align_Left.Click += new System.EventHandler( this.mnuParagraph_Align_Left_Click );
            // 
            // mnuParagraph_Align_Center
            // 
            this.mnuParagraph_Align_Center.Name = "mnuParagraph_Align_Center";
            this.mnuParagraph_Align_Center.Size = new System.Drawing.Size( 118, 22 );
            this.mnuParagraph_Align_Center.Text = "Center";
            this.mnuParagraph_Align_Center.Click += new System.EventHandler( this.mnuParagraph_Align_Center_Click );
            // 
            // mnuParagraph_Align_Right
            // 
            this.mnuParagraph_Align_Right.Name = "mnuParagraph_Align_Right";
            this.mnuParagraph_Align_Right.Size = new System.Drawing.Size( 118, 22 );
            this.mnuParagraph_Align_Right.Text = "Right";
            this.mnuParagraph_Align_Right.Click += new System.EventHandler( this.mnuParagraph_Align_Right_Click );
            // 
            // mnuBullets
            // 
            this.mnuBullets.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuBullets_AddBullets,
            this.mnuBullets_RemoveBullets} );
            this.mnuBullets.Name = "mnuBullets";
            this.mnuBullets.Size = new System.Drawing.Size( 50, 20 );
            this.mnuBullets.Text = "&Bullets";
            // 
            // mnuBullets_AddBullets
            // 
            this.mnuBullets_AddBullets.Name = "mnuBullets_AddBullets";
            this.mnuBullets_AddBullets.Size = new System.Drawing.Size( 158, 22 );
            this.mnuBullets_AddBullets.Text = "A&dd Bullets";
            this.mnuBullets_AddBullets.Click += new System.EventHandler( this.mnuBullets_AddBullets_Click );
            // 
            // mnuBullets_RemoveBullets
            // 
            this.mnuBullets_RemoveBullets.Name = "mnuBullets_RemoveBullets";
            this.mnuBullets_RemoveBullets.Size = new System.Drawing.Size( 158, 22 );
            this.mnuBullets_RemoveBullets.Text = "&Remove Bullets";
            this.mnuBullets_RemoveBullets.Click += new System.EventHandler( this.mnuBullets_RemoveBullets_Click );
            // 
            // tosToolbar
            // 
            this.tosToolbar.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.tbrNew,
            this.tbrOpen,
            this.tbrSave,
            this.ToolStripSeparator1,
            this.tbrFont,
            this.tbrColor,
            this.ToolStripSeparator4,
            this.tbrLeft,
            this.tbrCenter,
            this.tbrRight,
            this.ToolStripSeparator2,
            this.tbrBold,
            this.tbrItalic,
            this.tbrUnderline,
            this.ToolStripSeparator3,
            this.tbrFind} );
            this.tosToolbar.Location = new System.Drawing.Point( 0, 24 );
            this.tosToolbar.Name = "tosToolbar";
            this.tosToolbar.Size = new System.Drawing.Size( 640, 25 );
            this.tosToolbar.TabIndex = 2;
            this.tosToolbar.Text = "ToolStrip1";
            // 
            // tbrNew
            // 
            this.tbrNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrNew.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrNew.Image" ) ) );
            this.tbrNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrNew.Name = "tbrNew";
            this.tbrNew.Size = new System.Drawing.Size( 23, 22 );
            this.tbrNew.Text = "New";
            this.tbrNew.Click += new System.EventHandler( this.tbrNew_Click );
            // 
            // tbrOpen
            // 
            this.tbrOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrOpen.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrOpen.Image" ) ) );
            this.tbrOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrOpen.Name = "tbrOpen";
            this.tbrOpen.Size = new System.Drawing.Size( 23, 22 );
            this.tbrOpen.Text = "Open";
            this.tbrOpen.Click += new System.EventHandler( this.tbrOpen_Click );
            // 
            // tbrSave
            // 
            this.tbrSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrSave.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrSave.Image" ) ) );
            this.tbrSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrSave.Name = "tbrSave";
            this.tbrSave.Size = new System.Drawing.Size( 23, 22 );
            this.tbrSave.Text = "Save";
            this.tbrSave.Click += new System.EventHandler( this.tbrSave_Click );
            // 
            // ToolStripSeparator1
            // 
            this.ToolStripSeparator1.Name = "ToolStripSeparator1";
            this.ToolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
            // 
            // tbrFont
            // 
            this.tbrFont.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrFont.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrFont.Image" ) ) );
            this.tbrFont.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrFont.Name = "tbrFont";
            this.tbrFont.Size = new System.Drawing.Size( 23, 22 );
            this.tbrFont.Text = "Font";
            this.tbrFont.Click += new System.EventHandler( this.tbrFont_Click );
            // 
            // tbrColor
            // 
            this.tbrColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrColor.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrColor.Image" ) ) );
            this.tbrColor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrColor.Name = "tbrColor";
            this.tbrColor.Size = new System.Drawing.Size( 23, 22 );
            this.tbrColor.Text = "toolStripButton1";
            this.tbrColor.Click += new System.EventHandler( this.tbrColor_Click );
            // 
            // ToolStripSeparator4
            // 
            this.ToolStripSeparator4.Name = "ToolStripSeparator4";
            this.ToolStripSeparator4.Size = new System.Drawing.Size( 6, 25 );
            // 
            // tbrLeft
            // 
            this.tbrLeft.Checked = true;
            this.tbrLeft.CheckState = System.Windows.Forms.CheckState.Checked;
            this.tbrLeft.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrLeft.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrLeft.Image" ) ) );
            this.tbrLeft.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrLeft.Name = "tbrLeft";
            this.tbrLeft.Size = new System.Drawing.Size( 23, 22 );
            this.tbrLeft.Text = "Left";
            this.tbrLeft.Click += new System.EventHandler( this.tbrLeft_Click );
            // 
            // tbrCenter
            // 
            this.tbrCenter.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrCenter.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrCenter.Image" ) ) );
            this.tbrCenter.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrCenter.Name = "tbrCenter";
            this.tbrCenter.Size = new System.Drawing.Size( 23, 22 );
            this.tbrCenter.Text = "Center";
            this.tbrCenter.Click += new System.EventHandler( this.tbrCenter_Click );
            // 
            // tbrRight
            // 
            this.tbrRight.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrRight.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrRight.Image" ) ) );
            this.tbrRight.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrRight.Name = "tbrRight";
            this.tbrRight.Size = new System.Drawing.Size( 23, 22 );
            this.tbrRight.Text = "Right";
            this.tbrRight.Click += new System.EventHandler( this.tbrRight_Click );
            // 
            // ToolStripSeparator2
            // 
            this.ToolStripSeparator2.Name = "ToolStripSeparator2";
            this.ToolStripSeparator2.Size = new System.Drawing.Size( 6, 25 );
            // 
            // tbrBold
            // 
            this.tbrBold.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrBold.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrBold.Image" ) ) );
            this.tbrBold.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrBold.Name = "tbrBold";
            this.tbrBold.Size = new System.Drawing.Size( 23, 22 );
            this.tbrBold.Text = "Bold";
            this.tbrBold.Click += new System.EventHandler( this.tbrBold_Click );
            // 
            // tbrItalic
            // 
            this.tbrItalic.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrItalic.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrItalic.Image" ) ) );
            this.tbrItalic.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrItalic.Name = "tbrItalic";
            this.tbrItalic.Size = new System.Drawing.Size( 23, 22 );
            this.tbrItalic.Text = "Italic";
            this.tbrItalic.Click += new System.EventHandler( this.tbrItalic_Click );
            // 
            // tbrUnderline
            // 
            this.tbrUnderline.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrUnderline.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrUnderline.Image" ) ) );
            this.tbrUnderline.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrUnderline.Name = "tbrUnderline";
            this.tbrUnderline.Size = new System.Drawing.Size( 23, 22 );
            this.tbrUnderline.Text = "Underline";
            this.tbrUnderline.Click += new System.EventHandler( this.tbrUnderline_Click );
            // 
            // ToolStripSeparator3
            // 
            this.ToolStripSeparator3.Name = "ToolStripSeparator3";
            this.ToolStripSeparator3.Size = new System.Drawing.Size( 6, 25 );
            // 
            // tbrFind
            // 
            this.tbrFind.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbrFind.Image = ( (System.Drawing.Image)( resources.GetObject( "tbrFind.Image" ) ) );
            this.tbrFind.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbrFind.Name = "tbrFind";
            this.tbrFind.Size = new System.Drawing.Size( 23, 22 );
            this.tbrFind.Text = "Find";
            this.tbrFind.Click += new System.EventHandler( this.tbrFind_Click );
            // 
            // rtbDocument
            // 
            this.rtbDocument.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.rtbDocument.Location = new System.Drawing.Point( 0, 53 );
            this.rtbDocument.Name = "rtbDocument";
            this.rtbDocument.Size = new System.Drawing.Size( 637, 424 );
            this.rtbDocument.TabIndex = 3;
            this.rtbDocument.Text = "";
            this.rtbDocument.SelectionChanged += new System.EventHandler( this.rtbDocument_SelectionChanged );
            this.rtbDocument.LinkClicked += new System.Windows.Forms.LinkClickedEventHandler( this.rtbDocument_LinkClicked );
            // 
            // ofdDocument
            // 
            this.ofdDocument.FileName = "openFileDialog1";
            // 
            // prdDocument
            // 
            this.prdDocument.PrintPage += new System.Drawing.Printing.PrintPageEventHandler( this.prdDocument_PrintPage );
            // 
            // ppdDocument
            // 
            this.ppdDocument.AutoScrollMargin = new System.Drawing.Size( 0, 0 );
            this.ppdDocument.AutoScrollMinSize = new System.Drawing.Size( 0, 0 );
            this.ppdDocument.ClientSize = new System.Drawing.Size( 400, 300 );
            this.ppdDocument.Enabled = true;
            this.ppdDocument.Icon = ( (System.Drawing.Icon)( resources.GetObject( "ppdDocument.Icon" ) ) );
            this.ppdDocument.Name = "ppdDocument";
            this.ppdDocument.Visible = false;
            // 
            // prdDocumentDialog
            // 
            this.prdDocumentDialog.UseEXDialog = true;
            // 
            // RichTextEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add( this.rtbDocument );
            this.Controls.Add( this.tosToolbar );
            this.Controls.Add( this.mnuMain );
            this.Name = "RichTextEditor";
            this.Size = new System.Drawing.Size( 640, 480 );
            this.Load += new System.EventHandler( this.RichTextEditor_Load );
            this.mnuMain.ResumeLayout( false );
            this.mnuMain.PerformLayout();
            this.tosToolbar.ResumeLayout( false );
            this.tosToolbar.PerformLayout();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.MenuStrip mnuMain;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_New;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem1;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_Open;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_Save;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_SaveAs;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem2;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_PageSetup;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_Preview;
        internal System.Windows.Forms.ToolStripMenuItem mnuFile_Print;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Undo;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Redo;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator6;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Find;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_FindAndReplace;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem4;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_SelectAll;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem5;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Copy;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Cut;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_Paste;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem8;
        internal System.Windows.Forms.ToolStripMenuItem mnuEdit_InsertImage;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_SelectFont;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem6;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_ColorFont;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator5;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_Bold;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_Italic;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_Underline;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_Normal;
        internal System.Windows.Forms.ToolStripSeparator ToolStripMenuItem7;
        internal System.Windows.Forms.ToolStripMenuItem mnuFont_PageColor;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent_None;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent_5Pts;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent_10Pts;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent_15Pts;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Indent_20Pts;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Align;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Align_Left;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Align_Center;
        internal System.Windows.Forms.ToolStripMenuItem mnuParagraph_Align_Right;
        internal System.Windows.Forms.ToolStripMenuItem mnuBullets;
        internal System.Windows.Forms.ToolStripMenuItem mnuBullets_AddBullets;
        internal System.Windows.Forms.ToolStripMenuItem mnuBullets_RemoveBullets;
        internal System.Windows.Forms.ToolStrip tosToolbar;
        internal System.Windows.Forms.ToolStripButton tbrNew;
        internal System.Windows.Forms.ToolStripButton tbrOpen;
        internal System.Windows.Forms.ToolStripButton tbrSave;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator1;
        internal System.Windows.Forms.ToolStripButton tbrFont;
        private System.Windows.Forms.ToolStripButton tbrColor;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator4;
        internal System.Windows.Forms.ToolStripButton tbrLeft;
        internal System.Windows.Forms.ToolStripButton tbrCenter;
        internal System.Windows.Forms.ToolStripButton tbrRight;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator2;
        internal System.Windows.Forms.ToolStripButton tbrBold;
        internal System.Windows.Forms.ToolStripButton tbrItalic;
        internal System.Windows.Forms.ToolStripButton tbrUnderline;
        internal System.Windows.Forms.ToolStripSeparator ToolStripSeparator3;
        internal System.Windows.Forms.ToolStripButton tbrFind;
        private System.Windows.Forms.OpenFileDialog ofdDocument;
        private System.Windows.Forms.SaveFileDialog sfdDocument;
        private System.Windows.Forms.PageSetupDialog psdDocument;
        private System.Windows.Forms.PrintPreviewDialog ppdDocument;
        private System.Windows.Forms.PrintDialog prdDocumentDialog;
        internal System.Drawing.Printing.PrintDocument prdDocument;
        internal ExtendedRichTextBox.RichTextBoxPrintCtrl rtbDocument;
        private System.Windows.Forms.FontDialog ftdDocument;
        private System.Windows.Forms.ColorDialog cldDocument;
    }
}
