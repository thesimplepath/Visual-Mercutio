/*****************************************************************************
 * ==> Class ModifyPriority -------------------------------------------------*
 * ***************************************************************************
 * Description : Form to modify TPriority table.                             *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using Visual_Mercutio_Reports_Manager.Tools;
using Visual_Mercutio_Reports_Manager.Database;

namespace Visual_Mercutio_Reports_Manager.Forms
{
    public partial class ModifyPriority : Form
    {
        #region Global variables

        private string           m_InfoCancel = "Do you want really to cancel your changes ?\r\n(If you click Ok, all changes will be cancelled.)";
        private string           m_InfoAccept = "Do you want really to accept your changes ?\r\n(If you click Ok, all changes will be applied permanently.)";
        private DataTable        m_Table;

        private MessageDisplayer m_MessageDisplayer;

        private TraceSwitch      m_TraceSwitch;

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor.
        /// </summary>
        public ModifyPriority( MessageDisplayer Value )
        {
            InitializeComponent();

            m_MessageDisplayer = Value;

            m_TraceSwitch = new TraceSwitch( "ModifyPriorityTrace", "Trace switch for OS Table modifier form." );
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Bind data to form.
        /// </summary>
        /// <param name="Data">DataSet to bind</param>
        /// <param name="Index">Index of column to bind</param>
        /// <returns>True if success, otherwise false</returns>
        public bool BindData( DataTable Table )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "BindData",
                                "Begin function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            m_Table = Table;

            // Bind specified table to control.
            dgvPriority.DataSource = m_Table;

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "BindData",
                                "End function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            return true;
        }

        #endregion

        #region Events handling

        #region DataGrid handling

        /// <summary>
        /// Raised when an error occurs into datagrid control
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dgvPriority_DataError( object sender, DataGridViewDataErrorEventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "dgvPriority_DataError",
                                "Begin function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Get and display error message
            m_MessageDisplayer.ShowError( e.Exception.Message );

            // Close exception
            e.ThrowException = false;

            // Trace error message
            if ( m_TraceSwitch.TraceError )
            {
                TraceLog.Write( "ModifyPriority",
                                "dgvPriority_DataError",
                                "Error while data processing. Cause : " + e.Exception.Message,
                                e.Exception.Source,
                                TraceLog.TraceMsgLevel.Error,
                                m_TraceSwitch );
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "dgvPriority_DataError",
                                "End function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Function called when Cancel button is clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "btnCancel_Click",
                                "Begin function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Ask user to confirm cancel operation
            if ( MessageBox.Show( m_InfoCancel,
                                  m_MessageDisplayer.ApplicationTitle,
                                  MessageBoxButtons.OKCancel,
                                  MessageBoxIcon.Question ) == DialogResult.OK )
            {
                // Trace data changes cancelled message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ModifyPriority",
                                    "btnCancel_Click",
                                    "Data changes cancelled",
                                    this.Text,
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                DialogResult = DialogResult.Cancel;

                // Close the form.
                this.Close();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "btnCancel_Click",
                                "End function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        /// <summary>
        /// Function called when Ok button is clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOk_Click( object sender, EventArgs e )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "btnOk_Click",
                                "Begin function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Ask user to confirm modify operation
            if ( MessageBox.Show( m_InfoAccept,
                                  m_MessageDisplayer.ApplicationTitle,
                                  MessageBoxButtons.OKCancel,
                                  MessageBoxIcon.Question ) == DialogResult.OK )
            {
                // Trace data changes accepted message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ModifyPriority",
                                    "btnCancel_Click",
                                    "Data changes accepted",
                                    this.Text,
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                DialogResult = DialogResult.OK;

                // Close the form.
                this.Close();
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "ModifyPriority",
                                "btnOk_Click",
                                "End function",
                                this.Text,
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }
        }

        #endregion

        #endregion
    }
}
