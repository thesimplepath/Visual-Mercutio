namespace Visual_Mercutio_Reports_Manager
{
	partial class MainFrame
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

		#region Code généré par le Concepteur Windows Form

		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( MainFrame ) );
            this.lblConnectedDatabase = new System.Windows.Forms.Label();
            this.tbConnectedDatabase = new System.Windows.Forms.TextBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.gbxConnectionsData = new System.Windows.Forms.GroupBox();
            this.btnTestConnection = new System.Windows.Forms.Button();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.errConnectedDatabase = new System.Windows.Forms.ErrorProvider( this.components );
            this.ofdOpenDatabase = new System.Windows.Forms.OpenFileDialog();
            this.cbxOS = new System.Windows.Forms.ComboBox();
            this.btnModifyOS = new System.Windows.Forms.Button();
            this.gbxOS = new System.Windows.Forms.GroupBox();
            this.lblCurrentOS = new System.Windows.Forms.Label();
            this.gbxTasks = new System.Windows.Forms.GroupBox();
            this.rtbModifications = new RichTextEditor.RichTextEditor();
            this.lblModifications = new System.Windows.Forms.Label();
            this.tbDescription = new System.Windows.Forms.TextBox();
            this.lblDescription = new System.Windows.Forms.Label();
            this.lblDate = new System.Windows.Forms.Label();
            this.dtpDate = new System.Windows.Forms.DateTimePicker();
            this.btnModifyState = new System.Windows.Forms.Button();
            this.btnModifyPriority = new System.Windows.Forms.Button();
            this.btnModifyAuthor = new System.Windows.Forms.Button();
            this.btnModifyType = new System.Windows.Forms.Button();
            this.cbxState = new System.Windows.Forms.ComboBox();
            this.cbxPriority = new System.Windows.Forms.ComboBox();
            this.lblState = new System.Windows.Forms.Label();
            this.lblPriority = new System.Windows.Forms.Label();
            this.cbxAuthor = new System.Windows.Forms.ComboBox();
            this.lblAuthor = new System.Windows.Forms.Label();
            this.cbxType = new System.Windows.Forms.ComboBox();
            this.lblType = new System.Windows.Forms.Label();
            this.btnPrev = new System.Windows.Forms.Button();
            this.tbID = new System.Windows.Forms.TextBox();
            this.btnNext = new System.Windows.Forms.Button();
            this.btnFirst = new System.Windows.Forms.Button();
            this.btnLast = new System.Windows.Forms.Button();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnModifyMainTable = new System.Windows.Forms.Button();
            this.gbxConnectionsData.SuspendLayout();
            ( (System.ComponentModel.ISupportInitialize)( this.errConnectedDatabase ) ).BeginInit();
            this.gbxOS.SuspendLayout();
            this.gbxTasks.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblConnectedDatabase
            // 
            this.lblConnectedDatabase.AutoSize = true;
            this.lblConnectedDatabase.Location = new System.Drawing.Point( 3, 16 );
            this.lblConnectedDatabase.Name = "lblConnectedDatabase";
            this.lblConnectedDatabase.Size = new System.Drawing.Size( 107, 13 );
            this.lblConnectedDatabase.TabIndex = 0;
            this.lblConnectedDatabase.Text = "Database to connect";
            // 
            // tbConnectedDatabase
            // 
            this.tbConnectedDatabase.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.tbConnectedDatabase.Location = new System.Drawing.Point( 6, 32 );
            this.tbConnectedDatabase.Name = "tbConnectedDatabase";
            this.tbConnectedDatabase.Size = new System.Drawing.Size( 353, 20 );
            this.tbConnectedDatabase.TabIndex = 1;
            // 
            // btnConnect
            // 
            this.btnConnect.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.btnConnect.Enabled = false;
            this.btnConnect.Location = new System.Drawing.Point( 284, 58 );
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size( 75, 23 );
            this.btnConnect.TabIndex = 4;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler( this.btnConnect_Click );
            // 
            // gbxConnectionsData
            // 
            this.gbxConnectionsData.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.gbxConnectionsData.Controls.Add( this.btnTestConnection );
            this.gbxConnectionsData.Controls.Add( this.btnBrowse );
            this.gbxConnectionsData.Controls.Add( this.lblConnectedDatabase );
            this.gbxConnectionsData.Controls.Add( this.btnConnect );
            this.gbxConnectionsData.Controls.Add( this.tbConnectedDatabase );
            this.gbxConnectionsData.Location = new System.Drawing.Point( 13, 13 );
            this.gbxConnectionsData.Name = "gbxConnectionsData";
            this.gbxConnectionsData.Size = new System.Drawing.Size( 375, 90 );
            this.gbxConnectionsData.TabIndex = 0;
            this.gbxConnectionsData.TabStop = false;
            this.gbxConnectionsData.Text = "Connections datas";
            // 
            // btnTestConnection
            // 
            this.btnTestConnection.Location = new System.Drawing.Point( 40, 58 );
            this.btnTestConnection.Name = "btnTestConnection";
            this.btnTestConnection.Size = new System.Drawing.Size( 103, 23 );
            this.btnTestConnection.TabIndex = 3;
            this.btnTestConnection.Text = "Test Connection";
            this.btnTestConnection.UseVisualStyleBackColor = true;
            this.btnTestConnection.Click += new System.EventHandler( this.btnTestConnection_Click );
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point( 6, 58 );
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size( 28, 23 );
            this.btnBrowse.TabIndex = 2;
            this.btnBrowse.Text = "...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler( this.btnBrowse_Click );
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.btnSave.Enabled = false;
            this.btnSave.Location = new System.Drawing.Point( 695, 531 );
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size( 85, 23 );
            this.btnSave.TabIndex = 10;
            this.btnSave.Text = "Save changes";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler( this.btnSave_Click );
            // 
            // errConnectedDatabase
            // 
            this.errConnectedDatabase.ContainerControl = this;
            // 
            // ofdOpenDatabase
            // 
            this.ofdOpenDatabase.FileName = "Open Database";
            this.ofdOpenDatabase.Filter = "Access database file (*.mdb)|*.mdb";
            // 
            // cbxOS
            // 
            this.cbxOS.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.cbxOS.Enabled = false;
            this.cbxOS.FormattingEnabled = true;
            this.cbxOS.Location = new System.Drawing.Point( 6, 31 );
            this.cbxOS.Name = "cbxOS";
            this.cbxOS.Size = new System.Drawing.Size( 363, 21 );
            this.cbxOS.TabIndex = 1;
            this.cbxOS.SelectedIndexChanged += new System.EventHandler( this.cbxOS_SelectedIndexChanged );
            // 
            // btnModifyOS
            // 
            this.btnModifyOS.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.btnModifyOS.Enabled = false;
            this.btnModifyOS.Location = new System.Drawing.Point( 103, 58 );
            this.btnModifyOS.Name = "btnModifyOS";
            this.btnModifyOS.Size = new System.Drawing.Size( 169, 23 );
            this.btnModifyOS.TabIndex = 2;
            this.btnModifyOS.Text = "Modify Operating Systems table";
            this.btnModifyOS.UseVisualStyleBackColor = true;
            this.btnModifyOS.Click += new System.EventHandler( this.btnModifyOS_Click );
            // 
            // gbxOS
            // 
            this.gbxOS.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.gbxOS.Controls.Add( this.lblCurrentOS );
            this.gbxOS.Controls.Add( this.cbxOS );
            this.gbxOS.Controls.Add( this.btnModifyOS );
            this.gbxOS.Location = new System.Drawing.Point( 405, 13 );
            this.gbxOS.Name = "gbxOS";
            this.gbxOS.Size = new System.Drawing.Size( 375, 90 );
            this.gbxOS.TabIndex = 1;
            this.gbxOS.TabStop = false;
            this.gbxOS.Text = "Operating systems";
            // 
            // lblCurrentOS
            // 
            this.lblCurrentOS.AutoSize = true;
            this.lblCurrentOS.Location = new System.Drawing.Point( 6, 16 );
            this.lblCurrentOS.Name = "lblCurrentOS";
            this.lblCurrentOS.Size = new System.Drawing.Size( 123, 13 );
            this.lblCurrentOS.TabIndex = 0;
            this.lblCurrentOS.Text = "Current operating system";
            // 
            // gbxTasks
            // 
            this.gbxTasks.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.gbxTasks.Controls.Add( this.rtbModifications );
            this.gbxTasks.Controls.Add( this.lblModifications );
            this.gbxTasks.Controls.Add( this.tbDescription );
            this.gbxTasks.Controls.Add( this.lblDescription );
            this.gbxTasks.Controls.Add( this.lblDate );
            this.gbxTasks.Controls.Add( this.dtpDate );
            this.gbxTasks.Controls.Add( this.btnModifyState );
            this.gbxTasks.Controls.Add( this.btnModifyPriority );
            this.gbxTasks.Controls.Add( this.btnModifyAuthor );
            this.gbxTasks.Controls.Add( this.btnModifyType );
            this.gbxTasks.Controls.Add( this.cbxState );
            this.gbxTasks.Controls.Add( this.cbxPriority );
            this.gbxTasks.Controls.Add( this.lblState );
            this.gbxTasks.Controls.Add( this.lblPriority );
            this.gbxTasks.Controls.Add( this.cbxAuthor );
            this.gbxTasks.Controls.Add( this.lblAuthor );
            this.gbxTasks.Controls.Add( this.cbxType );
            this.gbxTasks.Controls.Add( this.lblType );
            this.gbxTasks.Location = new System.Drawing.Point( 12, 109 );
            this.gbxTasks.Name = "gbxTasks";
            this.gbxTasks.Size = new System.Drawing.Size( 768, 416 );
            this.gbxTasks.TabIndex = 2;
            this.gbxTasks.TabStop = false;
            this.gbxTasks.Text = "Visual Mercutio tasks";
            // 
            // rtbModifications
            // 
            this.rtbModifications.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                        | System.Windows.Forms.AnchorStyles.Left )
                        | System.Windows.Forms.AnchorStyles.Right ) ) );
            this.rtbModifications.Enabled = false;
            this.rtbModifications.Location = new System.Drawing.Point( 6, 145 );
            this.rtbModifications.Modified = false;
            this.rtbModifications.Name = "rtbModifications";
            this.rtbModifications.Size = new System.Drawing.Size( 756, 265 );
            this.rtbModifications.TabIndex = 18;
            // 
            // lblModifications
            // 
            this.lblModifications.AutoSize = true;
            this.lblModifications.Location = new System.Drawing.Point( 7, 129 );
            this.lblModifications.Name = "lblModifications";
            this.lblModifications.Size = new System.Drawing.Size( 69, 13 );
            this.lblModifications.TabIndex = 16;
            this.lblModifications.Text = "Modifications";
            // 
            // tbDescription
            // 
            this.tbDescription.Enabled = false;
            this.tbDescription.Location = new System.Drawing.Point( 198, 103 );
            this.tbDescription.Name = "tbDescription";
            this.tbDescription.Size = new System.Drawing.Size( 564, 20 );
            this.tbDescription.TabIndex = 15;
            // 
            // lblDescription
            // 
            this.lblDescription.AutoSize = true;
            this.lblDescription.Location = new System.Drawing.Point( 195, 86 );
            this.lblDescription.Name = "lblDescription";
            this.lblDescription.Size = new System.Drawing.Size( 60, 13 );
            this.lblDescription.TabIndex = 14;
            this.lblDescription.Text = "Description";
            // 
            // lblDate
            // 
            this.lblDate.AutoSize = true;
            this.lblDate.Location = new System.Drawing.Point( 6, 86 );
            this.lblDate.Name = "lblDate";
            this.lblDate.Size = new System.Drawing.Size( 65, 13 );
            this.lblDate.TabIndex = 12;
            this.lblDate.Text = "Closing date";
            // 
            // dtpDate
            // 
            this.dtpDate.Enabled = false;
            this.dtpDate.Location = new System.Drawing.Point( 7, 102 );
            this.dtpDate.Name = "dtpDate";
            this.dtpDate.Size = new System.Drawing.Size( 180, 20 );
            this.dtpDate.TabIndex = 13;
            // 
            // btnModifyState
            // 
            this.btnModifyState.Enabled = false;
            this.btnModifyState.Location = new System.Drawing.Point( 582, 59 );
            this.btnModifyState.Name = "btnModifyState";
            this.btnModifyState.Size = new System.Drawing.Size( 180, 23 );
            this.btnModifyState.TabIndex = 11;
            this.btnModifyState.Text = "Modify states table";
            this.btnModifyState.UseVisualStyleBackColor = true;
            this.btnModifyState.Click += new System.EventHandler( this.btnModifyState_Click );
            // 
            // btnModifyPriority
            // 
            this.btnModifyPriority.Enabled = false;
            this.btnModifyPriority.Location = new System.Drawing.Point( 389, 60 );
            this.btnModifyPriority.Name = "btnModifyPriority";
            this.btnModifyPriority.Size = new System.Drawing.Size( 180, 23 );
            this.btnModifyPriority.TabIndex = 8;
            this.btnModifyPriority.Text = "Modify Priority table";
            this.btnModifyPriority.UseVisualStyleBackColor = true;
            this.btnModifyPriority.Click += new System.EventHandler( this.btnModifyPriority_Click );
            // 
            // btnModifyAuthor
            // 
            this.btnModifyAuthor.Enabled = false;
            this.btnModifyAuthor.Location = new System.Drawing.Point( 198, 60 );
            this.btnModifyAuthor.Name = "btnModifyAuthor";
            this.btnModifyAuthor.Size = new System.Drawing.Size( 180, 23 );
            this.btnModifyAuthor.TabIndex = 5;
            this.btnModifyAuthor.Text = "Modify Authors table";
            this.btnModifyAuthor.UseVisualStyleBackColor = true;
            this.btnModifyAuthor.Click += new System.EventHandler( this.btnModifyAuthor_Click );
            // 
            // btnModifyType
            // 
            this.btnModifyType.Enabled = false;
            this.btnModifyType.Location = new System.Drawing.Point( 7, 60 );
            this.btnModifyType.Name = "btnModifyType";
            this.btnModifyType.Size = new System.Drawing.Size( 180, 23 );
            this.btnModifyType.TabIndex = 2;
            this.btnModifyType.Text = "Modify Types table";
            this.btnModifyType.UseVisualStyleBackColor = true;
            this.btnModifyType.Click += new System.EventHandler( this.btnModifyType_Click );
            // 
            // cbxState
            // 
            this.cbxState.Enabled = false;
            this.cbxState.FormattingEnabled = true;
            this.cbxState.IntegralHeight = false;
            this.cbxState.Location = new System.Drawing.Point( 582, 32 );
            this.cbxState.Name = "cbxState";
            this.cbxState.Size = new System.Drawing.Size( 180, 21 );
            this.cbxState.TabIndex = 10;
            // 
            // cbxPriority
            // 
            this.cbxPriority.Enabled = false;
            this.cbxPriority.FormattingEnabled = true;
            this.cbxPriority.Location = new System.Drawing.Point( 389, 32 );
            this.cbxPriority.Name = "cbxPriority";
            this.cbxPriority.Size = new System.Drawing.Size( 180, 21 );
            this.cbxPriority.TabIndex = 7;
            // 
            // lblState
            // 
            this.lblState.AutoSize = true;
            this.lblState.Location = new System.Drawing.Point( 577, 16 );
            this.lblState.Name = "lblState";
            this.lblState.Size = new System.Drawing.Size( 32, 13 );
            this.lblState.TabIndex = 9;
            this.lblState.Text = "State";
            // 
            // lblPriority
            // 
            this.lblPriority.AutoSize = true;
            this.lblPriority.Location = new System.Drawing.Point( 386, 16 );
            this.lblPriority.Name = "lblPriority";
            this.lblPriority.Size = new System.Drawing.Size( 38, 13 );
            this.lblPriority.TabIndex = 6;
            this.lblPriority.Text = "Priority";
            // 
            // cbxAuthor
            // 
            this.cbxAuthor.Enabled = false;
            this.cbxAuthor.FormattingEnabled = true;
            this.cbxAuthor.Location = new System.Drawing.Point( 198, 32 );
            this.cbxAuthor.Name = "cbxAuthor";
            this.cbxAuthor.Size = new System.Drawing.Size( 180, 21 );
            this.cbxAuthor.TabIndex = 4;
            this.cbxAuthor.SelectedIndexChanged += new System.EventHandler( this.cbxAuthor_SelectedIndexChanged );
            // 
            // lblAuthor
            // 
            this.lblAuthor.AutoSize = true;
            this.lblAuthor.Location = new System.Drawing.Point( 195, 16 );
            this.lblAuthor.Name = "lblAuthor";
            this.lblAuthor.Size = new System.Drawing.Size( 38, 13 );
            this.lblAuthor.TabIndex = 3;
            this.lblAuthor.Text = "Author";
            // 
            // cbxType
            // 
            this.cbxType.Enabled = false;
            this.cbxType.FormattingEnabled = true;
            this.cbxType.Location = new System.Drawing.Point( 7, 32 );
            this.cbxType.Name = "cbxType";
            this.cbxType.Size = new System.Drawing.Size( 180, 21 );
            this.cbxType.TabIndex = 1;
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point( 4, 16 );
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size( 31, 13 );
            this.lblType.TabIndex = 0;
            this.lblType.Text = "Type";
            // 
            // btnPrev
            // 
            this.btnPrev.Enabled = false;
            this.btnPrev.Location = new System.Drawing.Point( 53, 531 );
            this.btnPrev.Name = "btnPrev";
            this.btnPrev.Size = new System.Drawing.Size( 35, 23 );
            this.btnPrev.TabIndex = 4;
            this.btnPrev.Text = "<";
            this.btnPrev.UseVisualStyleBackColor = true;
            this.btnPrev.Click += new System.EventHandler( this.btnPrev_Click );
            // 
            // tbID
            // 
            this.tbID.Enabled = false;
            this.tbID.Location = new System.Drawing.Point( 94, 533 );
            this.tbID.Name = "tbID";
            this.tbID.Size = new System.Drawing.Size( 35, 20 );
            this.tbID.TabIndex = 5;
            // 
            // btnNext
            // 
            this.btnNext.Enabled = false;
            this.btnNext.Location = new System.Drawing.Point( 135, 531 );
            this.btnNext.Name = "btnNext";
            this.btnNext.Size = new System.Drawing.Size( 35, 23 );
            this.btnNext.TabIndex = 6;
            this.btnNext.Text = ">";
            this.btnNext.UseVisualStyleBackColor = true;
            this.btnNext.Click += new System.EventHandler( this.btnNext_Click );
            // 
            // btnFirst
            // 
            this.btnFirst.Enabled = false;
            this.btnFirst.Location = new System.Drawing.Point( 12, 531 );
            this.btnFirst.Name = "btnFirst";
            this.btnFirst.Size = new System.Drawing.Size( 35, 23 );
            this.btnFirst.TabIndex = 3;
            this.btnFirst.Text = "<<";
            this.btnFirst.UseVisualStyleBackColor = true;
            this.btnFirst.Click += new System.EventHandler( this.btnFirst_Click );
            // 
            // btnLast
            // 
            this.btnLast.Enabled = false;
            this.btnLast.Location = new System.Drawing.Point( 176, 531 );
            this.btnLast.Name = "btnLast";
            this.btnLast.Size = new System.Drawing.Size( 35, 23 );
            this.btnLast.TabIndex = 7;
            this.btnLast.Text = ">>";
            this.btnLast.UseVisualStyleBackColor = true;
            this.btnLast.Click += new System.EventHandler( this.btnLast_Click );
            // 
            // btnAdd
            // 
            this.btnAdd.Enabled = false;
            this.btnAdd.Location = new System.Drawing.Point( 217, 531 );
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size( 35, 23 );
            this.btnAdd.TabIndex = 8;
            this.btnAdd.Text = "+";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler( this.btnAdd_Click );
            // 
            // btnModifyMainTable
            // 
            this.btnModifyMainTable.Enabled = false;
            this.btnModifyMainTable.Location = new System.Drawing.Point( 258, 531 );
            this.btnModifyMainTable.Name = "btnModifyMainTable";
            this.btnModifyMainTable.Size = new System.Drawing.Size( 120, 23 );
            this.btnModifyMainTable.TabIndex = 9;
            this.btnModifyMainTable.Text = "Modify Main Table";
            this.btnModifyMainTable.UseVisualStyleBackColor = true;
            this.btnModifyMainTable.Click += new System.EventHandler( this.btnModifyMainTable_Click );
            // 
            // MainFrame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 792, 566 );
            this.Controls.Add( this.btnModifyMainTable );
            this.Controls.Add( this.btnAdd );
            this.Controls.Add( this.btnLast );
            this.Controls.Add( this.btnFirst );
            this.Controls.Add( this.btnNext );
            this.Controls.Add( this.tbID );
            this.Controls.Add( this.btnPrev );
            this.Controls.Add( this.gbxTasks );
            this.Controls.Add( this.gbxOS );
            this.Controls.Add( this.gbxConnectionsData );
            this.Controls.Add( this.btnSave );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainFrame";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Visual Mercutio Reports Manager";
            this.Load += new System.EventHandler( this.MainFrame_Load );
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.MainFrame_FormClosing );
            this.gbxConnectionsData.ResumeLayout( false );
            this.gbxConnectionsData.PerformLayout();
            ( (System.ComponentModel.ISupportInitialize)( this.errConnectedDatabase ) ).EndInit();
            this.gbxOS.ResumeLayout( false );
            this.gbxOS.PerformLayout();
            this.gbxTasks.ResumeLayout( false );
            this.gbxTasks.PerformLayout();
            this.ResumeLayout( false );
            this.PerformLayout();

		}

		#endregion

        private System.Windows.Forms.Label lblConnectedDatabase;
        private System.Windows.Forms.TextBox tbConnectedDatabase;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.GroupBox gbxConnectionsData;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.Button btnTestConnection;
        private System.Windows.Forms.ErrorProvider errConnectedDatabase;
        private System.Windows.Forms.OpenFileDialog ofdOpenDatabase;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.ComboBox cbxOS;
        private System.Windows.Forms.Button btnModifyOS;
        private System.Windows.Forms.GroupBox gbxOS;
        private System.Windows.Forms.Label lblCurrentOS;
        private System.Windows.Forms.GroupBox gbxTasks;
        private System.Windows.Forms.ComboBox cbxState;
        private System.Windows.Forms.ComboBox cbxPriority;
        private System.Windows.Forms.Label lblState;
        private System.Windows.Forms.Label lblPriority;
        private System.Windows.Forms.ComboBox cbxAuthor;
        private System.Windows.Forms.Label lblAuthor;
        private System.Windows.Forms.ComboBox cbxType;
        private System.Windows.Forms.Label lblType;
        private System.Windows.Forms.Button btnModifyState;
        private System.Windows.Forms.Button btnModifyPriority;
        private System.Windows.Forms.Button btnModifyAuthor;
        private System.Windows.Forms.Button btnModifyType;
        private System.Windows.Forms.DateTimePicker dtpDate;
        private System.Windows.Forms.Label lblModifications;
        private System.Windows.Forms.TextBox tbDescription;
        private System.Windows.Forms.Label lblDescription;
        private System.Windows.Forms.Label lblDate;
        private System.Windows.Forms.Button btnPrev;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnLast;
        private System.Windows.Forms.Button btnFirst;
        private System.Windows.Forms.Button btnNext;
        private System.Windows.Forms.TextBox tbID;
        private System.Windows.Forms.Button btnModifyMainTable;
        private RichTextEditor.RichTextEditor rtbModifications;
    }
}
