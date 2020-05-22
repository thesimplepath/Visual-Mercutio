using System;
using System.Windows.Forms;

namespace Visual_Mercutio_2006_Advanced.MainFrame
{
    public partial class MainFrame : Form
    {
        #region Variables

        private int                             m_ChildFormNumber = 0;
        private int                             m_ToolbarsHeight  = 10;
        private WorkspacesFrame.WorkspacesFrame m_Workspaces      = new WorkspacesFrame.WorkspacesFrame();

        #endregion

        #region Construction / Destruction

        public MainFrame()
        {
            InitializeComponent();

            Initialize();
        }

        #endregion

        #region Private functions

        /// <summary>
        /// Initializes the class
        /// </summary>
        private void Initialize()
        {
            int winX      = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.X;
            int winY      = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Y;
            int winWidth  = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Width;
            int winHeight = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Height;

            m_Workspaces.SetDesktopLocation(winX + (winWidth - m_Workspaces.Width - 10), winY + m_ToolbarsHeight);
            m_Workspaces.MdiParent = this;
            m_Workspaces.Show();
        }

        /// <summary>
        /// Shows the new form
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void ShowNewForm(object sender, EventArgs e)
        {
            Document.Document document = new Document.Document(640, 480);

            // make it a child of this MDI form before showing it
            document.MdiParent = this;
            document.Text      = "Document " + m_ChildFormNumber;
            document.Show();

            ++m_ChildFormNumber;
        }

        /// <summary>
        /// Opens a file
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void OpenFile(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog   = new OpenFileDialog();
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            openFileDialog.Filter           = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";

            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string fileName = openFileDialog.FileName;

                // todo -cFeature -oJean: Add code here to open the file
            }
        }

        /// <summary>
        /// Saves the document as
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog   = new SaveFileDialog();
            saveFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            saveFileDialog.Filter           = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";

            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string fileName = saveFileDialog.FileName;

                // todo -cFeature -oJean: Add code here to save the current contents of the form to a file
            }
        }

        /// <summary>
        /// Called when the exit button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void ExitToolsStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        /// <summary>
        /// Called when the cut button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void CutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // todo -cFeature -oJean: Use System.Windows.Forms.Clipboard to insert the selected text or images into the clipboard
        }

        /// <summary>
        /// Called when the copy button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void CopyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // TODO: Use System.Windows.Forms.Clipboard to insert the selected text or images into the clipboard
        }

        /// <summary>
        /// Called when the paste button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void PasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // todo -cFeature -oJean: Use System.Windows.Forms.Clipboard.GetText() or System.Windows.Forms.GetData to retrieve information from the clipboard
        }

        /// <summary>
        /// Called when the toolbar button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void ToolBarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            toolStrip.Visible = toolBarToolStripMenuItem.Checked;
        }

        /// <summary>
        /// Called when the status bar button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void StatusBarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            statusStrip.Visible = statusBarToolStripMenuItem.Checked;
        }

        /// <summary>
        /// Called when the cascade button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void CascadeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        /// <summary>
        /// Called when the tile vertically button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void TileVerticleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }

        /// <summary>
        /// Called when the tile horizontally button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void TileHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        /// <summary>
        /// Called when the arrange icons button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void ArrangeIconsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.ArrangeIcons);
        }

        /// <summary>
        /// Called when the close all button was clicked on the tools menu
        /// </summary>
        /// <param name="sender">event sender</param>
        /// <param name="e">event arguments</param>
        private void CloseAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form childForm in MdiChildren)
                childForm.Close();
        }

        #endregion
    }
}
