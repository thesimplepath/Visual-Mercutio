/********************************************************************************************************
 *                                            Classe RulebookToWord                                     *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 3 mai 2007                                                                             *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe permet de convertir un rapport HTML de type "Livre des règles" vers Word.               *
 ********************************************************************************************************/

using System;
using System.Collections;
using System.Diagnostics;
using ReportsTool.Forms;

namespace ReportsTool.Conversions
{
    class RulebookToWord : BaseConversions
    {
        #region Variables globales

        ArrayList p_Text            = new ArrayList();
        ArrayList p_RuleBookStyle   = new ArrayList();

        #endregion

        #region Constructeur(s) et destructeur

        /// <summary>
        /// Constructeur par défaut.
        /// </summary>
        /// <param name="RuleBookFilename">Nom du fichier contenant le rapport.</param>
        /// <param name="RuleBookStyle">Pointeur vers l'objet contenant les styles à appliquer au rapport.</param>
        public RulebookToWord(string RuleBookFilename, Style RuleBookStyle)
            : base(RuleBookFilename, RuleBookStyle)
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
                    string      s_Line              = "";

                    bool        b_TextIsClosed      = true;
                    bool        b_ParagraphIsClosed = true;

                    StyleFormat p_CurrentStyle      = StyleFormat.NORMAL;

                    // Règles de conversion :
                    // - Un paragraphe est entouré des balises <TR> et </TR>
                    // - Chaque ligne de texte est entourée des balises <STRONG> et </STRONG>
                    // - Titre1 contient toujours l'instruction size="6" ou size="5"
                    // - Titre2 contient toujours l'instruction size="4"
                    // - Titre3 contient toujours l'instruction size="3"
                    // - Normal contient toujours l'instruction size="2"
                    foreach (string p_Str in p_FileContent)
                    {
                        string  s_Text                  = "";
                        string  s_FinalText             = "";

                        int     i_StartIndex            = p_Str.IndexOf("<STRONG>");
                        int     i_EndIndex              = p_Str.IndexOf("</STRONG>");
                        int     i_StartParagraphIndex   = p_Str.IndexOf("<TR>");
                        int     i_EndParagraphIndex     = p_Str.IndexOf("</TR>");

                        // Il existe un point start et un point stop : Extrait le texte entre ces deux points
                        if (i_StartIndex >= 0 && i_EndIndex >= 0)
                        {
                            s_Text = p_Str.Substring(i_StartIndex + 8, i_EndIndex - (i_StartIndex + 8));
                        }
                        // Point start sans point stop : Copie la ligne depuis le point start, et change la valeur
                        // du drapeau de copie pour que les lignes suivantes soient copiées jusqu'au point stop.
                        else if (i_StartIndex >=0 && i_EndIndex < 0)
                        {
                            s_Text          = p_Str.Substring(i_StartIndex + 8, p_Str.Length - (i_StartIndex + 8));
                            s_Text         += "\n";
                            b_TextIsClosed  = false;
                        }
                        // Point stop sans point start : Copie la ligne jusqu'au point stop, et change la valeur
                        // du drapeau de copie pour que les lignes suivantes ne soient plus copiées.
                        else if (i_StartIndex < 0 && i_EndIndex >= 0)
                        {
                            s_Text          = p_Str.Substring(0, i_EndIndex);
                            b_TextIsClosed  = true;
                        }
                        // Pas de points start et stop, mais drapeau de copie posé : La ligne doit être copiée.
                        else if (i_StartIndex < 0 && i_EndIndex < 0 && b_TextIsClosed == false)
                        {
                            s_Text = p_Str + "\n";
                        }

                        // Change la valeur du drapeau si le code HTML indique le début d'un paragraphe.
                        if (i_StartParagraphIndex >= 0)
                        {
                            b_ParagraphIsClosed = false;
                        }
                        // Change la valeur du drapeau si le code HTML indique la fin d'un paragraphe.
                        else if (i_EndParagraphIndex >= 0)
                        {
                            b_ParagraphIsClosed = true;
                        }

                        // Si le paragraphe est en cours, copie la ligne courante à la fin du paragraphe.
                        // Sinon, on copie le texte final, puis on vide la variable représentant le paragraphe.
                        if (b_ParagraphIsClosed == false)
                        {
                            // Filtre les lignes vides.
                            if (s_Text != "" && s_Text != " ")
                            {
                                s_Line += s_Text + " ";
                            }
                        }
                        else
                        {
                            // Si la ligne ne contient aucun espace, c'est qu'elle n'a pas été générée.
                            if (s_Line.LastIndexOf(" ") >= 0)
                            {
                                // Copie le texte final, en supprimant l'espace de fin qui est généré d'office.
                                s_FinalText = s_Line.Substring(0, s_Line.Length - 1);
                                s_Line = "";
                            }
                        }

                        // Change la valeur du style en fonction des données récupérées dans le HTML.
                        if (p_Str.Contains("size=\"6\"") || p_Str.Contains("size=\"5\""))
                        {
                            p_CurrentStyle = StyleFormat.TITLE1;
                        }
                        else if (p_Str.Contains("size=\"4\""))
                        {
                            p_CurrentStyle = StyleFormat.TITLE2;
                        }
                        else if (p_Str.Contains("size=\"3\""))
                        {
                            p_CurrentStyle = StyleFormat.TITLE3;
                        }
                        else if (p_Str.Contains("size=\"2\""))
                        {
                            p_CurrentStyle = StyleFormat.NORMAL;
                        }

                        // Si la ligne n'est pas vide, on l'ajoute au document.
                        if (s_FinalText != "" && s_FinalText != " ")
                        {
                            string[] s_FinalParagraph = s_FinalText.Split('\n');

                            for (int i = 0; i < s_FinalParagraph.Length; i++)
                            {
                                p_Text.Add(s_FinalParagraph[i]);
                                p_RuleBookStyle.Add(p_CurrentStyle);
                            }
                        }
                    }

                    // Une erreur s'est produite si le nombre de paragraphes n'est pas égal au nombre de styles.
                    if (p_Text.Count != p_RuleBookStyle.Count)
                    {
                        throw new Exception(Culture.Culture.Instance.GetStr("IDS_ERR_BAD_RULEBOOK_CONVERSION"));
                    }

                    CreateWordDocument();

                    // Crée les paragraphes dans Word.
                    foreach (string s_Paragraph in p_Text)
                    {
                        p_Paragraph = p_Doc.Content.Paragraphs.Add(ref p_missing);
                        p_Paragraph.Range.Text = s_Paragraph;
                        p_Paragraph.Range.InsertParagraphAfter();
                    }
                    
                    int i_StyleCount = 1;

                    // Applique les styles aux différents paragraphes.
                    foreach (StyleFormat p_DocStyle in p_RuleBookStyle)
                    {
                        switch (p_DocStyle)
                        {
                            case StyleFormat.TITLE1:
                            {
                                p_Range = p_Doc.Paragraphs.Item(i_StyleCount).Range;
                                p_Range.set_Style(ref Title1);

                                if (p_Style.Title1Font != null)
                                {
                                    CopyFont(p_Style.Title1Font, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                    CopyColor(p_Style.Title1Color, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                }
                                else
                                {
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Bold = 1;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Size = 18;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Name = s_DefaultFont;
                                }

                                break;
                            }

                            case StyleFormat.TITLE2:
                            {
                                p_Range = p_Doc.Paragraphs.Item(i_StyleCount).Range;
                                p_Range.set_Style(ref Title2);

                                if (p_Style.Title2Font != null)
                                {
                                    CopyFont(p_Style.Title2Font, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                    CopyColor(p_Style.Title2Color, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                }
                                else
                                {
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Bold = 1;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Size = 16;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Name = s_DefaultFont;
                                }

                                break;
                            }

                            case StyleFormat.TITLE3:
                            {
                                p_Range = p_Doc.Paragraphs.Item(i_StyleCount).Range;
                                p_Range.set_Style(ref Title3);

                                if (p_Style.Title3Font != null)
                                {
                                    CopyFont(p_Style.Title3Font, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                    CopyColor(p_Style.Title3Color, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                }
                                else
                                {
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Bold = 1;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Size = 14;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Name = s_DefaultFont;
                                }

                                break;
                            }

                            case StyleFormat.NORMAL:
                            {
                                if (p_Style.NormalFont != null)
                                {
                                    CopyFont(p_Style.NormalFont, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                    CopyColor(p_Style.NormalColor, p_Doc.Paragraphs.Item(i_StyleCount).Range.Font);
                                }
                                else
                                {
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Bold = 0;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Size = 12;
                                    p_Doc.Paragraphs.Item(i_StyleCount).Range.Font.Name = s_DefaultFont;
                                }

                                break;
                            }

                            default:
                            {
                                throw new Exception
                                    (Culture.Culture.Instance.GetStr("IDS_ERR_UNEXPECTED_STYLE") + "\n");
                            }
                        }

                        i_StyleCount++;
                    }

                }


            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function CheckReportTypeValue failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }
        }

        #endregion
    }
}
