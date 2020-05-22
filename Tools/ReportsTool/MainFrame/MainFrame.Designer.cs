namespace ReportsTool
{
    partial class MainFrame
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainFrame));
            this.tsc_MainFrame = new System.Windows.Forms.ToolStripContainer();
            this.web_MainDoc = new System.Windows.Forms.WebBrowser();
            this.mnu_Frame = new System.Windows.Forms.MenuStrip();
            this.tos_Tools = new System.Windows.Forms.ToolStrip();
            this.mnu_File = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_Import = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_Quit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_Settings = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_StyleAndFonts = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_ReportType = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_ReportTypeTextOnly = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_ReportTypeTextWithTitles = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnu_Language = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_LanguageEnglish = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_LanguageFrancais = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_LanguageDeutsh = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_Tools = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_ConvertTo = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_ConvertToWord = new System.Windows.Forms.ToolStripMenuItem();
            this.tsb_ConvertToWord = new System.Windows.Forms.ToolStripButton();
            this.tsc_MainFrame.ContentPanel.SuspendLayout();
            this.tsc_MainFrame.TopToolStripPanel.SuspendLayout();
            this.tsc_MainFrame.SuspendLayout();
            this.mnu_Frame.SuspendLayout();
            this.tos_Tools.SuspendLayout();
            this.SuspendLayout();
            // 
            // tsc_MainFrame
            // 
            // 
            // tsc_MainFrame.ContentPanel
            // 
            resources.ApplyResources(this.tsc_MainFrame.ContentPanel, "tsc_MainFrame.ContentPanel");
            this.tsc_MainFrame.ContentPanel.Controls.Add(this.web_MainDoc);
            resources.ApplyResources(this.tsc_MainFrame, "tsc_MainFrame");
            this.tsc_MainFrame.Name = "tsc_MainFrame";
            // 
            // tsc_MainFrame.TopToolStripPanel
            // 
            this.tsc_MainFrame.TopToolStripPanel.Controls.Add(this.mnu_Frame);
            this.tsc_MainFrame.TopToolStripPanel.Controls.Add(this.tos_Tools);
            // 
            // web_MainDoc
            // 
            this.web_MainDoc.AllowWebBrowserDrop = false;
            resources.ApplyResources(this.web_MainDoc, "web_MainDoc");
            this.web_MainDoc.MinimumSize = new System.Drawing.Size(20, 20);
            this.web_MainDoc.Name = "web_MainDoc";
            // 
            // mnu_Frame
            // 
            resources.ApplyResources(this.mnu_Frame, "mnu_Frame");
            this.mnu_Frame.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_File,
            this.mnu_Settings,
            this.mnu_Tools});
            this.mnu_Frame.Name = "mnu_Frame";
            // 
            // tos_Tools
            // 
            resources.ApplyResources(this.tos_Tools, "tos_Tools");
            this.tos_Tools.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsb_ConvertToWord});
            this.tos_Tools.Name = "tos_Tools";
            // 
            // mnu_File
            // 
            this.mnu_File.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_Import,
            this.mnu_Quit});
            this.mnu_File.Image = global::ReportsTool.Properties.Resources.gnome_dev_floppy;
            this.mnu_File.Name = "mnu_File";
            resources.ApplyResources(this.mnu_File, "mnu_File");
            // 
            // mnu_Import
            // 
            this.mnu_Import.Image = global::ReportsTool.Properties.Resources.stock_new_html;
            this.mnu_Import.Name = "mnu_Import";
            resources.ApplyResources(this.mnu_Import, "mnu_Import");
            this.mnu_Import.Click += new System.EventHandler(this.mnu_Import_Click);
            // 
            // mnu_Quit
            // 
            this.mnu_Quit.Image = global::ReportsTool.Properties.Resources.stock_exit;
            this.mnu_Quit.Name = "mnu_Quit";
            resources.ApplyResources(this.mnu_Quit, "mnu_Quit");
            this.mnu_Quit.Click += new System.EventHandler(this.mnu_Quit_Click);
            // 
            // mnu_Settings
            // 
            this.mnu_Settings.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_StyleAndFonts,
            this.mnu_ReportType,
            this.toolStripMenuItem1,
            this.mnu_Language});
            this.mnu_Settings.Image = global::ReportsTool.Properties.Resources.gnome_settings;
            this.mnu_Settings.Name = "mnu_Settings";
            resources.ApplyResources(this.mnu_Settings, "mnu_Settings");
            // 
            // mnu_StyleAndFonts
            // 
            this.mnu_StyleAndFonts.Image = global::ReportsTool.Properties.Resources.stock_font;
            this.mnu_StyleAndFonts.Name = "mnu_StyleAndFonts";
            resources.ApplyResources(this.mnu_StyleAndFonts, "mnu_StyleAndFonts");
            this.mnu_StyleAndFonts.Click += new System.EventHandler(this.mnu_StyleAndFonts_Click);
            // 
            // mnu_ReportType
            // 
            this.mnu_ReportType.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_ReportTypeTextOnly,
            this.mnu_ReportTypeTextWithTitles});
            this.mnu_ReportType.Name = "mnu_ReportType";
            resources.ApplyResources(this.mnu_ReportType, "mnu_ReportType");
            // 
            // mnu_ReportTypeTextOnly
            // 
            this.mnu_ReportTypeTextOnly.Name = "mnu_ReportTypeTextOnly";
            resources.ApplyResources(this.mnu_ReportTypeTextOnly, "mnu_ReportTypeTextOnly");
            // 
            // mnu_ReportTypeTextWithTitles
            // 
            this.mnu_ReportTypeTextWithTitles.Name = "mnu_ReportTypeTextWithTitles";
            resources.ApplyResources(this.mnu_ReportTypeTextWithTitles, "mnu_ReportTypeTextWithTitles");
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            resources.ApplyResources(this.toolStripMenuItem1, "toolStripMenuItem1");
            // 
            // mnu_Language
            // 
            this.mnu_Language.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_LanguageEnglish,
            this.mnu_LanguageFrancais,
            this.mnu_LanguageDeutsh});
            this.mnu_Language.Image = global::ReportsTool.Properties.Resources.config_language;
            this.mnu_Language.Name = "mnu_Language";
            resources.ApplyResources(this.mnu_Language, "mnu_Language");
            // 
            // mnu_LanguageEnglish
            // 
            this.mnu_LanguageEnglish.Image = global::ReportsTool.Properties.Resources.English;
            resources.ApplyResources(this.mnu_LanguageEnglish, "mnu_LanguageEnglish");
            this.mnu_LanguageEnglish.Name = "mnu_LanguageEnglish";
            this.mnu_LanguageEnglish.Click += new System.EventHandler(this.mnu_LanguageEnglish_Click);
            // 
            // mnu_LanguageFrancais
            // 
            this.mnu_LanguageFrancais.Image = global::ReportsTool.Properties.Resources.Français;
            this.mnu_LanguageFrancais.Name = "mnu_LanguageFrancais";
            resources.ApplyResources(this.mnu_LanguageFrancais, "mnu_LanguageFrancais");
            this.mnu_LanguageFrancais.Click += new System.EventHandler(this.mnu_LanguageFrancais_Click);
            // 
            // mnu_LanguageDeutsh
            // 
            this.mnu_LanguageDeutsh.Image = global::ReportsTool.Properties.Resources.Deutsh;
            this.mnu_LanguageDeutsh.Name = "mnu_LanguageDeutsh";
            resources.ApplyResources(this.mnu_LanguageDeutsh, "mnu_LanguageDeutsh");
            this.mnu_LanguageDeutsh.Click += new System.EventHandler(this.mnu_LanguageDeutsh_Click);
            // 
            // mnu_Tools
            // 
            this.mnu_Tools.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_ConvertTo});
            this.mnu_Tools.Image = global::ReportsTool.Properties.Resources.gnome_run;
            this.mnu_Tools.Name = "mnu_Tools";
            resources.ApplyResources(this.mnu_Tools, "mnu_Tools");
            // 
            // mnu_ConvertTo
            // 
            this.mnu_ConvertTo.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnu_ConvertToWord});
            this.mnu_ConvertTo.Image = global::ReportsTool.Properties.Resources.stock_task_assigned_to;
            this.mnu_ConvertTo.Name = "mnu_ConvertTo";
            resources.ApplyResources(this.mnu_ConvertTo, "mnu_ConvertTo");
            // 
            // mnu_ConvertToWord
            // 
            this.mnu_ConvertToWord.Image = global::ReportsTool.Properties.Resources.gnome_mime_application_msword;
            this.mnu_ConvertToWord.Name = "mnu_ConvertToWord";
            resources.ApplyResources(this.mnu_ConvertToWord, "mnu_ConvertToWord");
            this.mnu_ConvertToWord.Click += new System.EventHandler(this.mnu_ConvertToWord_Click);
            // 
            // tsb_ConvertToWord
            // 
            this.tsb_ConvertToWord.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsb_ConvertToWord.Image = global::ReportsTool.Properties.Resources.gnome_mime_application_msword;
            resources.ApplyResources(this.tsb_ConvertToWord, "tsb_ConvertToWord");
            this.tsb_ConvertToWord.Name = "tsb_ConvertToWord";
            this.tsb_ConvertToWord.Click += new System.EventHandler(this.tsb_ConvertToWord_Click);
            // 
            // MainFrame
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tsc_MainFrame);
            this.Name = "MainFrame";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainFrame_Load);
            this.tsc_MainFrame.ContentPanel.ResumeLayout(false);
            this.tsc_MainFrame.TopToolStripPanel.ResumeLayout(false);
            this.tsc_MainFrame.TopToolStripPanel.PerformLayout();
            this.tsc_MainFrame.ResumeLayout(false);
            this.tsc_MainFrame.PerformLayout();
            this.mnu_Frame.ResumeLayout(false);
            this.mnu_Frame.PerformLayout();
            this.tos_Tools.ResumeLayout(false);
            this.tos_Tools.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MenuStrip mnu_Frame;
        private System.Windows.Forms.ToolStripMenuItem mnu_File;
        private System.Windows.Forms.ToolStripMenuItem mnu_Import;
        private System.Windows.Forms.ToolStripMenuItem mnu_Quit;
        private System.Windows.Forms.ToolStripMenuItem mnu_Tools;
        private System.Windows.Forms.ToolStripMenuItem mnu_ConvertTo;
        private System.Windows.Forms.WebBrowser web_MainDoc;
        private System.Windows.Forms.ToolStrip tos_Tools;
        private System.Windows.Forms.ToolStripButton tsb_ConvertToWord;
        private System.Windows.Forms.ToolStripMenuItem mnu_ConvertToWord;
        private System.Windows.Forms.ToolStripMenuItem mnu_Settings;
        private System.Windows.Forms.ToolStripMenuItem mnu_StyleAndFonts;
        private System.Windows.Forms.ToolStripMenuItem mnu_ReportType;
        private System.Windows.Forms.ToolStripMenuItem mnu_ReportTypeTextOnly;
        private System.Windows.Forms.ToolStripMenuItem mnu_ReportTypeTextWithTitles;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem mnu_Language;
        private System.Windows.Forms.ToolStripMenuItem mnu_LanguageEnglish;
        private System.Windows.Forms.ToolStripMenuItem mnu_LanguageFrancais;
        private System.Windows.Forms.ToolStripMenuItem mnu_LanguageDeutsh;
        private System.Windows.Forms.ToolStripContainer tsc_MainFrame;

    }
}

