/*****************************************************************************
 * ==> Class OleDatabaseConnection ------------------------------------------*
 * ***************************************************************************
 * Description : Manage database connection.                                 *
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
    /// <summary>
    /// Class for manage I/O database operations
    /// </summary>
    public class OleDatabaseConnection
    {
        #region Globals variables

        private OleDbConnection m_OleConnexion;

        private TraceSwitch     m_TraceSwitch;

        #endregion

        #region Properties

        /// <summary>
        /// Get database connection
        /// </summary>
        public OleDbConnection Connection
        {
            get
            {
                return m_OleConnexion;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        public OleDatabaseConnection()
        {
            // Create database objects
            m_OleConnexion = null;

            // Create OLE tracing switch
            m_TraceSwitch = new TraceSwitch( "OleConnectionTrace", "OLE database connection trace." );
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Create database connection
        /// </summary>
        /// <param name="Filename">Name of the database file</param>
        /// <returns>True if success, otherwise false</returns>
        public bool CreateConnection( string Filename )
        {
            try
            {
                // Trace begin function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "CreateConnection",
                                    "Begin function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                // Create database objects
                m_OleConnexion = new OleDbConnection();

                // Initialize connection string for Microsoft Access database
                m_OleConnexion.ConnectionString =
                    "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Filename;

                // Return true if success
                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "CreateConnection",
                                    "Connection failed. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                // Return false if error occur
                return false;
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "CreateConnection",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Test database connection
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool TestConnection()
        {
            // Trace begin function message
            if ( m_TraceSwitch.TraceInfo )
            {
                TraceLog.Write( "OleDatabaseConnection",
                                "TestConnection",
                                "Begin function",
                                "",
                                TraceLog.TraceMsgLevel.Message,
                                m_TraceSwitch );
            }

            // Test if connection object is valid
            if ( m_OleConnexion == null )
            {
                // Trace warning message
                if ( m_TraceSwitch.TraceWarning )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "TestConnection",
                                    "m_OleConnection is null. Function exit before end with false parameter",
                                    "",
                                    TraceLog.TraceMsgLevel.Warning,
                                    m_TraceSwitch );
                }

                return false;
            }

            try
            {
                // Try to open connection
                m_OleConnexion.Open();

                // If we can, return true
                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "TestConnection",
                                    "Cannot open connection. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                // If we cannot, return false
                return false;
            }
            finally
            {
                // In all cases, close connection after use
                m_OleConnexion.Close();

                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "TestConnection",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Disconnect the database
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public virtual bool Disconnect()
        {
            try
            {
                // Trace begin function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "Disconnect",
                                    "Begin function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                m_OleConnexion.Dispose();

                m_OleConnexion = null;

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "Disconnect",
                                    "Cannot open connection. Cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "OleDatabaseConnection",
                                    "Disconnect",
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
