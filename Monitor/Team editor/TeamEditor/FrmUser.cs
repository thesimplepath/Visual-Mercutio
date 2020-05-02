using System;
using System.Drawing;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmUser : Form
    {
        private Pemployee m_CurEmp;
        private int       m_EmplID ;
        private int       m_Year;

        public FrmUser()
        {
            m_CurEmp = new Pemployee();
            InitializeComponent();
        }

        private void FrmUser_Load(object sender, EventArgs e)
        {
            Pemployeetitle oPemployeetitle = new Pemployeetitle();

            // load Employee Grid
            LoadGridEmployee();

            // load EmployeeTitle combobox
            cboGrade.DataSource    = oPemployeetitle.getList().Tables[0];
            cboGrade.DisplayMember = "employeetitle";
            cboGrade.ValueMember   = "employeetitleID";

            m_Year = DateTime.Now.Year;
        }

        private void LoadGridEmployee()
        {
            Pemployee oPemployee = new Pemployee();
            dgrUser.DataSource   = oPemployee.getList();
            dgrUser.DataMember   = "Table";

            dgrUser.Columns["emplid"].Visible          = false;
            dgrUser.Columns["employeetitleid"].Visible = false;
            dgrUser.Columns["roleid"].Visible          = false;

            dgrUser.Columns["lname"].HeaderText            = "Nom";
            dgrUser.Columns["fname"].HeaderText            = "Prénom";
            dgrUser.Columns["flagasynchronous"].HeaderText = "Capsules";
            dgrUser.Columns["email"].HeaderText            = "Email";
            dgrUser.Columns["phone"].HeaderText            = "Téléphone";
            dgrUser.Columns["email"].Width                 = 200;
        }

        private void dgrUser_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            m_CurEmp.loadEmployee(Convert.ToInt32(dgrUser.CurrentRow.Cells["emplid"].Value));

            m_EmplID          = m_CurEmp.EmplID;
            txtNom.Text       = m_CurEmp.LName;
            txtPrenom.Text    = m_CurEmp.FName;
            txtEmail.Text     = m_CurEmp.Email;
            txtTelephone.Text = m_CurEmp.Phone;
            txtLogin.Text     = m_CurEmp.Login;

            if (m_CurEmp.FlagAsynchronous == (int)Pemployee.IEFlagAsychronous.IE_FA_Allowed)
                chkAsynchrone.Checked = true;
            else
                chkAsynchrone.Checked = false;

            cboGrade.SelectedValue = m_CurEmp.EmployeeTitleID;

            // load AIP config for this employee
            LoadGridAIP();

            // load AILE config for this employee
            LoadGridAILE();

            // load Calendar config for this employee
            LoadGridCalendar();
        }

        private void cmdSauver_Click(object sender, EventArgs e)
        {
            if (!checkFields())
                return;

            if (m_EmplID == -1)
            {
                Pemployee oPemployee = new Pemployee();

                oPemployee.Email           = txtEmail.Text;
                oPemployee.Phone           = txtTelephone.Text;
                oPemployee.FName           = txtPrenom.Text;
                oPemployee.LName           = txtNom.Text;
                oPemployee.Login           = txtLogin.Text;
                oPemployee.EmployeeTitleID = (int)cboGrade.SelectedValue;
                oPemployee.Password        = txtMotDePasse.Text;
                oPemployee.RoleID          = 3;

                if (chkAsynchrone.Checked)
                    oPemployee.FlagAsynchronous = (int)Pemployee.IEFlagAsychronous.IE_FA_Allowed;
                else
                    oPemployee.FlagAsynchronous = (int)Pemployee.IEFlagAsychronous.IE_FA_Denied;

                // add the new employee
                oPemployee.add();

                // reload employee grid
                LoadGridEmployee();

                MessageBox.Show("Employé ajouté avec succès", "Team Editor");
            }
            else
            {
                m_CurEmp.loadEmployee(m_EmplID);
                m_CurEmp.LName           = txtNom.Text;
                m_CurEmp.FName           = txtPrenom.Text;
                m_CurEmp.Email           = txtEmail.Text;
                m_CurEmp.Phone           = txtTelephone.Text;
                m_CurEmp.Login           = txtLogin.Text;
                m_CurEmp.EmployeeTitleID = (int)cboGrade.SelectedValue;
                m_CurEmp.Password        = txtMotDePasse.Text;

                if (chkAsynchrone.Checked)
                    m_CurEmp.FlagAsynchronous = (int)Pemployee.IEFlagAsychronous.IE_FA_Allowed;
                else
                    m_CurEmp.FlagAsynchronous = (int)Pemployee.IEFlagAsychronous.IE_FA_Denied;

                // update the current employee
                m_CurEmp.update();

                // reload employee grid
                LoadGridEmployee();

                MessageBox.Show("Employé sauvé avec succès", "Team Editor");
            }
        }

        private void cmdNouveau_Click(object sender, EventArgs e)
        {
            if (dgrUser.SelectedRows.Count > 0)
                dgrUser.SelectedRows[0].Selected = false;

            m_EmplID               = -1;
            txtConfirmation.Text   = "";
            txtEmail.Text          = "";
            txtTelephone.Text      = "";
            txtLogin.Text          = "";
            txtMotDePasse.Text     = "";
            txtNom.Text            = "";
            txtPrenom.Text         = "";
            chkAsynchrone.Checked  = false;
            cboGrade.SelectedIndex = 1;
        }

        private bool checkFields()
        {
            if (txtLogin.Text == "")
            {
                MessageBox.Show("Le champs Login est obligatoire !", "Team Editor");
                txtLogin.Focus();
                return false;
            }

            if (txtNom.Text == "")
            {
                MessageBox.Show("Le champs Nom est obligatoire !", "Team Editor");
                txtNom.Focus();
                return false;
            }

            if (txtPrenom.Text == "")
            {
                MessageBox.Show("Le champs Prénom est obligatoire !", "Team Editor");
                txtPrenom.Focus();
                return false;
            }

            if (txtMotDePasse.Text != txtConfirmation.Text)
            {
                MessageBox.Show("Les champs Mot de passe et confirmation doivent être identiques !", "Team Editor");
                txtMotDePasse.Focus();
                return false;
            }

            return true;
        }

        private void cmdNouveauAIP_Click(object sender, EventArgs e)
        {
            FrmAIP frmAIP   = new FrmAIP(m_EmplID);
            frmAIP.OpenMode = (int)FrmAIP.IEOpenMode.IE_OM_Add;
            frmAIP.ShowDialog() ;

            if (frmAIP.EndMode == (int)FrmAIP.IEEndMode.IE_EM_Added)
                MessageBox.Show("Configuration AIP ajoutée avec succès !", "Team Editor");

            if (frmAIP.EndMode == (int)FrmAIP.IEEndMode.IE_EM_Failed)
                MessageBox.Show("Une erreur s'est produite, l'action est annulée!", "Team Editor");

            // close and dispose the form
            frmAIP.Close();

            // reload gridAIP
            LoadGridAIP();
        }

        private void cmdEditerAIP_Click(object sender, EventArgs e)
        {
            if (grdAIP.SelectedRows.Count != 1)
                return;

            FrmAIP frmAIP = new FrmAIP(m_EmplID,  Convert.ToInt32(grdAIP["employeeaipid",grdAIP.SelectedRows[0].Index].Value));

            frmAIP.OpenMode = (int)FrmAIP.IEOpenMode.IE_OM_Edit;
            frmAIP.ShowDialog();

            if (frmAIP.EndMode == (int)FrmAIP.IEEndMode.IE_EM_Edited)
                MessageBox.Show("Configuration AIP éditée avec succès !", "Team Editor");

            if (frmAIP.EndMode == (int)FrmAIP.IEEndMode.IE_EM_Failed)
                MessageBox.Show("Une erreur s'est produite, l'action est annulée!", "Team Editor");

            // close and dispose the form
            frmAIP.Close();

            // reload gridAIP
            LoadGridAIP();
        }

        private void LoadGridAIP()
        {
            Employeeaip oEmployeeAIP = new Employeeaip();
            grdAIP.DataSource        = oEmployeeAIP.GetListByEmplID(m_EmplID);
            grdAIP.DataMember        = "Table";

            grdAIP.Columns["emplID"].Visible           = false;
            grdAIP.Columns["aipCriteriaID"].Visible    = false;
            grdAIP.Columns["employeeaipid"].Visible    = false;
            grdAIP.Columns["aipcriteria"].DisplayIndex = 1;
            grdAIP.Columns["aipcriteria"].HeaderText   = "Critère AIP";
            grdAIP.Columns["aipcriteria"].Width        = 150;
            grdAIP.Columns["motif"].HeaderText         = "Motif";
            grdAIP.Columns["motif"].Width              = 170;
            grdAIP.Columns["taux"].Width               = 30;
            grdAIP.Columns["startdate"].HeaderText     = "Date début";
            grdAIP.Columns["enddate"].HeaderText       = "Date fin";
        }

        private void LoadGridAILE()
        {
            Employeeaile oEmployeeAILE = new Employeeaile();
            grdAILE.DataSource         = oEmployeeAILE.GetListByEmplID(m_EmplID);
            grdAILE.DataMember         = "Table";

            grdAILE.Columns["emplID"].Visible            = false;
            grdAILE.Columns["aileCriteriaID"].Visible    = false;
            grdAILE.Columns["employeeaileid"].Visible    = false;
            grdAILE.Columns["wkgid"].Visible             = false;
            grdAILE.Columns["ailecriteria"].DisplayIndex = 1;
            grdAILE.Columns["ailecriteria"].HeaderText   = "Critère AILE";
            grdAILE.Columns["ailecriteria"].Width        = 150;
            grdAILE.Columns["wkgname"].DisplayIndex      = 0;
            grdAILE.Columns["wkgname"].HeaderText        = "Equipe";
            grdAILE.Columns["wkgname"].Width             = 170;
            grdAILE.Columns["motif"].HeaderText          = "Motif";
            grdAILE.Columns["motif"].Width               = 170;
            grdAILE.Columns["taux"].Width                = 30;
            grdAILE.Columns["startdate"].HeaderText      = "Date début";
            grdAILE.Columns["enddate"].HeaderText        = "Date fin";
        }

        private void grdAIP_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {}

        private void cmdNouveauAILE_Click(object sender, EventArgs e)
        {
            FrmAILE frmAILE  = new FrmAILE(m_EmplID);
            frmAILE.OpenMode = (int)FrmAILE.IEOpenMode.IE_OM_Add;
            frmAILE.ShowDialog();

            if (frmAILE.EndMode == (int)FrmAILE.IEEndMode.IE_EM_Added)
                MessageBox.Show("Configuration AILE ajoutée avec succès !", "Team Editor");

            if (frmAILE.EndMode == (int)FrmAILE.IEEndMode.IE_EM_Failed)
                MessageBox.Show("Une erreur s'est produite, l'action est annulée!", "Team Editor");

            // close and dispose the form
            frmAILE.Close();

            // reload gridAILE
            LoadGridAILE();
        }

        private void cmdEditerAILE_Click(object sender, EventArgs e)
        {
            if (grdAILE.SelectedRows.Count != 1)
                return;

            int selectedEmployeeAileID = Convert.ToInt32(grdAILE["employeeAILEid", grdAILE.SelectedRows[0].Index].Value);
            int selectedWkgID          = Convert.ToInt32(grdAILE["wkgid", grdAILE.SelectedRows[0].Index].Value);

            FrmAILE frmAILE  = new FrmAILE(m_EmplID,  selectedEmployeeAileID, selectedWkgID);
            frmAILE.OpenMode = (int)FrmAILE.IEOpenMode.IE_OM_Edit;
            frmAILE.ShowDialog();

            if (frmAILE.EndMode == (int)FrmAILE.IEEndMode.IE_EM_Edited)
                MessageBox.Show("Configuration AILE éditée avec succès !", "Team Editor");

            if (frmAILE.EndMode == (int)FrmAILE.IEEndMode.IE_EM_Failed)
                MessageBox.Show("Une erreur s'est produite, l'action est annulée!", "Team Editor");

            // close and dispose the form
            frmAILE.Close();

            // reload gridAILE
            LoadGridAILE();
        }

        private void cmdSupprimerAILE_Click(object sender, EventArgs e)
        {
            if (grdAILE.SelectedRows.Count != 1)
                return;

            int selectedEmployeeAileID = Convert.ToInt32(grdAILE["employeeAILEid", grdAILE.SelectedRows[0].Index].Value);
            int selectedWkgID          = Convert.ToInt32(grdAILE["wkgid", grdAILE.SelectedRows[0].Index].Value);

            Employeeaile oEmployeeAILE = new Employeeaile();
            oEmployeeAILE.loadEmployeeAILE(selectedEmployeeAileID);
            oEmployeeAILE.Delete();

            MessageBox.Show("Configuration AILE supprimée avec succès !", "Team Editor");

            // reload gridAILE
            LoadGridAILE();
        }

        private void cmdSupprimerAIP_Click(object sender, EventArgs e)
        {
            if (grdAIP.SelectedRows.Count != 1)
                return;

            int selectedEmployeeAipID = Convert.ToInt32(grdAIP["employeeaipid", grdAIP.SelectedRows[0].Index].Value);

            Employeeaip oEmployeeAIP = new Employeeaip();
            oEmployeeAIP.loadEmployeeAIP(selectedEmployeeAipID);
            oEmployeeAIP.Delete() ;

            MessageBox.Show("Configuration AI$P supprimée avec succès !", "Team Editor");

            // reload gridAIP
            LoadGridAIP();
        }

        private void tabUser_SelectedIndexChanged(object sender, EventArgs e)
        {}

        private void LoadGridCalendar()
        {
            Calendar cal = new Calendar();

            grdCalendar.DataSource                    = cal.GetDataSet(m_Year, m_EmplID).Tables[0];
            grdCalendar.Columns["Libelle"].Width      = 123;
            grdCalendar.Columns["Month1"].HeaderText  = "Jan";
            grdCalendar.Columns["Month1"].Width       = 40;
            grdCalendar.Columns["Month2"].HeaderText  = "Fév";
            grdCalendar.Columns["Month2"].Width       = 40;
            grdCalendar.Columns["Month3"].HeaderText  = "Mar";
            grdCalendar.Columns["Month3"].Width       = 40;
            grdCalendar.Columns["Month4"].HeaderText  = "Avr";
            grdCalendar.Columns["Month4"].Width       = 40;
            grdCalendar.Columns["Month5"].HeaderText  = "Mai";
            grdCalendar.Columns["Month5"].Width       = 40;
            grdCalendar.Columns["Month6"].HeaderText  = "Jun";
            grdCalendar.Columns["Month6"].Width       = 40;
            grdCalendar.Columns["Month7"].HeaderText  = "Jui";
            grdCalendar.Columns["Month7"].Width       = 40;
            grdCalendar.Columns["Month8"].HeaderText  = "Aou";
            grdCalendar.Columns["Month8"].Width       = 40;
            grdCalendar.Columns["Month9"].HeaderText  = "Sep";
            grdCalendar.Columns["Month9"].Width       = 40;
            grdCalendar.Columns["Month10"].HeaderText = "Oct";
            grdCalendar.Columns["Month10"].Width      = 40;
            grdCalendar.Columns["Month11"].HeaderText = "Nov";
            grdCalendar.Columns["Month11"].Width      = 40;
            grdCalendar.Columns["Month12"].HeaderText = "Déc";
            grdCalendar.Columns["Month12"].Width      = 40;

            grdCalendar.Columns[0].DefaultCellStyle.Font = new Font(grdCalendar.DefaultCellStyle.Font.FontFamily,
                                                                    grdCalendar.DefaultCellStyle.Font.Size,
                                                                    FontStyle.Bold) ;
            grdCalendar.Columns[0].ReadOnly              = true;
            grdCalendar.Columns[1].ReadOnly              = true;

            lblYear.Text = m_Year.ToString();

            for (int i = 0; i < grdCalendar.Rows.Count; i++)
                grdCalendar.Rows[i].ReadOnly = true;

            grdCalendar.Rows[1].ReadOnly = false;
        }

        private void cmdNextYear_Click(object sender, EventArgs e)
        {
            try
            {
                ++m_Year;
                LoadGridCalendar();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdPreviousYear_Click(object sender, EventArgs e)
        {
            try
            {
                --m_Year;
                LoadGridCalendar();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdSaveCalendar_Click(object sender, EventArgs e)
        {
            try
            {
                Employeecalendar empCal = new Employeecalendar();

                empCal.CalYear = m_Year ;
                empCal.EmplID  = m_EmplID;

                for (int i = 1; i <= 12; ++i)
                {
                    empCal.CalMonth    = i;
                    empCal.DaysPlanned = Convert.ToInt32(grdCalendar[(i + 1),1].Value);
                    empCal.Update();
                }

                MessageBox.Show("Plannification enregistrée avec succès !", "Team Editor");

                LoadGridCalendar();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void tbCalendar_Click(object sender, EventArgs e)
        {}

        private void grdCalendar_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {}

        private void lblYear_Click(object sender, EventArgs e)
        {}

        private void cmdFermer_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void dgrUser_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {}
    }
}
