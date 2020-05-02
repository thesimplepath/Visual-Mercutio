using System;
using System.Data;
using System.Windows.Forms;
using System.Xml;
using System.Data.OleDb;

namespace XmlBuilderBCVS
{
    public partial class FrmMain : Form
    {
        private String m_DialogTitle = "Processsoft XML Builder";

        public FrmMain()
        {
            InitializeComponent();
        }

        private void cmdProcess_Click(object sender, EventArgs e)
        {
            DateTime curDate = new DateTime();

            if (txtXmlPath.Text == "" || txtExcelPath.Text == "")
            {
                MessageBox.Show("Vous devez sélectionner un fichier Excel source et un fichier XML destination !", m_DialogTitle);
                return;
            }

            radStep5.Enabled      = false;
            prgBarProcess.Value   = 0;
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

            // parse every record
            for (int i = 0; i < dt.Rows.Count; ++i)
            {
                switch(dt.Rows[i][2].ToString())
                {
                    // deliverable 12 created, process 3 terminated, non final status
                    case "Compléter éval. qualitative et réexamen":
                        // <message>
                        writer.WriteStartElement("message");

                        curDate = Convert.ToDateTime(dt.Rows[i][3]);

                        writer.WriteAttributeString("caseid",             dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("caseidremark",       "");
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprocid",       "3");
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("statut",             "0");
                        writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());

                        writer.WriteStartElement("messagedeliv");

                        // attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    "0");
                        writer.WriteAttributeString("externdelivid",    "-");
                        writer.WriteAttributeString("externdelividint", "12");
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("timestampdeliv",   curDate.ToString("yyyyMMdd hhmmss"));

                        // </messagedeliv>
                        writer.WriteEndElement();

                        // write the last </message> element
                        writer.WriteEndElement();
                        break;

                    // deliverable 4 created, process 50 terminated, final status
                    case "Traiter le reexamen":
                        // <message>
                        writer.WriteStartElement("message");

                        curDate = Convert.ToDateTime(dt.Rows[i][3]);

                        writer.WriteAttributeString("caseid",             dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("caseidremark",       "");
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprocid",       "50");
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("statut",             "1");
                        writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());

                        writer.WriteStartElement("messagedeliv");

                        //attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    "0");
                        writer.WriteAttributeString("externdelivid",    "-");
                        writer.WriteAttributeString("externdelividint", "4");
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("timestampdeliv",   curDate.ToString("yyyyMMdd hhmmss"));

                        // </messagedeliv>
                        writer.WriteEndElement();

                        // write the last </message> element
                        writer.WriteEndElement();
                        break;

                    // deliverable 41 created, process 10 terminated, final status
                    case "Terminer le réexamen":
                        // <message>
                        writer.WriteStartElement("message");

                        curDate = Convert.ToDateTime(dt.Rows[i][3]);

                        writer.WriteAttributeString("caseid",             dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("caseidremark",       "");
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprocid",       "10");
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("statut",             "1");
                        writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());

                        writer.WriteStartElement("messagedeliv");

                        // attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    "0");
                        writer.WriteAttributeString("externdelivid",    "-");
                        writer.WriteAttributeString("externdelividint", "41");
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("timestampdeliv",   curDate.ToString("yyyyMMdd hhmmss"));

                        // </messagedeliv>
                        writer.WriteEndElement();

                        // write the last </message> element
                        writer.WriteEndElement();
                        break;

                    // deliverable 23 created, process 3 terminated, final status
                    case "Traiter le réexamen standard":
                        // <message>
                        writer.WriteStartElement("message");

                        curDate = Convert.ToDateTime(dt.Rows[i][3]);

                        writer.WriteAttributeString("caseid",             dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("caseidremark",       "");
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprocid",       "3");
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("statut",             "1");
                        writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());

                        writer.WriteStartElement("messagedeliv");

                        // attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    "0");
                        writer.WriteAttributeString("externdelivid",    "-");
                        writer.WriteAttributeString("externdelividint", "23");
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("timestampdeliv",   curDate.ToString("yyyyMMdd hhmmss"));

                        // </messagedeliv>
                        writer.WriteEndElement();

                        // write the last </message> element
                        writer.WriteEndElement();
                        break;

                    // deliverable 8 created, process 13 terminared, final status
                    case "Réexamen standard accepté":
                        // <message>
                        writer.WriteStartElement("message");

                        curDate = Convert.ToDateTime(dt.Rows[i][3]);

                        writer.WriteAttributeString("caseid",             dt.Rows[i][6].ToString());
                        writer.WriteAttributeString("caseidremark",       "");
                        writer.WriteAttributeString("externmessageid",    dt.Rows[i][9].ToString());
                        writer.WriteAttributeString("externprocid",       "13");
                        writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                        writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("statut",             "1");
                        writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                        writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());

                        writer.WriteStartElement("messagedeliv");

                        // attributes for <messagedeliv>
                        writer.WriteAttributeString("doublecontrol",    "0");
                        writer.WriteAttributeString("externdelivid",    "-");
                        writer.WriteAttributeString("externdelividint", "8");
                        writer.WriteAttributeString("externuserid",     dt.Rows[i][4].ToString());
                        writer.WriteAttributeString("timestampdeliv",   curDate.ToString("yyyyMMdd hhmmss"));

                        // </messagedeliv>
                        writer.WriteEndElement();

                        // write the last </message> element
                        writer.WriteEndElement();
                        break;
                }

                prgBarProcess.PerformStep();
            }

            // write the </root> element
            writer.WriteEndElement();

            // Write end of document
            writer.WriteEndDocument();

            writer.Close();

            prgBarProcess.Enabled = false;
            radStep3.Enabled      = false;
            radStep5.Enabled      = true;
            radStep5.Checked      = true;

            Cursor = Cursors.Default;

            MessageBox.Show("Génération du fichier XML terminée avec succès (" + txtXmlPath.Text + ")", m_DialogTitle);
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
