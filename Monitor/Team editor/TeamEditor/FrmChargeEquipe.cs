using System;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmChargeEquipe : Form
    {
        private Indicator m_Indic;
        private int       m_ModelID;
        private int       m_Year;
        private int       m_WkgID;

        public FrmChargeEquipe()
        {
            InitializeComponent();

            m_Indic = new Indicator();
        }

        private void FrmChargeEquipe_Load(object sender, EventArgs e)
        {
            PModel pModel = new PModel();

            // load model ref combo
            cboModel.DisplayMember = "model";
            cboModel.ValueMember   = "modelid";
            cboModel.DataSource    = pModel.getListForComboBox().Tables[0];

            // load year combo
            loadComboYear();

            // update after the combo selection
            updateComboSelection();

            // load ComboTeam
            LoadComboTeam();
        }

        private void LoadComboTeam()
        {
            Pworkgroup pTeam = new Pworkgroup() ;

            cboTeam.DisplayMember = "wkgname";
            cboTeam.ValueMember   = "wkgid";
            cboTeam.DataSource    = pTeam.GetListByType((int)Pworkgroup.IEType.IE_T_Team).Tables[0];
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
            m_Year    = Convert.ToInt32(cboAnnee.SelectedItem);
            m_WkgID   = Convert.ToInt32(cboTeam.SelectedValue);
            m_ModelID = Convert.ToInt32(cboModel.SelectedValue);

            grdPreview.DataSource = m_Indic.QueryIndicatorChargeTeam(m_WkgID, m_Year, m_ModelID);
            grdPreview.DataMember = "Table";

            // fill label table
            Indicator indic = new Indicator();
            indic.AddLabel(m_Year, cboTeam.Text);

            MessageBox.Show("Génération de l'indicateur \"" + this.Text + "\" terminée");
        }
    }
}
