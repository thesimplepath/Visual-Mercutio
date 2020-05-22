using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using ReportsTool.Conversions;
using ReportsTool.FilesManager;
using ReportsTool.Forms;

namespace ReportsTool
{
    public partial class MainFrame : Form
    {
        Report p_Selection = new Report();
        Style p_Style = new Style();

        public MainFrame()
        {
            InitializeComponent();
            Init();
        }

        private void UpdateLanguage(string Language)
        {
            switch (Language)
            {
                case "en-GB":
                {
                    Culture.Culture.Instance.ChangeLanguage("en-GB");

                    mnu_LanguageEnglish.Checked = true;
                    mnu_LanguageFrancais.Checked = false;
                    mnu_LanguageDeutsh.Checked = false;

                    break;
                }

                case "fr-CH":
                {
                    Culture.Culture.Instance.ChangeLanguage("fr-CH");

                    mnu_LanguageEnglish.Checked = false;
                    mnu_LanguageFrancais.Checked = true;
                    mnu_LanguageDeutsh.Checked = false;

                    break;
                }

                case "de-DE":
                {
                    Culture.Culture.Instance.ChangeLanguage("de-DE");

                    mnu_LanguageEnglish.Checked = false;
                    mnu_LanguageFrancais.Checked = false;
                    mnu_LanguageDeutsh.Checked = true;

                    break;
                }

                default:
                {
                    Culture.Culture.Instance.ChangeLanguage("en-GB");

                    mnu_LanguageEnglish.Checked = true;
                    mnu_LanguageFrancais.Checked = false;
                    mnu_LanguageDeutsh.Checked = false;

                    break;
                }
            }

            Culture.Culture.Instance.OnChangeLanguage(this);
            p_Selection = new ReportsTool.Forms.Report();
        }

        private void Init()
        {
            try
            {
                if (ConfigFile.Instance.Exists() == true)
                {
                    UpdateLanguage(ConfigFile.Instance.Read("Language"));
                }
                else
                {
                    ConfigFile.Instance.Write("Language", "en-GB");
                    UpdateLanguage("en-GB");
                }
            }
            catch (Exception ex)
            {
            }
        }

        private void tsb_ConvertToWord_Click(object sender, EventArgs e)
        {
            mnu_ConvertToWord_Click(sender, e);
        }

        private void mnu_Quit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void mnu_ConvertToWord_Click(object sender, EventArgs e)
        {
            try
            {
                // OK Pour Rulebook : Code ci-dessous fonctionne.
                
                RulebookToWord p_Conversion = new RulebookToWord(p_Selection.Filename, p_Style);
                p_Conversion.Convert();
                p_Conversion.IsVisible = true;
                
                /*
                ProcessReportToWord p_Conversion = new ProcessReportToWord(p_Selection.Filename, p_Style);
                p_Conversion.Convert();
                p_Conversion.IsVisible = true;
                */

                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, Culture.Culture.Instance.GetStr("IDS_APPTITLE"));
            }
        }

        private void mnu_LanguageEnglish_Click(object sender, EventArgs e)
        {
            ApplyChangeLanguage("en-GB");
        }

        private void mnu_LanguageFrancais_Click(object sender, EventArgs e)
        {
            ApplyChangeLanguage("fr-CH");
        }

        private void mnu_LanguageDeutsh_Click(object sender, EventArgs e)
        {
            ApplyChangeLanguage("de-DE");
        }

        private void ApplyChangeLanguage(string Language)
        {
            UpdateLanguage(Language);
            ConfigFile.Instance.Write("Language", Language);
        }

        private void mnu_Import_Click(object sender, EventArgs e)
        {
            if (p_Selection.ShowDialog() == DialogResult.OK)
            {
                web_MainDoc.Navigate(p_Selection.Filename);
            }
        }

        private void MainFrame_Load(object sender, EventArgs e)
        {
            Process p_Running = Process.GetCurrentProcess();
            Process[] p_Procs = Process.GetProcesses();

            foreach (Process p_Process in p_Procs)
            {
                if (p_Running.Id != p_Process.Id)
                {
                    if (p_Running.ProcessName == p_Process.ProcessName &&
                        p_Running.MainModule.FileName == p_Process.MainModule.FileName)
                    {
                        MessageBox.Show("Le programme ne peut pas être lancé 2 fois!");
                        this.Close();
                    }
                }
            }
        }

        private void mnu_StyleAndFonts_Click(object sender, EventArgs e)
        {
            p_Style.ShowDialog();
        }
    }
}