using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Visual_Mercutio_2006_Advanced.Document
{
    public partial class Document : Form
    {
        #region Variables

        Page m_Page;

        #endregion

        #region Construction / Destruction

        public Document(int docWidth, int docHeight)
        {
            InitializeComponent();

            m_Page = new Page(docWidth, docHeight)
            {
                Parent = this
            };
        }

        #endregion
    }
}
