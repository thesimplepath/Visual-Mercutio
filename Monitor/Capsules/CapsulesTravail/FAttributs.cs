using System;
using System.Data;

namespace CapsulesTravail
{
    /// <author>Cédric Michelet</author>
    /// <date>16.06.2005</date>
    /// <version>1.0 made by Icare Institute, CH-Sierre</version>
    /// <modification>
    ///		<author></author>
    ///		<date></date>
    ///		<description></description>
    /// </modification>
    /// <summary>
    /// Form to handle the attributs
    /// </summary>
    public class FAttributs : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Button bClose;
        private System.Windows.Forms.DataGrid dgAttributs;
        private System.Windows.Forms.DataGridTableStyle dataGridTableStyleAttributs;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnAttributsName;
        private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumnAttributsValue;

        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.Container components = null;

        private DataView _dsView;
        private bool _dataHaveBeenModified = false;
        private FMain _parent;
        private bool _canEdit;

        public FAttributs(DataSet dsToDisplay, String tableName, FMain parent, bool canEdit)
        {
            // required for Windows Form Designer support
            InitializeComponent();

            // the dataset allow adding value, and this functionality cannot be invalidated.
            // As we don't want to add value, but just modify the existing one, we create a dataset
            // to wrap around the selected table
            _dsView                                 = new DataView(dsToDisplay.Tables[tableName]);
            _dsView.AllowDelete                     = false;
            _dsView.AllowNew                        = false;
            _dsView.AllowEdit                       = canEdit;
            _canEdit                                = canEdit;
            dgAttributs.DataSource                  = _dsView;
            dataGridTableStyleAttributs.MappingName = tableName;

            // event to handle the flag that indicate a change in the data
            _dsView.ListChanged += new System.ComponentModel.ListChangedEventHandler(OnListChanged);

            _parent = parent;
        }

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
                if(components != null)
                    components.Dispose();

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FAttributs));
            this.dgAttributs = new System.Windows.Forms.DataGrid();
            this.dataGridTableStyleAttributs = new System.Windows.Forms.DataGridTableStyle();
            this.dataGridTextBoxColumnAttributsName = new System.Windows.Forms.DataGridTextBoxColumn();
            this.dataGridTextBoxColumnAttributsValue = new System.Windows.Forms.DataGridTextBoxColumn();
            this.bClose = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgAttributs)).BeginInit();
            this.SuspendLayout();
            // 
            // dgAttributs
            // 
            this.dgAttributs.CaptionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(204)))), ((int)(((byte)(66)))), ((int)(((byte)(0)))));
            this.dgAttributs.CaptionText = "Attributs";
            this.dgAttributs.ColumnHeadersVisible = false;
            this.dgAttributs.DataMember = "";
            this.dgAttributs.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgAttributs.Location = new System.Drawing.Point(8, 8);
            this.dgAttributs.Name = "dgAttributs";
            this.dgAttributs.ParentRowsVisible = false;
            this.dgAttributs.RowHeadersVisible = false;
            this.dgAttributs.Size = new System.Drawing.Size(464, 216);
            this.dgAttributs.TabIndex = 0;
            this.dgAttributs.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
            this.dataGridTableStyleAttributs});
            this.dgAttributs.CurrentCellChanged += new System.EventHandler(this.dgAttributs_CurrentCellChanged);
            // 
            // dataGridTableStyleAttributs
            // 
            this.dataGridTableStyleAttributs.ColumnHeadersVisible = false;
            this.dataGridTableStyleAttributs.DataGrid = this.dgAttributs;
            this.dataGridTableStyleAttributs.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
            this.dataGridTextBoxColumnAttributsName,
            this.dataGridTextBoxColumnAttributsValue});
            this.dataGridTableStyleAttributs.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridTableStyleAttributs.RowHeadersVisible = false;
            // 
            // dataGridTextBoxColumnAttributsName
            // 
            this.dataGridTextBoxColumnAttributsName.Format = "";
            this.dataGridTextBoxColumnAttributsName.FormatInfo = null;
            this.dataGridTextBoxColumnAttributsName.MappingName = "name";
            this.dataGridTextBoxColumnAttributsName.ReadOnly = true;
            this.dataGridTextBoxColumnAttributsName.Width = 75;
            // 
            // dataGridTextBoxColumnAttributsValue
            // 
            this.dataGridTextBoxColumnAttributsValue.Format = "";
            this.dataGridTextBoxColumnAttributsValue.FormatInfo = null;
            this.dataGridTextBoxColumnAttributsValue.MappingName = "value";
            this.dataGridTextBoxColumnAttributsValue.Width = 75;
            // 
            // bClose
            // 
            this.bClose.Location = new System.Drawing.Point(392, 232);
            this.bClose.Name = "bClose";
            this.bClose.Size = new System.Drawing.Size(75, 23);
            this.bClose.TabIndex = 1;
            this.bClose.Text = "Fermer";
            this.bClose.Click += new System.EventHandler(this.bClose_Click);
            // 
            // FAttributs
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(480, 285);
            this.Controls.Add(this.bClose);
            this.Controls.Add(this.dgAttributs);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FAttributs";
            this.Text = "Attributs";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.FAttributs_Closing);
            this.Load += new System.EventHandler(this.FAttributs_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgAttributs)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private void FAttributs_Load(object sender, System.EventArgs e)
        {
            // do the layout of the grids
            doLayout();
        }

        /// <summary>
        /// Event on the dataview that change the flag that indicate that the data have been modified
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        protected void OnListChanged(object sender, System.ComponentModel.ListChangedEventArgs args)
        {
            _dataHaveBeenModified = true ;
        }

        /// <summary>
        /// Close the window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bClose_Click(object sender, System.EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// Check if the data have been modified, and if the user want to save the modifications
        /// </summary>
        private void checkIfNeedToBeSaved()
        {
            if (!_dataHaveBeenModified)
                return;

            // inform the parent that data need to be saved
            _parent.setFileHasBeenModified(true);
        }

        /// <summary>
        /// Before closing the window, check is need to save
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FAttributs_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            checkIfNeedToBeSaved();
        }

        /// <summary>
        /// Do the layout of the grid (size of columns)
        /// </summary>
        private void doLayout()
        {
            dataGridTextBoxColumnAttributsName.Width  = dgAttributs.Width / 2 - 5;
            dataGridTextBoxColumnAttributsValue.Width = dgAttributs.Width / 2;
        }

        /// <summary>
        /// Check if we can edit or not the current attribut
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dgAttributs_CurrentCellChanged(object sender, System.EventArgs e)
        {
            if ((String)_dsView.Table.Rows[dgAttributs.CurrentRowIndex]["mflag"] != "2")
                _dsView.AllowEdit = false;
            else
                _dsView.AllowEdit = _canEdit;
        }
    }
}
