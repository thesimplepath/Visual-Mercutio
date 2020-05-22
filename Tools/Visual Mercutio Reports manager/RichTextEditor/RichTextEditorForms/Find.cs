/*****************************************************************************
 * ==> Class Find -----------------------------------------------------------*
 * ***************************************************************************
 * Description : Find form to allow find text operations.                    *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Resources;
using System.Windows.Forms;

namespace RichTextEditor.RichTextEditorForms
{
    internal partial class Find : Form
    {
        #region Global variables

        private RichTextEditor  m_Owner     = null;
        private ResourceManager m_Resources = null;

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        public Find()
        {
            InitializeComponent();
        }


        /// <summary>
        /// Overloaded constructor
        /// </summary>
        /// <param name="Owner">Ovner control</param>
        public Find( RichTextEditor Owner )
        {
            InitializeComponent();
            m_Owner = Owner;
        }

        #endregion

        #region Message handling

        #region No controls

        /// <summary>
        /// Function called when control is loading
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Find_Load( object sender, EventArgs e )
        {
            try
            {
                // Create resource manager
                m_Resources = new ResourceManager( "RichTextEditor.Resources",
                                                   this.GetType().Assembly );

                // Check if owner exists
                if ( m_Owner == null )
                {
                    // Cannot work with this form if owner not exists
                    throw new Exception( (string)m_Resources.GetObject( "err_OwnerIsNullException" ) );
                }
            }
            catch ( Exception ex )
            {
                // Disable all buttons
                tbSearch.Enabled         = false;
                btnFind.Enabled          = false;
                btnFindNext.Enabled      = false;
                cbxCaseSensitive.Enabled = false;

                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(), "Error" );
            }
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Function called when Find button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFind_Click( object sender, System.EventArgs e )
        {
            try
            {
                int StartPosition;
                StringComparison SearchType;

                // Check if Case Sensitive button is checked
                if ( cbxCaseSensitive.Checked == true )
                {
                    // If Case Sensitive is checked, set case sensitive for searching
                    SearchType = StringComparison.Ordinal;
                }
                else
                {
                    // Otherwise, ignore case sensitive for searching
                    SearchType = StringComparison.OrdinalIgnoreCase;
                }

                // Get first ocurence start position
                StartPosition = m_Owner.rtbDocument.Text.IndexOf( tbSearch.Text, SearchType );

                // Check if start position is valid
                if ( StartPosition == -1 )
                {
                    // If not, show not found info message
                    MessageBox.Show( (string)m_Resources.GetObject( "title_String" ) +
                                     tbSearch.Text.ToString() +
                                     (string)m_Resources.GetObject( "info_NotFound" ),
                                     (string)m_Resources.GetObject( "title_Control" ),
                                     MessageBoxButtons.OK,
                                     MessageBoxIcon.Asterisk );

                    return;
                }

                // Select first text ocurence into document, and focus it
                m_Owner.rtbDocument.Select( StartPosition, tbSearch.Text.Length );
                m_Owner.rtbDocument.ScrollToCaret();
                m_Owner.Focus();

                // Enable Find Next button
                btnFindNext.Enabled = true;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Find Next button is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFindNext_Click( object sender, System.EventArgs e )
        {
            try
            {
                // Get text current start position
                int StartPosition = m_Owner.rtbDocument.SelectionStart + 2;

                StringComparison SearchType;

                // Check if Case Sensitive button is checked
                if ( cbxCaseSensitive.Checked == true )
                {
                    // If Case Sensitive is checked, set case sensitive for searching
                    SearchType = StringComparison.Ordinal;
                }
                else
                {
                    // Otherwise, ignore case sensitive for searching
                    SearchType = StringComparison.OrdinalIgnoreCase;
                }

                // Get next ocurence start position
                StartPosition = m_Owner.rtbDocument.Text.IndexOf( tbSearch.Text,
                                                                  StartPosition,
                                                                  SearchType );

                // Check if new start position is valid
                if ( StartPosition == -1 )
                {
                    // If not, show not found info message
                    MessageBox.Show( (string)m_Resources.GetObject( "title_String" ) +
                                     tbSearch.Text.ToString() +
                                     (string)m_Resources.GetObject( "info_NotFound" ),
                                     (string)m_Resources.GetObject( "title_Control" ),
                                     MessageBoxButtons.OK,
                                     MessageBoxIcon.Asterisk );
                    return;
                }

                // Select next text ocurence into document, and focus it
                m_Owner.rtbDocument.Select( StartPosition, tbSearch.Text.Length );
                m_Owner.rtbDocument.ScrollToCaret();
                m_Owner.Focus();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Text boxes

        /// <summary>
        /// Function called when text into tbSearch text box has changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbSearch_TextChanged( object sender, EventArgs e )
        {
            // Disable Find Next button
            btnFindNext.Enabled = false;
        }

        #endregion

        #endregion
    }
}
