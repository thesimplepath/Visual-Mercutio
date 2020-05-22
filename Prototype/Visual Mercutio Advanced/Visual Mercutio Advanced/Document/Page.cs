using System.Drawing;

namespace Visual_Mercutio_2006_Advanced.Document
{
    class Page : System.Windows.Forms.PictureBox
    {
        #region Variables

        #region Grid variables

        Bitmap m_Grid;
        int    m_GridScaleValue = 0;
        bool   m_GridIsVisible = true;

        #endregion

        #region Rules variables

        bool m_RulesIsVisible = true;

        #endregion

        #endregion

        #region Properties

        #region Grid properties

        /// <summary>
        /// Gets or sets if the grid is visible
        /// </summary>
        public bool GridIsVisible
        {
            get
            {
                return m_GridIsVisible;
            }

            set
            {
                if (value)
                    ShowGrid();
                else
                    HideGrid();
            }
        }

        #endregion

        #endregion

        #region Construction / Destruction

        public Page(int pageWidth, int pageHeight)
        {
            Name             = "Sans titre";
            Location         = new Point(0, 0);
            Size             = new Size(pageWidth, pageHeight);
            TabIndex         = 0;
            BackColor        = Color.White;
            m_GridScaleValue = 5;

            CreateGrid();
        }

        #endregion

        #region Grid Functions

        /// <summary>
        /// Creates the grid image and shows it in background
        /// </summary>
        private void CreateGrid()
        {
            try
            {
                m_Grid = new Bitmap(Size.Width, Size.Height);

                for (int i = m_GridScaleValue; i < Size.Width; i += m_GridScaleValue)
                    for (int j = m_GridScaleValue; j < Size.Height; j += m_GridScaleValue)
                        m_Grid.SetPixel(i, j, Color.Black);

                BackgroundImage = m_Grid;
            }
            catch
            {}
        }

        /// <summary>
        /// Shows the grid
        /// </summary>
        public void ShowGrid()
        {
            try
            {
                if (m_Grid == null)
                    CreateGrid();
                else
                    BackgroundImage = m_Grid;

                m_GridIsVisible = true;
            }
            catch
            {}
        }

        /// <summary>
        /// Hides the grid
        /// </summary>
        public void HideGrid()
        {
            try
            {
                BackgroundImage = null;
                m_GridIsVisible = false;
            }
            catch
            {}
        }

        /// <summary>
        /// Changes the grid size
        /// </summary>
        /// <param name="scaleValue"></param>
        /// <returns></returns>
        public bool ChangeGridScale(int scaleValue)
        {
            try
            {
                if (scaleValue > 5 && scaleValue < 20)
                {
                    m_GridScaleValue = scaleValue;
                    CreateGrid();

                    return true;
                }
            }
            catch
            {}

            return false;
        }

        #endregion

        #region Rules functions

        /// <summary>
        /// Creates the rules
        /// </summary>
        private void CreateRules()
        {}

        #endregion
    }
}
