namespace TeamEditor
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMain));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.applicationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.quitterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.utilisateursToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.equipesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.critèresAIPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.critèresAILEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.systèmesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mappageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.indicateursToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.etatDuStockAnnuelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eQU3ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.applicationToolStripMenuItem,
            this.editionToolStripMenuItem,
            this.systèmesToolStripMenuItem,
            this.indicateursToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1158, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // applicationToolStripMenuItem
            // 
            this.applicationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.quitterToolStripMenuItem});
            this.applicationToolStripMenuItem.Name = "applicationToolStripMenuItem";
            this.applicationToolStripMenuItem.Size = new System.Drawing.Size(80, 20);
            this.applicationToolStripMenuItem.Text = "&Application";
            // 
            // quitterToolStripMenuItem
            // 
            this.quitterToolStripMenuItem.Name = "quitterToolStripMenuItem";
            this.quitterToolStripMenuItem.Size = new System.Drawing.Size(111, 22);
            this.quitterToolStripMenuItem.Text = "&Quitter";
            // 
            // editionToolStripMenuItem
            // 
            this.editionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.utilisateursToolStripMenuItem,
            this.equipesToolStripMenuItem,
            this.toolStripMenuItem1,
            this.critèresAIPToolStripMenuItem,
            this.critèresAILEToolStripMenuItem});
            this.editionToolStripMenuItem.Name = "editionToolStripMenuItem";
            this.editionToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.editionToolStripMenuItem.Text = "&Edition";
            // 
            // utilisateursToolStripMenuItem
            // 
            this.utilisateursToolStripMenuItem.Name = "utilisateursToolStripMenuItem";
            this.utilisateursToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.utilisateursToolStripMenuItem.Text = "&Utilisateurs...";
            this.utilisateursToolStripMenuItem.Click += new System.EventHandler(this.utilisateursToolStripMenuItem_Click);
            // 
            // equipesToolStripMenuItem
            // 
            this.equipesToolStripMenuItem.Name = "equipesToolStripMenuItem";
            this.equipesToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.equipesToolStripMenuItem.Text = "&Equipes...";
            this.equipesToolStripMenuItem.Click += new System.EventHandler(this.equipesToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(138, 6);
            // 
            // critèresAIPToolStripMenuItem
            // 
            this.critèresAIPToolStripMenuItem.Name = "critèresAIPToolStripMenuItem";
            this.critèresAIPToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.critèresAIPToolStripMenuItem.Text = "Critères AI&P";
            // 
            // critèresAILEToolStripMenuItem
            // 
            this.critèresAILEToolStripMenuItem.Name = "critèresAILEToolStripMenuItem";
            this.critèresAILEToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.critèresAILEToolStripMenuItem.Text = "Critères AI&LE";
            // 
            // systèmesToolStripMenuItem
            // 
            this.systèmesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mappageToolStripMenuItem});
            this.systèmesToolStripMenuItem.Name = "systèmesToolStripMenuItem";
            this.systèmesToolStripMenuItem.Size = new System.Drawing.Size(68, 20);
            this.systèmesToolStripMenuItem.Text = "&Systèmes";
            // 
            // mappageToolStripMenuItem
            // 
            this.mappageToolStripMenuItem.Name = "mappageToolStripMenuItem";
            this.mappageToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.mappageToolStripMenuItem.Text = "&Mappage...";
            this.mappageToolStripMenuItem.Click += new System.EventHandler(this.mappageToolStripMenuItem_Click);
            // 
            // indicateursToolStripMenuItem
            // 
            this.indicateursToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.etatDuStockAnnuelToolStripMenuItem,
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem,
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem,
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem,
            this.eQU3ToolStripMenuItem,
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem});
            this.indicateursToolStripMenuItem.Name = "indicateursToolStripMenuItem";
            this.indicateursToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this.indicateursToolStripMenuItem.Text = "&Indicateurs";
            // 
            // etatDuStockAnnuelToolStripMenuItem
            // 
            this.etatDuStockAnnuelToolStripMenuItem.Name = "etatDuStockAnnuelToolStripMenuItem";
            this.etatDuStockAnnuelToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.etatDuStockAnnuelToolStripMenuItem.Text = "PRO1 - &Etat du stock annuel  des traitements à réaliser par processus";
            this.etatDuStockAnnuelToolStripMenuItem.Click += new System.EventHandler(this.etatDuStockAnnuelToolStripMenuItem_Click);
            // 
            // nombreDeCasTraitésParProcessuprestationToolStripMenuItem
            // 
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem.Name = "nombreDeCasTraitésParProcessuprestationToolStripMenuItem";
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem.Text = "PRO2 - Livraisons du Processus";
            this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem.Click += new System.EventHandler(this.nombreDeCasTraitésParProcessuprestationToolStripMenuItem_Click);
            // 
            // nombreDeCasTraitésParProcédureéquipeToolStripMenuItem
            // 
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem.Name = "nombreDeCasTraitésParProcédureéquipeToolStripMenuItem";
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem.Text = "EQU2 - Cas traités par la procédure";
            this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem.Click += new System.EventHandler(this.nombreDeCasTraitésParProcédureéquipeToolStripMenuItem_Click);
            // 
            // chargecoûtDuTravailProduitParÉquipeToolStripMenuItem
            // 
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem.Name = "chargecoûtDuTravailProduitParÉquipeToolStripMenuItem";
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem.Text = "EQU3- Charge de travail produite par l\'équipe";
            this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem.Click += new System.EventHandler(this.chargecoûtDuTravailProduitParÉquipeToolStripMenuItem_Click);
            // 
            // eQU3ToolStripMenuItem
            // 
            this.eQU3ToolStripMenuItem.Name = "eQU3ToolStripMenuItem";
            this.eQU3ToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.eQU3ToolStripMenuItem.Text = "PRE1 - Livraisons, par produit, du processus";
            this.eQU3ToolStripMenuItem.Click += new System.EventHandler(this.eQU3ToolStripMenuItem_Click);
            // 
            // eFF2ProductivitéDeLéquipeToolStripMenuItem
            // 
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem.Name = "eFF2ProductivitéDeLéquipeToolStripMenuItem";
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem.Size = new System.Drawing.Size(432, 22);
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem.Text = "EFF2 - Productivité de l\'équipe";
            this.eFF2ProductivitéDeLéquipeToolStripMenuItem.Click += new System.EventHandler(this.eFF2ProductivitéDeLéquipeToolStripMenuItem_Click);
            // 
            // FrmMain
            // 
            this.ClientSize = new System.Drawing.Size(1158, 681);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FrmMain";
            this.Text = "Team Editor";
            this.Activated += new System.EventHandler(this.FrmMain_Activated);
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem editionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem utilisateursToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem applicationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitterToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem critèresAIPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem critèresAILEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem equipesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem systèmesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mappageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem indicateursToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem etatDuStockAnnuelToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nombreDeCasTraitésParProcédureéquipeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nombreDeCasTraitésParProcessuprestationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chargecoûtDuTravailProduitParÉquipeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eQU3ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eFF2ProductivitéDeLéquipeToolStripMenuItem;
    }
}