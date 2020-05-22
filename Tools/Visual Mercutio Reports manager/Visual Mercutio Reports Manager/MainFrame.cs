/*****************************************************************************
 * ==> Class MainFrame ------------------------------------------------------*
 * ***************************************************************************
 * Description : Main frame for the application.                             *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using Visual_Mercutio_Reports_Manager.Tools;
using Visual_Mercutio_Reports_Manager.Database;
using Visual_Mercutio_Reports_Manager.Forms;

namespace Visual_Mercutio_Reports_Manager
{
    public partial class MainFrame : Form
    {
        #region Global variables

        private string                m_InfoCnSuccess          = "Connection successfull.";
        private string                m_UpdateSuccessfull      = "Update successfull.";
        private string                m_ErrEmptyField          = "This field cannot be empty.";
        private string                m_ErrFileDoesNotExist    = "This file does not exist.";
        private string                m_ErrCannotCreateConn    = "Error while creating new database connection.";
        private string                m_ErrCannotConnect       = "Error while connecting to database.";
        private string                m_ErrCannotUpdate        = "Error while updating database.";
        private string                m_ErrCannotFillOSCbx     = "Error while fill Operating Systems Combo Box.";
        private string                m_ErrCannotFillAuthorCbx = "Error while fill Authors Combo Box.";
        private string                m_InfoHasChanged         = "Do you want to save your changes ?";
        private string                m_Connect                = "Connect";
        private string                m_Disconnect             = "Disconnect";
        private string                m_ConfigFilename         = "Program.config";
        private string                m_InfoModifiedDoc        = "Your document is modified. Would you save your changes before go to next form ?";
        private string                m_Extension              = "mdb";
        private string                m_DatabaseDir            = "Database\\";
        private string                m_DataDir                = "Data\\";
        private string                m_InitialDir             = "";
        private string                m_CurrentDir             = "";

        private OleDatabaseConnection m_Connection;

        private OleDataSet            m_DataSet;
        private MessageDisplayer      m_MsgDisplayer;
        private ConfigFile            m_ConfigFile;

        private TraceSwitch           m_TraceSwitch;

        #endregion

        #region Delegates

        private delegate void ConnectionEnabledDelegate();
        private event ConnectionEnabledDelegate OnConnectionEnabled;

        private delegate void ConnectionDisabledDelegate();
        private event ConnectionDisabledDelegate OnConnectionDisabled;

        #endregion

        #region Construction/Desctuction

        /// <summary>
        /// Default constructor
        /// </summary>
        public MainFrame()
        {
            InitializeComponent();

            m_Connection   = null;
            m_MsgDisplayer = null;
            m_DataSet      = null;

            OnConnectionEnabled  += new ConnectionEnabledDelegate( EnableControls );
            OnConnectionDisabled += new ConnectionDisabledDelegate( DisableControls );

            m_TraceSwitch = new TraceSwitch( "MainTrace", "Main form trace switch." );
        }

        #endregion

        #region Private functions

        /// <summary>
        /// Test the connection
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        private bool TestConnection()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "TestConnection",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if filename is empty
            if ( tbConnectedDatabase.Text == "" )
            {
                // If empty, set error provider message, disable connect button, and return false.
                errConnectedDatabase.SetError( tbConnectedDatabase, m_ErrEmptyField );
                btnConnect.Enabled = false;

                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "MainFrame",
                                    "TestConnection",
                                    "Cannot connect to database because filename is empty. Function will quit with false value",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Check if filename exists
            if ( File.Exists( tbConnectedDatabase.Text ) == false )
            {
                // If not, set error provider message, disable connect button, and return false.
                errConnectedDatabase.SetError( tbConnectedDatabase, m_ErrFileDoesNotExist );
                btnConnect.Enabled = false;

                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "MainFrame",
                                    "TestConnection",
                                    "Cannot connect to database because file does not exist. Function will quit with false value",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Create a new connection
            if ( m_Connection.CreateConnection( tbConnectedDatabase.Text ) == false )
            {
                // If not, set error provider message, disable connect button, and return false.
                errConnectedDatabase.SetError( tbConnectedDatabase, m_ErrCannotCreateConn );
                btnConnect.Enabled = false;

                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "MainFrame",
                                    "TestConnection",
                                    "Cannot create connection.  Function will quit with false value",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Check if database connection success
            if ( m_Connection.TestConnection() == false )
            {
                // If not, set error provider message, disable connect button, and return false.
                errConnectedDatabase.SetError( tbConnectedDatabase, m_ErrCannotConnect );
                btnConnect.Enabled = false;

                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "MainFrame",
                                    "TestConnection",
                                    "Cannot connect to database because connection fails.  Function will quit with false value",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // If no errors, empty error provider message, enable connect button, and return true.
            errConnectedDatabase.SetError( tbConnectedDatabase, "" );
            btnConnect.Enabled = true;

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "TestConnection",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            return true;
        }

        /// <summary>
        /// Fill Operating System combo box
        /// </summary>
        private void FillOSComboBox()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "FillOSComboBox",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Get each row from table, and fill control with
                for ( int i = 0; i < m_DataSet.Data.Tables[1].Rows.Count; ++i )
                {
                    cbxOS.Items.Add( m_DataSet.Data.Tables[1].Rows[i]["Editor"] + " " +
                                     m_DataSet.Data.Tables[1].Rows[i]["Name"] + " " +
                                     m_DataSet.Data.Tables[1].Rows[i]["Version"] + " " +
                                     m_DataSet.Data.Tables[1].Rows[i]["ServicePack"] );
                }

                // Check if at least one row is filled
                if ( m_DataSet.Data.Tables[1].Rows.Count > 0 )
                {
                    // If yes, attempt to report user choice from table
                    if ( m_ConfigFile.OsID <= cbxOS.Items.Count )
                    {
                        // If choice is valid, report it
                        cbxOS.SelectedIndex = m_ConfigFile.OsID;
                    }
                    else
                    {
                        // If choice is not valid, select first ocurence
                        cbxOS.SelectedIndex = 0;
                    }
                }
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "FillOSComboBox",
                                    "Cannot fill OS Combobox, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                // Display message error
                m_MsgDisplayer.ShowError( m_ErrCannotFillOSCbx );
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "FillOSComboBox",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Fill authors combo box
        /// </summary>
        private void FillAuthorsComboBox()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "FillAuthorsComboBox",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Get each row from table, and fill control with
                for ( int i = 0; i < m_DataSet.Data.Tables[5].Rows.Count; ++i )
                {
                    cbxAuthor.Items.Add( m_DataSet.Data.Tables[5].Rows[i]["FirstName"] + " " +
                                         m_DataSet.Data.Tables[5].Rows[i]["LastName"] );
                }

                if ( m_DataSet.Data.Tables[5].Rows.Count > 0 )
                {
                    cbxAuthor.SelectedIndex = 0;
                }
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "FillAuthorsComboBox",
                                    "Cannot fill Authors combobox, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                m_MsgDisplayer.ShowError( m_ErrCannotFillAuthorCbx );
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "FillAuthorsComboBox",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Enables apropriate controls after database connected
        /// </summary>
        private void EnableControls()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "EnableControls",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Disable file dialog box while connection is open
            tbConnectedDatabase.Enabled = false;

            // Update controls
            btnBrowse.Enabled          = false;
            btnTestConnection.Enabled  = false;
            btnSave.Enabled            = true;
            cbxOS.Enabled              = true;
            btnModifyOS.Enabled        = true;
            cbxAuthor.Enabled          = true;
            cbxPriority.Enabled        = true;
            cbxState.Enabled           = true;
            cbxType.Enabled            = true;
            btnModifyAuthor.Enabled    = true;
            btnModifyPriority.Enabled  = true;
            btnModifyState.Enabled     = true;
            btnModifyType.Enabled      = true;
            dtpDate.Enabled            = true;
            tbDescription.Enabled      = true;
            rtbModifications.Enabled   = true;
            btnFirst.Enabled           = false;
            btnPrev.Enabled            = false;
            btnNext.Enabled            = true;
            btnLast.Enabled            = true;
            tbID.Enabled               = false;
            btnAdd.Enabled             = true;
            btnModifyMainTable.Enabled = true;

            // Modify connect text button
            btnConnect.Text = m_Disconnect;

            // Fill controls
            FillAuthorsComboBox();
            FillOSComboBox();

            // Link Priority control to Database
            cbxPriority.DataSource = m_DataSet.Data.Tables[2];
            cbxPriority.DisplayMember = "Name";

            // Link State control to Database
            cbxState.DataSource = m_DataSet.Data.Tables[3];
            cbxState.DisplayMember = "Name";

            // Link Type control to Database
            cbxType.DataSource = m_DataSet.Data.Tables[4];
            cbxType.DisplayMember = "Name";

            // We assume that at this point, database is correctly opened
            tbID.DataBindings.Add( "Text", m_DataSet.Data.Tables[0], "CaseID" );
            tbDescription.DataBindings.Add( "Text", m_DataSet.Data.Tables[0], "Description" );
            dtpDate.DataBindings.Add( "Text", m_DataSet.Data.Tables[0], "Date" );

            this.BindingContext[m_DataSet.Data.Tables[0]].Position = 0;

            // Update all controls
            UpdateControls();

            // Load data
            LoadData();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "EnableControls",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Disable controls after database disconnected
        /// </summary>
        private void DisableControls()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "DisableControls",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Enable file dialog box again after connection is disabled
            tbConnectedDatabase.Enabled = true;

            // Update controls
            btnBrowse.Enabled          = true;
            btnTestConnection.Enabled  = true;
            btnSave.Enabled            = false;
            cbxOS.Enabled              = false;
            btnModifyOS.Enabled        = false;
            cbxAuthor.Enabled          = false;
            cbxPriority.Enabled        = false;
            cbxState.Enabled           = false;
            cbxType.Enabled            = false;
            btnModifyAuthor.Enabled    = false;
            btnModifyPriority.Enabled  = false;
            btnModifyState.Enabled     = false;
            btnModifyType.Enabled      = false;
            dtpDate.Enabled            = false;
            tbDescription.Enabled      = false;
            rtbModifications.Enabled   = false;
            btnFirst.Enabled           = false;
            btnNext.Enabled            = false;
            btnPrev.Enabled            = false;
            btnLast.Enabled            = false;
            tbID.Enabled               = false;
            btnAdd.Enabled             = false;
            btnModifyMainTable.Enabled = false;

            // Modify disconnect text button
            btnConnect.Text = m_Connect;

            // Empty combo boxes
            cbxOS.Items.Clear();
            cbxOS.ResetText();
            cbxAuthor.Items.Clear();
            cbxAuthor.ResetText();
            cbxPriority.Items.Clear();
            cbxPriority.ResetText();
            cbxState.Items.Clear();
            cbxState.ResetText();
            cbxType.Items.Clear();
            cbxType.ResetText();

            // Remove data binding
            cbxPriority.DataSource    = null;
            cbxPriority.DisplayMember = "";
            cbxState.DataSource       = null;
            cbxState.DisplayMember    = "";
            cbxType.DataSource        = null;
            cbxType.DisplayMember     = "";
            tbID.DataBindings.Remove( tbID.DataBindings["Text"] );
            tbDescription.DataBindings.Remove( tbDescription.DataBindings["Text"] );
            dtpDate.DataBindings.Remove( dtpDate.DataBindings["Text"] );

            // Empty description text box
            tbDescription.Text = "";

            // Empty Modifications Rich Text Box
            rtbModifications.Text = "";

            // Empty ID text box
            tbID.Text = "";

            // Clear modifications
            rtbModifications.Clear();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "DisableControls",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Update controls after form changed
        /// </summary>
        private void UpdateControls()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "UpdateControls",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Update First and Prev buttons
                if ( this.BindingContext[m_DataSet.Data.Tables[0]].Position <= 0 )
                {
                    btnFirst.Enabled = false;
                    btnPrev.Enabled = false;
                }
                else
                {
                    btnFirst.Enabled = true;
                    btnPrev.Enabled = true;
                }

                // Update Last and Next buttons
                if ( this.BindingContext[m_DataSet.Data.Tables[0]].Position >=
                     m_DataSet.Data.Tables[0].Rows.Count - 1 )
                {
                    btnNext.Enabled = false;
                    btnLast.Enabled = false;
                }
                else
                {
                    btnNext.Enabled = true;
                    btnLast.Enabled = true;
                }

                // Update Priority combo box
                for ( int i = 0; i < m_DataSet.Data.Tables[2].Rows.Count; ++i )
                {
                    if ( m_DataSet.Data.Tables[0].Rows[this.BindingContext[m_DataSet.Data.Tables[0]].Position]["Priority"].ToString() == m_DataSet.Data.Tables[2].Rows[i]["PriorityID"].ToString() )
                    {
                        cbxPriority.SelectedIndex = i;
                    }
                }

                // Update State combo box
                for ( int i = 0; i < m_DataSet.Data.Tables[3].Rows.Count; ++i )
                {
                    if ( m_DataSet.Data.Tables[0].Rows[this.BindingContext[m_DataSet.Data.Tables[0]].Position]["State"].ToString() == m_DataSet.Data.Tables[3].Rows[i]["StateID"].ToString() )
                    {
                        cbxState.SelectedIndex = i;
                    }
                }

                // Update Type combo box
                for ( int i = 0; i < m_DataSet.Data.Tables[4].Rows.Count; ++i )
                {
                    if ( m_DataSet.Data.Tables[0].Rows[this.BindingContext[m_DataSet.Data.Tables[0]].Position]["Type"].ToString() == m_DataSet.Data.Tables[4].Rows[i]["TypeID"].ToString() )
                    {
                        cbxType.SelectedIndex = i;
                    }
                }

                // Update Authors combo box
                for ( int i = 0; i < m_DataSet.Data.Tables[5].Rows.Count; ++i )
                {
                    if ( m_DataSet.Data.Tables[0].Rows[this.BindingContext[m_DataSet.Data.Tables[0]].Position]["User"].ToString() == m_DataSet.Data.Tables[5].Rows[i]["UserID"].ToString() )
                    {
                        cbxAuthor.SelectedIndex = i;
                    }
                }
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "UpdateControls",
                                    "Cannot update controls, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "UpdateControls",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Check if data was modified, and ask user about data storing
        /// </summary>
        /// <returns>False if changes cancelled, otherwise true</returns>
        private bool CheckChanges()
        {
            try
            {
                // Trace begin function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "CheckChanges",
                                    "Begin function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                // Check for data changes into DataSet
                if ( m_DataSet != null && m_DataSet.Data != null && m_DataSet.Data.HasChanges() == true )
                {
                    // If changes, ask user about next operation
                    DialogResult Result = MessageBox.Show( m_InfoHasChanged,
                                                           m_MsgDisplayer.ApplicationTitle,
                                                           MessageBoxButtons.YesNoCancel,
                                                           MessageBoxIcon.Question );

                    if ( Result == DialogResult.Yes )
                    {
                        // Changes must be report into database. Attempt to update
                        if ( m_DataSet.Update() == false )
                        {
                            // If update failed, show error and cancel operation
                            m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                            return false;
                        }
                        else
                        {
                            // If update success, show message and confirm operation
                            m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                            return true;
                        }
                    }
                    else if ( Result == DialogResult.Cancel )
                    {
                        // If user cancel operation, return apropriate message
                        return false;
                    }
                }

                // In other case, confirm operation
                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "CheckChanges",
                                    "Cannot check changes, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                // Returns false if operation failed
                return false;
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "CheckChanges",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Load data form file
        /// </summary>
        /// <returns>True if document loaded, otherwise false</returns>
        private bool LoadData()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "LoadData",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Check if Rich text documents directory exists into current working dir
                if ( Directory.Exists( m_CurrentDir ) == true )
                {
                    // Check if Rich Text document file exists
                    if ( File.Exists( m_CurrentDir + tbID.Text + ".rtf" ) == true )
                    {
                        // If document exists, load it
                        rtbModifications.OpenFile( m_CurrentDir + tbID.Text + ".rtf" );

                        return true;
                    }
                }

                // If no document exists, simply clear control
                rtbModifications.Clear();

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "LoadData",
                                    "Cannot load document, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "LoadData",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Save data into file
        /// </summary>
        /// <returns>True if document saved, otherwise false</returns>
        private bool SaveData()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "SaveData",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Save global states
                if ( m_ConfigFile.Write() == false )
                {
                    m_MsgDisplayer.ShowError( "Error while writing program config file." );
                }

                // Check if directory exists into current working dir
                if ( Directory.Exists( rtbModifications.Directory ) == false )
                {
                    // If not, creates it
                    Directory.CreateDirectory( rtbModifications.Directory );
                }

                // Save current modifications into apropriate Rich Text file
                rtbModifications.SaveFile( rtbModifications.Directory + tbID.Text + ".rtf" );

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "SaveData",
                                    "Cannot save file, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "SaveData",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        #endregion

        #region Messages handling

        #region No controls messages handling
        /// <summary>
        /// Load application form
        /// </summary>
        /// <param name="sender">Object who are raised the event</param>
        /// <param name="e">Events arguments</param>
        private void MainFrame_Load( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "MainFrame_Load",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Initialize internal objects
                m_InitialDir               = Directory.GetCurrentDirectory() + "\\";
                m_Connection               = new OleDatabaseConnection();
                m_MsgDisplayer             = new MessageDisplayer( Text );
                m_ConfigFile               = new ConfigFile( m_InitialDir + m_ConfigFilename );
                TraceLog.Directory         = m_InitialDir;
                rtbModifications.Directory = m_InitialDir + m_DatabaseDir + m_DataDir;
                m_CurrentDir               = rtbModifications.Directory;

                m_ConfigFile.Read();
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "MainFrame",
                                    "MainFrame_Load",
                                    "Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "MainFrame",
                                    "MainFrame_Load",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Function called when form is closing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainFrame_FormClosing( object sender, FormClosingEventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "MainFrame_FormClosing",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check changes before closing
            if ( CheckChanges() == false )
            {
                e.Cancel = true;
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "MainFrame_FormClosing",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Raised when browse button is clicked
        /// </summary>
        /// <param name="sender">Object who are raised the event</param>
        /// <param name="e">Events arguments</param>
        private void btnBrowse_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnBrowse_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Configure dialog box with default extension
            ofdOpenDatabase.DefaultExt       = m_Extension;
            ofdOpenDatabase.InitialDirectory = m_InitialDir + m_DatabaseDir;

            // Open dialog box, and wait user result
            if ( ofdOpenDatabase.ShowDialog(this ) == DialogResult.OK)
            {
                // If Ok is clicked, update text box, and test connection
                tbConnectedDatabase.Text = ofdOpenDatabase.FileName;
                TestConnection();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnBrowse_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Raised when test connection button is clicked
        /// </summary>
        /// <param name="sender">Object who are raised the event</param>
        /// <param name="e">Events arguments</param>
        private void btnTestConnection_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnTestConnection_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check the database connection
            if ( TestConnection() == false )
            {
                // If an error occur, show dialog box error.
                m_MsgDisplayer.ShowError( m_ErrCannotConnect );
            }
            else
            {
                // If all is fine, show dialog box message.
                m_MsgDisplayer.ShowMessage( m_InfoCnSuccess );
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnTestConnection_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Raised when connect button is clicked
        /// </summary>
        /// <param name="sender">Object who are raised the event</param>
        /// <param name="e">Events arguments</param>
        private void btnConnect_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnConnect_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            if ( btnConnect.Text == m_Connect )
            {
                // Check the database connection
                if ( TestConnection() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnConnect_Click",
                                        "Connection to database failed. Function will quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // If an error occur, show dialog box error.
                    m_MsgDisplayer.ShowError( m_ErrCannotConnect );

                    return;
                }
                else
                {
                    // If connection success, configure current rich text box directory
                    rtbModifications.Directory = Directory.GetCurrentDirectory() + "\\" + m_DataDir;
                    m_CurrentDir               = rtbModifications.Directory;
                }

                try
                {
                    // Attempt to create database connection.
                    if ( m_Connection.CreateConnection( tbConnectedDatabase.Text ) == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "MainFrame",
                                            "btnConnect_Click",
                                            "Cannot create connection to database. Function will quit",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        // If an error occur, show dialog box error.
                        m_MsgDisplayer.ShowError( m_ErrCannotConnect );

                        return;
                    }

                    // Create new OleDataSet
                    m_DataSet = new OleDataSet( m_Connection );

                    // Attempt to connect OleDataSet to database.
                    if ( m_DataSet.Connect() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "MainFrame",
                                            "btnConnect_Click",
                                            "Cannot fill OleDataSet. Function will quit",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        // If an error occur, show dialog box error.
                        m_MsgDisplayer.ShowError( m_ErrCannotConnect );

                        return;
                    }

                    // Raise OnConnectionEnabled event.
                    OnConnectionEnabled();
                }
                catch ( Exception ex )
                {
                    // Trace error message
                    if ( m_TraceSwitch.TraceError )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnConnect_Click",
                                        "Cannot connect database, cause : " + ex.Message,
                                        ex.Source,
                                        TraceLog.TraceMsgLevel.Error,
                                        m_TraceSwitch );
                    }

                    m_MsgDisplayer.ShowError( m_ErrCannotConnect + " Cause :\r\n" + ex.Message );
                }
            }
            else
            {
                // Check for write user changes
                if ( CheckChanges() == true )
                {
                    m_DataSet.Disconnect();
                    m_Connection.Disconnect();

                    // Raise OnConnectionDisabled event.
                    OnConnectionDisabled();
                }
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnConnect_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Save button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSave_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnSave_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Attempt to update database
            if ( m_DataSet.Update() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "MainFrame",
                                    "btnSave_Click",
                                    "Cannot update database",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                // Show error message
                m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
            }
            else
            {
                // Save others data
                SaveData();

                // Show success message
                m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnSave_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify OS button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyOS_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyOS_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyOS ModifyOSForm = new ModifyOS( m_MsgDisplayer );
            int      TableID      = 1;

            // Set data source into Modify OS form
            ModifyOSForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify OS user interface, and wait for user result
            if ( ModifyOSForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyOS_Click",
                                        "Cannot update table T_OperatingSystems",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();

                // Refresh OS combo box
                cbxOS.Items.Clear();
                cbxOS.ResetText();
                FillOSComboBox();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyOS_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify Type button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyType_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyType_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyType ModifyTypeForm = new ModifyType( m_MsgDisplayer );
            int        TableID        = 4;

            // Set data source into Modify Type form
            ModifyTypeForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify Type user interface, and wait for user result
            if ( ModifyTypeForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyType_Click",
                                        "Cannot update table T_Type",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyType_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify Author button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyAuthor_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyAuthor_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyUsers ModifyUSersForm = new ModifyUsers( m_MsgDisplayer );
            int         TableID         = 5;

            // Set data source into Modify Authors form
            ModifyUSersForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify Authors user interface, and wait for user result
            if ( ModifyUSersForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyAuthor_Click",
                                        "Cannot update table T_Users",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();

                // Update Authors combo box
                cbxAuthor.Items.Clear();
                cbxAuthor.ResetText();
                FillAuthorsComboBox();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyAuthor_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify Priority button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyPriority_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyPriority_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyPriority ModifyPriorityForm = new ModifyPriority( m_MsgDisplayer );
            int            TableID            = 2;

            // Set data source into Modify Priority form
            ModifyPriorityForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify Priority user interface, and wait for user result
            if ( ModifyPriorityForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyPriority_Click",
                                        "Cannot update table T_Priority",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyPriority_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify State button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyState_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyState_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyState ModifyStateForm = new ModifyState( m_MsgDisplayer );
            int         TableID         = 3;

            // Set data source into Modify State form
            ModifyStateForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify State user interface, and wait for user result
            if ( ModifyStateForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyState_Click",
                                        "Cannot update table T_State",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyState_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Modify Main Table button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModifyMainTable_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyMainTable_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            ModifyCase ModifyCaseForm = new ModifyCase( m_MsgDisplayer );
            int         TableID       = 0;

            // Set data source into Modify Main Table form
            ModifyCaseForm.BindData( m_DataSet.Data.Tables[TableID] );

            // Open Modify Main table user interface, and wait for user result
            if ( ModifyCaseForm.ShowDialog( this ) == DialogResult.OK )
            {
                // If result is Ok, update table
                if ( m_DataSet.UpdateTable( TableID ) == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnModifyMainTable_Click",
                                        "Cannot update table T_Case",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    // Show error
                    m_MsgDisplayer.ShowError( m_ErrCannotUpdate );
                }
                else
                {
                    // Show success message
                    m_MsgDisplayer.ShowMessage( m_UpdateSuccessfull );
                }

                // Accept changes into database
                m_DataSet.Data.Tables[TableID].AcceptChanges();
            }
            else
            {
                // Otherwise, reject changes into database
                m_DataSet.Data.Tables[TableID].RejectChanges();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnModifyMainTable_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when First button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFirst_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnFirst_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if document is modified
            if ( rtbModifications.Modified == true )
            {
                // If yes, ask user about modifications
                DialogResult Result =  MessageBox.Show( m_InfoModifiedDoc,
                                       this.Text,
                                       MessageBoxButtons.YesNoCancel,
                                       MessageBoxIcon.Question );

                // If cancel, simply return
                if ( Result == DialogResult.Cancel )
                {
                    // Trace info message
                    if ( m_TraceSwitch.TraceInfo )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnFirst_Click",
                                        "Changes cancelled by user. Function will now quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Message,
                                        m_TraceSwitch );
                    }

                    return;
                }
                else if ( Result == DialogResult.Yes )
                {
                    // If user choice is yes, save data
                    SaveData();
                }
            }

            // Go to first form, update controls and load document
            this.BindingContext[m_DataSet.Data.Tables[0]].Position = 0;
            UpdateControls();
            LoadData();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnFirst_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Prev button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPrev_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnPrev_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if document is modified
            if ( rtbModifications.Modified == true )
            {
                // If yes, ask user about modifications
                DialogResult Result =  MessageBox.Show( m_InfoModifiedDoc,
                                       this.Text,
                                       MessageBoxButtons.YesNoCancel,
                                       MessageBoxIcon.Question );

                // If cancel, simply return
                if ( Result == DialogResult.Cancel )
                {
                    // Trace info message
                    if ( m_TraceSwitch.TraceInfo )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnPrev_Click",
                                        "Changes cancelled by user. Function will now quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Message,
                                        m_TraceSwitch );
                    }

                    return;
                }
                else if ( Result == DialogResult.Yes )
                {
                    // If user choice is yes, save data
                    SaveData();
                }
            }

            // Go to first form, update controls and load document
            this.BindingContext[m_DataSet.Data.Tables[0]].Position--;
            UpdateControls();
            LoadData();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnPrev_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Next button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnNext_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnNext_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if document is modified
            if ( rtbModifications.Modified == true )
            {
                // If yes, ask user about modifications
                DialogResult Result =  MessageBox.Show( m_InfoModifiedDoc,
                                       this.Text,
                                       MessageBoxButtons.YesNoCancel,
                                       MessageBoxIcon.Question );

                // If cancel, simply return
                if ( Result == DialogResult.Cancel )
                {
                    // Trace info message
                    if ( m_TraceSwitch.TraceInfo )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnNext_Click",
                                        "Changes cancelled by user. Function will now quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Message,
                                        m_TraceSwitch );
                    }

                    return;
                }
                else if ( Result == DialogResult.Yes )
                {
                    // If user choice is yes, save data
                    SaveData();
                }
            }

            // Go to first form, update controls and load document
            this.BindingContext[m_DataSet.Data.Tables[0]].Position++;
            UpdateControls();
            LoadData();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnNext_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Last button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLast_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnLast_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if document is modified
            if ( rtbModifications.Modified == true )
            {
                // If yes, ask user about modifications
                DialogResult Result =  MessageBox.Show( m_InfoModifiedDoc,
                                       this.Text,
                                       MessageBoxButtons.YesNoCancel,
                                       MessageBoxIcon.Question );

                // If cancel, simply return
                if ( Result == DialogResult.Cancel )
                {
                    // Trace info message
                    if ( m_TraceSwitch.TraceInfo )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnLast_Click",
                                        "Changes cancelled by user. Function will now quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Message,
                                        m_TraceSwitch );
                    }

                    return;
                }
                else if ( Result == DialogResult.Yes )
                {
                    // If user choice is yes, save data
                    SaveData();
                }
            }

            // Go to first form, update controls and load document
            this.BindingContext[m_DataSet.Data.Tables[0]].Position =
                m_DataSet.Data.Tables[0].Rows.Count;
            UpdateControls();
            LoadData();

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnLast_Click",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Add button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAdd_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "btnAdd_Click",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if document is modified
            if ( rtbModifications.Modified == true )
            {
                // If yes, ask user about modifications
                DialogResult Result =  MessageBox.Show( m_InfoModifiedDoc,
                                       this.Text,
                                       MessageBoxButtons.YesNoCancel,
                                       MessageBoxIcon.Question );

                // If cancel, simply return
                if ( Result == DialogResult.Cancel )
                {
                    // Trace info message
                    if ( m_TraceSwitch.TraceInfo )
                    {
                        TraceLog.Write( "MainFrame",
                                        "btnAdd_Click",
                                        "Changes cancelled by user. Function will now quit",
                                        "",
                                        TraceLog.TraceMsgLevel.Message,
                                        m_TraceSwitch );
                    }

                    return;
                }
                else if ( Result == DialogResult.Yes )
                {
                    // If user choice is yes, save data
                    SaveData();
                }
            }

            // Create new row
            System.Data.DataRow Row = m_DataSet.Data.Tables[0].NewRow();

            // Populate new row
            Row["User"]     = 1;
            Row["Type"]     = 1;
            Row["Priority"] = 1;
            Row["State"]    = 1;
            Row["CaseID"]   = m_DataSet.Data.Tables[0].Rows.Count + 1;

            // Add row to Rows set
            m_DataSet.Data.Tables[0].Rows.Add( Row );

            // Go to new row's form
            this.BindingContext[m_DataSet.Data.Tables[0]].Position =
                m_DataSet.Data.Tables[0].Rows.Count;

            // Update controls, and clear document
            UpdateControls();
            rtbModifications.Clear();
        }

        #endregion

        #region Combo boxes

        /// <summary>
        /// Function called when OS index has changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cbxOS_SelectedIndexChanged( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "cbxOS_SelectedIndexChanged",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Save current index into config file
            m_ConfigFile.OsID = cbxOS.SelectedIndex;

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "cbxOS_SelectedIndexChanged",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Authors index has changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cbxAuthor_SelectedIndexChanged( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "cbxAuthor_SelectedIndexChanged",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if table and combobox matches
            if ( m_DataSet.Data.Tables[5].Rows.Count == cbxAuthor.Items.Count )
            {
                // If yes, check all items into combobox
                for ( int i = 0; i < m_DataSet.Data.Tables[5].Rows.Count; ++i )
                {
                    // Construct matching name from table
                    string UserName = m_DataSet.Data.Tables[5].Rows[i]["FirstName"] + " " +
                                      m_DataSet.Data.Tables[5].Rows[i]["LastName"];

                    // Check if table name match with selected combobox name
                    if ( UserName == (string)cbxAuthor.Items[cbxAuthor.SelectedIndex] )
                    {
                        // If yes, bind user ID into T_Users with user ID into T_Case
                        m_DataSet.Data.Tables[0].Rows[this.BindingContext[m_DataSet.Data.Tables[0]].Position]["User"] =
                            m_DataSet.Data.Tables[5].Rows[i]["UserID"];
                    }
                }
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "MainFrame",
                                "cbxAuthor_SelectedIndexChanged",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        #endregion

        #endregion
    }
}
