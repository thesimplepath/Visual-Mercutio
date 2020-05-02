namespace TeamEditor
{
    partial class FrmUser
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmUser));
            this.dgrUser = new System.Windows.Forms.DataGridView();
            this.tabUser = new System.Windows.Forms.TabControl();
            this.tbData = new System.Windows.Forms.TabPage();
            this.cmdFermer = new System.Windows.Forms.Button();
            this.cmdNouveau = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtTelephone = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.chkAsynchrone = new System.Windows.Forms.CheckBox();
            this.cboGrade = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtEmail = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtPrenom = new System.Windows.Forms.TextBox();
            this.lblPrenom = new System.Windows.Forms.Label();
            this.txtNom = new System.Windows.Forms.TextBox();
            this.lblNom = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtConfirmation = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtMotDePasse = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtLogin = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cmdSauver = new System.Windows.Forms.Button();
            this.tbAIP = new System.Windows.Forms.TabPage();
            this.cmdSupprimerAIP = new System.Windows.Forms.Button();
            this.cmdEditerAIP = new System.Windows.Forms.Button();
            this.cmdNouveauAIP = new System.Windows.Forms.Button();
            this.grdAIP = new System.Windows.Forms.DataGridView();
            this.tbAILE = new System.Windows.Forms.TabPage();
            this.cmdSupprimerAILE = new System.Windows.Forms.Button();
            this.cmdEditerAILE = new System.Windows.Forms.Button();
            this.cmdNouveauAILE = new System.Windows.Forms.Button();
            this.grdAILE = new System.Windows.Forms.DataGridView();
            this.tbCalendar = new System.Windows.Forms.TabPage();
            this.cmdSaveCalendar = new System.Windows.Forms.Button();
            this.lblYear = new System.Windows.Forms.Label();
            this.cmdNextYear = new System.Windows.Forms.Button();
            this.cmdPreviousYear = new System.Windows.Forms.Button();
            this.grdCalendar = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.dgrUser)).BeginInit();
            this.tabUser.SuspendLayout();
            this.tbData.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tbAIP.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdAIP)).BeginInit();
            this.tbAILE.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdAILE)).BeginInit();
            this.tbCalendar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendar)).BeginInit();
            this.SuspendLayout();
            // 
            // dgrUser
            // 
            this.dgrUser.AllowUserToAddRows = false;
            this.dgrUser.AllowUserToDeleteRows = false;
            this.dgrUser.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgrUser.Location = new System.Drawing.Point(2, 1);
            this.dgrUser.MultiSelect = false;
            this.dgrUser.Name = "dgrUser";
            this.dgrUser.ReadOnly = true;
            this.dgrUser.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgrUser.Size = new System.Drawing.Size(764, 230);
            this.dgrUser.TabIndex = 0;
            this.dgrUser.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgrUser_CellClick);
            this.dgrUser.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgrUser_CellContentClick);
            // 
            // tabUser
            // 
            this.tabUser.Controls.Add(this.tbData);
            this.tabUser.Controls.Add(this.tbAIP);
            this.tabUser.Controls.Add(this.tbAILE);
            this.tabUser.Controls.Add(this.tbCalendar);
            this.tabUser.Location = new System.Drawing.Point(5, 237);
            this.tabUser.Name = "tabUser";
            this.tabUser.SelectedIndex = 0;
            this.tabUser.Size = new System.Drawing.Size(765, 374);
            this.tabUser.TabIndex = 1;
            this.tabUser.SelectedIndexChanged += new System.EventHandler(this.tabUser_SelectedIndexChanged);
            // 
            // tbData
            // 
            this.tbData.Controls.Add(this.cmdFermer);
            this.tbData.Controls.Add(this.cmdNouveau);
            this.tbData.Controls.Add(this.groupBox2);
            this.tbData.Controls.Add(this.groupBox1);
            this.tbData.Controls.Add(this.cmdSauver);
            this.tbData.Location = new System.Drawing.Point(4, 22);
            this.tbData.Name = "tbData";
            this.tbData.Padding = new System.Windows.Forms.Padding(3);
            this.tbData.Size = new System.Drawing.Size(757, 348);
            this.tbData.TabIndex = 0;
            this.tbData.Text = "Données personnelles";
            this.tbData.UseVisualStyleBackColor = true;
            // 
            // cmdFermer
            // 
            this.cmdFermer.Location = new System.Drawing.Point(575, 246);
            this.cmdFermer.Name = "cmdFermer";
            this.cmdFermer.Size = new System.Drawing.Size(99, 23);
            this.cmdFermer.TabIndex = 21;
            this.cmdFermer.Text = "Fermer";
            this.cmdFermer.UseVisualStyleBackColor = true;
            this.cmdFermer.Click += new System.EventHandler(this.cmdFermer_Click);
            // 
            // cmdNouveau
            // 
            this.cmdNouveau.Location = new System.Drawing.Point(352, 246);
            this.cmdNouveau.Name = "cmdNouveau";
            this.cmdNouveau.Size = new System.Drawing.Size(94, 23);
            this.cmdNouveau.TabIndex = 19;
            this.cmdNouveau.Text = "Créer Nouveau";
            this.cmdNouveau.UseVisualStyleBackColor = true;
            this.cmdNouveau.Click += new System.EventHandler(this.cmdNouveau_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtTelephone);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.chkAsynchrone);
            this.groupBox2.Controls.Add(this.cboGrade);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.txtEmail);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.txtPrenom);
            this.groupBox2.Controls.Add(this.lblPrenom);
            this.groupBox2.Controls.Add(this.txtNom);
            this.groupBox2.Controls.Add(this.lblNom);
            this.groupBox2.Location = new System.Drawing.Point(6, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(355, 218);
            this.groupBox2.TabIndex = 18;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Paramètres personnels";
            // 
            // txtTelephone
            // 
            this.txtTelephone.Location = new System.Drawing.Point(91, 105);
            this.txtTelephone.Name = "txtTelephone";
            this.txtTelephone.Size = new System.Drawing.Size(159, 20);
            this.txtTelephone.TabIndex = 28;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(5, 108);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 13);
            this.label7.TabIndex = 27;
            this.label7.Text = "Téléphone :";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(5, 157);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(56, 13);
            this.label6.TabIndex = 26;
            this.label6.Text = "Capsules :";
            // 
            // chkAsynchrone
            // 
            this.chkAsynchrone.AutoSize = true;
            this.chkAsynchrone.Location = new System.Drawing.Point(91, 158);
            this.chkAsynchrone.Name = "chkAsynchrone";
            this.chkAsynchrone.Size = new System.Drawing.Size(15, 14);
            this.chkAsynchrone.TabIndex = 25;
            this.chkAsynchrone.UseVisualStyleBackColor = true;
            // 
            // cboGrade
            // 
            this.cboGrade.FormattingEnabled = true;
            this.cboGrade.Location = new System.Drawing.Point(91, 131);
            this.cboGrade.Name = "cboGrade";
            this.cboGrade.Size = new System.Drawing.Size(159, 21);
            this.cboGrade.TabIndex = 24;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 134);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 23;
            this.label2.Text = "Grade :";
            // 
            // txtEmail
            // 
            this.txtEmail.Location = new System.Drawing.Point(91, 79);
            this.txtEmail.Name = "txtEmail";
            this.txtEmail.Size = new System.Drawing.Size(258, 20);
            this.txtEmail.TabIndex = 22;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(5, 82);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 21;
            this.label1.Text = "Email :";
            // 
            // txtPrenom
            // 
            this.txtPrenom.Location = new System.Drawing.Point(91, 53);
            this.txtPrenom.Name = "txtPrenom";
            this.txtPrenom.Size = new System.Drawing.Size(258, 20);
            this.txtPrenom.TabIndex = 20;
            // 
            // lblPrenom
            // 
            this.lblPrenom.AutoSize = true;
            this.lblPrenom.Location = new System.Drawing.Point(5, 56);
            this.lblPrenom.Name = "lblPrenom";
            this.lblPrenom.Size = new System.Drawing.Size(49, 13);
            this.lblPrenom.TabIndex = 19;
            this.lblPrenom.Text = "Prénom :";
            // 
            // txtNom
            // 
            this.txtNom.Location = new System.Drawing.Point(91, 27);
            this.txtNom.Name = "txtNom";
            this.txtNom.Size = new System.Drawing.Size(258, 20);
            this.txtNom.TabIndex = 18;
            // 
            // lblNom
            // 
            this.lblNom.AutoSize = true;
            this.lblNom.Location = new System.Drawing.Point(5, 30);
            this.lblNom.Name = "lblNom";
            this.lblNom.Size = new System.Drawing.Size(35, 13);
            this.lblNom.TabIndex = 17;
            this.lblNom.Text = "Nom :";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtConfirmation);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txtMotDePasse);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.txtLogin);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(367, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(290, 218);
            this.groupBox1.TabIndex = 17;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Paramètres de connexion";
            // 
            // txtConfirmation
            // 
            this.txtConfirmation.Location = new System.Drawing.Point(94, 83);
            this.txtConfirmation.Name = "txtConfirmation";
            this.txtConfirmation.PasswordChar = '*';
            this.txtConfirmation.Size = new System.Drawing.Size(152, 20);
            this.txtConfirmation.TabIndex = 19;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 86);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Confirmation :";
            // 
            // txtMotDePasse
            // 
            this.txtMotDePasse.Location = new System.Drawing.Point(94, 57);
            this.txtMotDePasse.Name = "txtMotDePasse";
            this.txtMotDePasse.PasswordChar = '*';
            this.txtMotDePasse.Size = new System.Drawing.Size(152, 20);
            this.txtMotDePasse.TabIndex = 17;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 60);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "Mot de passe :";
            // 
            // txtLogin
            // 
            this.txtLogin.Location = new System.Drawing.Point(94, 31);
            this.txtLogin.Name = "txtLogin";
            this.txtLogin.Size = new System.Drawing.Size(152, 20);
            this.txtLogin.TabIndex = 15;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 13);
            this.label3.TabIndex = 14;
            this.label3.Text = "Login :";
            // 
            // cmdSauver
            // 
            this.cmdSauver.Location = new System.Drawing.Point(461, 246);
            this.cmdSauver.Name = "cmdSauver";
            this.cmdSauver.Size = new System.Drawing.Size(75, 23);
            this.cmdSauver.TabIndex = 14;
            this.cmdSauver.Text = "Sauver";
            this.cmdSauver.UseVisualStyleBackColor = true;
            this.cmdSauver.Click += new System.EventHandler(this.cmdSauver_Click);
            // 
            // tbAIP
            // 
            this.tbAIP.Controls.Add(this.cmdSupprimerAIP);
            this.tbAIP.Controls.Add(this.cmdEditerAIP);
            this.tbAIP.Controls.Add(this.cmdNouveauAIP);
            this.tbAIP.Controls.Add(this.grdAIP);
            this.tbAIP.Location = new System.Drawing.Point(4, 22);
            this.tbAIP.Name = "tbAIP";
            this.tbAIP.Size = new System.Drawing.Size(757, 348);
            this.tbAIP.TabIndex = 2;
            this.tbAIP.Text = "Config AIP";
            this.tbAIP.UseVisualStyleBackColor = true;
            // 
            // cmdSupprimerAIP
            // 
            this.cmdSupprimerAIP.Location = new System.Drawing.Point(312, 234);
            this.cmdSupprimerAIP.Name = "cmdSupprimerAIP";
            this.cmdSupprimerAIP.Size = new System.Drawing.Size(75, 23);
            this.cmdSupprimerAIP.TabIndex = 3;
            this.cmdSupprimerAIP.Text = "Supprimer";
            this.cmdSupprimerAIP.UseVisualStyleBackColor = true;
            this.cmdSupprimerAIP.Click += new System.EventHandler(this.cmdSupprimerAIP_Click);
            // 
            // cmdEditerAIP
            // 
            this.cmdEditerAIP.Location = new System.Drawing.Point(444, 234);
            this.cmdEditerAIP.Name = "cmdEditerAIP";
            this.cmdEditerAIP.Size = new System.Drawing.Size(75, 23);
            this.cmdEditerAIP.TabIndex = 2;
            this.cmdEditerAIP.Text = "Editer...";
            this.cmdEditerAIP.UseVisualStyleBackColor = true;
            this.cmdEditerAIP.Click += new System.EventHandler(this.cmdEditerAIP_Click);
            // 
            // cmdNouveauAIP
            // 
            this.cmdNouveauAIP.Location = new System.Drawing.Point(525, 234);
            this.cmdNouveauAIP.Name = "cmdNouveauAIP";
            this.cmdNouveauAIP.Size = new System.Drawing.Size(100, 23);
            this.cmdNouveauAIP.TabIndex = 1;
            this.cmdNouveauAIP.Text = "Nouveau AIP...";
            this.cmdNouveauAIP.UseVisualStyleBackColor = true;
            this.cmdNouveauAIP.Click += new System.EventHandler(this.cmdNouveauAIP_Click);
            // 
            // grdAIP
            // 
            this.grdAIP.AllowUserToAddRows = false;
            this.grdAIP.AllowUserToDeleteRows = false;
            this.grdAIP.AllowUserToResizeRows = false;
            this.grdAIP.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdAIP.Location = new System.Drawing.Point(3, 3);
            this.grdAIP.MultiSelect = false;
            this.grdAIP.Name = "grdAIP";
            this.grdAIP.ReadOnly = true;
            this.grdAIP.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.grdAIP.Size = new System.Drawing.Size(657, 185);
            this.grdAIP.TabIndex = 0;
            this.grdAIP.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdAIP_CellContentClick);
            // 
            // tbAILE
            // 
            this.tbAILE.Controls.Add(this.cmdSupprimerAILE);
            this.tbAILE.Controls.Add(this.cmdEditerAILE);
            this.tbAILE.Controls.Add(this.cmdNouveauAILE);
            this.tbAILE.Controls.Add(this.grdAILE);
            this.tbAILE.Location = new System.Drawing.Point(4, 22);
            this.tbAILE.Name = "tbAILE";
            this.tbAILE.Size = new System.Drawing.Size(757, 348);
            this.tbAILE.TabIndex = 3;
            this.tbAILE.Text = "Config AILE";
            this.tbAILE.UseVisualStyleBackColor = true;
            // 
            // cmdSupprimerAILE
            // 
            this.cmdSupprimerAILE.Location = new System.Drawing.Point(296, 247);
            this.cmdSupprimerAILE.Name = "cmdSupprimerAILE";
            this.cmdSupprimerAILE.Size = new System.Drawing.Size(75, 23);
            this.cmdSupprimerAILE.TabIndex = 6;
            this.cmdSupprimerAILE.Text = "Supprimer";
            this.cmdSupprimerAILE.UseVisualStyleBackColor = true;
            this.cmdSupprimerAILE.Click += new System.EventHandler(this.cmdSupprimerAILE_Click);
            // 
            // cmdEditerAILE
            // 
            this.cmdEditerAILE.Location = new System.Drawing.Point(444, 247);
            this.cmdEditerAILE.Name = "cmdEditerAILE";
            this.cmdEditerAILE.Size = new System.Drawing.Size(75, 23);
            this.cmdEditerAILE.TabIndex = 5;
            this.cmdEditerAILE.Text = "Editer...";
            this.cmdEditerAILE.UseVisualStyleBackColor = true;
            this.cmdEditerAILE.Click += new System.EventHandler(this.cmdEditerAILE_Click);
            // 
            // cmdNouveauAILE
            // 
            this.cmdNouveauAILE.Location = new System.Drawing.Point(525, 247);
            this.cmdNouveauAILE.Name = "cmdNouveauAILE";
            this.cmdNouveauAILE.Size = new System.Drawing.Size(100, 23);
            this.cmdNouveauAILE.TabIndex = 4;
            this.cmdNouveauAILE.Text = "Nouveau AILE...";
            this.cmdNouveauAILE.UseVisualStyleBackColor = true;
            this.cmdNouveauAILE.Click += new System.EventHandler(this.cmdNouveauAILE_Click);
            // 
            // grdAILE
            // 
            this.grdAILE.AllowUserToAddRows = false;
            this.grdAILE.AllowUserToDeleteRows = false;
            this.grdAILE.AllowUserToResizeRows = false;
            this.grdAILE.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdAILE.Location = new System.Drawing.Point(3, 16);
            this.grdAILE.MultiSelect = false;
            this.grdAILE.Name = "grdAILE";
            this.grdAILE.ReadOnly = true;
            this.grdAILE.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.grdAILE.Size = new System.Drawing.Size(657, 185);
            this.grdAILE.TabIndex = 3;
            // 
            // tbCalendar
            // 
            this.tbCalendar.Controls.Add(this.cmdSaveCalendar);
            this.tbCalendar.Controls.Add(this.lblYear);
            this.tbCalendar.Controls.Add(this.cmdNextYear);
            this.tbCalendar.Controls.Add(this.cmdPreviousYear);
            this.tbCalendar.Controls.Add(this.grdCalendar);
            this.tbCalendar.Location = new System.Drawing.Point(4, 22);
            this.tbCalendar.Name = "tbCalendar";
            this.tbCalendar.Size = new System.Drawing.Size(757, 348);
            this.tbCalendar.TabIndex = 4;
            this.tbCalendar.Text = "Calendrier";
            this.tbCalendar.UseVisualStyleBackColor = true;
            this.tbCalendar.Click += new System.EventHandler(this.tbCalendar_Click);
            // 
            // cmdSaveCalendar
            // 
            this.cmdSaveCalendar.Location = new System.Drawing.Point(590, 15);
            this.cmdSaveCalendar.Name = "cmdSaveCalendar";
            this.cmdSaveCalendar.Size = new System.Drawing.Size(118, 23);
            this.cmdSaveCalendar.TabIndex = 4;
            this.cmdSaveCalendar.Text = "Sauver plannification";
            this.cmdSaveCalendar.UseVisualStyleBackColor = true;
            this.cmdSaveCalendar.Click += new System.EventHandler(this.cmdSaveCalendar_Click);
            // 
            // lblYear
            // 
            this.lblYear.AutoSize = true;
            this.lblYear.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblYear.Location = new System.Drawing.Point(321, 10);
            this.lblYear.Name = "lblYear";
            this.lblYear.Size = new System.Drawing.Size(65, 29);
            this.lblYear.TabIndex = 3;
            this.lblYear.Text = "2006";
            this.lblYear.Click += new System.EventHandler(this.lblYear_Click);
            // 
            // cmdNextYear
            // 
            this.cmdNextYear.Location = new System.Drawing.Point(392, 10);
            this.cmdNextYear.Name = "cmdNextYear";
            this.cmdNextYear.Size = new System.Drawing.Size(32, 33);
            this.cmdNextYear.TabIndex = 2;
            this.cmdNextYear.Text = ">>";
            this.cmdNextYear.UseVisualStyleBackColor = true;
            this.cmdNextYear.Click += new System.EventHandler(this.cmdNextYear_Click);
            // 
            // cmdPreviousYear
            // 
            this.cmdPreviousYear.Location = new System.Drawing.Point(283, 9);
            this.cmdPreviousYear.Name = "cmdPreviousYear";
            this.cmdPreviousYear.Size = new System.Drawing.Size(32, 34);
            this.cmdPreviousYear.TabIndex = 1;
            this.cmdPreviousYear.Text = "<<";
            this.cmdPreviousYear.UseVisualStyleBackColor = true;
            this.cmdPreviousYear.Click += new System.EventHandler(this.cmdPreviousYear_Click);
            // 
            // grdCalendar
            // 
            this.grdCalendar.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdCalendar.Location = new System.Drawing.Point(3, 49);
            this.grdCalendar.Name = "grdCalendar";
            this.grdCalendar.Size = new System.Drawing.Size(746, 294);
            this.grdCalendar.TabIndex = 0;
            this.grdCalendar.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.grdCalendar_CellContentClick);
            // 
            // FrmUser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(773, 614);
            this.Controls.Add(this.tabUser);
            this.Controls.Add(this.dgrUser);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmUser";
            this.Text = "Edition des utilisateurs";
            this.Load += new System.EventHandler(this.FrmUser_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgrUser)).EndInit();
            this.tabUser.ResumeLayout(false);
            this.tbData.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tbAIP.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdAIP)).EndInit();
            this.tbAILE.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdAILE)).EndInit();
            this.tbCalendar.ResumeLayout(false);
            this.tbCalendar.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdCalendar)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgrUser;
        private System.Windows.Forms.TabControl tabUser;
        private System.Windows.Forms.TabPage tbData;
        private System.Windows.Forms.TabPage tbAIP;
        private System.Windows.Forms.TabPage tbAILE;
        private System.Windows.Forms.Button cmdSauver;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox chkAsynchrone;
        private System.Windows.Forms.ComboBox cboGrade;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtEmail;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtPrenom;
        private System.Windows.Forms.Label lblPrenom;
        private System.Windows.Forms.TextBox txtNom;
        private System.Windows.Forms.Label lblNom;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtConfirmation;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtMotDePasse;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtLogin;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button cmdNouveau;
        private System.Windows.Forms.DataGridView grdAIP;
        private System.Windows.Forms.Button cmdNouveauAIP;
        private System.Windows.Forms.Button cmdEditerAIP;
        private System.Windows.Forms.Button cmdEditerAILE;
        private System.Windows.Forms.Button cmdNouveauAILE;
        private System.Windows.Forms.DataGridView grdAILE;
        private System.Windows.Forms.Button cmdSupprimerAILE;
        private System.Windows.Forms.Button cmdSupprimerAIP;
        private System.Windows.Forms.TabPage tbCalendar;
        private System.Windows.Forms.DataGridView grdCalendar;
        private System.Windows.Forms.Button cmdNextYear;
        private System.Windows.Forms.Button cmdPreviousYear;
        private System.Windows.Forms.Label lblYear;
        private System.Windows.Forms.Button cmdSaveCalendar;
        private System.Windows.Forms.TextBox txtTelephone;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button cmdFermer;
    }
}