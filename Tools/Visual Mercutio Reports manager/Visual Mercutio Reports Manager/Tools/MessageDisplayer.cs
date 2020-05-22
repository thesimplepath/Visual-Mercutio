/*****************************************************************************
 * ==> Class MessageDisplayer -----------------------------------------------*
 * ***************************************************************************
 * Description : Message displayer.                                          *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Windows.Forms;

namespace Visual_Mercutio_Reports_Manager.Tools
{
    /// <summary>
    /// Message displayer class
    /// </summary>
    public class MessageDisplayer
    {
        #region Global variables

        private string m_AppTitle = "";

        #endregion

        #region Properties

        /// <summary>
        /// Get application title
        /// </summary>
        public string ApplicationTitle
        {
            get
            {
                return m_AppTitle;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="ApplicationName">Name of application for caption</param>
        public MessageDisplayer( string ApplicationName )
        {
            m_AppTitle = ApplicationName;
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Show an information message
        /// </summary>
        /// <param name="Message">Message to display</param>
        public void ShowMessage( string Message )
        {
            MessageBox.Show( Message,
                             m_AppTitle,
                             MessageBoxButtons.OK,
                             MessageBoxIcon.Information );
        }

        /// <summary>
        /// Show an error message
        /// </summary>
        /// <param name="Error">Message to display</param>
        public void ShowError( string Error )
        {
            MessageBox.Show( Error,
                             m_AppTitle,
                             MessageBoxButtons.OK,
                             MessageBoxIcon.Error );
        }

        #endregion
    }
}
