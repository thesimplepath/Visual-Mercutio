/********************************************************************************************************
 *                                               Classe Report                                          *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 8 avril 2007                                                                           *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe représente le formulaire permettant l'importation d'un rapport. Elle contient également *
 * toutes les informations relatives au rapport, à savoir son type (livre des règles, prestations, etc) *
 * ainsi que le chemin du répertoire de publication, et le nom du fichier du rapport ouvert.            *
 ********************************************************************************************************/

using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using ReportsTool.FilesManager;

namespace ReportsTool.Forms
{
    public partial class Report : Form
    {
        #region Enumérateurs

        public enum ReportTypes
        {
            PRESTATIONS = 0,
            RULEBOOK = 1,
            PROCESS = 2,
        }

        #endregion

        #region Variables globales

        private string      s_PubFolder     = "";
        private string      s_PubFolderKey  = "PubFolder";
        private string      s_ReportTypeKey = "ReportType";
        private string      s_Filename      = "";

        private int         i_ReportTypeNbr = (int)ReportTypes.PRESTATIONS;

        private ArrayList   p_NameArray     = new ArrayList();
        private ArrayList   p_FilenameArray = new ArrayList();

        #endregion

        #region Propriétés

        /// <summary>
        /// Permet d'obtenir le type de rapport en cours d'utilisation.
        /// </summary>
        public int ReportType
        {
            get
            {
                return i_ReportTypeNbr;
            }
        }

        /// <summary>
        /// Permet d'obtenir ou de définir le répertoire de publication.
        /// </summary>
        public string PublicationFolder
        {
            get
            {
                return s_PubFolder;
            }

            set
            {
                try
                {
                    s_PubFolder = value;

                    ConfigFile.Instance.Write(s_PubFolderKey, s_PubFolder);
                    tb_PubFolder.Text = s_PubFolder;
                }
                catch (Exception ex)
                {
                    Trace.Write("Class Report -> Property PublicationFolder failed. Cause : " + ex.Message);

                    MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_PROPERTY_PUBLICATIONFOLDER"),
                                    Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Error);
                }
            }
        }

        /// <summary>
        /// Permet d'obtenir le nom du fichier en cours d'utilisation.
        /// </summary>
        public string Filename
        {
            get
            {
                return s_Filename;
            }
        }

        #endregion

        #region Constructeur(s) et destructeur

        /// <summary>
        /// Constructeur par défaut de la classe Report.
        /// </summary>
        public Report()
        {
            InitializeComponent();
            Initialize();
        }

        #endregion

        #region Fonctions privées

        #region Fonctions d'initialisation de la classe

        /// <summary>
        /// Cette fonction prend en charge les opérations d'initialisation de la classe.
        /// </summary>
        private void Initialize()
        {
            try
            {
                // Initialise la zone de sélection du dossier de publication
                s_PubFolder = ConfigFile.Instance.Read(s_PubFolderKey);
                tb_PubFolder.Text   = s_PubFolder;

                // Initialise le composant permettant le choix du type de rapports
                cbx_ReportType.Sorted = true;

                string theValue = ConfigFile.Instance.Read(s_ReportTypeKey);

                if (theValue.Length > 0)
                {
                    i_ReportTypeNbr = int.Parse(theValue);

                    switch (i_ReportTypeNbr)
                    {
                        case (int)ReportTypes.PRESTATIONS:
                        {
                            cbx_ReportType.Text = Culture.Culture.Instance.GetStr("IDS_PRESTATIONS");
                            break;
                        }

                        case (int)ReportTypes.RULEBOOK:
                        {
                            cbx_ReportType.Text = Culture.Culture.Instance.GetStr("IDS_RULEBOOK");
                            break;
                        }

                        case (int)ReportTypes.PROCESS:
                        {
                            cbx_ReportType.Text = Culture.Culture.Instance.GetStr("IDS_PROCESS");
                            break;
                        }

                        default:
                        {
                            cbx_ReportType.Text = Culture.Culture.Instance.GetStr("IDS_PRESTATIONS");
                            break;
                        }
                    }
                }
                else
                {
                    i_ReportTypeNbr     = (int)ReportTypes.PRESTATIONS;
                    cbx_ReportType.Text = Culture.Culture.Instance.GetStr("IDS_PRESTATIONS");
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function CheckReportTypeValue failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_INIT_REPORT_CLASS"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Fonctions de création et de filtrage des noms de fichier

        /// <summary>
        /// Cette fonction mets à jour et affiche la liste des fichiers disponibles par rapport au type de
        /// rapport choisi.
        /// </summary>
        private void UpdateFileListBox()
        {
            try
            {
                // Vide les listes contenant les noms et les chemins des fichiers disponibles.
                p_NameArray.Clear();
                p_FilenameArray.Clear();
                lbx_Files.Items.Clear();

                if (s_PubFolder.Length > 0)
                {
                    // Obtient tous les fichiers du répertoire.
                    string[] theFiles = System.IO.Directory.GetFiles(s_PubFolder);

                    for (int i = 0; i < theFiles.Length; i++)
                    {
                        switch (i_ReportTypeNbr)
                        {
                            case (int)ReportTypes.PRESTATIONS:
                            {
                                ComputeFilename(theFiles[i], "PrestationsReport");

                                break;
                            }

                            case (int)ReportTypes.RULEBOOK:
                            {
                                if (theFiles[i].Contains("RuleBook.htm"))
                                {
                                    p_NameArray.Add(Culture.Culture.Instance.GetStr("IDS_RULEBOOK"));
                                    p_FilenameArray.Add(theFiles[i]);
                                }

                                break;
                            }

                            case (int)ReportTypes.PROCESS:
                            {
                                ComputeFilename(theFiles[i], "ProcessReport");

                                break;
                            }

                            default:
                            {
                                break;
                            }
                        }
                    }
                }

                // Copie la liste des noms de fichiers correspondants au type choisi dans le contrôle d'affichage.
                foreach (string s_Name in p_NameArray)
                {
                    lbx_Files.Items.Add(s_Name);
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function UpdateFileListBox failed. Cause : " + ex.Message);
            }
        }

        /// <summary>
        /// Cette fonction transforme les noms des fichiers en noms compréhensibles par l'utilisateur.
        /// </summary>
        /// <param name="Filename">Le nom du fichier.</param>
        /// <param name="Filter">Le filtre permettant la sélection des fichiers.</param>
        private void ComputeFilename(string Filename, string Filter)
        {
            try
            {
                if (Filename.Contains(Filter + "_"))
                {
                    string[] s_SplittedName = Filename.Split('_');

                    if (s_SplittedName[0].Contains(Filter))
                    {
                        string s_Name = "";

                        for (int j = 1; j < s_SplittedName.Length - 1; j++)
                        {
                            s_Name += s_SplittedName[j] + " ";
                        }

                        string[] s_NameTerminaison =
                            s_SplittedName[s_SplittedName.Length - 1].Split('.');

                        s_Name += s_NameTerminaison[0];

                        p_NameArray.Add(s_Name);
                        p_FilenameArray.Add(Filename);
                    }
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function ComputeFilename failed. Cause : " + ex.Message);
            }
        }

        #endregion

        #region Fonctions de réponse liées aux événements des contrôles du formulaire

        /// <summary>
        /// Cette fonction est appelée lorsque le texte de la boîte indiquant le chemin de publication a changé.
        /// </summary>
        /// <param name="sender">Le pointeur vers l'objet responsable de l'envoi.</param>
        /// <param name="e">Les arguments de l'événement.</param>
        private void tb_PubFolder_TextChanged(object sender, EventArgs e)
        {
            UpdateFileListBox();
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Change Folder".
        /// </summary>
        /// <param name="sender">Le pointeur vers l'objet responsable de l'envoi.</param>
        /// <param name="e">Les arguments de l'événement.</param>
        private void btn_ChangeFolder_Click(object sender, EventArgs e)
        {
            try
            {
                fbd_ChangePubFolder.SelectedPath = s_PubFolder;

                fbd_ChangePubFolder.ShowDialog();

                if (fbd_ChangePubFolder.SelectedPath.Length > 0)
                {
                    this.PublicationFolder = fbd_ChangePubFolder.SelectedPath;
                }
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function btn_ChangeFolder_Click failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_EXECUTE"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur a changé le type de rapport dans la boîte combinée.
        /// </summary>
        /// <param name="sender">Le pointeur vers l'objet responsable de l'envoi.</param>
        /// <param name="e">Les arguments de l'événement.</param>
        private void cbx_ReportType_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (cbx_ReportType.Text == Culture.Culture.Instance.GetStr("IDS_PRESTATIONS"))
                {
                    i_ReportTypeNbr = (int)ReportTypes.PRESTATIONS;
                }
                else if (cbx_ReportType.Text == Culture.Culture.Instance.GetStr("IDS_RULEBOOK"))
                {
                    i_ReportTypeNbr = (int)ReportTypes.RULEBOOK;
                }
                else if (cbx_ReportType.Text == Culture.Culture.Instance.GetStr("IDS_PROCESS"))
                {
                    i_ReportTypeNbr = (int)ReportTypes.PROCESS;
                }

                ConfigFile.Instance.Write(s_ReportTypeKey, i_ReportTypeNbr.ToString());
                UpdateFileListBox();
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function cbx_ReportType_SelectedIndexChanged failed. Cause : " +
                            ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_EXECUTE"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Cancel".
        /// </summary>
        /// <param name="sender">Le pointeur vers l'objet responsable de l'envoi.</param>
        /// <param name="e">Les arguments de l'événement.</param>
        private void btn_Cancel_Click(object sender, EventArgs e)
        {
            s_Filename = "";
            this.Hide();
        }

        /// <summary>
        /// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Open".
        /// </summary>
        /// <param name="sender">Le pointeur vers l'objet responsable de l'envoi.</param>
        /// <param name="e">Les arguments de l'événement.</param>
        private void btn_Open_Click(object sender, EventArgs e)
        {
            try
            {
                if (lbx_Files.SelectedIndex >= 0)
                {
                    s_Filename = (string)p_FilenameArray[lbx_Files.SelectedIndex];
                }
                else
                {
                    s_Filename = "";
                }

                this.Hide();
            }
            catch (Exception ex)
            {
                Trace.Write("Class Report -> Function btn_Open_Click failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_ERR_CANNOT_EXECUTE"),
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        #endregion

        #endregion
    }
}