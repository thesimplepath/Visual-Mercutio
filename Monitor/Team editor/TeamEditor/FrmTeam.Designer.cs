namespace TeamEditor
{
    partial class FrmTeam
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmTeam));
            this.grdTeam = new System.Windows.Forms.DataGridView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.cmdFermer = new System.Windows.Forms.Button();
            this.cmdSauver = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txtPercentTotal = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.cboGroupe = new System.Windows.Forms.ComboBox();
            this.txtPercent = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.txtDateCreation = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtCommune = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtEmail = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtTelephone = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtPays = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtNpaLocalite = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtRue = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtVocation = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtMission = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtNom = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cmdNouveau = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.lblYear = new System.Windows.Forms.Label();
            this.cmdNextYear = new System.Windows.Forms.Button();
            this.cmdPreviousYear = new System.Windows.Forms.Button();
            this.grdCalendarAuto = new System.Windows.Forms.DataGridView();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.cmdSaveEptManual = new System.Windows.Forms.Button();
            this.lblYearManual = new System.Windows.Forms.Label();
            this.cmdNextYearManual = new System.Windows.Forms.Button();
            this.cmdPreviousYearManual = new System.Windows.Forms.Button();
            this.grdCalendarManual = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.grdTeam)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendarAuto)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendarManual)).BeginInit();
            this.SuspendLayout();
            // 
            // grdTeam
            // 
            this.grdTeam.AllowUserToAddRows = false;
            this.grdTeam.AllowUserToDeleteRows = false;
            this.grdTeam.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdTeam.Location = new System.Drawing.Point(2, 3);
            this.grdTeam.MultiSelect = false;
            this.grdTeam.Name = "grdTeam";
            this.grdTeam.ReadOnly = true;
            this.grdTeam.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.grdTeam.Size = new System.Drawing.Size(763, 231);
            this.grdTeam.TabIndex = 0;
            this.grdTeam.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdTeam_CellClick);
            this.grdTeam.SelectionChanged += new System.EventHandler(this.grdTeam_SelectionChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(2, 240);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(767, 378);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.cmdFermer);
            this.tabPage1.Controls.Add(this.cmdSauver);
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Controls.Add(this.cmdNouveau);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(759, 352);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Données";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // cmdFermer
            // 
            this.cmdFermer.Location = new System.Drawing.Point(645, 282);
            this.cmdFermer.Name = "cmdFermer";
            this.cmdFermer.Size = new System.Drawing.Size(99, 23);
            this.cmdFermer.TabIndex = 14;
            this.cmdFermer.Text = "Fermer";
            this.cmdFermer.UseVisualStyleBackColor = true;
            this.cmdFermer.Click += new System.EventHandler(this.cmdVider_Click);
            // 
            // cmdSauver
            // 
            this.cmdSauver.Location = new System.Drawing.Point(510, 282);
            this.cmdSauver.Name = "cmdSauver";
            this.cmdSauver.Size = new System.Drawing.Size(99, 23);
            this.cmdSauver.TabIndex = 13;
            this.cmdSauver.Text = "Enregistrer";
            this.cmdSauver.UseVisualStyleBackColor = true;
            this.cmdSauver.Click += new System.EventHandler(this.cmdSauver_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label15);
            this.groupBox3.Controls.Add(this.txtPercentTotal);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.cboGroupe);
            this.groupBox3.Controls.Add(this.txtPercent);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.txtDateCreation);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Location = new System.Drawing.Point(345, 10);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(399, 100);
            this.groupBox3.TabIndex = 32;
            this.groupBox3.TabStop = false;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(324, 73);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(15, 13);
            this.label15.TabIndex = 36;
            this.label15.Text = "%";
            // 
            // txtPercentTotal
            // 
            this.txtPercentTotal.Enabled = false;
            this.txtPercentTotal.Location = new System.Drawing.Point(277, 68);
            this.txtPercentTotal.Name = "txtPercentTotal";
            this.txtPercentTotal.Size = new System.Drawing.Size(41, 20);
            this.txtPercentTotal.TabIndex = 12;
            this.txtPercentTotal.Text = "0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(183, 71);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(88, 13);
            this.label14.TabIndex = 34;
            this.label14.Text = "Total du groupe :";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(158, 71);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(15, 13);
            this.label13.TabIndex = 33;
            this.label13.Text = "%";
            // 
            // cboGroupe
            // 
            this.cboGroupe.FormattingEnabled = true;
            this.cboGroupe.Location = new System.Drawing.Point(111, 39);
            this.cboGroupe.Name = "cboGroupe";
            this.cboGroupe.Size = new System.Drawing.Size(282, 21);
            this.cboGroupe.TabIndex = 10;
            this.cboGroupe.SelectedIndexChanged += new System.EventHandler(this.cboGroupe_SelectedIndexChanged);
            this.cboGroupe.SelectedValueChanged += new System.EventHandler(this.cboGroupe_SelectedValueChanged);
            // 
            // txtPercent
            // 
            this.txtPercent.Location = new System.Drawing.Point(111, 68);
            this.txtPercent.Name = "txtPercent";
            this.txtPercent.Size = new System.Drawing.Size(41, 20);
            this.txtPercent.TabIndex = 11;
            this.txtPercent.Text = "0";
            this.txtPercent.TextChanged += new System.EventHandler(this.txtPercent_TextChanged);
            this.txtPercent.Validating += new System.ComponentModel.CancelEventHandler(this.txtPercent_Validating);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(4, 71);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(74, 13);
            this.label12.TabIndex = 30;
            this.label12.Text = "Pourcentage :";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(4, 42);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(81, 13);
            this.label11.TabIndex = 29;
            this.label11.Text = "Groupe parent :";
            // 
            // txtDateCreation
            // 
            this.txtDateCreation.Enabled = false;
            this.txtDateCreation.Location = new System.Drawing.Point(111, 13);
            this.txtDateCreation.Name = "txtDateCreation";
            this.txtDateCreation.Size = new System.Drawing.Size(153, 20);
            this.txtDateCreation.TabIndex = 9;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(4, 16);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(92, 13);
            this.label10.TabIndex = 27;
            this.label10.Text = "Date de création :";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtCommune);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.txtEmail);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.txtTelephone);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.txtPays);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.txtNpaLocalite);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.txtRue);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.txtVocation);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.txtMission);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.txtNom);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(6, 10);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(330, 266);
            this.groupBox2.TabIndex = 31;
            this.groupBox2.TabStop = false;
            // 
            // txtCommune
            // 
            this.txtCommune.Location = new System.Drawing.Point(87, 151);
            this.txtCommune.Name = "txtCommune";
            this.txtCommune.Size = new System.Drawing.Size(208, 20);
            this.txtCommune.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 154);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(60, 13);
            this.label6.TabIndex = 36;
            this.label6.Text = "Commune :";
            // 
            // txtEmail
            // 
            this.txtEmail.Location = new System.Drawing.Point(87, 229);
            this.txtEmail.Name = "txtEmail";
            this.txtEmail.Size = new System.Drawing.Size(208, 20);
            this.txtEmail.TabIndex = 8;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 232);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(38, 13);
            this.label9.TabIndex = 34;
            this.label9.Text = "Email :";
            // 
            // txtTelephone
            // 
            this.txtTelephone.Location = new System.Drawing.Point(87, 203);
            this.txtTelephone.Name = "txtTelephone";
            this.txtTelephone.Size = new System.Drawing.Size(208, 20);
            this.txtTelephone.TabIndex = 7;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 206);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(64, 13);
            this.label8.TabIndex = 32;
            this.label8.Text = "Téléphone :";
            // 
            // txtPays
            // 
            this.txtPays.Location = new System.Drawing.Point(87, 177);
            this.txtPays.Name = "txtPays";
            this.txtPays.Size = new System.Drawing.Size(208, 20);
            this.txtPays.TabIndex = 6;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 180);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(36, 13);
            this.label7.TabIndex = 30;
            this.label7.Text = "Pays :";
            // 
            // txtNpaLocalite
            // 
            this.txtNpaLocalite.Location = new System.Drawing.Point(87, 125);
            this.txtNpaLocalite.Name = "txtNpaLocalite";
            this.txtNpaLocalite.Size = new System.Drawing.Size(208, 20);
            this.txtNpaLocalite.TabIndex = 4;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 128);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(76, 13);
            this.label5.TabIndex = 26;
            this.label5.Text = "Npa, Localité :";
            // 
            // txtRue
            // 
            this.txtRue.Location = new System.Drawing.Point(87, 99);
            this.txtRue.Name = "txtRue";
            this.txtRue.Size = new System.Drawing.Size(208, 20);
            this.txtRue.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 102);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(33, 13);
            this.label4.TabIndex = 24;
            this.label4.Text = "Rue :";
            // 
            // txtVocation
            // 
            this.txtVocation.Location = new System.Drawing.Point(87, 73);
            this.txtVocation.Name = "txtVocation";
            this.txtVocation.Size = new System.Drawing.Size(238, 20);
            this.txtVocation.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 22;
            this.label3.Text = "Vocation :";
            // 
            // txtMission
            // 
            this.txtMission.Enabled = false;
            this.txtMission.Location = new System.Drawing.Point(87, 47);
            this.txtMission.Name = "txtMission";
            this.txtMission.Size = new System.Drawing.Size(238, 20);
            this.txtMission.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 13);
            this.label2.TabIndex = 20;
            this.label2.Text = "Mission :";
            // 
            // txtNom
            // 
            this.txtNom.Location = new System.Drawing.Point(87, 21);
            this.txtNom.Name = "txtNom";
            this.txtNom.Size = new System.Drawing.Size(238, 20);
            this.txtNom.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 18;
            this.label1.Text = "Nom :";
            // 
            // cmdNouveau
            // 
            this.cmdNouveau.Location = new System.Drawing.Point(405, 282);
            this.cmdNouveau.Name = "cmdNouveau";
            this.cmdNouveau.Size = new System.Drawing.Size(99, 23);
            this.cmdNouveau.TabIndex = 15;
            this.cmdNouveau.Text = "Créer Nouvelle";
            this.cmdNouveau.UseVisualStyleBackColor = true;
            this.cmdNouveau.Click += new System.EventHandler(this.cmdNouveau_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.lblYear);
            this.tabPage2.Controls.Add(this.cmdNextYear);
            this.tabPage2.Controls.Add(this.cmdPreviousYear);
            this.tabPage2.Controls.Add(this.grdCalendarAuto);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(759, 352);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Calendrier Calculé";
            this.tabPage2.UseVisualStyleBackColor = true;
            this.tabPage2.Click += new System.EventHandler(this.tabPage2_Click);
            // 
            // lblYear
            // 
            this.lblYear.AutoSize = true;
            this.lblYear.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblYear.Location = new System.Drawing.Point(324, 6);
            this.lblYear.Name = "lblYear";
            this.lblYear.Size = new System.Drawing.Size(65, 29);
            this.lblYear.TabIndex = 7;
            this.lblYear.Text = "2006";
            // 
            // cmdNextYear
            // 
            this.cmdNextYear.Location = new System.Drawing.Point(395, 6);
            this.cmdNextYear.Name = "cmdNextYear";
            this.cmdNextYear.Size = new System.Drawing.Size(32, 33);
            this.cmdNextYear.TabIndex = 6;
            this.cmdNextYear.Text = ">>";
            this.cmdNextYear.UseVisualStyleBackColor = true;
            this.cmdNextYear.Click += new System.EventHandler(this.cmdNextYear_Click);
            // 
            // cmdPreviousYear
            // 
            this.cmdPreviousYear.Location = new System.Drawing.Point(286, 5);
            this.cmdPreviousYear.Name = "cmdPreviousYear";
            this.cmdPreviousYear.Size = new System.Drawing.Size(32, 34);
            this.cmdPreviousYear.TabIndex = 5;
            this.cmdPreviousYear.Text = "<<";
            this.cmdPreviousYear.UseVisualStyleBackColor = true;
            this.cmdPreviousYear.Click += new System.EventHandler(this.cmdPreviousYear_Click);
            // 
            // grdCalendarAuto
            // 
            this.grdCalendarAuto.AllowUserToAddRows = false;
            this.grdCalendarAuto.AllowUserToDeleteRows = false;
            this.grdCalendarAuto.AllowUserToResizeColumns = false;
            this.grdCalendarAuto.AllowUserToResizeRows = false;
            this.grdCalendarAuto.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdCalendarAuto.Location = new System.Drawing.Point(6, 45);
            this.grdCalendarAuto.Name = "grdCalendarAuto";
            this.grdCalendarAuto.Size = new System.Drawing.Size(746, 294);
            this.grdCalendarAuto.TabIndex = 4;
            this.grdCalendarAuto.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdCalendarAuto_CellContentClick);
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.cmdSaveEptManual);
            this.tabPage3.Controls.Add(this.lblYearManual);
            this.tabPage3.Controls.Add(this.cmdNextYearManual);
            this.tabPage3.Controls.Add(this.cmdPreviousYearManual);
            this.tabPage3.Controls.Add(this.grdCalendarManual);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(759, 352);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Calendrier Manuel";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // cmdSaveEptManual
            // 
            this.cmdSaveEptManual.Location = new System.Drawing.Point(616, 311);
            this.cmdSaveEptManual.Name = "cmdSaveEptManual";
            this.cmdSaveEptManual.Size = new System.Drawing.Size(136, 23);
            this.cmdSaveEptManual.TabIndex = 12;
            this.cmdSaveEptManual.Text = "Sauver plannification";
            this.cmdSaveEptManual.UseVisualStyleBackColor = true;
            this.cmdSaveEptManual.Click += new System.EventHandler(this.cmdSaveEptManual_Click);
            // 
            // lblYearManual
            // 
            this.lblYearManual.AutoSize = true;
            this.lblYearManual.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblYearManual.Location = new System.Drawing.Point(324, 10);
            this.lblYearManual.Name = "lblYearManual";
            this.lblYearManual.Size = new System.Drawing.Size(65, 29);
            this.lblYearManual.TabIndex = 11;
            this.lblYearManual.Text = "2006";
            // 
            // cmdNextYearManual
            // 
            this.cmdNextYearManual.Location = new System.Drawing.Point(395, 10);
            this.cmdNextYearManual.Name = "cmdNextYearManual";
            this.cmdNextYearManual.Size = new System.Drawing.Size(32, 33);
            this.cmdNextYearManual.TabIndex = 10;
            this.cmdNextYearManual.Text = ">>";
            this.cmdNextYearManual.UseVisualStyleBackColor = true;
            this.cmdNextYearManual.Click += new System.EventHandler(this.cmdNextYearManual_Click);
            // 
            // cmdPreviousYearManual
            // 
            this.cmdPreviousYearManual.Location = new System.Drawing.Point(286, 9);
            this.cmdPreviousYearManual.Name = "cmdPreviousYearManual";
            this.cmdPreviousYearManual.Size = new System.Drawing.Size(32, 34);
            this.cmdPreviousYearManual.TabIndex = 9;
            this.cmdPreviousYearManual.Text = "<<";
            this.cmdPreviousYearManual.UseVisualStyleBackColor = true;
            this.cmdPreviousYearManual.Click += new System.EventHandler(this.cmdPreviousYearManual_Click);
            // 
            // grdCalendarManual
            // 
            this.grdCalendarManual.AllowUserToAddRows = false;
            this.grdCalendarManual.AllowUserToDeleteRows = false;
            this.grdCalendarManual.AllowUserToResizeColumns = false;
            this.grdCalendarManual.AllowUserToResizeRows = false;
            this.grdCalendarManual.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdCalendarManual.Location = new System.Drawing.Point(6, 49);
            this.grdCalendarManual.Name = "grdCalendarManual";
            this.grdCalendarManual.Size = new System.Drawing.Size(746, 243);
            this.grdCalendarManual.TabIndex = 8;
            // 
            // FrmTeam
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(774, 618);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.grdTeam);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmTeam";
            this.Text = "FrmTeam";
            this.Load += new System.EventHandler(this.FrmTeam_Load);
            ((System.ComponentModel.ISupportInitialize)(this.grdTeam)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendarAuto)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendarManual)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView grdTeam;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button cmdNouveau;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ComboBox cboGroupe;
        private System.Windows.Forms.TextBox txtPercent;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtDateCreation;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtEmail;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtTelephone;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtPays;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtNpaLocalite;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtRue;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtVocation;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtMission;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtNom;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtCommune;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button cmdSauver;
        private System.Windows.Forms.Button cmdFermer;
        private System.Windows.Forms.TextBox txtPercentTotal;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label lblYear;
        private System.Windows.Forms.Button cmdNextYear;
        private System.Windows.Forms.Button cmdPreviousYear;
        private System.Windows.Forms.DataGridView grdCalendarAuto;
        private System.Windows.Forms.Label lblYearManual;
        private System.Windows.Forms.Button cmdNextYearManual;
        private System.Windows.Forms.Button cmdPreviousYearManual;
        private System.Windows.Forms.DataGridView grdCalendarManual;
        private System.Windows.Forms.Button cmdSaveEptManual;
    }
}