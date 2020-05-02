using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmAILE : Form
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

        private Employeeaile m_EmployeeAILE;
        private int          m_EmplID;
        private int          m_WkgID;
        private int          m_EmployeeAileID;

        /// getter/setter
        public int OpenMode {get{return (int)m_OpenMode;} set {m_OpenMode = (IEOpenMode)value;}}
        public int EndMode  {get{return (int)m_EndMode;}  set {m_EndMode  = (IEEndMode) value;}}

        public FrmAILE()
        {
            InitializeComponent();
        }

        public FrmAILE(int emplID)
        {
            InitializeComponent();

            m_EmplID         = emplID;
            m_EmployeeAileID = -1;
        }

        public FrmAILE(int emplID, int employeeAipID, int wkgID)
        {
            InitializeComponent();

            m_EmplID         = emplID;
            m_EmployeeAileID = employeeAipID;
            m_WkgID          = wkgID;
        }

        private void FrmAILE_Load(object sender, EventArgs e)
        {
            m_EmployeeAILE = new Employeeaile();

            // load AILE criteria combobox
            Ailecriteria aile = new Ailecriteria();

            cboCritereAILE.DataSource    = aile.GetList().Tables[0];
            cboCritereAILE.DisplayMember = "ailecriteria";
            cboCritereAILE.ValueMember   = "ailecriteriaid";

            // load Combobox TEAM
            Pworkgroup pworkgrp = new Pworkgroup();

            cboEquipe.DataSource    = pworkgrp.GetListByType((int)Pworkgroup.IEType.IE_T_Team).Tables[0];
            cboEquipe.DisplayMember = "wkgname";
            cboEquipe.ValueMember   = "wkgid";

            // get employee name for display
            Pemployee oPemployee = new Pemployee();
            oPemployee.loadEmployee(m_EmplID);

            txtEmploye.Text = oPemployee.LName + " " + oPemployee.FName;

            // check open mode
            if (OpenMode == (int)IEOpenMode.IE_OM_Edit || OpenMode == (int)IEOpenMode.IE_OM_View)
            {
                m_EmployeeAILE.loadEmployeeAILE(m_EmployeeAileID);

                txtDateDebut.Value           = m_EmployeeAILE.StartDate;
                txtDateFin.Value             = m_EmployeeAILE.EndDate;
                txtMotif.Text                = m_EmployeeAILE.Motif;
                txtTaux.Text                 = m_EmployeeAILE.Taux.ToString();
                cboEquipe.SelectedValue      = m_EmployeeAILE.WkgID;
                cboCritereAILE.SelectedValue = m_EmployeeAILE.AileCriteriaID;
            }

            if (OpenMode == (int)IEOpenMode.IE_OM_Add)
            {
                cmdSauver.Text = "Ajouter";
                this.Text      = "Ajout d'une nouvelle configuration AILE";
            }
        }

        private void cmdAnnuler_Click(object sender, EventArgs e)
        {
            m_EndMode = IEEndMode.IE_EM_Canceled;
            this.Hide();
        }

        private void cmdSauver_Click(object sender, EventArgs e)
        {
            try
            {
                if (!CheckFields())
                    return;

                if (OpenMode == (int)IEOpenMode.IE_OM_Add)
                {
                    m_EmployeeAILE.EmplID         = m_EmplID;
                    m_EmployeeAILE.WkgID          = (int)cboEquipe.SelectedValue;
                    m_EmployeeAILE.AileCriteriaID = Convert.ToInt32(cboCritereAILE.SelectedValue);
                    m_EmployeeAILE.Motif          = txtMotif.Text;
                    m_EmployeeAILE.Taux           = Convert.ToSingle(txtTaux.Text);
                    m_EmployeeAILE.StartDate      = txtDateDebut.Value;
                    m_EmployeeAILE.EndDate        = txtDateFin.Value;

                    m_EmployeeAILE.Add();

                    m_EndMode = IEEndMode.IE_EM_Added;
                }

                if (OpenMode == (int)IEOpenMode.IE_OM_Edit)
                {
                    m_EmployeeAILE.EmployeeaileID = m_EmployeeAileID;
                    m_EmployeeAILE.WkgID          = (int)cboEquipe.SelectedValue;
                    m_EmployeeAILE.EmplID         = m_EmplID;
                    m_EmployeeAILE.AileCriteriaID = Convert.ToInt32(cboCritereAILE.SelectedValue);
                    m_EmployeeAILE.Motif          = txtMotif.Text;
                    m_EmployeeAILE.Taux           = Convert.ToSingle(txtTaux.Text);
                    m_EmployeeAILE.StartDate      = txtDateDebut.Value;
                    m_EmployeeAILE.EndDate        = txtDateFin.Value;

                    m_EmployeeAILE.Update();

                    m_EndMode = IEEndMode.IE_EM_Edited;
                }

                this.Hide();
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
    }
}
