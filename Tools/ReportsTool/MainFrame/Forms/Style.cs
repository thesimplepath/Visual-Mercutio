/********************************************************************************************************
 *                                                Classe Style                                          *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 3 mai 2007                                                                             *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe permet à l'utilisateur de personnaliser les styles utilisés pour la création du         *
 * document sous Word.                                                                                  *
 ********************************************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using ReportsTool.FilesManager;

namespace ReportsTool.Forms
{
    public partial class Style : Form
    {
        #region Variables globales

        private Font    p_Title1Font    = null;
        private Color   p_Title1Color   = Color.Empty;

        private Font    p_Title2Font    = null;
        private Color   p_Title2Color   = Color.Empty;

        private Font    p_Title3Font    = null;
        private Color   p_Title3Color   = Color.Empty;

        private Font    p_NormalFont    = null;
        private Color   p_NormalColor   = Color.Empty;

        /* Clés pour les inscriptions dans le fichier de configuration.*/

        private string  s_Title1Key     = "Title1";
        private string  s_Title2Key     = "Title2";
        private string  s_Title3Key     = "Title3";
        private string  s_NormalKey     = "Normal";

        private string  s_FontKey       = "Font";
        private string  s_SizeKey       = "Size";
        private string  s_ColorKey      = "Color";
        private string  s_BoldKey       = "Bold";
        private string  s_ItalicKey     = "Italic";
        private string  s_StrikeoutKey  = "Strikeout";
        private string  s_UnderlineKey  = "Underline";

        #endregion

        #region Propriétés

        /// <summary>
        /// Obtient la valeur de la police pour le titre 1.
        /// </summary>
        public Font Title1Font
        {
            get
            {
                return p_Title1Font;
            }
        }

        /// <summary>
        /// Obtient la valeur de la couleur pour le titre 1.
        /// </summary>
        public Color Title1Color
        {
            get
            {
                return p_Title1Color;
            }
        }

        /// <summary>
        /// Obtient la valeur de la police pour le titre 2.
        /// </summary>
        public Font Title2Font
        {
            get
            {
                return p_Title2Font;
            }
        }

        /// <summary>
        /// Obtient la valeur de la couleur pour le titre 2.
        /// </summary>
        public Color Title2Color
        {
            get
            {
                return p_Title2Color;
            }
        }

        /// <summary>
        /// Obtient la valeur de la police pour le titre 3.
        /// </summary>
        public Font Title3Font
        {
            get
            {
                return p_Title3Font;
            }
        }

        /// <summary>
        /// Obtient la valeur de la couleur pour le titre 3.
        /// </summary>
        public Color Title3Color
        {
            get
            {
                return p_Title3Color;
            }
        }

        /// <summary>
        /// Obtient la valeur de la police pour le corps de texte.
        /// </summary>
        public Font NormalFont
        {
            get
            {
                return p_NormalFont;
            }
        }

        /// <summary>
        /// Obtient la valeur de la couleur pour le corps de texte.
        /// </summary>
        public Color NormalColor
        {
            get
            {
                return p_NormalColor;
            }
        }

        #endregion

        #region Constructeur(s) et destructeur

        /// <summary>
        /// Constructeur par défaut.
        /// </summary>
        public Style()
        {
            InitializeComponent();
            Initialize();
        }

        #endregion

        #region Fonctions privées

        #region Fonctions d'initialisation

        /// <summary>
        /// Cette fonction initialise la classe.
        /// </summary>
        private void Initialize()
        {
            try
            {
                ftd_Fonts.FontMustExist = true;
                ftd_Fonts.ShowColor = true;

                p_Title1Font = LoadFont(s_Title1Key, 20, true);
                p_Title1Color = LoadColor(s_Title1Key);

                lbl_Title1FontNameViewer.Text = p_Title1Font.Name;
                pnl_Title1Color.BackColor = p_Title1Color;

                p_Title2Font = LoadFont(s_Title2Key, 18, true);
                p_Title2Color = LoadColor(s_Title2Key);

                lbl_Title2FontNameViewer.Text = p_Title2Font.Name;
                pnl_Title2Color.BackColor = p_Title2Color;

                p_Title3Font = LoadFont(s_Title3Key, 16, true);
                p_Title3Color = LoadColor(s_Title3Key);

                lbl_Title3FontNameViewer.Text = p_Title3Font.Name;
                pnl_Title3Color.BackColor = p_Title3Color;

                p_NormalFont = LoadFont(s_NormalKey, 12, false);
                p_NormalColor = LoadColor(s_NormalKey);

                lbl_NormalFontNameViewer.Text = p_NormalFont.Name;
                pnl_NormalColor.BackColor = p_NormalColor;
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function LoadFont failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_INIT_STYLE_CLASS"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Fonctions de chargement des données depuis le fichier de configuration

        /// <summary>
        /// Cette fonction permet d'obtenir la valeur d'une police inscrite dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La clé de la police à chercher dans le fichier.</param>
        /// <param name="DefaultSize">La taille par défaut, si aucune valeur disponible.</param>
        /// <param name="DefaultBold">La mise en gras par défaut, si aucune valeur disponible.</param>
        /// <returns>La police correspondante à la clé demandée.</returns>
        private Font LoadFont(string Key, float DefaultSize, bool DefaultBold)
        {
            try
            {
                if (ConfigFile.Instance.Read(Key + s_FontKey).Length > 0)
                {
                    FontStyle p_FontStyle = FontStyle.Regular;

                    if (bool.Parse(ConfigFile.Instance.Read(Key + s_UnderlineKey)) == true)
                    {
                        p_FontStyle |= FontStyle.Underline;
                    }

                    if (bool.Parse(ConfigFile.Instance.Read(Key + s_ItalicKey)) == true)
                    {
                        p_FontStyle |= FontStyle.Italic;
                    }

                    if (bool.Parse(ConfigFile.Instance.Read(Key + s_BoldKey)) == true)
                    {
                        p_FontStyle |= FontStyle.Bold;
                    }

                    if (bool.Parse(ConfigFile.Instance.Read(Key + s_StrikeoutKey)) == true)
                    {
                        p_FontStyle |= FontStyle.Strikeout;
                    }

                    Font p_Font = new Font(ConfigFile.Instance.Read(Key + s_FontKey),
                                           float.Parse(ConfigFile.Instance.Read(Key + s_SizeKey)),
                                           p_FontStyle);

                    return p_Font;
                }
                else
                {
                    FontStyle p_FontStyle = FontStyle.Regular;

                    if (DefaultBold == true)
                    {
                        p_FontStyle |= FontStyle.Bold;
                    }

                    Font p_Font = new Font("Arial",
                                           DefaultSize,
                                           p_FontStyle);

                    return p_Font;
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function LoadFont failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction permet d'obtenir la valeur d'une couleur inscrite dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La clé de la couleur à chercher dans le fichier.</param>
        /// <returns>La couleur correspondante à la clé demandée.</returns>
        private Color LoadColor(string Key)
        {
            try
            {
                if (ConfigFile.Instance.Read(Key + s_ColorKey).Length > 0)
                {
                    return Color.FromName(ConfigFile.Instance.Read(Key + s_ColorKey));
                }
                else
                {
                    return Color.Black;
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function LoadColor failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        #endregion

        #region Fonctions de sauvegarde des données dans le fichier de configuration

        /// <summary>
        /// Cette fonction permet de sauvegarder la valeur d'une police dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La clé de la police à mettre à jour dans le fichier.</param>
        /// <param name="theFont">Le pointeur vers la nouvelle police à écrire.</param>
        private void WriteFont(string Key, Font theFont)
        {
            try
            {
                ConfigFile.Instance.Write(Key + s_FontKey, theFont.Name);
                ConfigFile.Instance.Write(Key + s_SizeKey, theFont.Size.ToString());
                ConfigFile.Instance.Write(Key + s_UnderlineKey, theFont.Underline.ToString());
                ConfigFile.Instance.Write(Key + s_ItalicKey, theFont.Italic.ToString());
                ConfigFile.Instance.Write(Key + s_BoldKey, theFont.Bold.ToString());
                ConfigFile.Instance.Write(Key + s_StrikeoutKey, theFont.Strikeout.ToString());
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteFont failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction permet de sauvegarder la valeur d'une couleur dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La clé de la couleur à mettre à jour dans le fichier.</param>
        /// <param name="theColor">Le pointeur vers la nouvelle couleur à écrire.</param>
        private void WriteColor(string Key, Color theColor)
        {
            try
            {
                ConfigFile.Instance.Write(Key + s_ColorKey, theColor.Name);
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteColor failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        #endregion

        #region Fonctions de réponses aux événements du formulaire

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Change font" du groupe Title 1.
        /// </summary>
        /// <param name="sender">Pointeur vers l'objet appelant.</param>
        /// <param name="e">Paramètres d'appel.</param>
        private void btn_ChangeFontTitle1_Click(object sender, EventArgs e)
        {
            try
            {
                ftd_Fonts.Font = p_Title1Font;
                ftd_Fonts.Color = p_Title1Color;

                if (ftd_Fonts.ShowDialog() == DialogResult.OK)
                {
                    p_Title1Font = ftd_Fonts.Font;
                    p_Title1Color = ftd_Fonts.Color;

                    lbl_Title1FontNameViewer.Text = ftd_Fonts.Font.Name;
                    pnl_Title1Color.BackColor = ftd_Fonts.Color;

                    WriteFont(s_Title1Key, ftd_Fonts.Font);
                    WriteColor(s_Title1Key, ftd_Fonts.Color);
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteColor failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_CHANGE_FONT"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Change font" du groupe Title 2.
        /// </summary>
        /// <param name="sender">Pointeur vers l'objet appelant.</param>
        /// <param name="e">Paramètres d'appel.</param>
        private void btn_ChangeFontTitle2_Click(object sender, EventArgs e)
        {
            try
            {
                ftd_Fonts.Font = p_Title2Font;
                ftd_Fonts.Color = p_Title2Color;

                if (ftd_Fonts.ShowDialog() == DialogResult.OK)
                {
                    p_Title2Font = ftd_Fonts.Font;
                    p_Title2Color = ftd_Fonts.Color;

                    lbl_Title2FontNameViewer.Text = ftd_Fonts.Font.Name;
                    pnl_Title2Color.BackColor = ftd_Fonts.Color;

                    WriteFont(s_Title2Key, ftd_Fonts.Font);
                    WriteColor(s_Title2Key, ftd_Fonts.Color);
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteColor failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_CHANGE_FONT"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Change font" du groupe Title 3.
        /// </summary>
        /// <param name="sender">Pointeur vers l'objet appelant.</param>
        /// <param name="e">Paramètres d'appel.</param>
        private void btn_ChangeFontTitle3_Click(object sender, EventArgs e)
        {
            try
            {
                ftd_Fonts.Font = p_Title3Font;
                ftd_Fonts.Color = p_Title3Color;

                if (ftd_Fonts.ShowDialog() == DialogResult.OK)
                {
                    p_Title3Font = ftd_Fonts.Font;
                    p_Title3Color = ftd_Fonts.Color;

                    lbl_Title3FontNameViewer.Text = ftd_Fonts.Font.Name;
                    pnl_Title3Color.BackColor = ftd_Fonts.Color;

                    WriteFont(s_Title3Key, ftd_Fonts.Font);
                    WriteColor(s_Title3Key, ftd_Fonts.Color);
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteColor failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_CHANGE_FONT"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Change font" du groupe Normal.
        /// </summary>
        /// <param name="sender">Pointeur vers l'objet appelant.</param>
        /// <param name="e">Paramètres d'appel.</param>
        private void btn_ChangeFontNormal_Click(object sender, EventArgs e)
        {
            try
            {
                ftd_Fonts.Font = p_NormalFont;
                ftd_Fonts.Color = p_NormalColor;

                if (ftd_Fonts.ShowDialog() == DialogResult.OK)
                {
                    p_NormalFont = ftd_Fonts.Font;
                    p_NormalColor = ftd_Fonts.Color;

                    lbl_NormalFontNameViewer.Text = ftd_Fonts.Font.Name;
                    pnl_NormalColor.BackColor = ftd_Fonts.Color;

                    WriteFont(s_NormalKey, ftd_Fonts.Font);
                    WriteColor(s_NormalKey, ftd_Fonts.Color);
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Style -> Function WriteColor failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_CHANGE_FONT"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton Close.
        /// </summary>
        /// <param name="sender">Pointeur vers l'objet appelant.</param>
        /// <param name="e">Paramètres d'appel.</param>
        private void btn_Close_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        #endregion

        #endregion
    }
}