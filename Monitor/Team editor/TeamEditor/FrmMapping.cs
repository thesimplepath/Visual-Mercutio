using System;
using System.Drawing;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmMapping : Form
    {
        private string m_ModelRef;
        private int    m_ExternSystemID;
        private bool   m_FlagGrdProcLoaded;
        private bool   m_FlagGrdDelivLoaded;
        private bool   m_FlagGrdUserLoaded;
        private bool   m_FlagGrdPrestationLoaded;

        public FrmMapping()
        {
            InitializeComponent();
        }

        private void FrmMapping_Load(object sender, EventArgs e)
        {
            ExternSystem externSystem = new ExternSystem();
            PModel       pModel       = new PModel();

            // load extern system combo
            cboExternSystem.DisplayMember = "externsystemdesc";
            cboExternSystem.ValueMember   = "externsystemid";
            cboExternSystem.DataSource    = externSystem.getList().Tables[0];

            // load model ref combo
            cboModel.DisplayMember = "modelref";
            cboModel.ValueMember   = "modelref";
            cboModel.DataSource    = pModel.getListOfModelRef().Tables[0];

            // update after the combo selection
            updateComboSelection() ;
        }

        private void updateComboSelection()
        {
            m_ModelRef       = cboModel.SelectedValue.ToString();
            m_ExternSystemID = (int)cboExternSystem.SelectedValue;

            // update Grid Mapping Proc
            LoadGridMappingProc();

            // update Grid Mapping Deliv
            LoadGridMappingDeliv();

            // update Grid Mapping User
            LoadGridMappingUser();

            // update Grid Mapping Prestation
            LoadGridMappingPrestation();
        }

        private void LoadGridMappingProc()
        {
            m_FlagGrdProcLoaded = false;

            ExternProc externProc = new ExternProc();
            grdProc.DataSource    = externProc.getListMapping(m_ExternSystemID, m_ModelRef);
            grdProc.DataMember    = "Table";

            grdProc.Columns["externprocid"].Visible                       = false;
            grdProc.Columns["procstableid"].HeaderText                    = "ID Conceptor";
            grdProc.Columns["externproctrans"].HeaderText                 = "ID Externe";
            grdProc.Columns["externprocdesc"].HeaderText                  = "Description";
            grdProc.Columns["procname"].HeaderText                        = "Procédure";
            grdProc.Columns["procname"].Width                             = 400;
            grdProc.Columns["externprocdesc"].Width                       = 300;
            grdProc.Columns["procstableid"].ReadOnly                      = true;
            grdProc.Columns["procname"].ReadOnly                          = true;
            grdProc.Columns["externproctrans"].DefaultCellStyle.BackColor = Color.LightGreen;
            grdProc.Columns["externprocdesc"].DefaultCellStyle.BackColor  = Color.LightGreen;

            m_FlagGrdProcLoaded = true;
        }

        private void LoadGridMappingDeliv()
        {
            m_FlagGrdDelivLoaded = false;

            ExternDeliv externDeliv = new ExternDeliv();
            grdDeliv.DataSource     = externDeliv.getListMapping(m_ExternSystemID, m_ModelRef);
            grdDeliv.DataMember     = "Table";

            grdDeliv.Columns["externdelivid"].Visible                       = false;
            grdDeliv.Columns["externprocid"].Visible                        = false;
            grdDeliv.Columns["delivstableid"].HeaderText                    = "ID Conceptor";
            grdDeliv.Columns["externdelivtrans"].HeaderText                 = "ID Externe";
            grdDeliv.Columns["externdelivdesc"].HeaderText                  = "Description";
            grdDeliv.Columns["procname"].HeaderText                         = "Procédure source";
            grdDeliv.Columns["delivname"].HeaderText                        = "Livrable";
            grdDeliv.Columns["procname"].Width                              = 300;
            grdDeliv.Columns["delivname"].Width                             = 300;
            grdDeliv.Columns["delivstableid"].ReadOnly                      = true;
            grdDeliv.Columns["procname"].ReadOnly                           = true;
            grdDeliv.Columns["delivname"].ReadOnly                          = true;
            grdDeliv.Columns["externdelivtrans"].DefaultCellStyle.BackColor = Color.LightGreen;
            grdDeliv.Columns["externdelivdesc"].DefaultCellStyle.BackColor  = Color.LightGreen;

            m_FlagGrdDelivLoaded = true;
        }

        private void LoadGridMappingUser()
        {
            m_FlagGrdUserLoaded = false;

            ExternUser externUser = new ExternUser();
            grdUser.DataSource    = externUser.getListMapping(m_ExternSystemID);
            grdUser.DataMember    = "Table";

            grdUser.Columns["externuserid"].Visible                  = false;
            grdUser.Columns["externuser"].HeaderText                 = "UserID Externe";
            grdUser.Columns["externuser"].Width                      = 130;
            grdUser.Columns["emplid"].HeaderText                     = "UserID Messenger";
            grdUser.Columns["emplid"].Width                          = 130;
            grdUser.Columns["login"].HeaderText                      = "Login";
            grdUser.Columns["login"].Width                           = 130;
            grdUser.Columns["lname"].HeaderText                      = "Nom";
            grdUser.Columns["lname"].Width                           = 130;
            grdUser.Columns["fname"].HeaderText                      = "Prénom";
            grdUser.Columns["fname"].Width                           = 130;
            grdUser.Columns["externuserid"].ReadOnly                 = true;
            grdUser.Columns["emplid"].ReadOnly                       = true;
            grdUser.Columns["login"].ReadOnly                        = true;
            grdUser.Columns["lname"].ReadOnly                        = true;
            grdUser.Columns["fname"].ReadOnly                        = true;
            grdUser.Columns["externuser"].DefaultCellStyle.BackColor = Color.LightGreen;

            m_FlagGrdUserLoaded = true;
        }

        private void LoadGridMappingPrestation()
        {
            m_FlagGrdPrestationLoaded = false;

            ExternPrestation externPrestation = new ExternPrestation();
            grdPrestation.DataSource          = externPrestation.getListMapping(m_ExternSystemID);
            grdPrestation.DataMember          = "Table";

            grdPrestation.Columns["externprestationid"].Visible                  = false;
            grdPrestation.Columns["externprestation"].HeaderText                 = "PrestationID Externe";
            grdPrestation.Columns["externprestation"].Width                      = 130;
            grdPrestation.Columns["prestationid"].HeaderText                     = "PrestationID Messenger";
            grdPrestation.Columns["prestationid"].Width                          = 130;
            grdPrestation.Columns["prestationtitle"].HeaderText                  = "Titre Prestation";
            grdPrestation.Columns["prestationtitle"].Width                       = 130;
            grdPrestation.Columns["externprestationid"].ReadOnly                 = true;
            grdPrestation.Columns["prestationid"].ReadOnly                       = true;
            grdPrestation.Columns["prestationtitle"].ReadOnly                    = true;
            grdPrestation.Columns["externprestation"].DefaultCellStyle.BackColor = Color.LightGreen;

            m_FlagGrdPrestationLoaded = true;
        }

        private void grdProc_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                ExternProc externProc;
                int        newID;

                if (m_FlagGrdProcLoaded)
                {
                    externProc = new ExternProc();

                    if (grdProc[grdProc.Columns["externproctrans"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        MessageBox.Show("Le mapping ne peut pas être vide", "Team Editor");
                        LoadGridMappingProc();
                        return;
                    }

                    // check if the extern proc is already created
                    if (grdProc[grdProc.Columns["externprocid"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        externProc.ExternProcDesc  = grdProc[grdProc.Columns["externprocdesc"].Index, e.RowIndex].Value.ToString();
                        externProc.ExternProcTrans = grdProc[grdProc.Columns["externproctrans"].Index, e.RowIndex].Value.ToString();
                        externProc.ModelRef        = m_ModelRef;
                        externProc.SystemID        = m_ExternSystemID;
                        externProc.ProcStableID    = Convert.ToInt32(grdProc[grdProc.Columns["procstableid"].Index, e.RowIndex].Value);

                        newID = externProc.Add();

                        if (newID != -1)
                        {
                            m_FlagGrdProcLoaded = false;

                            grdProc[grdProc.Columns["externproctrans"].Index, e.RowIndex].Value = externProc.ExternProcTrans;
                            grdProc[grdProc.Columns["externprocdesc"].Index, e.RowIndex].Value  = externProc.ExternProcDesc;
                            grdProc[grdProc.Columns["externprocid"].Index, e.RowIndex].Value    = newID;

                            // update the deliverable grid
                            LoadGridMappingDeliv();

                            m_FlagGrdProcLoaded = true;
                        }
                    }
                    else
                    {
                        // update
                        externProc.Load(Convert.ToInt32(grdProc[grdProc.Columns["externprocid"].Index, e.RowIndex].Value));
                        externProc.ExternProcTrans = grdProc[grdProc.Columns["externproctrans"].Index, e.RowIndex].Value.ToString();
                        externProc.ExternProcDesc  = grdProc[grdProc.Columns["externprocdesc"].Index, e.RowIndex].Value.ToString();
                        externProc.Update();
                    }
                }
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cmdClose_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void grdDeliv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                ExternDeliv externDeliv;
                int newID;

                if (m_FlagGrdDelivLoaded)
                {
                    externDeliv = new ExternDeliv();

                    if (grdDeliv[grdDeliv.Columns["externdelivtrans"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        MessageBox.Show("Le mapping ne peut pas être vide", "Team Editor");
                        LoadGridMappingDeliv();
                        return;
                    }

                    // check if the extern deliv is already created
                    if (grdDeliv[grdDeliv.Columns["externdelivid"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        externDeliv.ExternDelivDesc  = grdDeliv[grdDeliv.Columns["externdelivdesc"].Index, e.RowIndex].Value.ToString();
                        externDeliv.ExternDelivTrans = grdDeliv[grdDeliv.Columns["externdelivtrans"].Index, e.RowIndex].Value.ToString();
                        externDeliv.DelivStableID    = Convert.ToInt32(grdDeliv[grdDeliv.Columns["delivstableid"].Index, e.RowIndex].Value);
                        externDeliv.ExernProcID      = Convert.ToInt32(grdDeliv[grdDeliv.Columns["externprocid"].Index, e.RowIndex].Value);

                        newID = externDeliv.Add();

                        if (newID != -1)
                        {
                            m_FlagGrdDelivLoaded = false;

                            grdDeliv[grdDeliv.Columns["externdelivtrans"].Index, e.RowIndex].Value = externDeliv.ExternDelivTrans;
                            grdDeliv[grdDeliv.Columns["externdelivdesc"].Index, e.RowIndex].Value  = externDeliv.ExternDelivDesc;
                            grdDeliv[grdDeliv.Columns["externdelivid"].Index, e.RowIndex].Value    = newID;
                            grdDeliv[grdDeliv.Columns["externprocid"].Index, e.RowIndex].Value     = externDeliv.ExernProcID;

                            // update the deliverable grid
                            LoadGridMappingDeliv();

                            m_FlagGrdDelivLoaded = true;
                        }
                    }
                    else
                    {
                        // update
                        externDeliv.Load(Convert.ToInt32(grdDeliv[grdDeliv.Columns["externdelivid"].Index, e.RowIndex].Value));
                        externDeliv.ExternDelivTrans = grdDeliv[grdDeliv.Columns["externdelivtrans"].Index, e.RowIndex].Value.ToString();
                        externDeliv.ExternDelivDesc  = grdDeliv[grdDeliv.Columns["externdelivdesc"].Index, e.RowIndex].Value.ToString();
                        externDeliv.Update();
                    }
                }
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void grdUser_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            ExternUser externUser;
            int        newID;

            if (m_FlagGrdUserLoaded)
            {
                externUser = new ExternUser();

                if (grdUser[grdUser.Columns["externuser"].Index, e.RowIndex].Value.ToString() == "")
                {
                    MessageBox.Show("Le mapping ne peut pas être vide", "Team Editor");
                    LoadGridMappingUser();
                    return;
                }

                // check if the externuser is already created
                if (grdUser[grdUser.Columns["externuserid"].Index, e.RowIndex].Value.ToString() == "")
                {
                    externUser.ExternUserValue = grdUser[grdUser.Columns["externuser"].Index, e.RowIndex].Value.ToString();
                    externUser.ExternSystemID  = m_ExternSystemID;
                    externUser.EmplID          = Convert.ToInt32(grdUser[grdUser.Columns["emplid"].Index, e.RowIndex].Value);

                    newID = externUser.Add();

                    if (newID != -1)
                    {
                        m_FlagGrdUserLoaded = false;

                        grdUser[grdUser.Columns["externuser"].Index, e.RowIndex].Value   = externUser.ExternUserValue;
                        grdUser[grdUser.Columns["externuserid"].Index, e.RowIndex].Value = newID;
                        grdUser[grdUser.Columns["emplid"].Index, e.RowIndex].Value       = externUser.EmplID;

                        // update the usererable grid
                        LoadGridMappingUser();

                        m_FlagGrdUserLoaded = true;
                    }
                }
                else
                {
                    // update
                    externUser.Load(Convert.ToInt32(grdUser[grdUser.Columns["externuserid"].Index, e.RowIndex].Value));
                    externUser.ExternUserValue = grdUser[grdUser.Columns["externuser"].Index, e.RowIndex].Value.ToString();
                    externUser.Update();
                }
            }
        }

        private void grdPrestation_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                ExternPrestation externPrestation;
                int              newID;

                if (m_FlagGrdPrestationLoaded)
                {
                    externPrestation = new ExternPrestation();

                    if (grdPrestation[grdPrestation.Columns["externprestation"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        MessageBox.Show("Le mapping ne peut pas être vide", "Team Editor");
                        LoadGridMappingPrestation();
                        return;
                    }

                    // check if the externprestation is already created
                    if (grdPrestation[grdPrestation.Columns["externprestationid"].Index, e.RowIndex].Value.ToString() == "")
                    {
                        externPrestation.ExternPrestationValue = grdPrestation[grdPrestation.Columns["externprestation"].Index, e.RowIndex].Value.ToString();
                        externPrestation.ExternSystemID        = m_ExternSystemID;
                        externPrestation.PrestationID          = Convert.ToInt32(grdPrestation[grdPrestation.Columns["prestationid"].Index, e.RowIndex].Value);

                        newID = externPrestation.Add();

                        if (newID != -1)
                        {
                            m_FlagGrdPrestationLoaded = false;

                            grdPrestation[grdPrestation.Columns["externprestation"].Index, e.RowIndex].Value   = externPrestation.ExternPrestationValue;
                            grdPrestation[grdPrestation.Columns["externprestationid"].Index, e.RowIndex].Value = newID;
                            grdPrestation[grdPrestation.Columns["prestationid"].Index, e.RowIndex].Value       = externPrestation.PrestationID;


                            // update the usererable grid
                            LoadGridMappingPrestation();

                            m_FlagGrdPrestationLoaded = true;
                        }
                    }
                    else
                    {
                        // update
                        externPrestation.Load(Convert.ToInt32(grdPrestation[grdPrestation.Columns["externprestationid"].Index, e.RowIndex].Value));
                        externPrestation.ExternPrestationValue = grdPrestation[grdPrestation.Columns["externprestation"].Index, e.RowIndex].Value.ToString();
                        externPrestation.Update();
                    }
                }
            }
            catch (Exception err)
            {
                MessageBox.Show("Message : " + err.Message + "- Source : " + err.Source);
            }
        }

        private void cboModel_SelectedValueChanged(object sender, EventArgs e)
        {}

        private void cboModel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboModel.SelectedIndex != -1)
                updateComboSelection();
        }
    }
}
