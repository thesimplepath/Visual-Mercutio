/********************************************************************************************************
 *                                           Classe BaseConversions                                     *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 3 mai 2007                                                                             *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe, de type abstraite, fournit les outils communs pour la conversion de rapports vers Word.*
 * On y trouve notamment : Les outils de conversions de données de types C# à ceux utilisés dans Word,  *
 * les objets de base de Word prêts à l'utilisation, et l'extraction de données HTML depuis un fichier. *
 ********************************************************************************************************/

using System;
using System.IO;
using System.Drawing;
using System.Collections;
using System.Diagnostics;
using ReportsTool.Forms;

namespace ReportsTool.Conversions
{
    public abstract class BaseConversions
    {
        #region Enumérateurs

        /// <summary>
        /// Enumérateur des styles utilisés pour la conversion des rapports.
        /// </summary>
        protected enum StyleFormat
        {
            NORMAL = 0,
            TITLE1 = 1,
            TITLE2 = 2,
            TITLE3 = 3
        }

        #endregion

        #region Variables globales

        protected Word.ApplicationClass p_Word          = null;
        protected Word.Document         p_Doc;
        protected Word.Paragraph        p_Paragraph;
        protected Word.Range            p_Range;

        protected string                s_DefaultFont   = "verdana";
        protected string                s_Filename      = "";

        protected Forms.Style           p_Style         = null;

        protected object                p_missing       = System.Reflection.Missing.Value;

        protected Object                Title1          = "Titre 1";
        protected Object                Title2          = "Titre 2";
        protected Object                Title3          = "Titre 3";

        #endregion

        #region Propriétés de la classe

        /// <summary>
        /// Cette propriété permet de rendre visible une instance de Word préalablement démarrée.
        /// </summary>
        public bool IsVisible
        {
            set
            {
                if (p_Word != null)
                {
                    p_Word.Visible = value;
                }
            }
        }

        #endregion

        #region Constructeur(s) et destructeur

        /// <summary>
        /// Constructeur par défaut.
        /// </summary>
        /// <param name="ReportFilename">Nom du fichier contenant le rapport.</param>
        /// <param name="ReportStyle">Pointeur vers l'objet contenant les styles à appliquer au rapport.</param>
        public BaseConversions(string ReportFilename, Style ReportStyle)
        {
            Initialize();

            s_Filename = ReportFilename;
            p_Style = ReportStyle;
        }

        #endregion

        #region Fonctions privées

        private void Initialize()
        {
            try
            {
                Title1 = Culture.Culture.Instance.GetStr("IDS_TITLE1");
                Title2 = Culture.Culture.Instance.GetStr("IDS_TITLE2");
                Title3 = Culture.Culture.Instance.GetStr("IDS_TITLE3");

                p_Word = new Word.ApplicationClass();
            }
            catch (Exception ex)
            {
                Trace.Write("Class BaseConversions -> Function Initialize failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        #endregion

        #region Fonctions protégées

        /// <summary>
        /// Cette fonction permet d'obtenir le contenu du fichier HTML représentant le rapport.
        /// </summary>
        /// <returns>Une liste contenant les chaînes de caractères du fichier.</returns>
        protected ArrayList GetFileContent()
        {
            try
            {
                if (s_Filename.Length > 0)
                {
                    ArrayList p_FileContent = new ArrayList();

                    FileStream oReadStream = new FileStream(s_Filename,
                                                            FileMode.OpenOrCreate,
                                                            FileAccess.Read,
                                                            FileShare.None);

                    StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                    while (oFileReader.Peek() != -1)
                    {
                        p_FileContent.Add(oFileReader.ReadLine());
                    }

                    oFileReader.Close();
                    oReadStream.Close();

                    return p_FileContent;
                }
                else
                {
                    return null;
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class BaseConversions -> Function GetFileContent failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction permet d'initialiser un nouveau document dans Word.
        /// </summary>
        /// <returns>True si le document s'est correctement initialisé, sinon false.</returns>
        protected bool CreateWordDocument()
        {
            try
            {
                if (p_Word == null)
                {
                    return false;
                }

                p_Doc = p_Word.Documents.Add(ref p_missing,
                                             ref p_missing,
                                             ref p_missing,
                                             ref p_missing);

                return true;
            }
            catch (Exception ex)
            {
                Trace.Write("Class BaseConversions -> Function CreateWordDocument failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction permet de copier une police depuis un objet C# vers un objet utilisé par Word.
        /// </summary>
        /// <param name="From">Pointeur vers l'objet C#.</param>
        /// <param name="To">Pointeur vers l'objet Word.</param>
        protected void CopyFont(Font From, Word.Font To)
        {
            try
            {
                To.Name = From.Name;
                To.Size = From.Size;

                if (From.Bold == true)
                {
                    To.Bold = 1;
                }
                else
                {
                    To.Bold = 0;
                }

                if (From.Italic == true)
                {
                    To.Italic = 1;
                }
                else
                {
                    To.Italic = 0;
                }

                if (From.Strikeout == true)
                {
                    To.StrikeThrough = 1;
                }
                else
                {
                    To.StrikeThrough = 0;
                }

                if (From.Underline == true)
                {
                    To.Underline = Word.WdUnderline.wdUnderlineSingle;
                }
                else
                {
                    To.Underline = Word.WdUnderline.wdUnderlineNone;
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class BaseConversions -> Function CopyFont failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction permet de copier une couleur depuis un objet C# vers un objet utilisé par Word.
        /// </summary>
        /// <param name="From">Pointeur vers l'objet C#.</param>
        /// <param name="To">Pointeur vers l'objet Word.</param>
        protected void CopyColor(Color From, Word.Font To)
        {
            try
            {
                To.Color = (Word.WdColor)(From.B * 65536) + (From.G * 256) + From.R;
            }
            catch (Exception ex)
            {
                Trace.Write("Class BaseConversions -> Function CopyColor failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        #endregion

        #region Fonctions abstraites

        /// <summary>
        /// Les fonctions héritées de cette classe doivent posséder une fonction Convert pour fonctionner.
        /// </summary>
        public abstract void Convert();

        #endregion
    }
}
