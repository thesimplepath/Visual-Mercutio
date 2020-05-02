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
    public partial class FrmTeam : Form
    {
        private Pworkgroup m_pWorkgroup;
        private int        m_WkgID;
        private int        m_Year;
        private int        m_YearManual;

        public FrmTeam()
        {
            m_WkgID      = -1;
            m_pWorkgroup = new Pworkgroup();

            InitializeComponent();
        }

        private void FrmTeam_Load(object sender, EventArgs e)
        {
            Pworkgroup oPworkgroup = new Pworkgroup();

            m_Year       = DateTime.Now.Year;
            m_YearManual = DateTime.Now.Year;

            // load Team Grid
            LoadGridTeam();

            if (grdTeam.Rows.Count > 0)
                grdTeam.Rows[0].Selected = true;

            // load parentGroup combobox
            cboGroupe.DisplayMember = "wkgname";
            cboGroupe.ValueMember   = "wkgid";
            cboGroupe.DataSource    = oPworkgroup.GetListByType((int)Pworkgroup.IEType.IE_T_Workgroup).Tables[0];
        }

        private void LoadGridTeam()
        {
            Pworkgroup oWorkgroup                   = new Pworkgroup();
            grdTeam.DataSource                      = oWorkgroup.GetListByType((int)Pworkgroup.IEType.IE_T_Team);
            grdTeam.DataMember                      = "Table";
            grdTeam.Columns["wkgid"].Visible        = false;
            grdTeam.Columns["eptflag"].Visible      = false;
            grdTeam.Columns["creationdate"].Visible = false;
            grdTeam.Columns["wkgparent"].Visible    = false;
            grdTeam.Columns["wkgtype"].Visible      = false;

            grdTeam.Columns["wkgname"].HeaderText       = "Equipe";
            grdTeam.Columns["phone"].HeaderText         = "Téléphone";
            grdTeam.Columns["country"].HeaderText       = "Pays";
            grdTeam.Columns["street"].HeaderText        = "Rue";
            grdTeam.Columns["npalocality"].HeaderText   = "Localité";
            grdTeam.Columns["municipality"].HeaderText  = "Commune";
            grdTeam.Columns["mission"].HeaderText       = "Mission";
            grdTeam.Columns["wkgpercent"].HeaderText    = "% / Groupe";
            grdTeam.Columns["wkgparentname"].HeaderText = "Groupe parent";
            grdTeam.Columns["vocation"].HeaderText      = "Vocation";
        }

        private void LoadGridCalendarAuto()
        {
            Calendar cal = new Calendar();

            grdCalendarAuto.DataSource = cal.GetDataSetEptTeamAuto(m_Year, m_WkgID).Tables[0];

            grdCalendarAuto.Columns["Participant"].Width  = 123;
            grdCalendarAuto.Columns["Month1"].HeaderText  = "Jan";
            grdCalendarAuto.Columns["Month1"].Width       = 40;
            grdCalendarAuto.Columns["Month2"].HeaderText  = "Fév";
            grdCalendarAuto.Columns["Month2"].Width       = 40;
            grdCalendarAuto.Columns["Month3"].HeaderText  = "Mar";
            grdCalendarAuto.Columns["Month3"].Width       = 40;
            grdCalendarAuto.Columns["Month4"].HeaderText  = "Avr";
            grdCalendarAuto.Columns["Month4"].Width       = 40;
            grdCalendarAuto.Columns["Month5"].HeaderText  = "Mai";
            grdCalendarAuto.Columns["Month5"].Width       = 40;
            grdCalendarAuto.Columns["Month6"].HeaderText  = "Jun";
            grdCalendarAuto.Columns["Month6"].Width       = 40;
            grdCalendarAuto.Columns["Month7"].HeaderText  = "Jui";
            grdCalendarAuto.Columns["Month7"].Width       = 40;
            grdCalendarAuto.Columns["Month8"].HeaderText  = "Aou";
            grdCalendarAuto.Columns["Month8"].Width       = 40;
            grdCalendarAuto.Columns["Month9"].HeaderText  = "Sep";
            grdCalendarAuto.Columns["Month9"].Width       = 40;
            grdCalendarAuto.Columns["Month10"].HeaderText = "Oct";
            grdCalendarAuto.Columns["Month10"].Width      = 40;
            grdCalendarAuto.Columns["Month11"].HeaderText = "Nov";
            grdCalendarAuto.Columns["Month11"].Width      = 40;
            grdCalendarAuto.Columns["Month12"].HeaderText = "Déc";
            grdCalendarAuto.Columns["Month12"].Width      = 40;

            grdCalendarAuto.Columns[0].DefaultCellStyle.Font = new Font(grdCalendarAuto.DefaultCellStyle.Font.FontFamily,
                                                                        grdCalendarAuto.DefaultCellStyle.Font.Size,
                                                                        FontStyle.Bold);
            grdCalendarAuto.Columns[0].ReadOnly              = true;

            lblYear.Text = m_Year.ToString();

            for (int i = 0; i < grdCalendarAuto.Rows.Count; ++i)
                grdCalendarAuto.Rows[i].ReadOnly = true;
        }

        private void LoadGridCalendarManual()
        {
            Calendar cal = new Calendar();

            grdCalendarManual.DataSource = cal.GetDataSetEptTeamManual(m_YearManual, m_WkgID).Tables[0];

            grdCalendarManual.Columns["Team"].HeaderText    = "Equipe";
            grdCalendarManual.Columns["Team"].Width         = 123;
            grdCalendarManual.Columns["Month1"].HeaderText  = "Jan";
            grdCalendarManual.Columns["Month1"].Width       = 40;
            grdCalendarManual.Columns["Month2"].HeaderText  = "Fév";
            grdCalendarManual.Columns["Month2"].Width       = 40;
            grdCalendarManual.Columns["Month3"].HeaderText  = "Mar";
            grdCalendarManual.Columns["Month3"].Width       = 40;
            grdCalendarManual.Columns["Month4"].HeaderText  = "Avr";
            grdCalendarManual.Columns["Month4"].Width       = 40;
            grdCalendarManual.Columns["Month5"].HeaderText  = "Mai";
            grdCalendarManual.Columns["Month5"].Width       = 40;
            grdCalendarManual.Columns["Month6"].HeaderText  = "Jun";
            grdCalendarManual.Columns["Month6"].Width       = 40;
            grdCalendarManual.Columns["Month7"].HeaderText  = "Jui";
            grdCalendarManual.Columns["Month7"].Width       = 40;
            grdCalendarManual.Columns["Month8"].HeaderText  = "Aou";
            grdCalendarManual.Columns["Month8"].Width       = 40;
            grdCalendarManual.Columns["Month9"].HeaderText  = "Sep";
            grdCalendarManual.Columns["Month9"].Width       = 40;
            grdCalendarManual.Columns["Month10"].HeaderText = "Oct";
            grdCalendarManual.Columns["Month10"].Width      = 40;
            grdCalendarManual.Columns["Month11"].HeaderText = "Nov";
            grdCalendarManual.Columns["Month11"].Width      = 40;
            grdCalendarManual.Columns["Month12"].HeaderText = "Déc";
            grdCalendarManual.Columns["Month12"].Width      = 40;

            grdCalendarManual.Columns[0].DefaultCellStyle.Font = new Font(grdCalendarManual.DefaultCellStyle.Font.FontFamily,
                                                                          grdCalendarManual.DefaultCellStyle.Font.Size,
                                                                          FontStyle.Bold);
            grdCalendarManual.Columns[0].ReadOnly              = true;

            lblYearManual.Text = m_YearManual.ToString();

            for (int i = 0; i < grdCalendarManual.Rows.Count; ++i)
                grdCalendarManual.Rows[i].ReadOnly = true;
        }

        private bool checkFields()
        {
            if (txtNom.Text == "")
            {
                MessageBox.Show("Le champs Nom est obligatoire !", "Team Editor");
                txtNom.Focus();
                return false;
            }

            return true;
        }

        private void cmdNouveau_Click(object sender, EventArgs e)
        {
            if (grdTeam.SelectedRows.Count > 0)
                grdTeam.SelectedRows[0].Selected = false ;

            m_WkgID                 = -1;
            txtCommune.Text         =  "";
            txtDateCreation.Text    =  "";
            txtEmail.Text           =  "";
            txtMission.Text         =  "";
            txtNom.Text             =  "";
            txtNpaLocalite.Text     =  "";
            txtPays.Text            =  "";
            txtPercent.Text         =  "0";
            txtRue.Text             =  "";
            txtTelephone.Text       =  "";
            txtVocation.Text        =  "";
            cboGroupe.SelectedIndex =  0;
        }

        private void grdTeam_CellClick(object sender, DataGridViewCellEventArgs e)
        {}

        private void cmdSauver_Click(object sender, EventArgs e)
        {
            if (!checkFields())
                return;

            if (m_WkgID == -1)
            {
                m_pWorkgroup.Country      = txtPays.Text;
                m_pWorkgroup.Email        = txtEmail.Text;
                m_pWorkgroup.EptFlag      = (int)Pworkgroup.IEEPT.IE_E_CalculatedBySystem;
                m_pWorkgroup.Mission      = txtMission.Text;
                m_pWorkgroup.Municipality = txtCommune.Text;
                m_pWorkgroup.NpaLocality  = txtNpaLocalite.Text;
                m_pWorkgroup.Street       = txtRue.Text;
                m_pWorkgroup.Vocation     = txtVocation.Text;
                m_pWorkgroup.WkgName      = txtNom.Text;
                m_pWorkgroup.WkgParentID  = (int)cboGroupe.SelectedValue;
                m_pWorkgroup.WkgPercent   = Convert.ToInt32(txtPercent.Text);
                m_pWorkgroup.WkgType      = (int)Pworkgroup.IEType.IE_T_Team;
                m_pWorkgroup.Phone        = txtTelephone.Text;

                // add the new team into the database
                m_pWorkgroup.Add();

                // refresh datagrid
                LoadGridTeam();

                MessageBox.Show("Equipe ajoutée avec succès", "Team Editor");
            }
            else
            {
                m_pWorkgroup.LoadWorkgroup(m_WkgID);

                m_pWorkgroup.Municipality = txtCommune.Text;
                m_pWorkgroup.Email        = txtEmail.Text;
                m_pWorkgroup.WkgName      = txtNom.Text;
                m_pWorkgroup.NpaLocality  = txtNpaLocalite.Text;
                m_pWorkgroup.Country      = txtPays.Text;
                m_pWorkgroup.WkgPercent   = Convert.ToInt32(txtPercent.Text);
                m_pWorkgroup.Street       = txtRue.Text;
                m_pWorkgroup.Phone        = txtTelephone.Text;
                m_pWorkgroup.Vocation     = txtVocation.Text;
                m_pWorkgroup.WkgType      = (int)Pworkgroup.IEType.IE_T_Team;
                m_pWorkgroup.WkgParentID  = Convert.ToInt32(cboGroupe.SelectedValue);

                // update the current team
                m_pWorkgroup.Update();

                // reload team grid
                LoadGridTeam();

                MessageBox.Show("Equipe sauvée avec succès", "Team Editor");
            }
        }

        private void cmdVider_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void cboGroupe_SelectedValueChanged(object sender, EventArgs e)
        {
            UpdateTotalPercent();
        }

        private void UpdateTotalPercent()
        {
            Pworkgroup wkg = new Pworkgroup();

            if (cboGroupe.SelectedIndex != -1)
                if (txtPercent.Text != "" && m_WkgID == -1)
                    txtPercentTotal.Text = Convert.ToString(wkg.GetPercentForGroup((int)cboGroupe.SelectedValue) + Convert.ToInt32(txtPercent.Text));
                else
                    txtPercentTotal.Text = Convert.ToString(wkg.GetPercentForGroup((int)cboGroupe.SelectedValue));

            if (Convert.ToInt32(txtPercentTotal.Text) > 100)
            {
                MessageBox.Show("Le groupe possède un total d'activité plus grand que 100%. Veuillez corriger le pourcentage d'activité de l'équipe");
                txtPercent.Focus();
                txtPercent.SelectAll();
            }
        }

        private void txtPercent_TextChanged(object sender, EventArgs e)
        {
            UpdateTotalPercent();
        }

        private void txtPercent_Validating(object sender, CancelEventArgs e)
        {
            if (txtPercent.Text == "")
                txtPercent.Text = "0";
        }

        private void tabPage2_Click(object sender, EventArgs e)
        {}

        private void cmdPreviousYear_Click(object sender, EventArgs e)
        {
            try
            {
                --m_Year;

                LoadGridCalendarAuto();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdNextYear_Click(object sender, EventArgs e)
        {
            try
            {
                ++m_Year;

                LoadGridCalendarAuto();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void grdTeam_SelectionChanged(object sender, EventArgs e)
        {
            if (grdTeam.Rows.Count == 0)
                return;

            m_pWorkgroup.LoadWorkgroup(Convert.ToInt32(grdTeam.CurrentRow.Cells["wkgid"].Value));

            m_WkgID                 = m_pWorkgroup.WkgID;
            txtCommune.Text         = m_pWorkgroup.Municipality;
            txtDateCreation.Text    = m_pWorkgroup.CreationDate;
            txtEmail.Text           = m_pWorkgroup.Email;
            txtMission.Text         = m_pWorkgroup.Mission;
            txtNom.Text             = m_pWorkgroup.WkgName;
            txtNpaLocalite.Text     = m_pWorkgroup.NpaLocality;
            txtPays.Text            = m_pWorkgroup.Country;
            txtPercent.Text         = Convert.ToString(m_pWorkgroup.WkgPercent);
            txtRue.Text             = m_pWorkgroup.Street;
            txtTelephone.Text       = m_pWorkgroup.Phone;
            txtVocation.Text        = m_pWorkgroup.Vocation;
            m_pWorkgroup.EptFlag    = (int)Pworkgroup.IEEPT.IE_E_CalculatedBySystem;
            cboGroupe.SelectedValue = m_pWorkgroup.WkgParentID;

            // load grid calculated auto
            LoadGridCalendarAuto();

            // load grid ept manual
            LoadGridCalendarManual();

            // update total % for the group
            UpdateTotalPercent();
        }

        private void cmdNextYearManual_Click(object sender, EventArgs e)
        {
            try
            {
                ++m_YearManual;

                LoadGridCalendarManual();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdPreviousYearManual_Click(object sender, EventArgs e)
        {
            try
            {
                --m_YearManual;

                LoadGridCalendarManual();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdSaveEptManual_Click(object sender, EventArgs e)
        {
            try
            {
                Eptteammanual eptTeamManual = new Eptteammanual();
                eptTeamManual.CalYear       = m_YearManual;
                eptTeamManual.WkgID         = m_WkgID;

                for (int i = 1; i <= 12; ++i)
                {
                    eptTeamManual.CalMonth = i;
                    eptTeamManual.EptValue = Convert.ToInt32(grdCalendarManual[i, 0].Value);

                    eptTeamManual.Update();
                }

                MessageBox.Show("Plannification enregistrée avec succès !", "Team Editor");

                LoadGridCalendarManual();
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cboGroupe_SelectedIndexChanged(object sender, EventArgs e)
        {}

        private void grdCalendarAuto_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {}
    }
}
