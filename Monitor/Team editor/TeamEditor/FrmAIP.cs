using System;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmAIP : Form
    {
        public enum IEOpenMode
        {
            IE_OM_View = 0,
            IE_OM_Edit = 1,
            IE_OM_Add  = 2
        };

        public enum IEEndMode
        {
            IE_EM_Canceled = 0,
            IE_EM_Added    = 1,
            IE_EM_Edited   = 2,
            IE_EM_Failed   = 3
        };

        public IEOpenMode m_OpenMode;
        public IEEndMode  m_EndMode;

        private Employeeaip m_EmployeeAIP;
        private int         m_EmplID;
        private int         m_EmployeeAipID;

        /// getter/setter
        public int OpenMode {get{return (int)m_OpenMode;} set{m_OpenMode = (IEOpenMode)value;}}
        public int EndMode  {get{return (int)m_EndMode;}  set{m_EndMode  = (IEEndMode) value;}}

        public FrmAIP()
        {
            InitializeComponent();
        }

        public FrmAIP(int emplID)
        {
            InitializeComponent();

            m_EmplID        = emplID;
            m_EmployeeAipID = -1;
        }

        public FrmAIP(int emplID, int employeeAipID)
        {
            InitializeComponent();

            m_EmplID = emplID;
            m_EmployeeAipID = employeeAipID;
        }

        private void FrmAIP_Load(object sender, EventArgs e)
        {
            m_EmployeeAIP = new Employeeaip();

            // load AIP criteria combobox
            Aipcriteria aip = new Aipcriteria();

            cboCritereAIP.DataSource    = aip.GetList().Tables[0];
            cboCritereAIP.DisplayMember = "aipcriteria";
            cboCritereAIP.ValueMember   = "aipcriteriaid";

            // get employee name for display
            Pemployee oPemployee = new Pemployee();
            oPemployee.loadEmployee(m_EmplID);

            txtEmploye.Text = oPemployee.LName + " " + oPemployee.FName;

            // check open mode
            if (OpenMode == (int)IEOpenMode.IE_OM_Edit || OpenMode == (int)IEOpenMode.IE_OM_View)
            {
                m_EmployeeAIP.loadEmployeeAIP(m_EmployeeAipID);

                txtDateDebut.Value = m_EmployeeAIP.StartDate;
                txtDateFin.Value   = m_EmployeeAIP.EndDate;
                txtMotif.Text      = m_EmployeeAIP.Motif;
                txtTaux.Text       = m_EmployeeAIP.Taux.ToString();
            }

            if (OpenMode == (int)IEOpenMode.IE_OM_Add)
            {
                cmdSauver.Text = "Ajouter";
                this.Text      = "Ajout d'une nouvelle configuration AIP";
            }
        }

        private void cmdSauver_Click(object sender, EventArgs e)
        {
            try
            {
                if (!CheckFields())
                    return;

                if (OpenMode == (int)IEOpenMode.IE_OM_Add)
                {
                    m_EmployeeAIP.EmplID        = m_EmplID;
                    m_EmployeeAIP.AipCriteriaID = (int)cboCritereAIP.SelectedValue;
                    m_EmployeeAIP.Motif         = txtMotif.Text;
                    m_EmployeeAIP.Taux          = Convert.ToSingle(txtTaux.Text);
                    m_EmployeeAIP.StartDate     = txtDateDebut.Value;
                    m_EmployeeAIP.EndDate       = txtDateFin.Value;

                    m_EmployeeAIP.Add();

                    m_EndMode = IEEndMode.IE_EM_Added;
                }

                if (OpenMode == (int)IEOpenMode.IE_OM_Edit)
                {
                    m_EmployeeAIP.EmployeeAipID = m_EmployeeAipID;
                    m_EmployeeAIP.EmplID        = m_EmplID;
                    m_EmployeeAIP.AipCriteriaID = (int)cboCritereAIP.SelectedValue;
                    m_EmployeeAIP.Motif         = txtMotif.Text;
                    m_EmployeeAIP.Taux          = Convert.ToSingle(txtTaux.Text);
                    m_EmployeeAIP.StartDate     = txtDateDebut.Value;
                    m_EmployeeAIP.EndDate       = txtDateFin.Value;

                    m_EmployeeAIP.Update();

                    m_EndMode = IEEndMode.IE_EM_Edited;
                }

                // update employee AIP calculation
                Aip oAip = new Aip();
                oAip.Update(m_EmplID);

                // close the form
                Hide();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
                m_EndMode = IEEndMode.IE_EM_Failed;
                this.Hide();
            }
        }

        private bool CheckFields()
        {
            if (txtMotif.Text == "")
            {
                MessageBox.Show("Le champs Motif est obligatoire !", "Team Editor");
                txtMotif.Focus();
                return false;
            }

            if (txtTaux.Text == "")
            {
                MessageBox.Show("Le champs Taux est obligatoire !", "Team Editor");
                txtTaux.Focus();
                return false;
            }

            if (txtDateDebut.Value > txtDateFin.Value)
            {
                MessageBox.Show("La date de fin ne peut pas être plus petite que la date de début", "Team Editor");
                txtDateFin.Focus();
                return false;
            }

            return true;
        }

        private void cmdAnnuler_Click(object sender, EventArgs e)
        {
            m_EndMode = IEEndMode.IE_EM_Canceled;
            Hide();
        }
    }
}
