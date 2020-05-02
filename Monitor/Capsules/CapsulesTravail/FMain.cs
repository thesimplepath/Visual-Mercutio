using System;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using CapsulesTravailDLL;

namespace CapsulesTravail
{
    /// <author>Cédric Michelet</author>
    /// <date>09.06.2005</date>
    /// <version>1.0 made by Icare Institute, CH-Sierre</version>
    /// <modification>
    ///		<author></author>
    ///		<date></date>
    ///		<description></description>
    /// </modification>
    /// <summary>
    /// Form to handle the offline forms (capsules de travail) - work on PC
    /// </summary>
    public class FMain : System.Windows.Forms.Form
    {
        private CapsulesXML _cxml;
        private bool _trackerIsInstalled = false;
        private bool _fileHasBeenModified;
        private System.Windows.Forms.ListBox lbFiles;
        private System.Windows.Forms.DataGrid dgTasks;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGrid dgRules;
        private System.Windows.Forms.DataGrid dgDecisions;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleTasks;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnTasksName;
        private System.Windows.Forms.DataGridBoolColumn dataGridBoolColumnTasksValue;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleRules;
        private System.Windows.Forms.DataGridBoolColumn dataGridBoolColumnRulesValue;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnRulesName;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleDecisions;
        private System.Windows.Forms.DataGridBoolColumn dataGridBoolColumnDecisionsValue;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnDecisionsName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lCaseName;
        private System.Windows.Forms.Button bSave;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lProcName;
        private System.Windows.Forms.DataGrid dgFiles;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleFiles;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnFilesName;
        private System.Windows.Forms.TabControl tabControlPages;
        private System.Windows.Forms.TabPage tabPageLivrables;
        private System.Windows.Forms.TabPage tabPageElements;
        private System.Windows.Forms.DataGrid dgLivrablesInput;
        private System.Windows.Forms.DataGrid dgLivrablesLateraux;
        private System.Windows.Forms.DataGrid dgLivrablesOutput;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleLivrablesInput;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesInputName;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleLivrablesLateraux;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesLaterauxName;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleLivrablesOutput;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesOutputName;
        private System.Windows.Forms.TabPage tabPageMessage;
        private System.Windows.Forms.Label lInfos;
        private System.Windows.Forms.Button btSetToWait;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesLaterauxProcname;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesLaterauxDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesOutputProcname;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesOutputDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesInputDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnFilesLogin;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnFilesDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnTasksDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnDecisionsDate;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnRulesDate;
        private System.Windows.Forms.Button bAttributsInput;
        private System.Windows.Forms.TabPage tabPageApplications;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleApplications;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnApplicationsName;
        private System.Windows.Forms.Button bNotConform;
        private System.Windows.Forms.Button bBackToChief;
        private System.Windows.Forms.Button bTerminate;
        private System.Windows.Forms.Button btSynchronise;
        private System.Windows.Forms.Button btSynchroniseAll;
        private System.Windows.Forms.Button bAttributsLateral;
        private System.Windows.Forms.Button bAttributsOutput;
        private System.Windows.Forms.DataGrid dgApplications;
        private System.Windows.Forms.Button btnLaunch;
        private System.Windows.Forms.Button btDelete;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesOutputRequested;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnLivrablesLaterauxRequested;
        private System.Windows.Forms.Button btLaunchLateral;
        private System.Windows.Forms.Button btLaunchOutput;

        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.Container components = null;

        public FMain()
        {
            // required for Windows Form Designer support
            InitializeComponent();

            // initialise local variable
            _cxml = new CapsulesXML() ;
        }

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if( disposing )
                if (components != null)
                    components.Dispose();

            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FMain));
            this.lbFiles = new System.Windows.Forms.ListBox();
            this.dgTasks = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleTasks = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridBoolColumnTasksValue = new System.Windows.Forms.DataGridBoolColumn();
            this.dataGridTextBoxColumnTasksName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnTasksDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.label1 = new System.Windows.Forms.Label();
            this.dgRules = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleRules = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridBoolColumnRulesValue = new System.Windows.Forms.DataGridBoolColumn();
            this.dataGridTextBoxColumnRulesName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnRulesDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dgDecisions = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleDecisions = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridBoolColumnDecisionsValue = new System.Windows.Forms.DataGridBoolColumn();
            this.dataGridTextBoxColumnDecisionsName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnDecisionsDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.label2 = new System.Windows.Forms.Label();
            this.lCaseName = new System.Windows.Forms.Label();
            this.bSave = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.lProcName = new System.Windows.Forms.Label();
            this.dgFiles = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleFiles = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnFilesName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnFilesLogin = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnFilesDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.tabControlPages = new System.Windows.Forms.TabControl();
            this.tabPageLivrables = new System.Windows.Forms.TabPage();
            this.btLaunchOutput = new System.Windows.Forms.Button();
            this.btLaunchLateral = new System.Windows.Forms.Button();
            this.bAttributsOutput = new System.Windows.Forms.Button();
            this.bAttributsLateral = new System.Windows.Forms.Button();
            this.bAttributsInput = new System.Windows.Forms.Button();
            this.dgLivrablesOutput = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleLivrablesOutput = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnLivrablesOutputRequested = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesOutputName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesOutputProcname = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesOutputDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dgLivrablesLateraux = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleLivrablesLateraux = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnLivrablesLaterauxRequested = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesLaterauxName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesLaterauxProcname = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesLaterauxDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dgLivrablesInput = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleLivrablesInput = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnLivrablesInputName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnLivrablesInputDate = new System.Windows.Forms.DataGridTextBoxColumn();
            this.tabPageElements = new System.Windows.Forms.TabPage();
            this.tabPageMessage = new System.Windows.Forms.TabPage();
            this.lInfos = new System.Windows.Forms.Label();
            this.tabPageApplications = new System.Windows.Forms.TabPage();
            this.btnLaunch = new System.Windows.Forms.Button();
            this.dgApplications = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleApplications = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnApplicationsName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.btSetToWait = new System.Windows.Forms.Button();
            this.bNotConform = new System.Windows.Forms.Button();
            this.bBackToChief = new System.Windows.Forms.Button();
            this.bTerminate = new System.Windows.Forms.Button();
            this.btSynchronise = new System.Windows.Forms.Button();
            this.btSynchroniseAll = new System.Windows.Forms.Button();
            this.btDelete = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgTasks)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgRules)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgDecisions)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgFiles)).BeginInit();
            this.tabControlPages.SuspendLayout();
            this.tabPageLivrables.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesOutput)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesLateraux)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesInput)).BeginInit();
            this.tabPageElements.SuspendLayout();
            this.tabPageMessage.SuspendLayout();
            this.tabPageApplications.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgApplications)).BeginInit();
            this.SuspendLayout();
            // 
            // lbFiles
            // 
            this.lbFiles.Location = new System.Drawing.Point(0, 48);
            this.lbFiles.Name = "lbFiles";
            this.lbFiles.Size = new System.Drawing.Size(176, 485);
            this.lbFiles.TabIndex = 0;
            this.lbFiles.SelectedIndexChanged += new System.EventHandler(this.lbFiles_SelectedIndexChanged);
            // 
            // dgTasks
            // 
            this.dgTasks.AllowSorting = false;
            this.dgTasks.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgTasks.CaptionText = "Tâches";
            this.dgTasks.ColumnHeadersVisible = false;
            this.dgTasks.DataMember = "";
            this.dgTasks.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgTasks.Location = new System.Drawing.Point(8, 8);
            this.dgTasks.Name = "dgTasks";
            this.dgTasks.Size = new System.Drawing.Size(600, 120);
            this.dgTasks.TabIndex = 1;
            this.dgTasks.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleTasks});
            // 
            // dataGridTableStyleTasks
            // 
            this.dataGridTableStyleTasks.ColumnHeadersVisible = false;
            this.dataGridTableStyleTasks.DataGrid = this.dgTasks;
            this.dataGridTableStyleTasks.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridBoolColumnTasksValue,
            this.dataGridTextBoxColumnTasksName,
            this.dataGridTextBoxColumnTasksDate});
            this.dataGridTableStyleTasks.HeaderBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.dataGridTableStyleTasks.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleTasks.MappingName = "ELEMENTS";
            this.dataGridTableStyleTasks.RowHeadersVisible = false;
            // 
            // dataGridBoolColumnTasksValue
            // 
            this.dataGridBoolColumnTasksValue.AllowNull = false;
            this.dataGridBoolColumnTasksValue.MappingName = "mstate";
            this.dataGridBoolColumnTasksValue.Width = 75;
            // 
            // dataGridTextBoxColumnTasksName
            // 
            this.dataGridTextBoxColumnTasksName.Format = "";
            this.dataGridTextBoxColumnTasksName.FormatInfo = null;
            this.dataGridTextBoxColumnTasksName.MappingName = "mvalue";
            this.dataGridTextBoxColumnTasksName.ReadOnly = true;
            this.dataGridTextBoxColumnTasksName.Width = 250;
            // 
            // dataGridTextBoxColumnTasksDate
            // 
            this.dataGridTextBoxColumnTasksDate.Format = "";
            this.dataGridTextBoxColumnTasksDate.FormatInfo = null;
            this.dataGridTextBoxColumnTasksDate.MappingName = "mdated";
            this.dataGridTextBoxColumnTasksDate.Width = 75;
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.DarkOrange;
            this.label1.Dock = System.Windows.Forms.DockStyle.Top;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(832, 32);
            this.label1.TabIndex = 5;
            this.label1.Text = "Capsules de travail";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // dgRules
            // 
            this.dgRules.AllowSorting = false;
            this.dgRules.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgRules.CaptionText = "Règles";
            this.dgRules.ColumnHeadersVisible = false;
            this.dgRules.DataMember = "";
            this.dgRules.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgRules.Location = new System.Drawing.Point(8, 248);
            this.dgRules.Name = "dgRules";
            this.dgRules.RowHeadersVisible = false;
            this.dgRules.Size = new System.Drawing.Size(600, 112);
            this.dgRules.TabIndex = 3;
            this.dgRules.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleRules});
            // 
            // dataGridTableStyleRules
            // 
            this.dataGridTableStyleRules.DataGrid = this.dgRules;
            this.dataGridTableStyleRules.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridBoolColumnRulesValue,
            this.dataGridTextBoxColumnRulesName,
            this.dataGridTextBoxColumnRulesDate});
            this.dataGridTableStyleRules.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleRules.MappingName = "ELEMENTS";
            this.dataGridTableStyleRules.RowHeadersVisible = false;
            // 
            // dataGridBoolColumnRulesValue
            // 
            this.dataGridBoolColumnRulesValue.AllowNull = false;
            this.dataGridBoolColumnRulesValue.MappingName = "mstate";
            this.dataGridBoolColumnRulesValue.Width = 75;
            // 
            // dataGridTextBoxColumnRulesName
            // 
            this.dataGridTextBoxColumnRulesName.Format = "";
            this.dataGridTextBoxColumnRulesName.FormatInfo = null;
            this.dataGridTextBoxColumnRulesName.MappingName = "mvalue";
            this.dataGridTextBoxColumnRulesName.ReadOnly = true;
            this.dataGridTextBoxColumnRulesName.Width = 250;
            // 
            // dataGridTextBoxColumnRulesDate
            // 
            this.dataGridTextBoxColumnRulesDate.Format = "";
            this.dataGridTextBoxColumnRulesDate.FormatInfo = null;
            this.dataGridTextBoxColumnRulesDate.MappingName = "mdated";
            this.dataGridTextBoxColumnRulesDate.Width = 75;
            // 
            // dgDecisions
            // 
            this.dgDecisions.AllowSorting = false;
            this.dgDecisions.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgDecisions.CaptionText = "Décisions";
            this.dgDecisions.ColumnHeadersVisible = false;
            this.dgDecisions.DataMember = "";
            this.dgDecisions.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgDecisions.Location = new System.Drawing.Point(8, 136);
            this.dgDecisions.Name = "dgDecisions";
            this.dgDecisions.RowHeadersVisible = false;
            this.dgDecisions.Size = new System.Drawing.Size(600, 104);
            this.dgDecisions.TabIndex = 2;
            this.dgDecisions.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleDecisions});
            // 
            // dataGridTableStyleDecisions
            // 
            this.dataGridTableStyleDecisions.DataGrid = this.dgDecisions;
            this.dataGridTableStyleDecisions.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridBoolColumnDecisionsValue,
            this.dataGridTextBoxColumnDecisionsName,
            this.dataGridTextBoxColumnDecisionsDate});
            this.dataGridTableStyleDecisions.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleDecisions.MappingName = "ELEMENTS";
            this.dataGridTableStyleDecisions.RowHeadersVisible = false;
            // 
            // dataGridBoolColumnDecisionsValue
            // 
            this.dataGridBoolColumnDecisionsValue.AllowNull = false;
            this.dataGridBoolColumnDecisionsValue.MappingName = "mstate";
            this.dataGridBoolColumnDecisionsValue.Width = 75;
            // 
            // dataGridTextBoxColumnDecisionsName
            // 
            this.dataGridTextBoxColumnDecisionsName.Format = "";
            this.dataGridTextBoxColumnDecisionsName.FormatInfo = null;
            this.dataGridTextBoxColumnDecisionsName.MappingName = "mvalue";
            this.dataGridTextBoxColumnDecisionsName.ReadOnly = true;
            this.dataGridTextBoxColumnDecisionsName.Width = 250;
            // 
            // dataGridTextBoxColumnDecisionsDate
            // 
            this.dataGridTextBoxColumnDecisionsDate.Format = "";
            this.dataGridTextBoxColumnDecisionsDate.FormatInfo = null;
            this.dataGridTextBoxColumnDecisionsDate.MappingName = "mdated";
            this.dataGridTextBoxColumnDecisionsDate.Width = 75;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(208, 40);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Cas :";
            // 
            // lCaseName
            // 
            this.lCaseName.Location = new System.Drawing.Point(280, 40);
            this.lCaseName.Name = "lCaseName";
            this.lCaseName.Size = new System.Drawing.Size(440, 16);
            this.lCaseName.TabIndex = 7;
            // 
            // bSave
            // 
            this.bSave.Location = new System.Drawing.Point(192, 608);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(75, 23);
            this.bSave.TabIndex = 4;
            this.bSave.Text = "Enregistrer";
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(208, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(100, 16);
            this.label3.TabIndex = 8;
            this.label3.Text = "Procédure :";
            // 
            // lProcName
            // 
            this.lProcName.Location = new System.Drawing.Point(280, 64);
            this.lProcName.Name = "lProcName";
            this.lProcName.Size = new System.Drawing.Size(432, 23);
            this.lProcName.TabIndex = 9;
            // 
            // dgFiles
            // 
            this.dgFiles.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgFiles.CaptionText = "Fichiers";
            this.dgFiles.ColumnHeadersVisible = false;
            this.dgFiles.DataMember = "";
            this.dgFiles.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgFiles.Location = new System.Drawing.Point(8, 368);
            this.dgFiles.Name = "dgFiles";
            this.dgFiles.Size = new System.Drawing.Size(600, 112);
            this.dgFiles.TabIndex = 10;
            this.dgFiles.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleFiles});
            // 
            // dataGridTableStyleFiles
            // 
            this.dataGridTableStyleFiles.ColumnHeadersVisible = false;
            this.dataGridTableStyleFiles.DataGrid = this.dgFiles;
            this.dataGridTableStyleFiles.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnFilesName,
            this.dataGridTextBoxColumnFilesLogin,
            this.dataGridTextBoxColumnFilesDate});
            this.dataGridTableStyleFiles.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleFiles.MappingName = "ELEMENTS";
            this.dataGridTableStyleFiles.ReadOnly = true;
            this.dataGridTableStyleFiles.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnFilesName
            // 
            this.dataGridTextBoxColumnFilesName.Format = "";
            this.dataGridTextBoxColumnFilesName.FormatInfo = null;
            this.dataGridTextBoxColumnFilesName.MappingName = "name";
            this.dataGridTextBoxColumnFilesName.ReadOnly = true;
            this.dataGridTextBoxColumnFilesName.Width = 325;
            // 
            // dataGridTextBoxColumnFilesLogin
            // 
            this.dataGridTextBoxColumnFilesLogin.Format = "";
            this.dataGridTextBoxColumnFilesLogin.FormatInfo = null;
            this.dataGridTextBoxColumnFilesLogin.MappingName = "login";
            this.dataGridTextBoxColumnFilesLogin.Width = 75;
            // 
            // dataGridTextBoxColumnFilesDate
            // 
            this.dataGridTextBoxColumnFilesDate.Format = "";
            this.dataGridTextBoxColumnFilesDate.FormatInfo = null;
            this.dataGridTextBoxColumnFilesDate.MappingName = "mdated";
            this.dataGridTextBoxColumnFilesDate.Width = 75;
            // 
            // tabControlPages
            // 
            this.tabControlPages.Controls.Add(this.tabPageLivrables);
            this.tabControlPages.Controls.Add(this.tabPageElements);
            this.tabControlPages.Controls.Add(this.tabPageMessage);
            this.tabControlPages.Controls.Add(this.tabPageApplications);
            this.tabControlPages.Location = new System.Drawing.Point(184, 90);
            this.tabControlPages.Name = "tabControlPages";
            this.tabControlPages.SelectedIndex = 0;
            this.tabControlPages.Size = new System.Drawing.Size(632, 510);
            this.tabControlPages.TabIndex = 11;
            this.tabControlPages.SelectedIndexChanged += new System.EventHandler(this.tabControlPages_SelectedIndexChanged);
            // 
            // tabPageLivrables
            // 
            this.tabPageLivrables.Controls.Add(this.btLaunchOutput);
            this.tabPageLivrables.Controls.Add(this.btLaunchLateral);
            this.tabPageLivrables.Controls.Add(this.bAttributsOutput);
            this.tabPageLivrables.Controls.Add(this.bAttributsLateral);
            this.tabPageLivrables.Controls.Add(this.bAttributsInput);
            this.tabPageLivrables.Controls.Add(this.dgLivrablesOutput);
            this.tabPageLivrables.Controls.Add(this.dgLivrablesLateraux);
            this.tabPageLivrables.Controls.Add(this.dgLivrablesInput);
            this.tabPageLivrables.Location = new System.Drawing.Point(4, 22);
            this.tabPageLivrables.Name = "tabPageLivrables";
            this.tabPageLivrables.Size = new System.Drawing.Size(624, 484);
            this.tabPageLivrables.TabIndex = 0;
            this.tabPageLivrables.Text = "Livrables";
            // 
            // btLaunchOutput
            // 
            this.btLaunchOutput.Location = new System.Drawing.Point(104, 456);
            this.btLaunchOutput.Name = "btLaunchOutput";
            this.btLaunchOutput.Size = new System.Drawing.Size(75, 23);
            this.btLaunchOutput.TabIndex = 7;
            this.btLaunchOutput.Text = "Lancer";
            this.btLaunchOutput.Click += new System.EventHandler(this.btLaunchOutput_Click);
            // 
            // btLaunchLateral
            // 
            this.btLaunchLateral.Location = new System.Drawing.Point(104, 296);
            this.btLaunchLateral.Name = "btLaunchLateral";
            this.btLaunchLateral.Size = new System.Drawing.Size(75, 23);
            this.btLaunchLateral.TabIndex = 6;
            this.btLaunchLateral.Text = "Lancer";
            this.btLaunchLateral.Click += new System.EventHandler(this.btLaunchLateral_Click);
            // 
            // bAttributsOutput
            // 
            this.bAttributsOutput.Location = new System.Drawing.Point(8, 456);
            this.bAttributsOutput.Name = "bAttributsOutput";
            this.bAttributsOutput.Size = new System.Drawing.Size(75, 23);
            this.bAttributsOutput.TabIndex = 5;
            this.bAttributsOutput.Text = "Attributs";
            this.bAttributsOutput.Click += new System.EventHandler(this.bAttributsOutput_Click);
            // 
            // bAttributsLateral
            // 
            this.bAttributsLateral.Location = new System.Drawing.Point(8, 296);
            this.bAttributsLateral.Name = "bAttributsLateral";
            this.bAttributsLateral.Size = new System.Drawing.Size(75, 23);
            this.bAttributsLateral.TabIndex = 4;
            this.bAttributsLateral.Text = "Attributs";
            this.bAttributsLateral.Click += new System.EventHandler(this.bAttributsLateral_Click);
            // 
            // bAttributsInput
            // 
            this.bAttributsInput.Location = new System.Drawing.Point(8, 142);
            this.bAttributsInput.Name = "bAttributsInput";
            this.bAttributsInput.Size = new System.Drawing.Size(75, 23);
            this.bAttributsInput.TabIndex = 3;
            this.bAttributsInput.Text = "Attributs";
            this.bAttributsInput.Click += new System.EventHandler(this.bAttributsInput_Click);
            // 
            // dgLivrablesOutput
            // 
            this.dgLivrablesOutput.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgLivrablesOutput.CaptionText = "Livrables en sortie";
            this.dgLivrablesOutput.ColumnHeadersVisible = false;
            this.dgLivrablesOutput.DataMember = "";
            this.dgLivrablesOutput.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgLivrablesOutput.Location = new System.Drawing.Point(8, 328);
            this.dgLivrablesOutput.Name = "dgLivrablesOutput";
            this.dgLivrablesOutput.Size = new System.Drawing.Size(600, 120);
            this.dgLivrablesOutput.TabIndex = 2;
            this.dgLivrablesOutput.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleLivrablesOutput});
            // 
            // dataGridTableStyleLivrablesOutput
            // 
            this.dataGridTableStyleLivrablesOutput.ColumnHeadersVisible = false;
            this.dataGridTableStyleLivrablesOutput.DataGrid = this.dgLivrablesOutput;
            this.dataGridTableStyleLivrablesOutput.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnLivrablesOutputRequested,
            this.dataGridTextBoxColumnLivrablesOutputName,
            this.dataGridTextBoxColumnLivrablesOutputProcname,
            this.dataGridTextBoxColumnLivrablesOutputDate});
            this.dataGridTableStyleLivrablesOutput.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleLivrablesOutput.MappingName = "ELEMENTS";
            this.dataGridTableStyleLivrablesOutput.ReadOnly = true;
            this.dataGridTableStyleLivrablesOutput.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnLivrablesOutputRequested
            // 
            this.dataGridTextBoxColumnLivrablesOutputRequested.Format = "";
            this.dataGridTextBoxColumnLivrablesOutputRequested.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesOutputRequested.MappingName = "requested";
            this.dataGridTextBoxColumnLivrablesOutputRequested.Width = 75;
            // 
            // dataGridTextBoxColumnLivrablesOutputName
            // 
            this.dataGridTextBoxColumnLivrablesOutputName.Format = "";
            this.dataGridTextBoxColumnLivrablesOutputName.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesOutputName.MappingName = "name";
            this.dataGridTextBoxColumnLivrablesOutputName.Width = 375;
            // 
            // dataGridTextBoxColumnLivrablesOutputProcname
            // 
            this.dataGridTextBoxColumnLivrablesOutputProcname.Format = "";
            this.dataGridTextBoxColumnLivrablesOutputProcname.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesOutputProcname.MappingName = "procname";
            this.dataGridTextBoxColumnLivrablesOutputProcname.Width = 75;
            // 
            // dataGridTextBoxColumnLivrablesOutputDate
            // 
            this.dataGridTextBoxColumnLivrablesOutputDate.Format = "";
            this.dataGridTextBoxColumnLivrablesOutputDate.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesOutputDate.MappingName = "mdated";
            this.dataGridTextBoxColumnLivrablesOutputDate.Width = 75;
            // 
            // dgLivrablesLateraux
            // 
            this.dgLivrablesLateraux.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgLivrablesLateraux.CaptionText = "Livrables latéraux";
            this.dgLivrablesLateraux.ColumnHeadersVisible = false;
            this.dgLivrablesLateraux.DataMember = "";
            this.dgLivrablesLateraux.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgLivrablesLateraux.Location = new System.Drawing.Point(8, 168);
            this.dgLivrablesLateraux.Name = "dgLivrablesLateraux";
            this.dgLivrablesLateraux.Size = new System.Drawing.Size(600, 120);
            this.dgLivrablesLateraux.TabIndex = 1;
            this.dgLivrablesLateraux.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleLivrablesLateraux});
            // 
            // dataGridTableStyleLivrablesLateraux
            // 
            this.dataGridTableStyleLivrablesLateraux.ColumnHeadersVisible = false;
            this.dataGridTableStyleLivrablesLateraux.DataGrid = this.dgLivrablesLateraux;
            this.dataGridTableStyleLivrablesLateraux.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnLivrablesLaterauxRequested,
            this.dataGridTextBoxColumnLivrablesLaterauxName,
            this.dataGridTextBoxColumnLivrablesLaterauxProcname,
            this.dataGridTextBoxColumnLivrablesLaterauxDate});
            this.dataGridTableStyleLivrablesLateraux.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleLivrablesLateraux.MappingName = "ELEMENTS";
            this.dataGridTableStyleLivrablesLateraux.ReadOnly = true;
            this.dataGridTableStyleLivrablesLateraux.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnLivrablesLaterauxRequested
            // 
            this.dataGridTextBoxColumnLivrablesLaterauxRequested.Format = "";
            this.dataGridTextBoxColumnLivrablesLaterauxRequested.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesLaterauxRequested.MappingName = "requested";
            this.dataGridTextBoxColumnLivrablesLaterauxRequested.Width = 75;
            // 
            // dataGridTextBoxColumnLivrablesLaterauxName
            // 
            this.dataGridTextBoxColumnLivrablesLaterauxName.Format = "";
            this.dataGridTextBoxColumnLivrablesLaterauxName.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesLaterauxName.MappingName = "name";
            this.dataGridTextBoxColumnLivrablesLaterauxName.Width = 375;
            // 
            // dataGridTextBoxColumnLivrablesLaterauxProcname
            // 
            this.dataGridTextBoxColumnLivrablesLaterauxProcname.Format = "";
            this.dataGridTextBoxColumnLivrablesLaterauxProcname.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesLaterauxProcname.MappingName = "procname";
            this.dataGridTextBoxColumnLivrablesLaterauxProcname.Width = 75;
            // 
            // dataGridTextBoxColumnLivrablesLaterauxDate
            // 
            this.dataGridTextBoxColumnLivrablesLaterauxDate.Format = "";
            this.dataGridTextBoxColumnLivrablesLaterauxDate.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesLaterauxDate.MappingName = "mdated";
            this.dataGridTextBoxColumnLivrablesLaterauxDate.Width = 75;
            // 
            // dgLivrablesInput
            // 
            this.dgLivrablesInput.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgLivrablesInput.CaptionText = "Livrables en entrée";
            this.dgLivrablesInput.ColumnHeadersVisible = false;
            this.dgLivrablesInput.DataMember = "";
            this.dgLivrablesInput.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgLivrablesInput.Location = new System.Drawing.Point(8, 16);
            this.dgLivrablesInput.Name = "dgLivrablesInput";
            this.dgLivrablesInput.Size = new System.Drawing.Size(600, 120);
            this.dgLivrablesInput.TabIndex = 0;
            this.dgLivrablesInput.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleLivrablesInput});
            // 
            // dataGridTableStyleLivrablesInput
            // 
            this.dataGridTableStyleLivrablesInput.ColumnHeadersVisible = false;
            this.dataGridTableStyleLivrablesInput.DataGrid = this.dgLivrablesInput;
            this.dataGridTableStyleLivrablesInput.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnLivrablesInputName,
            this.dataGridTextBoxColumnLivrablesInputDate});
            this.dataGridTableStyleLivrablesInput.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleLivrablesInput.MappingName = "ELEMENTS";
            this.dataGridTableStyleLivrablesInput.ReadOnly = true;
            this.dataGridTableStyleLivrablesInput.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnLivrablesInputName
            // 
            this.dataGridTextBoxColumnLivrablesInputName.Format = "";
            this.dataGridTextBoxColumnLivrablesInputName.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesInputName.MappingName = "name";
            this.dataGridTextBoxColumnLivrablesInputName.Width = 325;
            // 
            // dataGridTextBoxColumnLivrablesInputDate
            // 
            this.dataGridTextBoxColumnLivrablesInputDate.Format = "";
            this.dataGridTextBoxColumnLivrablesInputDate.FormatInfo = null;
            this.dataGridTextBoxColumnLivrablesInputDate.MappingName = "mdated";
            this.dataGridTextBoxColumnLivrablesInputDate.Width = 75;
            // 
            // tabPageElements
            // 
            this.tabPageElements.Controls.Add(this.dgRules);
            this.tabPageElements.Controls.Add(this.dgFiles);
            this.tabPageElements.Controls.Add(this.dgDecisions);
            this.tabPageElements.Controls.Add(this.dgTasks);
            this.tabPageElements.Location = new System.Drawing.Point(4, 22);
            this.tabPageElements.Name = "tabPageElements";
            this.tabPageElements.Size = new System.Drawing.Size(624, 484);
            this.tabPageElements.TabIndex = 1;
            this.tabPageElements.Text = "Elements";
            // 
            // tabPageMessage
            // 
            this.tabPageMessage.Controls.Add(this.lInfos);
            this.tabPageMessage.Location = new System.Drawing.Point(4, 22);
            this.tabPageMessage.Name = "tabPageMessage";
            this.tabPageMessage.Size = new System.Drawing.Size(624, 484);
            this.tabPageMessage.TabIndex = 2;
            this.tabPageMessage.Text = "Infos";
            // 
            // lInfos
            // 
            this.lInfos.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lInfos.ForeColor = System.Drawing.Color.Red;
            this.lInfos.Location = new System.Drawing.Point(8, 8);
            this.lInfos.Name = "lInfos";
            this.lInfos.Size = new System.Drawing.Size(608, 456);
            this.lInfos.TabIndex = 0;
            this.lInfos.Text = "label4";
            // 
            // tabPageApplications
            // 
            this.tabPageApplications.Controls.Add(this.btnLaunch);
            this.tabPageApplications.Controls.Add(this.dgApplications);
            this.tabPageApplications.Location = new System.Drawing.Point(4, 22);
            this.tabPageApplications.Name = "tabPageApplications";
            this.tabPageApplications.Size = new System.Drawing.Size(624, 484);
            this.tabPageApplications.TabIndex = 3;
            this.tabPageApplications.Text = "Applications";
            // 
            // btnLaunch
            // 
            this.btnLaunch.Location = new System.Drawing.Point(16, 216);
            this.btnLaunch.Name = "btnLaunch";
            this.btnLaunch.Size = new System.Drawing.Size(128, 23);
            this.btnLaunch.TabIndex = 1;
            this.btnLaunch.Text = "Lancer application";
            this.btnLaunch.Click += new System.EventHandler(this.btnLaunch_Click);
            // 
            // dgApplications
            // 
            this.dgApplications.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgApplications.CaptionText = "Applications";
            this.dgApplications.ColumnHeadersVisible = false;
            this.dgApplications.DataMember = "";
            this.dgApplications.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgApplications.Location = new System.Drawing.Point(16, 16);
            this.dgApplications.Name = "dgApplications";
            this.dgApplications.ParentRowsVisible = false;
            this.dgApplications.RowHeadersVisible = false;
            this.dgApplications.Size = new System.Drawing.Size(592, 192);
            this.dgApplications.TabIndex = 0;
            this.dgApplications.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleApplications});
            // 
            // dataGridTableStyleApplications
            // 
            this.dataGridTableStyleApplications.ColumnHeadersVisible = false;
            this.dataGridTableStyleApplications.DataGrid = this.dgApplications;
            this.dataGridTableStyleApplications.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnApplicationsName});
            this.dataGridTableStyleApplications.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleApplications.MappingName = "ELEMENTS";
            this.dataGridTableStyleApplications.ReadOnly = true;
            this.dataGridTableStyleApplications.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnApplicationsName
            // 
            this.dataGridTextBoxColumnApplicationsName.Format = "";
            this.dataGridTextBoxColumnApplicationsName.FormatInfo = null;
            this.dataGridTextBoxColumnApplicationsName.MappingName = "name";
            this.dataGridTextBoxColumnApplicationsName.Width = 75;
            // 
            // btSetToWait
            // 
            this.btSetToWait.Location = new System.Drawing.Point(360, 608);
            this.btSetToWait.Name = "btSetToWait";
            this.btSetToWait.Size = new System.Drawing.Size(96, 23);
            this.btSetToWait.TabIndex = 12;
            this.btSetToWait.Text = "Mise en attente";
            this.btSetToWait.Click += new System.EventHandler(this.btSetToWait_Click);
            // 
            // bNotConform
            // 
            this.bNotConform.Location = new System.Drawing.Point(464, 608);
            this.bNotConform.Name = "bNotConform";
            this.bNotConform.Size = new System.Drawing.Size(152, 23);
            this.bNotConform.TabIndex = 13;
            this.bNotConform.Text = "Retour pour non conformité";
            this.bNotConform.Click += new System.EventHandler(this.bNotConform_Click);
            // 
            // bBackToChief
            // 
            this.bBackToChief.Location = new System.Drawing.Point(624, 608);
            this.bBackToChief.Name = "bBackToChief";
            this.bBackToChief.Size = new System.Drawing.Size(96, 23);
            this.bBackToChief.TabIndex = 14;
            this.bBackToChief.Text = "Remise au chef";
            this.bBackToChief.Click += new System.EventHandler(this.bBackToChief_Click);
            // 
            // bTerminate
            // 
            this.bTerminate.Location = new System.Drawing.Point(728, 608);
            this.bTerminate.Name = "bTerminate";
            this.bTerminate.Size = new System.Drawing.Size(75, 23);
            this.bTerminate.TabIndex = 15;
            this.bTerminate.Text = "Terminé";
            this.bTerminate.Click += new System.EventHandler(this.bTerminate_Click);
            // 
            // btSynchronise
            // 
            this.btSynchronise.Location = new System.Drawing.Point(6, 592);
            this.btSynchronise.Name = "btSynchronise";
            this.btSynchronise.Size = new System.Drawing.Size(168, 40);
            this.btSynchronise.TabIndex = 16;
            this.btSynchronise.Text = "Synchroniser la capsule en cours";
            this.btSynchronise.Click += new System.EventHandler(this.btSynchronise_Click);
            // 
            // btSynchroniseAll
            // 
            this.btSynchroniseAll.Location = new System.Drawing.Point(6, 544);
            this.btSynchroniseAll.Name = "btSynchroniseAll";
            this.btSynchroniseAll.Size = new System.Drawing.Size(168, 40);
            this.btSynchroniseAll.TabIndex = 17;
            this.btSynchroniseAll.Text = "Tout synchroniser";
            this.btSynchroniseAll.Click += new System.EventHandler(this.btSynchroniseAll_Click);
            // 
            // btDelete
            // 
            this.btDelete.Location = new System.Drawing.Point(280, 608);
            this.btDelete.Name = "btDelete";
            this.btDelete.Size = new System.Drawing.Size(75, 23);
            this.btDelete.TabIndex = 18;
            this.btDelete.Text = "Effacer";
            this.btDelete.Click += new System.EventHandler(this.btDelete_Click);
            // 
            // FMain
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(832, 637);
            this.Controls.Add(this.btDelete);
            this.Controls.Add(this.btSynchroniseAll);
            this.Controls.Add(this.btSynchronise);
            this.Controls.Add(this.bTerminate);
            this.Controls.Add(this.bBackToChief);
            this.Controls.Add(this.bNotConform);
            this.Controls.Add(this.btSetToWait);
            this.Controls.Add(this.tabControlPages);
            this.Controls.Add(this.lProcName);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.bSave);
            this.Controls.Add(this.lCaseName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lbFiles);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FMain";
            this.Text = "ProcessSoft - Capsules de travail";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.FMain_Closing);
            this.Load += new System.EventHandler(this.FMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgTasks)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgRules)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgDecisions)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgFiles)).EndInit();
            this.tabControlPages.ResumeLayout(false);
            this.tabPageLivrables.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesOutput)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesLateraux)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLivrablesInput)).EndInit();
            this.tabPageElements.ResumeLayout(false);
            this.tabPageMessage.ResumeLayout(false);
            this.tabPageApplications.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgApplications)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        /// <summary>
        /// The main entry point for the application
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new FMain());
        }

        private void FMain_Load(object sender, System.EventArgs e)
        {
            // load the cases
            loadFilesList();

            // check if we need to display a warning for the close cases
            displayWarningCases();
        }

        /// <summary>
        /// Load a list of all capsules available into the folder "capsules"
        /// </summary>
        private void loadFilesList()
        {
            _cxml.loadAllFilesInfoIntoList(Application.StartupPath + "\\capsules");

            lbFiles.DataSource = _cxml.getCasesNameList();

            // check if we must enable or not the buttons
            if (_cxml.getCasesNameList().Count == 0)
                activateInactivateButtons(false);
        }

        /// <summary>
        /// The user choose a new case to edit
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void lbFiles_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            // check if previous file has been changed, and need to be saved
            checkIfSaveIsNeeded();

            // load the file'infos
            loadFile();

            // select the first tab
            tabControlPages.SelectedIndex = 0;
        }

        /// <summary>
        /// Load the info about a file into the different datagrid
        /// </summary>
        private void loadFile()
        {
            _cxml.loadFileIntoList(_cxml.getPathOfFileAtIndex(lbFiles.SelectedIndex));

            // display the case and procedure names
            lCaseName.Text = _cxml.getCaseName() + ", " + _cxml.getTransName();
            lProcName.Text = _cxml.getProcName();

            // link the dataset to the grid
            dgTasks.DataSource             = _cxml.getTasksDataView();
            dgDecisions.DataSource         = _cxml.getDecisionsDataView();
            dgRules.DataSource             = _cxml.getRulesDataView();
            dgFiles.DataSource             = _cxml.getFilesDataView();
            dgLivrablesInput.DataSource    = _cxml.getLivrablesInputDataView();
            dgLivrablesLateraux.DataSource = _cxml.getLivrablesLaterauxDataView();
            dgLivrablesOutput.DataSource   = _cxml.getLivrablesOutputDataView();
            dgApplications.DataSource      = _cxml.getApplicationsDataView();

            _fileHasBeenModified = false;

            // check if we need to install the tracker to check, if we allow to save or not the modification
            if (!_trackerIsInstalled)
            {
                _cxml.getTasksDataView().ListChanged      += new System.ComponentModel.ListChangedEventHandler(OnListChanged);
                _cxml.getDecisionsDataView().ListChanged  += new System.ComponentModel.ListChangedEventHandler(OnListChanged);
                _cxml.getRulesDataView().ListChanged      += new System.ComponentModel.ListChangedEventHandler(OnListChanged);
                _cxml.getFilesDataView().ListChanged      += new System.ComponentModel.ListChangedEventHandler(OnListChanged);

                _trackerIsInstalled = true;
            }

            // do the layout of the grids
            doLayoutOfGrid();

            // check if we can show the case or not
            showInfos();
        }

        protected void OnListChanged(object sender, System.ComponentModel.ListChangedEventArgs args)
        {
            if (args.ListChangedType == ListChangedType.ItemChanged)
                _fileHasBeenModified = true;
        }

        /// <summary>
        /// As the content of the datagrid is generated on the fly, we need to customize at runtine
        /// how it is displayed (size of columns, ...)
        /// </summary>
        private void doLayoutOfGrid()
        {
            // tasks
            dataGridBoolColumnTasksValue.Width   = 20;
            dataGridTextBoxColumnTasksDate.Width = 120;
            dataGridTextBoxColumnTasksName.Width = dgTasks.Width-120-25;

            // rules
            dataGridBoolColumnRulesValue.Width   = 20;
            dataGridTextBoxColumnRulesDate.Width = 120;
            dataGridTextBoxColumnRulesName.Width = dgTasks.Width-120-25;

            // decisions
            dataGridBoolColumnDecisionsValue.Width   = 20;
            dataGridTextBoxColumnDecisionsDate.Width = 120;
            dataGridTextBoxColumnDecisionsName.Width = dgTasks.Width-120-25;

            // files
            dataGridTextBoxColumnFilesLogin.Width = 150;
            dataGridTextBoxColumnFilesDate.Width  = 120;
            dataGridTextBoxColumnFilesName.Width  = dgFiles.Width -150-120- 5;

            // livrables Input
            dataGridTextBoxColumnLivrablesInputDate.Width = 120;
            dataGridTextBoxColumnLivrablesInputName.Width = dgLivrablesInput.Width - 120 - 5;

            // livrables Lateraux
            dataGridTextBoxColumnLivrablesLaterauxRequested.Width = 15;
            dataGridTextBoxColumnLivrablesLaterauxProcname.Width  = 185;
            dataGridTextBoxColumnLivrablesLaterauxDate.Width      = 120;
            dataGridTextBoxColumnLivrablesLaterauxName.Width      = dgLivrablesLateraux.Width - 200-120- 5;

            // livrables Output
            dataGridTextBoxColumnLivrablesOutputRequested.Width = 15;
            dataGridTextBoxColumnLivrablesOutputDate.Width      = 120;
            dataGridTextBoxColumnLivrablesOutputProcname.Width  = 185;
            dataGridTextBoxColumnLivrablesOutputName.Width      = dgLivrablesOutput.Width -200-120- 5;

            // application
            dataGridTextBoxColumnApplicationsName.Width = dgApplications.Width-5;
        }

        /// <summary>
        /// Click on the button save
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bSave_Click(object sender, System.EventArgs e)
        {
            doSave();
        }

        /// <summary>
        /// Save the modification in the xml file
        /// </summary>
        private void doSave()
        {
            _cxml.SaveAsXML();

            // set the flag to false
            _fileHasBeenModified = false;
        }

        /// <summary>
        /// Check if the file has been modified, and if yes, ask the user if he wants to save the modification
        /// </summary>
        private void checkIfSaveIsNeeded()
        {
            if (!this._fileHasBeenModified)
                return;

            DialogResult result =
                    MessageBox.Show(this,
                                    "Ce processus a été modifié.\nVoulez-vous sauver les modifications ?",
                                    "Sauver les modifications",
                                    MessageBoxButtons.YesNo,
                                    MessageBoxIcon.Warning);

            if (result == DialogResult.Yes)
                doSave();
        }

        /// <summary>
        /// Before the application quit, check if we need to save
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FMain_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            // check if previous file has been changed, and need to be saved
            checkIfSaveIsNeeded();
        }

        /// <summary>
        /// Display information about the current case.
        /// Mainly used to inform that the case cannot be modified, because it has
        /// a particular status (return to chief, terminate, wait, ...)
        /// </summary>
        private void showInfos()
        {
            bool isOk   = true;
            lInfos.Text = "Rien de particulier.";

            if (_cxml.getIsBackToSender())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il a été retourné pour non conformité.";
                isOk        = false;
            }

            if (_cxml.getIsSendToChief())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il a été retourné au chef.";
                isOk        = false;
            }

            if (_cxml.getIsSetToWait())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il a été mis en attente.";
                isOk        = false;
            }

            if (_cxml.getIsTerminate())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il a été terminé.";
                isOk        = false;
            }

            // check if the date is valid
            if (_cxml.isAfterDatePeremption())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il est échue au " + _cxml.getDatePeremption();
                isOk        = false;
            }

            // if not ok, let only select the message page
            if (!isOk)
            {
                // set the buttons
                activateInactivateButtons(false);

                if (tabControlPages.SelectedIndex != tabControlPages.TabPages.IndexOf(tabPageMessage))
                    tabControlPages.SelectedIndex = tabControlPages.TabPages.IndexOf(tabPageMessage);
            }
            else
                //set the buttons
                activateInactivateButtons(true) ;

            // is the case already synchronised
            if (_cxml.getHasBeenSynchronised())
            {
                lInfos.Text = "Ce cas ne peut plus être modifié car il a déjà été synchronisé.";

                // pas de isOk = false, car on laisse quand même naviguer dans le cas
                activateInactivateButtons(false);
            }
        }

        private void tabControlPages_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            // check if we can let the user select any tab, or it the case is closed
            this.showInfos();
        }

        /// <summary>
        /// Button : set to wait
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btSetToWait_Click(object sender, System.EventArgs e)
        {
            _cxml.setIsSetToWait(true);
            _fileHasBeenModified = true;
            showInfos();
        }

        /// <summary>
        /// Open the window to show the attribut of a livrable
        /// </summary>
        /// <param name="dsToDisplay"></param>
        /// <param name="canEdit"></param>
        private void openAttributs(DataSet dsToDisplay, String tableName, bool canEdit)
        {
            FAttributs win = new FAttributs(dsToDisplay, tableName, this, canEdit);
            win.Show();
        }

        /// <summary>
        /// Allow the attribut window to set the flag modification to true
        /// </summary>
        public void setFileHasBeenModified(bool value)
        {
            _fileHasBeenModified = value;
        }

        /// <summary>
        /// Open the attributs
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bAttributsInput_Click(object sender, System.EventArgs e)
        {
            openAttributs(_cxml.getLivrablesInputAttributs(), "ELEMENTS_" + dgLivrablesInput.CurrentRowIndex, false);
        }

        /// <summary>
        /// Not conform
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bNotConform_Click(object sender, System.EventArgs e)
        {
            _cxml.setIsBackToSender(true);
            _fileHasBeenModified = true;
            showInfos();
        }

        /// <summary>
        /// Back to chief
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bBackToChief_Click(object sender, System.EventArgs e)
        {
            _cxml.setIsSendToChief(true);
            _fileHasBeenModified = true;
            showInfos();
        }

        /// <summary>
        /// Terminate
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bTerminate_Click(object sender, System.EventArgs e)
        {
            _cxml.setIsTerminate(true);
            _fileHasBeenModified = true;
            showInfos();
        }

        /// <summary>
        /// Synchronize the current capsule with the server
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btSynchronise_Click(object sender, System.EventArgs e)
        {
            FSynchro synchro = new FSynchro(_cxml, lbFiles.SelectedIndex);

            synchro.ShowDialog();
        }

        /// <summary>
        /// Open the attributs
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bAttributsLateral_Click(object sender, System.EventArgs e)
        {
            openAttributs(_cxml.getLivrablesLaterauxAttributs(), "ELEMENTS_" + dgLivrablesLateraux.CurrentRowIndex, true);
        }

        /// <summary>
        /// Open the attributs
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bAttributsOutput_Click(object sender, System.EventArgs e)
        {
            openAttributs(_cxml.getLivrablesOutputAttributs(), "ELEMENTS_" + dgLivrablesOutput.CurrentRowIndex, true);
        }

        /// <summary>
        /// Launch an application
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLaunch_Click(object sender, System.EventArgs e)
        {
            try
            {
                if (_cxml.getApplicationsDataView().Table.Rows.Count == 0)
                    return;

                String command = (String)_cxml.getApplicationsDataView().Table.Rows[dgApplications.CurrentRowIndex]["command"];
                System.Diagnostics.Process.Start(command);
            }
            catch(Exception ex)
            {
                MessageBox.Show(this, "Une erreur est survenue : " + ex.Message);
            }
        }

        /// <summary>
        /// Delete the current capsule
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btDelete_Click(object sender, System.EventArgs e)
        {
            DialogResult result =
                    MessageBox.Show(this,
                                    "Etes-vous sûr de vouloir effacer définitivement cette capsule ?",
                                    "Effacer capsule",
                                    MessageBoxButtons.YesNo,
                                    MessageBoxIcon.Warning,
                                    MessageBoxDefaultButton.Button2);

            if (result == DialogResult.Yes)
            {
                // delete the capsule
                _cxml.deleteCapsuleAtIndex(lbFiles.SelectedIndex);

                // reload the list
                loadFilesList() ;
            }
        }

        /// <summary>
        /// Set the enabled property of all buttons
        /// </summary>
        private void activateInactivateButtons(bool enabled)
        {
            bSave.Enabled            = enabled;
            btSetToWait.Enabled      = enabled;
            bTerminate.Enabled       = enabled;
            bNotConform.Enabled      = enabled;
            bBackToChief.Enabled     = enabled;
            btSynchronise.Enabled    = enabled;
            btSynchroniseAll.Enabled = enabled;
        }

        /// <summary>
        /// Synchronize all capsules
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btSynchroniseAll_Click(object sender, System.EventArgs e)
        {
            FSynchro synchro = new FSynchro(_cxml, -1);
            synchro.ShowDialog();
        }

        /// <summary>
        /// Display all the cases which the warning date are close
        /// </summary>
        private void displayWarningCases()
        {
            DateTime  d;
            ArrayList aCloseToEndDate = new ArrayList();
            ArrayList aDates          = _cxml.getCasesDateWarning();

            // check the warning date of each case, and check if we are before or after this date
            for (int i = 0; i < aDates.Count; ++i)
            {
                if (aDates[i] != null)
                {
                    try
                    {
                        d = DateTime.Parse((string)aDates[i]);

                        //check if we are after or before the date
                        if (d.CompareTo(DateTime.Now) < 0)
                            aCloseToEndDate.Add((string)_cxml.getCasesNameList()[i]);
                    }
                    catch (Exception)
                    {}
                }
            }

            // do we need to display a warning?
            if(aCloseToEndDate.Count > 0)
            {
                string msg = "Attention ! Certaines capsules arrivent à échéance : ";

                for(int i = 0; i < aCloseToEndDate.Count; ++i)
                    msg += "\n- " + aCloseToEndDate[i];

                MessageBox.Show(this, msg);
            }
        }

        /// <summary>
        /// Launch a lateral livrable
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btLaunchLateral_Click(object sender, System.EventArgs e)
        {
            if (_cxml.getLivrablesLaterauxDataView().Count == 0)
                return;

            _cxml.getLivrablesLaterauxDataView().Table.Rows[dgLivrablesLateraux.CurrentRowIndex]["requested"] = "1";
        }

        /// <summary>
        /// Launch an output livrable
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btLaunchOutput_Click(object sender, System.EventArgs e)
        {
            if(_cxml.getLivrablesOutputDataView().Count == 0)
                return;

            _cxml.getLivrablesOutputDataView().Table.Rows[dgLivrablesOutput.CurrentRowIndex]["requested"] = "1";
        }
    }
}
