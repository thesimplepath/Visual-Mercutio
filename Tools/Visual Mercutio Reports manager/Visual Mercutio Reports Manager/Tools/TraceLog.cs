/*****************************************************************************
 * ==> Class TraceLog -------------------------------------------------------*
 * ***************************************************************************
 * Description : Trace and reports messages for the application.             *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;

namespace Visual_Mercutio_Reports_Manager.Tools
{
    static class TraceLog
    {
        #region Enumerators

        public enum TraceMsgLevel
        {
            Message = 0,
            Warning = 1,
            Error   = 2
        };

        #endregion

        #region Global variables

        private static string m_Directory             = "";
        private static string m_Version               = "1.0.0";
        private static bool   m_TraceServiceIsRunning = false;

        #endregion

        #region Properties

        /// <summary>
        /// Get or set log directory for publication
        /// </summary>
        public static string Directory
        {
            get
            {
                if ( m_Directory == "" )
                {
                    // retruns default directory if no other exists
                    return System.IO.Directory.GetCurrentDirectory() + "\\";
                }
                else
                {
                    // Otherwise, return predefined directory
                    return m_Directory;
                }
            }

            set
            {
                m_Directory = value;
            }
        }

        #endregion

        #region Private functions

        /// <summary>
        /// Create log file
        /// </summary>
        /// <param name="Filename">Path and filename for log file</param>
        /// <returns>True if success, otherwise false</returns>
        private static bool Create( string Filename )
        {
            try
            {
                // Create a stream for log file
                FileStream m_LogStream = new FileStream( Filename, FileMode.Create );

                // Create a Trace listener for log file
                TextWriterTraceListener m_TraceListener =
                    new TextWriterTraceListener( m_LogStream );

                // Add the listener to the Trace object
                Trace.Listeners.Add( m_TraceListener );

                // Enable auto-flush propertie
                Trace.AutoFlush = true;

                return true;
            }
            catch ( Exception ex )
            {
                MessageBox.Show( "Error : Cannot initialize trace log.\r\nCause : " + ex.Message,
                                 "TraceLog",
                                 MessageBoxButtons.OK,
                                 MessageBoxIcon.Error );

                return false;
            }
        }

        /// <summary>
        /// Write console log header
        /// </summary>
        private static void WriteHeader()
        {
            Trace.WriteLine( "***********************************************" );

            Trace.WriteLine( "********* Trace console version " +
                             m_Version +
                             " *********" );

            Trace.WriteLine( "***********************************************" );
            Trace.WriteLine( "" );
        }

        /// <summary>
        /// Translate Message Level to string
        /// </summary>
        /// <param name="MsgLevel">The MEssage level to translate</param>
        /// <returns>The apropriate string</returns>
        private static string TranslateMsgLevel( TraceMsgLevel MsgLevel )
        {
            // Translate apropiate level message
            switch ( MsgLevel )
            {
                case TraceMsgLevel.Message:
                {
                    return "Info";
                }

                case TraceMsgLevel.Warning:
                {
                    return "Warning";
                }

                case TraceMsgLevel.Error:
                {
                    return "Error";
                }

                default:
                {
                    return "Unknown info type";
                }
            }
        }

        /// <summary>
        /// Writes one formatted line to log file
        /// </summary>
        /// <param name="ClassName">Name of the sender class</param>
        /// <param name="FunctionName">Name of the sender function</param>
        /// <param name="Message">Message to log</param>
        /// <param name="Source">Source of error, if exists</param>
        /// <param name="MsgLevel">Message level (Info, Warning or Error)</param>
        private static bool WriteToLog( string        ClassName,
                                        string        FunctionName,
                                        string        Message,
                                        string        Source,
                                        TraceMsgLevel MsgLevel )
        {
            // Test if Trace service is already initialized
            if ( m_TraceServiceIsRunning == false )
            {
                // If owner no exist, use apropriate function.
                if ( Create( TraceLog.Directory + "TraceLog.txt" ) == false )
                {
                    return false;
                }

                // Write log header
                WriteHeader();

                // Write Trace service to Enabled
                m_TraceServiceIsRunning = true;
            }

            // Get apropriate message level
            string TraceMsg = TranslateMsgLevel( MsgLevel );

            // Write output to log
            Trace.WriteLine( "==> " + TraceMsg + " message has been raised from application. Details are :" );
            Trace.WriteLine( "Class : " + ClassName );
            Trace.WriteLine( "Function : " + FunctionName );
            Trace.WriteLine( "Error source : " + ( Source == "" ? "None" : Source ) );
            Trace.WriteLine( "Message : " + Message );
            Trace.WriteLine( "" );

            return true;
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Write a line to log file
        /// </summary>
        /// <param name="ClassName">Name of the sender class</param>
        /// <param name="FunctionName">Name of the sender function</param>
        /// <param name="Message">Message to log</param>
        /// <param name="Source">Source of error, if exists</param>
        /// <param name="MsgLevel">Message level (Info, Warning or Error)</param>
        /// <param name="Switch">Switch to control the log statement</param>
        public static void Write( string        ClassName,
                                  string        FunctionName,
                                  string        Message,
                                  string        Source,
                                  TraceMsgLevel MsgLevel,
                                  BooleanSwitch Switch )
        {
            // Test if switch is enabled
            if ( Switch.Enabled == true )
            {
                // Write infos to log file.
                WriteToLog( ClassName,
                            FunctionName,
                            Message,
                            Source,
                            MsgLevel );
            }
        }

        /// <summary>
        /// Write a line into log file
        /// </summary>
        /// <param name="ClassName">Name of the sender class</param>
        /// <param name="FunctionName">Name of the sender function</param>
        /// <param name="Message">Message to log</param>
        /// <param name="Source">Source of error, if exists</param>
        /// <param name="MsgLevel">Message level (Info, Warning or Error)</param>
        /// <param name="Switch">Switch to control the log statement</param>
        public static void Write( string        ClassName,
                                  string        FunctionName,
                                  string        Message,
                                  string        Source,
                                  TraceMsgLevel MsgLevel,
                                  TraceSwitch   Switch )
        {
            // Test if switch is enabled
            if ( Switch.Level != 0 )
            {
                // Write infos to log file.
                WriteToLog( ClassName,
                            FunctionName,
                            Message,
                            Source,
                            MsgLevel );
            }
        }

        #endregion
    }
}
