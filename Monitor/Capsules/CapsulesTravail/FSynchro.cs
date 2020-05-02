using System;
using System.Windows.Forms;
using System.IO;
using CapsulesTravailDLL;

namespace CapsulesTravail
{
    /// <summary>
    /// Summary description for FSynchro
    /// </summary>
    public class FSynchro : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btOk;
        private System.Windows.Forms.Button btCancel;
        private System.Windows.Forms.TextBox tbServer;
        private CapsulesXML _cxml;
        private int _indexToSynchronize;
        private System.Windows.Forms.CheckBox cbDeleteAfter;

        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.Container components = null;

        /// <summary>
        /// </summary>
        /// <param name="cxml"></param>
        /// <param name="indexToSynchronize">index of the file in the array. If -1, synchronize all capsules</param>
        public FSynchro(CapsulesXML cxml, int indexToSynchronize)
        {
            // required for Windows Form Designer support
            InitializeComponent();

            _cxml               = cxml;
            _indexToSynchronize = indexToSynchronize;
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
                if(components != null)
                    components.Dispose();

            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FSynchro));
            this.btOk = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.tbServer = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbDeleteAfter = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // btOk
            // 
            this.btOk.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btOk.Location = new System.Drawing.Point(512, 48);
            this.btOk.Name = "btOk";
            this.btOk.Size = new System.Drawing.Size(144, 24);
            this.btOk.TabIndex = 0;
            this.btOk.Text = "Synchroniser";
            this.btOk.Click += new System.EventHandler(this.btOk_Click);
            // 
            // btCancel
            // 
            this.btCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btCancel.Location = new System.Drawing.Point(344, 48);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(144, 24);
            this.btCancel.TabIndex = 1;
            this.btCancel.Text = "Annuler";
            this.btCancel.Click += new System.EventHandler(this.btCancel_Click);
            // 
            // tbServer
            // 
            this.tbServer.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbServer.Location = new System.Drawing.Point(104, 8);
            this.tbServer.Name = "tbServer";
            this.tbServer.Size = new System.Drawing.Size(552, 26);
            this.tbServer.TabIndex = 2;
            this.tbServer.Text = "http://wrkmora04:8080/soap/servlet/rpcrouter";
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(8, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 23);
            this.label1.TabIndex = 3;
            this.label1.Text = "Serveur :";
            // 
            // cbDeleteAfter
            // 
            this.cbDeleteAfter.Checked = true;
            this.cbDeleteAfter.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbDeleteAfter.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbDeleteAfter.Location = new System.Drawing.Point(16, 48);
            this.cbDeleteAfter.Name = "cbDeleteAfter";
            this.cbDeleteAfter.Size = new System.Drawing.Size(328, 24);
            this.cbDeleteAfter.TabIndex = 4;
            this.cbDeleteAfter.Text = "Effacer capsule(s) après synchronisation";
            // 
            // FSynchro
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(664, 77);
            this.Controls.Add(this.cbDeleteAfter);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbServer);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOk);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FSynchro";
            this.Text = "Synchronisation";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private void btOk_Click(object sender, System.EventArgs e)
        {
            String path;
            int    nbrOfFiles;
            bool   isOk;
            long   ret;
            String err = "";
            int[]  capsulesToDelete;
            int    nbreToDelete;
            int    currentIndex;

            try
            {
                // synchronize 1 capsule or all?
                if (_indexToSynchronize == -1)
                    nbrOfFiles = _cxml.getNbrOfFiles();
                else
                    nbrOfFiles = 1;

                //to store the index of the capsules to delete
                capsulesToDelete = new int[nbrOfFiles];
                nbreToDelete     = 0;

                capsulesSOAP _proxy = new capsulesSOAP(tbServer.Text);
                isOk                = true;

                // go through all files
                for(int i = 0; i < nbrOfFiles; ++i)
                {
                    if (_indexToSynchronize == -1)
                        currentIndex = i;
                    else
                        currentIndex = _indexToSynchronize;

                    path = _cxml.getPathOfFileAtIndex(currentIndex);

                    // load the content of the file
                    StreamReader sr      = new StreamReader(path);
                    String       content = sr.ReadToEnd();

                    // synchronize the current capsule
                    ret = _proxy.processCapsule(content);

                    if (ret != 0)
                    {
                        isOk = false;

                        switch(ret)
                        {
                            case 1:
                                err += "\nCapsule \"" + _cxml.getCaseName() + "\" est passée de date.";
                                break;

                            default:
                                err += "\nCapsule \"" + _cxml.getCaseName() + "\" : erreur inconnue.";
                                break;
                        }
                    }
                    else
                    {
                        // the capsule has been synchronised correctly. Mark it to be deleted
                        // don't delete know, otherwise the index of the array inside _cxml would be wrong
                        capsulesToDelete[nbreToDelete++] = currentIndex;
                    }
                }

                //if required, delete the capsules which have been correctly synchronized
                if (cbDeleteAfter.Enabled == true)
                {
                    for (int i = nbreToDelete; i > 0; ++i)
                        _cxml.deleteCapsuleAtIndex(capsulesToDelete[i - 1]) ;
                }
                else
                    // otherwise, mark the capsule as synchronised
                    for (int i = nbreToDelete; i > 0; ++i)
                    {
                        // load the file
                        _cxml.loadFileIntoList(_cxml.getPathOfFileAtIndex(capsulesToDelete[i-1]));

                        // set the flag
                        _cxml.setHasBeenSynchronised(true);

                        // save back the file
                        _cxml.SaveAsXML();
                    }

                if (isOk)
                    MessageBox.Show("La synchronisation s'est bien déroulée.");
                else
                    MessageBox.Show("Une erreur est survenue lors de la synchronisation : " + err);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Erreur : " + ex.Message);
            }

            Close();
        }

        private void btCancel_Click(object sender, System.EventArgs e)
        {
            Close();
        }
    }
}
