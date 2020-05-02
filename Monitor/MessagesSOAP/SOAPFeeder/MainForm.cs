using System;
using System.Windows.Forms;
using System.IO;
using System.Web.Services.Protocols;

namespace SOAPFeeder
{
    /// <summary>
    /// Summary description for MainForm
    /// </summary>
    public class MainForm : System.Windows.Forms.Form
    {
        private System.Windows.Forms.TextBox        tbURL;
        private System.Windows.Forms.Label          label1;
        private System.Windows.Forms.Label          label2;
        private System.Windows.Forms.Button         bSend;
        private System.Windows.Forms.Label          lResult;
        private System.Windows.Forms.TextBox        tbPath;
        private System.Windows.Forms.Button         bOpen;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private Label                               label3;
        private TextBox                             tbAlias;

        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.Container components = null;

        public MainForm()
        {
            // Required for Windows Form Designer support
            InitializeComponent();
        }

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if (disposing)
                if (components != null)
                    components.Dispose();

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.tbURL = new System.Windows.Forms.TextBox();
            this.tbPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.bSend = new System.Windows.Forms.Button();
            this.lResult = new System.Windows.Forms.Label();
            this.bOpen = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label3 = new System.Windows.Forms.Label();
            this.tbAlias = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // tbURL
            // 
            this.tbURL.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbURL.Location = new System.Drawing.Point(156, 14);
            this.tbURL.Name = "tbURL";
            this.tbURL.Size = new System.Drawing.Size(441, 23);
            this.tbURL.TabIndex = 0;
            this.tbURL.Text = "http://localhost:8080/soap/servlet/rpcrouter";
            // 
            // tbPath
            // 
            this.tbPath.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbPath.Location = new System.Drawing.Point(155, 99);
            this.tbPath.Name = "tbPath";
            this.tbPath.Size = new System.Drawing.Size(399, 23);
            this.tbPath.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(21, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(110, 23);
            this.label1.TabIndex = 2;
            this.label1.Text = "SOAP URL";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(20, 100);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 3;
            this.label2.Text = "XML File";
            // 
            // bSend
            // 
            this.bSend.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bSend.Location = new System.Drawing.Point(457, 142);
            this.bSend.Name = "bSend";
            this.bSend.Size = new System.Drawing.Size(140, 46);
            this.bSend.TabIndex = 4;
            this.bSend.Text = "Send file";
            this.bSend.Click += new System.EventHandler(this.bSend_Click);
            // 
            // lResult
            // 
            this.lResult.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lResult.ForeColor = System.Drawing.Color.Red;
            this.lResult.Location = new System.Drawing.Point(45, 122);
            this.lResult.Name = "lResult";
            this.lResult.Size = new System.Drawing.Size(396, 23);
            this.lResult.TabIndex = 2;
            // 
            // bOpen
            // 
            this.bOpen.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bOpen.Location = new System.Drawing.Point(561, 99);
            this.bOpen.Name = "bOpen";
            this.bOpen.Size = new System.Drawing.Size(37, 24);
            this.bOpen.TabIndex = 6;
            this.bOpen.Text = "...";
            this.bOpen.Click += new System.EventHandler(this.bOpen_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "xml|*.xml";
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(21, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(110, 23);
            this.label3.TabIndex = 8;
            this.label3.Text = "ALIAS";
            // 
            // tbAlias
            // 
            this.tbAlias.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbAlias.Location = new System.Drawing.Point(156, 56);
            this.tbAlias.Name = "tbAlias";
            this.tbAlias.Size = new System.Drawing.Size(200, 23);
            this.tbAlias.TabIndex = 1;
            this.tbAlias.TextChanged += new System.EventHandler(this.tbAlias_TextChanged);
            // 
            // MainForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(612, 199);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbAlias);
            this.Controls.Add(this.bOpen);
            this.Controls.Add(this.lResult);
            this.Controls.Add(this.bSend);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbPath);
            this.Controls.Add(this.tbURL);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "Soap Feeder";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        /// <summary>
        /// The main entry point for the application
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new MainForm());
        }

        private void bSend_Click(object sender, System.EventArgs e)
        {
            if (tbAlias.Text == "" || tbPath.Text == "" || tbURL.Text == "")
            {
                MessageBox.Show("Please fill all the entries");
                return;
            }

            try
            {
                lResult.Text = "";
                String message = this.readFile();

                if (message != null)
                {
                    MessagesSOAPService _service = new MessagesSOAPService();
                    _service.Url = tbURL.Text;
                    int i = _service.sendMessage(message, tbAlias.Text);
                    displayResult(i);
                    _service = null;
                }
            }
            catch (SoapException se)
            {
                MessageBox.Show(this, "Erreur interne : " + se.Message);
                MessageBox.Show(this, "Erreur externe : " + se.Detail.InnerText);
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, "Erreur : " + ex.Message);
            }
        }

        private String readFile()
        {
            if (!File.Exists(tbPath.Text))
            {
                MessageBox.Show(this, "A file doesn't exist at this path");
                return null;
            }

            StreamReader sr = File.OpenText(tbPath.Text);
            String content  = sr.ReadToEnd();

            sr.Close();
            sr = null;
            return content;
        }

        private void displayResult(int result)
        {
            switch (result)
            {
                case 0:
                    // ERROR_NO_ERROR: all is OK
                    lResult.Text = "0 - OK";
                    break;

                case 1:
                    // ERROR_UNKNOW_ERROR: unknown error happened (see in the Tomcat log for details)
                    lResult.Text = "1 - unknow error";
                    break;

                case 2:
                    // ERROR_STATUT_NOT_VALID: invalid message status
                    lResult.Text = "2 - statut message pas valide";
                    break;

                case 3:
                    // ERROR_TIME_STAMP_PROC_NOT_VALID: message timestamp or time is invalid (i.e impossible
                    // to convert in date object, cf. below)
                    lResult.Text = "3 - timestamp ou messagetime du message pas valide (cf format timestamp)";
                    break;

                case 4:
                    // ERROR_MESSAGE_DELIV_DOUBLECONTROL_NOT_VALID: the deliverable double check isn't valid
                    lResult.Text = "4 - double control du deliv pas valide";
                    break;

                case 5:
                    // ERROR_MESSAGE_DELIV_TIMESTAMP_NOT_VALID: the deliverable time stamp isn't valid
                    lResult.Text = "5 - timestamp du deliv pas valide";
                    break;

                default:
                    lResult.Text = result + " - oups ?????????????????";
                    break;
            }
        }

        private void Form1_Load(object sender, System.EventArgs e)
        {}

        private void bOpen_Click(object sender, System.EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                tbPath.Text = openFileDialog1.FileName;
        }

        private void tbAlias_TextChanged(object sender, EventArgs e)
        {}
    }
}
