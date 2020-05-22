/*****************************************************************************
 * ==> Class ConfigFile -----------------------------------------------------*
 * ***************************************************************************
 * Description : Manage read/write operations for config file.               *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace Visual_Mercutio_Reports_Manager.Tools
{
    class ConfigFile
    {
        #region Global variables

        private string      m_Filename;
        
        private int         m_OsID;

        private TraceSwitch m_TraceSwitch;

        #endregion

        #region Propertes

        /// <summary>
        /// Get or set current Operating System ID
        /// </summary>
        public int OsID
        {
            get
            {
                return m_OsID;
            }

            set
            {
                m_OsID = value;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="Filename">File name to read/write</param>
        public ConfigFile( string Filename )
        {
            m_Filename    = Filename;
            m_OsID        = 0;
            m_TraceSwitch = new TraceSwitch( "ConfigFileTrace", "Config file trace switch." );
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Writes internal data to config file
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Write()
        {
            XmlTextWriter FileWriter = null;

            try
            {
                // Trace begin function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Write",
                                    "Begin function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                // Create new XML write stream
                FileWriter = new XmlTextWriter( m_Filename, System.Text.Encoding.UTF8 );

                // Inititialize XML stream parameters
                FileWriter.Formatting  = Formatting.Indented;
                FileWriter.Indentation = 3;

                // Writes document header
                FileWriter.WriteStartDocument();

                // Writes comment
                FileWriter.WriteComment( "Current OS ID for ComboBox" );

                // Writes data
                FileWriter.WriteStartElement( "CurrentOS" );
                FileWriter.WriteValue( m_OsID );
                FileWriter.WriteEndElement();

                // Writes document footer
                FileWriter.WriteEndDocument();

                // Flush stream
                FileWriter.Flush();

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Write",
                                    "Cannot write into file, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // Close XML stream
                if ( FileWriter != null )
                {
                    FileWriter.Close();
                }

                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Write",
                                    "End function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }
            }
        }

        /// <summary>
        /// Read XML stream and update internal data
        /// </summary>
        /// <returns>True if success, otherwise false</returns>
        public bool Read()
        {
            XmlTextReader FileReader = null;

            try
            {
                // Trace begin function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Read",
                                    "Begin function",
                                    "",
                                    TraceLog.TraceMsgLevel.Message,
                                    m_TraceSwitch );
                }

                if ( File.Exists( m_Filename ) == false )
                {
                    // Trace begin function message
                    if ( m_TraceSwitch.TraceWarning )
                    {
                        TraceLog.Write( "ConfigFile",
                                        "Read",
                                        "File " + m_Filename + " does not exist.",
                                        "",
                                        TraceLog.TraceMsgLevel.Warning,
                                        m_TraceSwitch );
                    }

                    return false;
                }

                // Create XML read stream
                FileReader = new XmlTextReader( m_Filename );

                // Inititialize XML stream parameters
                FileReader.WhitespaceHandling = WhitespaceHandling.All;

                // Read nodes
                while ( FileReader.Read() )
                {
                    // Check if CurrentOS tag is reached
                    if ( FileReader.NodeType == XmlNodeType.Element && FileReader.Name == "CurrentOS" )
                    {
                        // If yes, read next node, witch contains value
                        FileReader.Read();

                        // If value is a text element, parse it
                        if ( FileReader.NodeType == XmlNodeType.Text )
                        {
                            // Get and parse OS ID value
                            m_OsID = int.Parse( FileReader.Value );
                        }
                    }
                }

                return true;
            }
            catch ( Exception ex )
            {
                // Trace error message
                if ( m_TraceSwitch.TraceError )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Read",
                                    "Cannot write into file, cause : " + ex.Message,
                                    ex.Source,
                                    TraceLog.TraceMsgLevel.Error,
                                    m_TraceSwitch );
                }

                return false;
            }
            finally
            {
                // Close XML Stream
                if ( FileReader != null )
                {
                    FileReader.Close();
                }

                // Trace end function message
                if ( m_TraceSwitch.TraceInfo )
                {
                    TraceLog.Write( "ConfigFile",
                                    "Read",
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
