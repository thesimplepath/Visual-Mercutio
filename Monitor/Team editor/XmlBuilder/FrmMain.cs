using System;
using System.Data;
using System.Windows.Forms;
using System.Xml;
using System.Data.OleDb;

namespace XmlBuilder
{
    public partial class frmMain : Form
    {
        private String m_DialogTitle = "Processsoft XML Builder";

        public frmMain()
        {
            InitializeComponent();
        }

        private void cmdProcess_Click(object sender, EventArgs e)
        {
            try
            {
                if (txtXmlPath.Text == "" || txtExcelPath.Text == "")
                {
                    MessageBox.Show("Vous devez sélectionner un fichier Excel source et un fichier XML destination !", m_DialogTitle);
                    return;
                }

                radStep5.Enabled = false;
                prgBarProcess.Value = 0;
                prgBarProcess.Enabled = false;

                Cursor = Cursors.WaitCursor;

                // open oledb connection on excel file
                OleDbConnection oleConn = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
                                                              txtExcelPath.Text                               +
                                                              ";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1;\"");

                oleConn.Open();

                // select all in sheet
                OleDbCommand oleCmdSelect = new OleDbCommand(@"SELECT * FROM [" + "Feuil1$" + "]", oleConn);

                radStep2.Enabled = true;
                radStep2.Checked = true;

                // get the data
                OleDbDataAdapter oleAdapter = new OleDbDataAdapter();
                oleAdapter.SelectCommand    = oleCmdSelect;
                DataTable dt                = new DataTable("test");
                oleAdapter.FillSchema(dt, SchemaType.Source);
                oleAdapter.Fill(dt);

                // open the XML Writer
                XmlTextWriter writer;
                string        xmlFilename = txtXmlPath.Text;
                writer                    = new XmlTextWriter(xmlFilename, System.Text.Encoding.UTF8);

                // indent the XML document for readability
                writer.Formatting = System.Xml.Formatting.Indented;

                // call WriteStartDocument to write XML declaration
                writer.WriteStartDocument();

                // write the root element
                writer.WriteStartElement("root");

                prgBarProcess.Minimum = 0;
                prgBarProcess.Maximum = dt.Rows.Count;

                System.Threading.Thread.Sleep(1000);

                radStep2.Enabled      = false;
                radStep3.Enabled      = true;
                radStep3.Checked      = true;
                prgBarProcess.Enabled = true;

                bool flagFirstPass = true;

                // parse every record
                for (int i = 0; i < dt.Rows.Count; ++i)
                {
                    // check if recrod is Message (M) or Deliverable (D)
                    if (dt.Rows[i][0].ToString() == "M")
                    {
                        if (!flagFirstPass)
                            writer.WriteEndElement();
                        else
                            flagFirstPass = false;

                        // <message>
                        writer.WriteStartElement("message");

                        // attributes for <message>
                        writer.WriteAttributeString("caseid",             dt.Rows[i][3].ToString());
                        writer.WriteAttributeString("caseidremark",       dt.Rows[i][11].ToString());
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][1].ToString());
                        writer.WriteAttributeString("externprocid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][2].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][5].ToString());
                        writer.WriteAttributeString("messagetime",        dt.Rows[i][6].ToString() + " " + dt.Rows[i][7].ToString());
                        writer.WriteAttributeString("statut",             dt.Rows[i][10].ToString());
                        writer.WriteAttributeString("timestampproc",      dt.Rows[i][8].ToString() + " " + dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][12].ToString());
                    }
                    else
                    {
                        // <messagedeliv>
                        writer.WriteStartElement("messagedeliv");

                        // attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("externdelivid",    dt.Rows[i][1].ToString());
                        writer.WriteAttributeString("externdelividint", dt.Rows[i][2].ToString());
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][7].ToString());
                        writer.WriteAttributeString("timestampdeliv",   dt.Rows[i][4].ToString() + " " + dt.Rows[i][5].ToString());

                        // </messagedeliv>
                        writer.WriteEndElement();
                    }

                    prgBarProcess.PerformStep();
                }

                // write the last </message> element
                writer.WriteEndElement();

                // write the </root> element
                writer.WriteEndElement();

                // write End of document
                writer.WriteEndDocument();

                writer.Close();

                prgBarProcess.Enabled = false;
                radStep3.Enabled      = false;
                radStep5.Enabled      = true;
                radStep5.Checked      = true;

                Cursor = Cursors.Default;

                MessageBox.Show("Génération du fichier XML terminée avec succès (" + txtXmlPath.Text + ")" , m_DialogTitle);
            }
            catch (Exception err)
            {
                MessageBox.Show("Une erreur s'est produite : " + err.Message, m_DialogTitle);

                radStep2.Enabled    = false;
                radStep3.Enabled    = false;
                radStep5.Enabled    = false;
                prgBarProcess.Value = 0;
                cmdProcess.Enabled  = true;
            }
        }

        // return string for OLEDB connexion on excel file
        private string ExcelConnection(String excelFilePath)
        {
            return @"Provider=Microsoft.Jet.OLEDB.4.0;" +
                   @"Data Source="                      + excelFilePath                 + ";" +
                   @"Extended Properties="              + Convert.ToChar(34).ToString() +
                   @"Excel 8.0;"                        + Convert.ToChar(34).ToString();
        }

        private void cmdParcourirExcel_Click(object sender, EventArgs e)
        {
            cmdProcess.Enabled = false;

            if (openFileDlgExcel.ShowDialog() == DialogResult.OK)
            {
                txtExcelPath.Text = openFileDlgExcel.FileName;

                if (txtXmlPath.Text != "")
                    cmdProcess.Enabled = true;
            }
        }

        private void cmdParcourirXml_Click(object sender, EventArgs e)
        {
            cmdProcess.Enabled = false;

            if (openFileDlgXml.ShowDialog() == DialogResult.OK)
            {
                txtXmlPath.Text = openFileDlgXml.FileName;

                if (txtExcelPath.Text != "")
                    cmdProcess.Enabled = true;
            }
        }

        private void cmdQuitter_Click(object sender, EventArgs e)
        {
            Dispose();
        }
    }
}
