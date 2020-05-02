using System;
using System.Windows.Forms;

namespace TeamEditor
{
    public partial class FrmMain : Form
    {
        public FrmMain()
        {
            InitializeComponent();
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            FrmChooseAlias form = new FrmChooseAlias();

            if (form.ShowDialog() != DialogResult.OK)
                this.Dispose();
        }

        private void utilisateursToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmUser();
            form.MdiParent = this;
            form.Show();
        }

        private void equipesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form frmTeam      = new FrmTeam();
            frmTeam.MdiParent = this;
            frmTeam.Show();
        }

        private void mappageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmMapping();
            form.MdiParent = this;
            form.Show();
        }

        private void etatDuStockAnnuelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmIndicStock();
            form.Text      = "PRO1 - Etat du stock annuel  des traitements à réaliser par processus";
            form.MdiParent = this;
            form.Show();
        }

        private void nombreDeCasTraitésParProcédureéquipeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmIndicCasProcEquipe();
            form.Text      = "EQU2 - Cas traités par la procédure";
            form.MdiParent = this;
            form.Show();
        }

        private void nombreDeCasTraitésParProcessuprestationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmIndicNbrCasTraite();
            form.Text      = "PRO2 - Livraisons du Processus";
            form.MdiParent = this;
            form.Show();
        }

        private void chargecoûtDuTravailProduitParÉquipeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmChargeEquipe();
            form.Text      = "EQU3- Charge de travail produite par l'équipe";
            form.MdiParent = this;
            form.Show();
        }

        private void eQU3ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmIndicNbrCasTraite();
            form.Text      = "PRE1 - Livraisons, par produit, du processus";
            form.MdiParent = this;
            form.Show();
        }

        private void eFF2ProductivitéDeLéquipeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form form      = new FrmIndicProducTeam();
            form.Text      = "EFF2 - Productivité de l'équipe";
            form.MdiParent = this;
            form.Show();
        }

        private void FrmMain_Activated(object sender, EventArgs e)
        {}
    }
}
