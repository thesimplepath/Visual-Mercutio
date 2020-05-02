using System;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmIndicCasProcEquipe : Form
    {
        private Indicator m_Indic;
        private int       m_ModelID;
        private int       m_Year;
        private int       m_ProcID;

        public FrmIndicCasProcEquipe()
        {
            InitializeComponent();

            m_Indic = new Indicator();
        }

        private void FrmIndicCasProcEquipe_Load(object sender, EventArgs e)
        {
            PModel pModel = new PModel();

            // load model ref combo
            cboModel.DisplayMember = "model";
            cboModel.ValueMember   = "modelid";
            cboModel.DataSource    = pModel.getListForComboBox().Tables[0];

            // load year combo
            loadComboYear();

            //update after the combo selection
            updateComboSelection();

            // load ComboDeliv
            LoadComboProc();
        }

        private void LoadComboProc()
        {
            cboProc.DisplayMember = "procname";
            cboProc.ValueMember   = "procid";
            cboProc.DataSource    = m_Indic.GetProcList(m_ModelID).Tables[0];
        }

        private void updateComboSelection()
        {
            m_ModelID = Convert.ToInt32(cboModel.SelectedValue);
        }

        private void loadComboYear()
        {
            for (int i = 1990; i <= DateTime.Now.Year; ++i)
                cboAnnee.Items.Add(Convert.ToString(i));

            cboAnnee.SelectedIndex = cboAnnee.Items.Count - 1;
        }

        private void cmdQuery_Click(object sender, EventArgs e)
        {
            m_Year   = Convert.ToInt32(cboAnnee.SelectedItem);
            m_ProcID = Convert.ToInt32(cboProc.SelectedValue) ;

            grdPreview.DataSource = m_Indic.QueryIndicatorCasProcTeam(m_ProcID, m_Year);
            grdPreview.DataMember = "Table";

            // fill label table
            Indicator indic = new Indicator();
            indic.AddLabel(m_Year, cboProc.Text);

            MessageBox.Show("Génération de l'indicateur \"" + this.Text + "\" terminée");
        }

        private void cboModel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboModel.SelectedIndex != -1)
            {
                updateComboSelection();
                LoadComboProc();
            }
        }
    }
}
