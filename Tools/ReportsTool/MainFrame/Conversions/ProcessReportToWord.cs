using System;
using System.Collections;
using System.Diagnostics;
using ReportsTool.Forms;

namespace ReportsTool.Conversions
{
    class ProcessReportToWord : BaseConversions
    {
        ArrayList p_Text = new ArrayList();
        ArrayList p_ProcessReportStyle = new ArrayList();

        #region Constructeur(s) et destructeur

        /// <summary>
        /// Constructeur par défaut.
        /// </summary>
        /// <param name="RuleBookFilename">Nom du fichier contenant le rapport.</param>
        /// <param name="RuleBookStyle">Pointeur vers l'objet contenant les styles à appliquer au rapport.</param>
        public ProcessReportToWord(string ProcessReportFilename, Style ProcessReportStyle)
            : base(ProcessReportFilename, ProcessReportStyle)
        {
        }

        #endregion

        #region Fonctions publiques

        /// <summary>
        /// Cette fonction convertit le rapport depuis le format HTML vers le format Word.
        /// </summary>
        public override void Convert()
        {
            try
            {
                ArrayList p_FileContent = GetFileContent();

                if (p_FileContent != null)
                {
                    CreateWordDocument();
                    /*
                    p_Paragraph = p_Doc.Content.Paragraphs.Add(ref p_missing);
                    p_Paragraph.Range.Text = "Ceci est un test";
                    p_Paragraph.Range.Columns.Add(ref p_missing);
                    p_Paragraph.Range.Columns.Width = 20;
                    Word.Column theColumn = p_Paragraph.Range.Columns.Item(0);*/
                }
            }
            catch (Exception ex)
            {
            }
        }

        #endregion
    }
}
