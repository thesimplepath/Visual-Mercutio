/*****************************************************************************
 * ==> Class Table_TUsers ---------------------------------------------------*
 * ***************************************************************************
 * Description : Manage database operations specialized for T_Users table.   *
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
    class Table_TUsers : ITable
    {
        #region Global variables

        private string                m_TableName     = "T_Users";
        private string                m_SelectColumns = "UserID, [ID], FirstName, LastName, [Company]";
        private string                m_SelectParams  = "UserID";
        private string                m_InsertColumns = "[ID], FirstName, LastName, [Company]";
        private string                m_InsertParams  = "?, ?, ?, ?";
        private string                m_UpdateColumns = "[ID] = ?, FirstName = ?, LastName = ?, [Company] = ?";
        private string                m_UpdateParams  = "(UserID = ?) AND ([ID] = ? OR ? IS NULL AND [ID] IS NULL) AND (FirstName = ? OR ? IS NULL AND FirstName IS NULL) AND (LastName = ? OR ? IS NULL AND LastName IS NULL) AND ([Company] = ? OR ? IS NULL AND [Company] IS NULL)";
        private string                m_DeleteParams  = "(UserID = ?) AND ([ID] = ? OR ? IS NULL AND [ID] IS NULL) AND (FirstName = ? OR ? IS NULL AND FirstName IS NULL) AND (LastName = ? OR ? IS NULL AND LastName IS NULL) AND ([Company] = ? OR ? IS NULL AND [Company] IS NULL)";

        private OleDbCommand          m_SelectCommand;
        private OleDbCommand          m_InsertCommand;
        private OleDbCommand          m_UpdateCommand;
        private OleDbCommand          m_DeleteCommand;

        private OleDbDataAdapter      m_Adapter;

        private OleDatabaseConnection m_OleConnection;
        private DataTable             m_OleDataTable;

        private TraceSwitch           m_TraceSwitch;

        #endregion

        #region Properties

        /// <summary>
        /// Get data table
        /// </summary>
        public DataTable Table
        {
            get
            {
                return m_OleDataTable;
            }
        }

        /// <summary>
        /// Get SELECT command for the table
        /// </summary>
        public string SelectCommand
        {
            get
            {
                return "SELECT "       +
                       m_SelectColumns +
                       " FROM "        +
                       m_TableName     +
                       " ORDER BY "    +
                       m_SelectParams;
            }
        }

        /// <summary>
        /// Get INSERT command for the table
        /// </summary>
        public string InsertCommand
        {
            get
            {
                return "INSERT INTO "  +
                       m_TableName     +
                       "("             +
                       m_InsertColumns +
                       ") VALUES ("    +
                       m_InsertParams  +
                       ")";
            }
        }

        /// <summary>
        /// Get UPDATE command for the table
        /// </summary>
        public string UpdateCommand
        {
            get
            {
                return @"UPDATE "      +
                       m_TableName     +
                       " SET "         +
                       m_UpdateColumns +
                       " WHERE "       +
                       m_UpdateParams;
            }
        }

        /// <summary>
        /// Get DELETE command for the table
        /// </summary>
        public string DeleteCommand
        {
            get
            {
                return @"DELETE FROM " +
                       m_TableName     +
                       " WHERE "       +
                       m_DeleteParams;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="Connection">Database connection</param>
        public Table_TUsers( OleDatabaseConnection Connection )
        {
            m_OleConnection = Connection;

            m_OleDataTable  = null;
            m_SelectCommand = null;
            m_InsertCommand = null;
            m_UpdateCommand = null;
            m_DeleteCommand = null;
            m_Adapter       = null;

            m_TraceSwitch   = new TraceSwitch( "Table_TUsersTrace", "Trace the T_Case table messages." );
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Prepare connection to database
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Connect()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "Table_TUsers",
                                "Connect",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Check if database connection is initialized
            if ( m_OleConnection == null )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "Connect",
                                    "m_OleConnection is null. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            try
            {
                // Create new DataTable object
                m_OleDataTable = new DataTable();

                // Create new command objects
                m_SelectCommand = new OleDbCommand();
                m_InsertCommand = new OleDbCommand();
                m_UpdateCommand = new OleDbCommand();
                m_DeleteCommand = new OleDbCommand();

                // Create new adapter object
                m_Adapter = new OleDbDataAdapter();

                // Create SELECT command
                m_SelectCommand.CommandType = CommandType.Text;
                m_SelectCommand.CommandText = SelectCommand;
                m_SelectCommand.Connection  = m_OleConnection.Connection;

                // Create INSERT command. Parameters are for command mapping, and must be unique
                m_InsertCommand.CommandType = CommandType.Text;
                m_InsertCommand.CommandText = InsertCommand;
                m_InsertCommand.Connection  = m_OleConnection.Connection;
                m_InsertCommand.Parameters.Add( new OleDbParameter( "ID",        OleDbType.VarWChar, 50, "ID" ) );
                m_InsertCommand.Parameters.Add( new OleDbParameter( "FirstName", OleDbType.VarWChar, 50, "FirstName" ) );
                m_InsertCommand.Parameters.Add( new OleDbParameter( "LastName",  OleDbType.VarWChar, 50, "LastName" ) );
                m_InsertCommand.Parameters.Add( new OleDbParameter( "Company",   OleDbType.VarWChar, 50, "Company" ) );

                // Create UPDATE command.  Parameters are for command mapping, and must be unique
                m_UpdateCommand.CommandType = CommandType.Text;
                m_UpdateCommand.CommandText = UpdateCommand;
                m_UpdateCommand.Connection  = m_OleConnection.Connection;
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "ID",                  OleDbType.VarWChar, 50, "ID" ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "FirstName",           OleDbType.VarWChar, 50, "FirstName" ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "LastName",            OleDbType.VarWChar, 50, "LastName" ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Company",             OleDbType.VarWChar, 50, "Company" ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_UserID",     OleDbType.Integer,  0,  ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "UserID",    DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_ID",         OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "ID",        DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_ID1",        OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "ID",        DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_FirstName",  OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "FirstName", DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_FirstName1", OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "FirstName", DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_LastName",   OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "LastName",  DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_LastName1",  OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "LastName",  DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_Company",    OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "Company",   DataRowVersion.Original, null ) );
                m_UpdateCommand.Parameters.Add( new OleDbParameter( "Original_Company1",   OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "Company",   DataRowVersion.Original, null ) );

                // Create DELETE command. Parameters are for command mapping, and must be unique
                m_DeleteCommand.CommandType = CommandType.Text;
                m_DeleteCommand.CommandText = DeleteCommand;
                m_DeleteCommand.Connection  = m_OleConnection.Connection;
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_UserID",     OleDbType.Integer,  0,  ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "UserID",    DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_ID",         OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "ID",        DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_ID1",        OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "ID",        DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_FirstName",  OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "FirstName", DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_FirstName1", OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "FirstName", DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_LastName",   OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "LastName",  DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_LastName1",  OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "LastName",  DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_Company",    OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "Company",   DataRowVersion.Original, null ) );
                m_DeleteCommand.Parameters.Add( new OleDbParameter( "Original_Company1",   OleDbType.VarWChar, 50, ParameterDirection.Input, false, ( (Byte)( 0 ) ), ( (Byte)( 0 ) ), "Company",   DataRowVersion.Original, null ) );

                // Create database adapter. We add Table mapping for data binding
                m_Adapter.SelectCommand = m_SelectCommand;
                m_Adapter.InsertCommand = m_InsertCommand;
                m_Adapter.UpdateCommand = m_UpdateCommand;
                m_Adapter.DeleteCommand = m_DeleteCommand;
                m_Adapter.TableMappings.AddRange( new System.Data.Common.DataTableMapping[]
                {
                    new System.Data.Common.DataTableMapping( "Table",
                                                             m_TableName,
                                                             new System.Data.Common.DataColumnMapping[]
                    {
                        new System.Data.Common.DataColumnMapping( "UserID",    "UserID" ),
                        new System.Data.Common.DataColumnMapping( "ID",        "ID" ),
                        new System.Data.Common.DataColumnMapping( "FirstName", "FirstName" ),
                        new System.Data.Common.DataColumnMapping( "LastName",  "LastName" ),
                        new System.Data.Common.DataColumnMapping( "Company",   "Company" )
                    } )
                } );

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "Connect",
                                    "Table_TCase connection failed. Cause : " + ex.Message,
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
                    TraceLog.Write( "Table_TUsers",
                                    "Connect",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Disconnect database and relese objects
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Disconnect()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "Table_TUsers",
                                "Disconnect",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                m_OleDataTable.Dispose();
                m_Adapter.Dispose();
                m_DeleteCommand.Dispose();
                m_InsertCommand.Dispose();
                m_UpdateCommand.Dispose();
                m_SelectCommand.Dispose();

                m_OleDataTable  = null;
                m_Adapter       = null;
                m_DeleteCommand = null;
                m_InsertCommand = null;
                m_UpdateCommand = null;
                m_SelectCommand = null;

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "Disconnect",
                                    "Cannot disconnect table. Cause : " + ex.Message,
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
                    TraceLog.Write( "Table_TUsers",
                                    "Disconnect",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Get table from database
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool GetTable()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "Table_TUsers",
                                "GetTable",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                // Open the database connection
                m_OleConnection.Connection.Open();

                // Fill DataSet object
                m_Adapter.Fill( m_OleDataTable );

                // Return true if all success
                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "GetTable",
                                    "Cannot get table. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                // Return false if an error occurs
                return false;
            }
            finally
            {
                // In all cases, close the connection
                m_OleConnection.Connection.Close();

                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "GetTable",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Update table to database
        /// </summary>
        /// <param name="TableName"></param>
        /// <returns>True if success, otherwise false</returns>
        public bool UpdateTable()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "Table_TUsers",
                                "UpdateTable",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            try
            {
                m_OleConnection.Connection.Open();

                m_Adapter.Update( m_OleDataTable );

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "UpdateTable",
                                    "Cannot update table. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // In all cases, close the connection
                m_OleConnection.Connection.Close();

                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "Table_TUsers",
                                    "UpdateTable",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        #endregion
    }
}
