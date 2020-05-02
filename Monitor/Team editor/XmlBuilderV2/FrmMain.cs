using System;
using System.Data;
using System.Windows.Forms;
using System.Xml;
using System.Data.OleDb;
using System.IO;

namespace XmlBuilderV2
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
            deleteIncompleteRows();

            DateTime curDate = new DateTime();

            if (txtXmlPath.Text == "" || txtExcelPath.Text == "")
            {
                MessageBox.Show("Vous devez sélectionner un fichier Excel source et un fichier XML destination !", m_DialogTitle);
                return;
            }

            radStep5.Enabled      = false;
            prgBarProcess.Value   = 0;
            prgBarProcess.Enabled = false;
            Cursor                = Cursors.WaitCursor;

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

            string[] criteres;
            int      countDiscardedRows = 0;

            // parse every record
            for (int i = 0; i < dt.Rows.Count; ++i)
            {
                criteres = getCriteresValues(dt.Rows[i][1].ToString(), dt.Rows[i][2].ToString());

                if (criteres[0] == null)
                {
                    prgBarProcess.PerformStep();
                    ++countDiscardedRows;
                    continue;
                }

                writer.WriteStartElement("message");

                curDate = Convert.ToDateTime(dt.Rows[i][3]);

                writer.WriteAttributeString("caseid", dt.Rows[i][6].ToString());
                writer.WriteAttributeString("caseidremark", "");
                writer.WriteAttributeString("externmessageid", dt.Rows[i][9].ToString());

                if(criteres[0] != null)
                    // from table
                    writer.WriteAttributeString("externprocid", criteres[0].ToString() );

                writer.WriteAttributeString("externsystemid",     dt.Rows[i][8].ToString());
                writer.WriteAttributeString("externuserid",       dt.Rows[i][4].ToString());
                writer.WriteAttributeString("messagetime",        curDate.ToString("yyyyMMdd hhmmss"));
                writer.WriteAttributeString("statut",             dt.Rows[i][7].ToString());
                writer.WriteAttributeString("timestampproc",      curDate.ToString("yyyyMMdd hhmmss"));
                writer.WriteAttributeString("externprestationid", dt.Rows[i][5].ToString());
                writer.WriteStartElement("messagedeliv");

                // attributes for <messagedeliv>
                writer.WriteAttributeString("doublecontrol", "0");
                writer.WriteAttributeString("externdelivid", "-");

                if( criteres[1] != null )
                    // from table
                    writer.WriteAttributeString("externdelividint", criteres[1].ToString() );

                writer.WriteAttributeString("externuserid", dt.Rows[i][4].ToString());
                writer.WriteAttributeString("timestampdeliv", curDate.ToString("yyyyMMdd hhmmss"));

                // </messagedeliv>
                writer.WriteEndElement();

                // write the last </message> element
                writer.WriteEndElement();

                prgBarProcess.PerformStep();
            }

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

            MessageBox.Show("Génération du fichier XML terminée avec succès, " +
                            countDiscardedRows                                 +
                            " lignes ignorées (" + txtXmlPath.Text + ")",
                            m_DialogTitle);
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

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {}

        private void button1_Click(object sender, EventArgs e)
        {
            // get rid of incomplete rows
            deleteIncompleteRows();

            // save rows of criteres to a file
            if( dataGridView1.Rows.Count > 1 )
                writefile();
        }

        private void deleteIncompleteRows()
        {
            bool column1OK = false;
            bool column2OK = false;
            bool column3OK = false;
            bool column4OK = false;
            bool column5OK = false;
            int  counter   = 0;

            for (int i = 0; i < dataGridView1.Rows.Count; ++i)
            {
                column1OK = true;
                column2OK = dataGridView1.Rows[i].Cells[1].Value != null && dataGridView1.Rows[i].Cells[1].Value.ToString().Trim() != "";
                column3OK = dataGridView1.Rows[i].Cells[2].Value != null && dataGridView1.Rows[i].Cells[2].Value.ToString().Trim() != "";
                column4OK = dataGridView1.Rows[i].Cells[3].Value != null && dataGridView1.Rows[i].Cells[3].Value.ToString().Trim() != "";
                column5OK = true;

                // get rid of the incomplete rows
                if (!dataGridView1.Rows[i].IsNewRow)
                    if (!column1OK || !column2OK || !column3OK || !column4OK || !column5OK)
                    {
                        dataGridView1.Rows.Remove(dataGridView1.Rows[i]);
                        ++counter;
                        --i;
                    }

            }
        }


        private string[] getCriteresValues( string critere1, string critere2 )
        {
            string[] criteres = new string[3];

            foreach (DataGridViewRow row in dataGridView1.Rows)
                if (!row.IsNewRow)
                    if (row.Cells[0].Value.ToString().Trim() == critere1 && row.Cells[1].Value.ToString().Trim() == critere2)
                    {
                        criteres[0] = row.Cells[2].Value.ToString();
                        criteres[1] = row.Cells[3].Value.ToString();
                    }

            return criteres;
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            dataGridView1.Columns[0].HeaderText = "Critère 1";
            dataGridView1.Columns[0].Width      = 200;
            dataGridView1.Columns[1].HeaderText = "Critère 2";
            dataGridView1.Columns[1].Width      = 200;
            dataGridView1.Columns[2].HeaderText = "ProcID";
            dataGridView1.Columns[3].HeaderText = "DelivID";
            dataGridView1.Columns[4].Visible    = false;
        }

        private void writefile()
        {
            // open the file
            FileStream   fs = new FileStream("settings.dat", FileMode.Create, FileAccess.Write);
            StreamWriter sw = new StreamWriter(fs);

            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                string line;

                // get rid of the incomplete rows
                if (!row.IsNewRow)
                {
                    if (row.Cells[0].Value == null)
                        row.Cells[0].Value = "";

                    line = (row.Cells[0].Value.ToString() == "" ? "EMPTY" : row.Cells[0].Value.ToString()) + ";" +
                            row.Cells[1].Value.ToString()                                                  + ";" +
                            row.Cells[2].Value.ToString()                                                  + ";" +
                            row.Cells[3].Value.ToString() ;
                    sw.WriteLine(line);
                }
            }

            sw.Close();
            fs.Close();
        }

        private void readfile()
        {
            if (!File.Exists("settings.dat"))
            {
                MessageBox.Show("Cannot find settings.dat");
                return;
            }

            FileStream   fs  = new FileStream("settings.dat", FileMode.Open, FileAccess.Read);
            StreamReader sr  = new StreamReader(fs);
            string       row = "";

            for (;;)
            {
                row = sr.ReadLine();

                if (row != null)
                {
                    LoadCritereRow(row);

                    if (row.Trim() == "")
                        break;
                }
                else
                    break;
            }

            sr.Close();
            fs.Close();
        }

        private void LoadCritereRow( string row )
        {
            char[]   splitter = {';'};
            string[] temp     = row.Split(splitter);

            for (int i = 0; i < temp.Length; ++i)
                if (temp[0] == "EMPTY")
                    temp[0] = "";

            dataGridView1.Rows.Add(temp);
        }

        private void btLoadCriteres_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            readfile();
        }
    }
}
