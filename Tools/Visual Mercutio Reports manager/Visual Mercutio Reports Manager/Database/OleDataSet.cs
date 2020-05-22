/*****************************************************************************
 * ==> Class OleDataSet -----------------------------------------------------*
 * ***************************************************************************
 * Description : Class that contain in-memory database.                      *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Data;
using System.Data.OleDb;
using System.Diagnostics;
using Visual_Mercutio_Reports_Manager.Tools;

namespace Visual_Mercutio_Reports_Manager.Database
{
    public class OleDataSet
    {
        #region Global variables

        private DataSet                 m_DataSet;

        private Table_TCase             m_TCase;
        private Table_TOperatingSystems m_TOS;
        private Table_TPriority         m_TPriority;
        private Table_TState            m_TState;
        private Table_TType             m_TType;
        private Table_TUsers            m_TUsers;

        private OleDatabaseConnection   m_Connection = null;

        private TraceSwitch             m_TraceSwitch;

        #endregion

        #region Properties

        /// <summary>
        /// Get data set
        /// </summary>
        public DataSet Data
        {
            get
            {
                return m_DataSet;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="Connection">Database connection</param>
        public OleDataSet( OleDatabaseConnection Connection )
        {
            m_Connection = Connection;

            m_DataSet    = null;

            m_TCase      = null;
            m_TOS        = null;
            m_TPriority  = null;
            m_TState     = null;
            m_TType      = null;
            m_TUsers     = null;

            m_TraceSwitch = new TraceSwitch( "OleDataSetTrace", "OLE DataSet operations trace." );
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Connect to Database
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Connect()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "Connect",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if connection is valid
            if ( m_Connection == null )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Connect",
                                    "m_Connection is null. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            try
            {
                // Construct data object containers
                m_DataSet   = new DataSet();
                m_TCase     = new Table_TCase( m_Connection );
                m_TOS       = new Table_TOperatingSystems( m_Connection );
                m_TPriority = new Table_TPriority( m_Connection );
                m_TState    = new Table_TState( m_Connection );
                m_TType     = new Table_TType( m_Connection );
                m_TUsers    = new Table_TUsers( m_Connection );

                // Attempt to connect to T_Case table
                if ( m_TCase.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TCase connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Attempt to connect to T_OperatingSystems table
                if ( m_TOS.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TOS connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Attempt to connect to T_Priority table
                if ( m_TPriority.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TPriority connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Attempt to connect to T_State table
                if ( m_TState.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TState connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Attempt to connect to T_Type table
                if ( m_TType.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TType connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Attempt to connect to T_Users table
                if ( m_TUsers.Connect() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "m_TUsers connection failed",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TCase table
                if ( m_TCase.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TCase table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TOS table
                if ( m_TOS.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TOS table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TPriority table
                if ( m_TPriority.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TPriority table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TState table
                if ( m_TState.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TState table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TType table
                if ( m_TType.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TType table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Get TUsers table
                if ( m_TUsers.GetTable() == false )
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "Connect",
                                        "Cannot get m_TUsers table",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Fill DataSet
                m_DataSet.Tables.Add( m_TCase.Table );
                m_DataSet.Tables.Add( m_TOS.Table );
                m_DataSet.Tables.Add( m_TPriority.Table );
                m_DataSet.Tables.Add( m_TState.Table );
                m_DataSet.Tables.Add( m_TType.Table );
                m_DataSet.Tables.Add( m_TUsers.Table );

                // Create unique constraints for each tables
                m_DataSet.Tables[0].Columns[0].Unique = true;
                m_DataSet.Tables[1].Columns[0].Unique = true;
                m_DataSet.Tables[2].Columns[0].Unique = true;
                m_DataSet.Tables[3].Columns[0].Unique = true;
                m_DataSet.Tables[4].Columns[0].Unique = true;
                m_DataSet.Tables[5].Columns[0].Unique = true;

                // Add foreign key constraint to link Priority tables
                ForeignKeyConstraint PriorityConstraint =
                    new ForeignKeyConstraint( m_DataSet.Tables[2].Columns["PriorityID"],
                                              m_DataSet.Tables[0].Columns["Priority"] );

                m_DataSet.Tables[0].Constraints.Add( PriorityConstraint );

                // Add foreign key constraint to link State tables
                ForeignKeyConstraint StateConstraint =
                    new ForeignKeyConstraint( m_DataSet.Tables[3].Columns["StateID"],
                                              m_DataSet.Tables[0].Columns["State"] );

                m_DataSet.Tables[0].Constraints.Add( StateConstraint );

                // Add foreign key constraint to link Type tables
                ForeignKeyConstraint TypeConstraint =
                    new ForeignKeyConstraint( m_DataSet.Tables[4].Columns["TypeID"],
                                              m_DataSet.Tables[0].Columns["Type"] );

                m_DataSet.Tables[0].Constraints.Add( TypeConstraint );

                // Add foreign key constraint to link User tables
                ForeignKeyConstraint UserConstraint =
                    new ForeignKeyConstraint( m_DataSet.Tables[5].Columns["UserID"],
                                              m_DataSet.Tables[0].Columns["User"] );

                m_DataSet.Tables[0].Constraints.Add( UserConstraint );

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Connect",
                                    "DataSet connection failed. Cause : " + ex.Message,
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
                    TraceLog.Write( "OleDataSet",
                                    "Connect",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Disconnect objects from database
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Disconnect()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "Disconnect",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Disconnect TCase table
            if ( m_TCase.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TCase table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Disconnect TOS table
            if ( m_TOS.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TOperatingSystems table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Disconnect TPriority table
            if ( m_TPriority.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TPriority table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Disconnect TState table
            if ( m_TState.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TState table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Disconnect TType table
            if ( m_TType.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TType table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Disconnect TUsers table
            if ( m_TUsers.Disconnect() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Cannot disconnect TUsers table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            try
            {
                // Dispose DataSet
                m_DataSet.Dispose();
                m_DataSet = null;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Disconnect",
                                    "Error while dispose m_DataSet. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "Disconnect",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            return true;
        }

        /// <summary>
        /// Update all tables into DataSet
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Update()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "Update",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Attempt to update T_Case table
            if ( m_TCase.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TCase table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Attempt to update T_OperatingSystems table
            if ( m_TOS.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TOS table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Attempt to update T_Priority table
            if ( m_TPriority.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TPriority table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Attempt to update T_State table
            if ( m_TState.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TState table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Attempt to update T_Type table
            if ( m_TType.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TType table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Attempt to update T_Users table
            if ( m_TUsers.UpdateTable() == false )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDataSet",
                                    "Update",
                                    "Cannot update m_TUsers table. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "Update",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            return true;
        }

        /// <summary>
        /// Update one given table
        /// </summary>
        /// <param name="Index">Index of the table to update</param>
        /// <returns>True if success, otherwise false</returns>
        public bool UpdateTable( int Index )
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "UpdateTable",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            switch ( Index )
            {
                case 0:
                {
                    // Attempt to update T_Case table
                    if ( m_TCase.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TCase table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                case 1:
                {
                    // Attempt to update T_OperatingSystems table
                    if ( m_TOS.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TOS table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                case 2:
                {
                    // Attempt to update T_Priority table
                    if ( m_TPriority.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TPriority table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                case 3:
                {
                    // Attempt to update T_State table
                    if ( m_TState.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TState table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                case 4:
                {
                    // Attempt to update T_Type table
                    if ( m_TType.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TType table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                case 5:
                {
                    // Attempt to update T_Users table
                    if ( m_TUsers.UpdateTable() == false )
                    {
                        // Trace warning message
                        if ( m_TraceSwitch.TraceWarning )
                        {
                            TraceLog.Write( "OleDataSet",
                                            "UpdateTable",
                                            "Cannot update m_TUsers table. Function exit before end with false parameter",
                                            "",
                                            TraceLog.TraceMsgLevel.Warning,
                                            m_TraceSwitch );
                        }

                        return false;
                    }

                    break;
                }

                default:
                {
                    // Trace warning message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "OleDataSet",
                                        "UpdateTable",
                                        "Unknown table. Function exit before end with false parameter",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }
            }

            // Trace end function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDataSet",
                                "UpdateTable",
                                "End function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            return true;
        }

        #endregion
    }
}
