/*****************************************************************************
 * ==> Class RichTextEditor -------------------------------------------------*
 * ***************************************************************************
 * Description : Main frame for Rich Text Edito control.                     *
 * Version     : 1.0                                                         *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

using System;
using System.Drawing;
using System.Resources;
using System.Windows.Forms;
using ExtendedRichTextBox;
using RichTextEditor.RichTextEditorForms;

namespace RichTextEditor
{
    [ToolboxBitmap( typeof( RichTextBox ) )]
    public partial class RichTextEditor : UserControl
    {
        #region Global variables

        private string          m_CurrentFile = "";
        private string          m_Directory   = "";
        private string          m_Extension   = "rtf";
        private string          m_Filters     = "Rich Text Files|*.rtf|Text Files|*.txt|HTML Files|*.htm|All Files|*.*";
        private int             m_CheckPrint  = 0;
        private ResourceManager m_Resources   = null;

        #endregion

        #region Properties

        /// <summary>
        /// Get or set default directory
        /// </summary>
        public string Directory
        {
            get
            {
                if ( m_CurrentFile != "" )
                {
                    // Get current file directory if current file is defined
                    return System.IO.Path.GetDirectoryName( m_CurrentFile ) + "\\";
                }
                else if ( m_Directory == "" )
                {
                    // Get default directory if no others exists
                    return System.IO.Directory.GetCurrentDirectory() + "\\";
                }
                else
                {
                    // Otherwise returns predefined directory
                    return m_Directory;
                }
            }

            set
            {
                m_Directory = value;
            }
        }

        /// <summary>
        /// Get or set modification flag onto document
        /// </summary>
        public bool Modified
        {
            get
            {
                return rtbDocument.Modified;
            }

            set
            {
                rtbDocument.Modified = value;
            }
        }

        #endregion

        #region Construction/Destruction

        /// <summary>
        /// Default constructor
        /// </summary>
        public RichTextEditor()
        {
            InitializeComponent();
        }

        #endregion

        #region Public functions

        /// <summary>
        /// Clear document
        /// </summary>
        public void Clear()
        {
            rtbDocument.Clear();
        }

        /// <summary>
        /// Open document
        /// </summary>
        /// <param name="Filename">File name to open</param>
        public void OpenFile( string Filename )
        {
            try
            {
                // Load file into Rich Text Control
                rtbDocument.LoadFile( Filename, RichTextBoxStreamType.RichText );

                m_CurrentFile        = Filename;
                rtbDocument.Modified = false;

                // Set control title
                this.Text = (string)m_Resources.GetObject( "title_Editor" ) +
                            m_CurrentFile.ToString();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Open document
        /// </summary>
        public void OpenFile()
        {
            try
            {
                // Create open file dialog box
                ofdDocument.Title            = (string)m_Resources.GetObject( "title_OpenFileDialogBox" );
                ofdDocument.DefaultExt       = m_Extension;
                ofdDocument.Filter           = m_Filters;
                ofdDocument.FilterIndex      = 1;
                ofdDocument.FileName         = string.Empty;
                ofdDocument.InitialDirectory = Directory;

                // Check for user
                if ( ofdDocument.ShowDialog() == DialogResult.OK )
                {
                    // If user click Ok, check if filename is valid
                    if ( ofdDocument.FileName == "" )
                    {
                        // If not, return
                        return;
                    }

                    // Get file extension
                    string strExt;
                    strExt = System.IO.Path.GetExtension( ofdDocument.FileName );
                    strExt = strExt.ToUpper();

                    // Check if extension is RTF
                    if ( strExt == ( "." + m_Extension.ToUpper() ) )
                    {
                        // If extension is RTF, simply load file into Rich Text Box
                        rtbDocument.LoadFile( ofdDocument.FileName, RichTextBoxStreamType.RichText );
                    }
                    else
                    {
                        // Otherwise, convert and open document
                        System.IO.StreamReader txtReader;
                        txtReader = new System.IO.StreamReader( ofdDocument.FileName );
                        rtbDocument.Text = txtReader.ReadToEnd();
                        txtReader.Close();
                        txtReader = null;
                        rtbDocument.SelectionStart = 0;
                        rtbDocument.SelectionLength = 0;
                    }

                    m_CurrentFile        = ofdDocument.FileName;
                    rtbDocument.Modified = false;

                    // Set control title
                    this.Text = (string)m_Resources.GetObject( "title_Editor" ) +
                                m_CurrentFile.ToString();
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Save document
        /// </summary>
        /// <param name="Filename">File name to save</param>
        /// <param name="StreamType">File stream type</param>
        public void SaveFile( string Filename )
        {
            try
            {
                string strExt;
                strExt = System.IO.Path.GetExtension( Filename );
                strExt = strExt.ToUpper();

                // Check if RTF extension
                if ( strExt == ( "." + m_Extension.ToUpper() ) )
                {
                    // If RTF extension, simply save document into Rich Text Control
                    rtbDocument.SaveFile( Filename );
                }
                else
                {
                    // Otherwise, convert and save document
                    System.IO.StreamWriter txtWriter;
                    txtWriter = new System.IO.StreamWriter( Filename );
                    txtWriter.Write( rtbDocument.Text );
                    txtWriter.Close();
                    txtWriter = null;
                    rtbDocument.SelectionStart = 0;
                    rtbDocument.SelectionLength = 0;
                }

                // Set control text
                this.Text = (string)m_Resources.GetObject( "title_Editor" ) +
                            Filename.ToString();

                // Reset modifications flag
                rtbDocument.Modified = false;

                // Update current file
                m_CurrentFile = Filename;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Save document
        /// </summary>
        public void SaveFile()
        {
            try
            {
                // Create Save As dialog box
                sfdDocument.Title            = (string)m_Resources.GetObject( "title_SaveFileDialogBox" );
                sfdDocument.DefaultExt       = m_Extension;
                sfdDocument.Filter           = m_Filters;
                sfdDocument.FilterIndex      = 1;
                sfdDocument.InitialDirectory = Directory;

                // Check for user
                if ( sfdDocument.ShowDialog() == DialogResult.OK )
                {
                    // If Ok, check if name is valid
                    if ( sfdDocument.FileName == "" )
                    {
                        // If not, return
                        return;
                    }

                    // Get extension
                    string strExt;
                    strExt = System.IO.Path.GetExtension( sfdDocument.FileName );
                    strExt = strExt.ToUpper();

                    // Check if extension is RTF
                    if ( strExt == ( "." + m_Extension.ToUpper() ) )
                    {
                        // If extension is RTF, simply save document
                        rtbDocument.SaveFile( sfdDocument.FileName, RichTextBoxStreamType.RichText );
                    }
                    else
                    {
                        // Otherwise, convert and save document
                        System.IO.StreamWriter txtWriter;
                        txtWriter = new System.IO.StreamWriter( sfdDocument.FileName );
                        txtWriter.Write( rtbDocument.Text );
                        txtWriter.Close();
                        txtWriter = null;
                        rtbDocument.SelectionStart = 0;
                        rtbDocument.SelectionLength = 0;
                    }

                    // Update values
                    m_CurrentFile        = sfdDocument.FileName;
                    rtbDocument.Modified = false;

                    // Set control name
                    this.Text = (string)m_Resources.GetObject( "title_Editor" ) +
                                m_CurrentFile.ToString();

                    // Show result message
                    MessageBox.Show( m_CurrentFile.ToString() +
                                     (string)m_Resources.GetObject( "info_Saved" ),
                                     (string)m_Resources.GetObject( "title_SaveFileDialogBox" ) );
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Message handling

        #region No controls

        /// <summary>
        /// Function called when control is loading
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RichTextEditor_Load( object sender, EventArgs e )
        {
            try
            {
                // Load resources manager
                m_Resources = new ResourceManager( "RichTextEditor.Resources",
                                                   this.GetType().Assembly );
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(), "Error" );
            }
        }

        #endregion

        #region Printing functions

        /// <summary>
        /// Function called when document must be printed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void prdDocument_PrintPage( object sender, System.Drawing.Printing.PrintPageEventArgs e )
        {
            // Run print task
            m_CheckPrint = rtbDocument.Print( m_CheckPrint, rtbDocument.TextLength, e );

            // Check if print task is finished
            if ( m_CheckPrint < rtbDocument.TextLength )
            {
                e.HasMorePages = true;
            }
            else
            {
                e.HasMorePages = false;
            }
        }

        #endregion

        #region Menus

        #region File menu

        /// <summary>
        /// Function called when File New menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_New_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document is modified
                if ( rtbDocument.Modified == true )
                {
                    System.Windows.Forms.DialogResult Dialog;

                    // If yes, ask user about save old document
                    Dialog = MessageBox.Show( (string)m_Resources.GetObject( "info_SaveCurrentDocBeforeNew" ),
                                              (string)m_Resources.GetObject( "title_UnsavedDoc" ),
                                              MessageBoxButtons.YesNo,
                                              MessageBoxIcon.Question );

                    // Check user answer
                    if ( Dialog == System.Windows.Forms.DialogResult.Yes )
                    {
                        // If yes, save document before create new one
                        SaveFile( m_CurrentFile );
                        rtbDocument.Modified = false;
                        rtbDocument.Clear();
                        m_CurrentFile = "";
                        this.Text = (string)m_Resources.GetObject( "name_NewDoc" );
                        return;
                    }
                    else
                    {
                        // Otherwise, simply erase old document
                        m_CurrentFile = "";
                        this.Text = (string)m_Resources.GetObject( "name_NewDoc" );
                        rtbDocument.Modified = false;
                        rtbDocument.Clear();
                        return;
                    }
                }
                else
                {
                    // Otherwise, simply create new document
                    m_CurrentFile = "";
                    this.Text = (string)m_Resources.GetObject( "name_NewDoc" );
                    rtbDocument.Modified = false;
                    rtbDocument.Clear();
                    return;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Open menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_Open_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document is modified
                if ( rtbDocument.Modified == true )
                {
                    System.Windows.Forms.DialogResult Dialog;

                    // If yes, ask user about save old document
                    Dialog = MessageBox.Show( (string)m_Resources.GetObject( "info_SaveCurrentDocBeforeOpen" ),
                                              (string)m_Resources.GetObject( "title_UnsavedDoc" ),
                                              MessageBoxButtons.YesNo,
                                              MessageBoxIcon.Question );

                    // Check user answer
                    if ( Dialog == System.Windows.Forms.DialogResult.Yes )
                    {
                        // If yes, save old document before open
                        mnuFile_Save_Click( this, new EventArgs() );
                        rtbDocument.Modified = false;
                        OpenFile();
                    }
                    else
                    {
                        // Otherwise, simply erase old document by new one
                        rtbDocument.Modified = false;
                        OpenFile();
                    }
                }
                else
                {
                    // Otherwise, simply open document
                    rtbDocument.Modified = false;
                    OpenFile();
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Save menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_Save_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if file defined
                if ( m_CurrentFile == string.Empty )
                {
                    // If no file defined, call SaveFile function with no parameters
                    SaveFile();
                    return;
                }

                // Otherwise, save current file
                SaveFile( m_CurrentFile );

                // Show message result
                MessageBox.Show( m_CurrentFile.ToString() +
                                 (string)m_Resources.GetObject( "info_Saved" ),
                                 (string)m_Resources.GetObject( "title_SaveFileDialogBox" ) );
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Save As menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_SaveAs_Click( object sender, EventArgs e )
        {
            try
            {
                // Call SaveFile function with no parameters
                SaveFile();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Page Setup menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_PageSetup_Click( object sender, EventArgs e )
        {
            try
            {
                // Show Page Setup dialog box
                psdDocument.Document = prdDocument;
                psdDocument.ShowDialog();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Page Preview menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_Preview_Click( object sender, EventArgs e )
        {
            try
            {
                // Show Page Preview dialog
                ppdDocument.Document = prdDocument;
                ppdDocument.ShowDialog();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when File Print menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFile_Print_Click( object sender, EventArgs e )
        {
            try
            {
                prdDocumentDialog.Document = prdDocument;

                // Check for user
                if ( prdDocumentDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK )
                {
                    // If user confirm, print document
                    prdDocument.Print();
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Edit menu

        /// <summary>
        /// Function called when Edit Undo menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Undo_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document can undo
                if ( rtbDocument.CanUndo )
                {
                    // If can, undo
                    rtbDocument.Undo();
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Redo menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Redo_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document can redo
                if ( rtbDocument.CanRedo )
                {
                    // If can, redo
                    rtbDocument.Redo();
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Find menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Find_Click( object sender, EventArgs e )
        {
            try
            {
                // Open Find dialog box
                Find Dialog = new Find( this );
                Dialog.Show();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Find and Replace menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_FindAndReplace_Click( object sender, EventArgs e )
        {
            try
            {
                // Open Find and Replace dialog box
                FindAndReplace Dialog = new FindAndReplace( this );
                Dialog.Show();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Select All menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_SelectAll_Click( object sender, EventArgs e )
        {
            try
            {
                // Select all
                rtbDocument.SelectAll();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Copy menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Copy_Click( object sender, EventArgs e )
        {
            try
            {
                // Copy to clipboard
                rtbDocument.Copy();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Cut menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Cut_Click( object sender, EventArgs e )
        {
            try
            {
                // Cut
                rtbDocument.Cut();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Paste menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_Paste_Click( object sender, EventArgs e )
        {
            try
            {
                // Paste
                rtbDocument.Paste();
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Edit Insert Image menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuEdit_InsertImage_Click( object sender, EventArgs e )
        {
            try
            {
                // Create open file dialog box
                ofdDocument.Title       = (string)m_Resources.GetObject( "title_InsertImage" );
                ofdDocument.DefaultExt  = "rtf";
                ofdDocument.Filter      = "Bitmap Files|*.bmp|JPEG Files|*.jpg|GIF Files|*.gif";
                ofdDocument.FilterIndex = 1;
                ofdDocument.ShowDialog();

                // Check if filename is valid
                if ( ofdDocument.FileName == "" )
                {
                    // If not, return
                    return;
                }

                string strImagePath = ofdDocument.FileName;

                // Open image from file
                Image img;
                img = Image.FromFile( strImagePath );
                
                Clipboard.SetDataObject( img );
                DataFormats.Format df;
                
                df = DataFormats.GetFormat( DataFormats.Bitmap );

                // Copy image to document
                if ( this.rtbDocument.CanPaste( df ) )
                {
                    this.rtbDocument.Paste( df );
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Font menu

        /// <summary>
        /// Function called when Select Font menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_SelectFont_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if font already defined
                if ( rtbDocument.SelectionFont != null )
                {
                    // If font is already defined, copy it into dialog box
                    ftdDocument.Font = rtbDocument.SelectionFont;
                }
                else
                {
                    // Otherwise, initialize font dialog box to null
                    ftdDocument.Font = null;
                }

                ftdDocument.ShowApply = true;

                // Ask user about font
                if ( ftdDocument.ShowDialog() == System.Windows.Forms.DialogResult.OK )
                {
                    // If user confirm changes, apply it
                    rtbDocument.SelectionFont = ftdDocument.Font;

                    // Update controls
                    mnuFont_Bold.Checked      = ftdDocument.Font.Bold;
                    mnuFont_Italic.Checked    = ftdDocument.Font.Italic;
                    mnuFont_Underline.Checked = ftdDocument.Font.Underline;
                    tbrBold.Checked           = ftdDocument.Font.Bold;
                    tbrItalic.Checked         = ftdDocument.Font.Italic;
                    tbrUnderline.Checked      = ftdDocument.Font.Underline;
                    mnuFont_Normal.Checked    = !( ftdDocument.Font.Bold   ||
                                                   ftdDocument.Font.Italic ||
                                                   ftdDocument.Font.Underline );
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Select Font Color menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_ColorFont_Click( object sender, EventArgs e )
        {
            try
            {
                // Copy fore text color into dialog box
                cldDocument.Color = rtbDocument.ForeColor;

                // Ask user about font color
                if ( cldDocument.ShowDialog() == System.Windows.Forms.DialogResult.OK )
                {
                    // If user confirm changes, apply it
                    rtbDocument.SelectionColor = cldDocument.Color;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Bold menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_Bold_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document font is valid
                if ( rtbDocument.SelectionFont != null )
                {
                    // If yes, apply bold
                    System.Drawing.Font currentFont = rtbDocument.SelectionFont;
                    System.Drawing.FontStyle newFontStyle;

                    newFontStyle = rtbDocument.SelectionFont.Style ^ FontStyle.Bold;

                    rtbDocument.SelectionFont =
                        new Font( currentFont.FontFamily, currentFont.Size, newFontStyle );

                    // update controls
                    mnuFont_Bold.Checked   = !mnuFont_Bold.Checked;
                    mnuFont_Normal.Checked = false;
                    tbrBold.Checked        = !tbrBold.Checked;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Italic menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_Italic_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document font is valid
                if ( rtbDocument.SelectionFont != null )
                {
                    // If yes, apply italic
                    System.Drawing.Font currentFont = rtbDocument.SelectionFont;
                    System.Drawing.FontStyle newFontStyle;

                    newFontStyle = rtbDocument.SelectionFont.Style ^ FontStyle.Italic;

                    rtbDocument.SelectionFont =
                        new Font( currentFont.FontFamily, currentFont.Size, newFontStyle );

                    // update controls
                    mnuFont_Italic.Checked = !mnuFont_Italic.Checked;
                    mnuFont_Normal.Checked = false;
                    tbrItalic.Checked      = !tbrItalic.Checked;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Underline menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_Underline_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document font is valid
                if ( rtbDocument.SelectionFont != null )
                {
                    // If yes, apply underline
                    System.Drawing.Font currentFont = rtbDocument.SelectionFont;
                    System.Drawing.FontStyle newFontStyle;

                    newFontStyle = rtbDocument.SelectionFont.Style ^ FontStyle.Underline;

                    rtbDocument.SelectionFont =
                        new Font( currentFont.FontFamily, currentFont.Size, newFontStyle );

                    // update controls
                    mnuFont_Underline.Checked = !mnuFont_Underline.Checked;
                    mnuFont_Normal.Checked    = false;
                    tbrUnderline.Checked      = !tbrUnderline.Checked;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Normal menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_Normal_Click( object sender, EventArgs e )
        {
            try
            {
                // Check if document font is valid
                if ( rtbDocument.SelectionFont != null )
                {
                    // If yes, release font styles
                    System.Drawing.Font currentFont = rtbDocument.SelectionFont;
                    System.Drawing.FontStyle newFontStyle;
                    newFontStyle = FontStyle.Regular;
                    rtbDocument.SelectionFont =
                        new Font( currentFont.FontFamily, currentFont.Size, newFontStyle );

                    // update controls
                    mnuFont_Bold.Checked      = false;
                    mnuFont_Italic.Checked    = false;
                    mnuFont_Underline.Checked = false;
                    mnuFont_Normal.Checked    = true;
                    tbrBold.Checked           = false;
                    tbrItalic.Checked         = false;
                    tbrUnderline.Checked      = false;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Page Color menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFont_PageColor_Click( object sender, EventArgs e )
        {
            try
            {
                // Copy back text color into dialog box
                cldDocument.Color = rtbDocument.BackColor;

                // Ask user about back color
                if ( cldDocument.ShowDialog() == System.Windows.Forms.DialogResult.OK )
                {
                    // If user confirm changes, apply it
                    rtbDocument.BackColor = cldDocument.Color;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Paragraph menu

        /// <summary>
        /// Function called when "Select indent : None" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Indent_None_Click( object sender, EventArgs e )
        {
            try
            {
                // Change indent to correct value
                rtbDocument.SelectionIndent = 0;

                // Update controls
                mnuParagraph_Indent_None.Checked  = true;
                mnuParagraph_Indent_5Pts.Checked  = false;
                mnuParagraph_Indent_10Pts.Checked = false;
                mnuParagraph_Indent_15Pts.Checked = false;
                mnuParagraph_Indent_20Pts.Checked = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select indent : 5" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Indent_5Pts_Click( object sender, EventArgs e )
        {
            try
            {
                // Change indent to correct value
                rtbDocument.SelectionIndent = 5;

                // Update controls
                mnuParagraph_Indent_None.Checked  = false;
                mnuParagraph_Indent_5Pts.Checked  = true;
                mnuParagraph_Indent_10Pts.Checked = false;
                mnuParagraph_Indent_15Pts.Checked = false;
                mnuParagraph_Indent_20Pts.Checked = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select indent : 10" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Indent_10Pts_Click( object sender, EventArgs e )
        {
            try
            {
                // Change indent to correct value
                rtbDocument.SelectionIndent = 10;

                // Update controls
                mnuParagraph_Indent_None.Checked  = false;
                mnuParagraph_Indent_5Pts.Checked  = false;
                mnuParagraph_Indent_10Pts.Checked = true;
                mnuParagraph_Indent_15Pts.Checked = false;
                mnuParagraph_Indent_20Pts.Checked = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select indent : 15" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Indent_15Pts_Click( object sender, EventArgs e )
        {
            try
            {
                // Change indent to correct value
                rtbDocument.SelectionIndent = 15;

                // Update controls
                mnuParagraph_Indent_None.Checked  = false;
                mnuParagraph_Indent_5Pts.Checked  = false;
                mnuParagraph_Indent_10Pts.Checked = false;
                mnuParagraph_Indent_15Pts.Checked = true;
                mnuParagraph_Indent_20Pts.Checked = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select indent : 20" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Indent_20Pts_Click( object sender, EventArgs e )
        {
            try
            {
                // Change indent to correct value
                rtbDocument.SelectionIndent = 20;

                // Update controls
                mnuParagraph_Indent_None.Checked  = false;
                mnuParagraph_Indent_5Pts.Checked  = false;
                mnuParagraph_Indent_10Pts.Checked = false;
                mnuParagraph_Indent_15Pts.Checked = false;
                mnuParagraph_Indent_20Pts.Checked = true;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select align : left" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Align_Left_Click( object sender, EventArgs e )
        {
            try
            {
                // Change alignment to correct value
                rtbDocument.SelectionAlignment = HorizontalAlignment.Left;

                // Update controls
                mnuParagraph_Align_Left.Checked   = true;
                mnuParagraph_Align_Center.Checked = false;
                mnuParagraph_Align_Right.Checked  = false;
                tbrLeft.Checked                   = true;
                tbrCenter.Checked                 = false;
                tbrRight.Checked                  = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select align : center" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Align_Center_Click( object sender, EventArgs e )
        {
            try
            {
                // Change alignment to correct value
                rtbDocument.SelectionAlignment = HorizontalAlignment.Center;

                // Update controls
                mnuParagraph_Align_Left.Checked   = false;
                mnuParagraph_Align_Center.Checked = true;
                mnuParagraph_Align_Right.Checked  = false;
                tbrLeft.Checked                   = false;
                tbrCenter.Checked                 = true;
                tbrRight.Checked                  = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when "Select align : right" menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuParagraph_Align_Right_Click( object sender, EventArgs e )
        {
            try
            {
                // Change alignment to correct value
                rtbDocument.SelectionAlignment = HorizontalAlignment.Right;

                // Update controls
                mnuParagraph_Align_Left.Checked   = false;
                mnuParagraph_Align_Center.Checked = false;
                mnuParagraph_Align_Right.Checked  = true;
                tbrLeft.Checked                   = false;
                tbrCenter.Checked                 = false;
                tbrRight.Checked                  = true;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #region Bullets menu

        /// <summary>
        /// Function called when Add Bullets menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuBullets_AddBullets_Click( object sender, EventArgs e )
        {
            try
            {
                // Initialize bullets
                rtbDocument.BulletIndent    = 10;
                rtbDocument.SelectionBullet = true;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when Remove Bullets menu entry is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuBullets_RemoveBullets_Click( object sender, EventArgs e )
        {
            try
            {
                // Remove bullets
                rtbDocument.SelectionBullet = false;
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #endregion

        #region Toolbar

        /// <summary>
        /// Function called when New button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrNew_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFile_New_Click( this, e );
        }

        /// <summary>
        /// Function called when Open button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrOpen_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFile_Open_Click( this, e );
        }

        /// <summary>
        /// Function called when Save button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrSave_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFile_Save_Click( this, e );
        }

        /// <summary>
        /// Function called when Font button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrFont_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFont_SelectFont_Click( this, e );
        }

        /// <summary>
        /// Function called when Font Color button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrColor_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFont_ColorFont_Click( this, e );
        }

        /// <summary>
        /// Function called when Left button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrLeft_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuParagraph_Align_Left_Click( this, e );
        }

        /// <summary>
        /// Function called when Center button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrCenter_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuParagraph_Align_Center_Click( this, e );
        }

        /// <summary>
        /// Function called when Right button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrRight_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuParagraph_Align_Right_Click( this, e );
        }

        /// <summary>
        /// Function called when Bold button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrBold_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFont_Bold_Click( this, e );
        }

        /// <summary>
        /// Function called when Italic button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrItalic_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFont_Italic_Click( this, e );
        }

        /// <summary>
        /// Function called when Underline button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrUnderline_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuFont_Underline_Click( this, e );
        }

        /// <summary>
        /// Function called when Find button is clicked on Toolbar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbrFind_Click( object sender, EventArgs e )
        {
            // Retransmit event
            mnuEdit_Find_Click( this, e );
        }

        #endregion

        #region Rich text box

        /// <summary>
        /// Function called when rich text box selection is changing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtbDocument_SelectionChanged( object sender, EventArgs e )
        {
            try
            {
                // If selection is not defined, quit
                if ( rtbDocument == null || rtbDocument.SelectionFont == null )
                {
                    return;
                }

                // Update menus and toolbox
                tbrBold.Checked           = rtbDocument.SelectionFont.Bold;
                mnuFont_Bold.Checked      = rtbDocument.SelectionFont.Bold;
                tbrItalic.Checked         = rtbDocument.SelectionFont.Italic;
                mnuFont_Italic.Checked    = rtbDocument.SelectionFont.Italic;
                tbrUnderline.Checked      = rtbDocument.SelectionFont.Underline;
                mnuFont_Underline.Checked = rtbDocument.SelectionFont.Underline;

                mnuFont_Normal.Checked = !mnuFont_Bold.Checked &&
                                         !mnuFont_Italic.Checked &&
                                         !mnuFont_Underline.Checked;

                switch ( rtbDocument.SelectionAlignment )
                {
                    case HorizontalAlignment.Left:
                        {
                            mnuParagraph_Align_Left.Checked   = true;
                            mnuParagraph_Align_Center.Checked = false;
                            mnuParagraph_Align_Right.Checked  = false;
                            tbrLeft.Checked                   = true;
                            tbrCenter.Checked                 = false;
                            tbrRight.Checked                  = false;

                            break;
                        }

                    case HorizontalAlignment.Center:
                        {
                            mnuParagraph_Align_Left.Checked   = false;
                            mnuParagraph_Align_Center.Checked = true;
                            mnuParagraph_Align_Right.Checked  = false;
                            tbrLeft.Checked                   = false;
                            tbrCenter.Checked                 = true;
                            tbrRight.Checked                  = false;

                            break;
                        }

                    case HorizontalAlignment.Right:
                        {
                            mnuParagraph_Align_Left.Checked   = false;
                            mnuParagraph_Align_Center.Checked = false;
                            mnuParagraph_Align_Right.Checked  = true;
                            tbrLeft.Checked                   = false;
                            tbrCenter.Checked                 = false;
                            tbrRight.Checked                  = true;

                            break;
                        }

                    default:
                        {
                            mnuParagraph_Align_Left.Checked   = true;
                            mnuParagraph_Align_Center.Checked = false;
                            mnuParagraph_Align_Right.Checked  = false;
                            tbrLeft.Checked                   = true;
                            tbrCenter.Checked                 = false;
                            tbrRight.Checked                  = false;

                            break;
                        }
                }

                // select max indent by default
                mnuParagraph_Indent_20Pts.Checked = true;
                mnuParagraph_Indent_15Pts.Checked = false;
                mnuParagraph_Indent_10Pts.Checked = false;
                mnuParagraph_Indent_5Pts.Checked  = false;
                mnuParagraph_Indent_None.Checked  = false;

                // Check if indent is 15
                if ( rtbDocument.SelectionIndent < 20 )
                {
                    mnuParagraph_Indent_20Pts.Checked = false;
                    mnuParagraph_Indent_15Pts.Checked = true;
                    mnuParagraph_Indent_10Pts.Checked = false;
                    mnuParagraph_Indent_5Pts.Checked  = false;
                    mnuParagraph_Indent_None.Checked  = false;
                }

                // Check if indent is 10
                if ( rtbDocument.SelectionIndent < 15 )
                {
                    mnuParagraph_Indent_20Pts.Checked = false;
                    mnuParagraph_Indent_15Pts.Checked = false;
                    mnuParagraph_Indent_10Pts.Checked = true;
                    mnuParagraph_Indent_5Pts.Checked  = false;
                    mnuParagraph_Indent_None.Checked  = false;
                }

                // Check if indent is 5
                if ( rtbDocument.SelectionIndent < 10 )
                {
                    mnuParagraph_Indent_20Pts.Checked = false;
                    mnuParagraph_Indent_15Pts.Checked = false;
                    mnuParagraph_Indent_10Pts.Checked = false;
                    mnuParagraph_Indent_5Pts.Checked  = true;
                    mnuParagraph_Indent_None.Checked  = false;
                }

                // Check if indent is none
                if ( rtbDocument.SelectionIndent < 5 )
                {
                    mnuParagraph_Indent_20Pts.Checked = false;
                    mnuParagraph_Indent_15Pts.Checked = false;
                    mnuParagraph_Indent_10Pts.Checked = false;
                    mnuParagraph_Indent_5Pts.Checked  = false;
                    mnuParagraph_Indent_None.Checked  = true;
                }
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        /// <summary>
        /// Function called when hyperlink is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtbDocument_LinkClicked( object sender, LinkClickedEventArgs e )
        {
            try
            {
                // Run apropriate process when a link is clicked
                System.Diagnostics.Process.Start( e.LinkText );
            }
            catch ( Exception ex )
            {
                // If an error occurs, show it
                MessageBox.Show( ex.Message.ToString(),
                                 (string)m_Resources.GetObject( "title_Error" ) );
            }
        }

        #endregion

        #endregion
    }
}
