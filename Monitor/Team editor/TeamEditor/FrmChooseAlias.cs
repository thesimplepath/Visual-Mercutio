using System;
using System.Windows.Forms;
using System.Collections.Specialized;
using System.Configuration;
using System.Collections;

namespace TeamEditor
{
    public partial class FrmChooseAlias : Form
    {
        public NameValueCollection m_AppSettings;

        public FrmChooseAlias()
        {
            InitializeComponent();
        }

        private void cmdOk_Click(object sender, EventArgs e)
        {
            m_AppSettings.Set("Processsoft.ConnectionString", m_AppSettings.Get(cboAlias.Items[cboAlias.SelectedIndex].ToString()));

            this.Dispose();
        }

        private void FrmChooseAlias_Load(object sender, EventArgs e)
        {
            m_AppSettings = ConfigurationManager.AppSettings;

            // get the collection enumerator
            IEnumerator appSettingsEnum = m_AppSettings.Keys.GetEnumerator();

            int i = 0;
            Console.WriteLine("App settings.");

            // loop through the collection of keys
            while (appSettingsEnum.MoveNext())
            {
                string key = m_AppSettings.Keys[i];

                if (key != "Processsoft.ConnectionString")
                    cboAlias.Items.Add(key) ;

                i += 1;
            }
        }

        private void cmdExit_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void cboAlias_SelectedIndexChanged(object sender, EventArgs e)
        {
            cmdOk.Enabled = true;
        }
    }
}
