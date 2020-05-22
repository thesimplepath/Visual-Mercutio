/********************************************************************************************************
 *                                               Classe Culture                                         *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 24 mars 2007                                                                           *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Note complémentaire : Le code permettant la mise à jour des fenêtre de l'application, exécuté lors   *
 * de l'appel à la fonction OnChangeLaguage, est une personnalisation d'un code publié sur le site      *
 * http://www.codeproject.com. L'auteur de ce code est Julijan Sribar.                                  *
 ********************************************************************************************************
 * Cette classe permet de gérer et d'obtenir les chaînes de caractères en fonction de la langue et de   *
 * la culture souhaitée.                                                                                *
 ********************************************************************************************************/

using System;
using System.Windows.Forms;
using System.Collections;
using System.Threading;
using System.Globalization;
using System.Resources;
using System.Diagnostics;
using System.Reflection;
using System.Drawing;

namespace ReportsTool.Culture
{
    public class Culture
    {
        #region Définition du Singleton de la classe

        /// <summary>
        /// La seule et unique instance de la classe Culture.
        /// </summary>
        protected static readonly Culture p_Instance = new Culture();

        #endregion

        #region Constructeur(s) / Destructeur

        /// <summary>
        /// Le constructeur est privé, ce qui interdit la construction d'une autre instance pour cette classe.
        /// </summary>
        private Culture()
        {
        }

        #endregion

        #region Propriétés de la classe

        /// <summary>
        /// Retourne un pointeur sur l'instance unique de la classe.
        /// </summary>
        public static Culture Instance
        {
            get
            {
                return p_Instance;
            }
        }

        #endregion

        #region Fonctions publiques

        /// <summary>
        /// Cette fonction permet de sélectionner le language de l'application.
        /// </summary>
        /// <param name="LanguageName">Le nom de la culture désirée.</param>
        public void ChangeLanguage(string LanguageName)
        {
            try
            {
                System.Threading.Thread.CurrentThread.CurrentCulture =
                    new System.Globalization.CultureInfo(LanguageName);
                System.Threading.Thread.CurrentThread.CurrentUICulture =
                    new System.Globalization.CultureInfo(LanguageName);
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class Culture -> Function ChangeLanguage failed. Cause : " + ex.Message);
                MessageBox.Show(ex.Message,
                                "Culture",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction permet d'appliquer les modifications aux divers objets lors d'un changement de language.
        /// </summary>
        /// <param name="MainForm">Le pointeur sur le formulaire principal de l'application.</param>
        public void OnChangeLanguage(Form MainForm)
        {
            ChangeFormLanguage(MainForm);

            foreach (Form p_childForm in MainForm.MdiChildren)
            {
                ChangeFormLanguage(p_childForm);
            }
        }

        /// <summary>
        /// Cette fonction retourne une chaîne de caractères dépendante du language choisi.
        /// </summary>
        /// <param name="ResourceName">Le nom de la ressource contenant la chaîne de caractères.</param>
        /// <returns></returns>
        public string GetStr(string ResourceName)
        {
            try
            {
                System.Reflection.Assembly myResources;

                myResources = System.Reflection.Assembly.Load("ReportsToolCulture");
                ResourceManager myManager = new ResourceManager("ReportsToolCulture.MainFrame", myResources);
                CultureInfo myCultureInfo = Thread.CurrentThread.CurrentCulture;

                return myManager.GetString(ResourceName, myCultureInfo);
            }
            catch (Exception ex)
            {
                Trace.WriteLine(string.Format("Class Culture -> Function GetStr failed. Cause : ", ResourceName) + ex.Message);
                MessageBox.Show(ex.Message,
                                "Culture",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);

                return "";
            }
        }

        #endregion

        #region Fonctions privées

        #region Fonction principale d'appel

        /// <summary>
        /// Cette fonction permet d'appliquer un changement de language à un formulaire précis.
        /// </summary>
        /// <param name="p_Form">Le pointeur sur le formulaire.</param>
        private void ChangeFormLanguage(Form p_Form)
        {
            p_Form.SuspendLayout();

            Cursor.Current = Cursors.WaitCursor;

            ResourceManager p_Resources = new ResourceManager(p_Form.GetType());

            p_Form.Text = (string)(GetSafeValue(p_Resources, "$this.Text", p_Form.Text));
            ReloadControlCommonProperties(p_Form, p_Resources);
            ToolTip toolTip = GetToolTip(p_Form);

            RecurControls(p_Form, p_Resources, toolTip);

            RecurNonControls(p_Form, p_Resources);

            p_Form.ResumeLayout();
        }

        #endregion

        #region Fonctions de récupération de ressources

        /// <summary>
        /// Cette fonction permet de récupérer les ressources d'un contrôle.
        /// </summary>
        /// <param name="p_Parent">Le pointeur vers le contrôle parent.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        /// <param name="p_ToolTip">Le pointeur vers l'info-bulle du contrôle.</param>
        private void RecurControls(Control p_Parent, ResourceManager p_Resources, ToolTip p_ToolTip)
        {
            foreach (Control p_Control in p_Parent.Controls)
            {
                p_Control.SuspendLayout();

                ReloadControlCommonProperties(p_Control, p_Resources);
                ReloadControlSpecificProperties(p_Control, p_Resources);

                if (p_ToolTip != null)
                {
                    p_ToolTip.SetToolTip(p_Control,
                                         (string)GetSafeValue(p_Resources,
                                                              p_Control.Name + ".ToolTip",
                                                              p_Control.Text));
                }

                if (p_Control is UserControl)
                {
                    RecurUserControl((UserControl)p_Control);
                }
                else
                {
                    ReloadTextForSelectedControls(p_Control, p_Resources);
                    ReloadListItems(p_Control, p_Resources);

                    if (p_Control is TreeView)
                    {
                        ReloadTreeViewNodes((TreeView)p_Control, p_Resources);
                    }

                    if (p_Control.Controls.Count > 0)
                    {
                        RecurControls(p_Control, p_Resources, p_ToolTip);
                    }
                }

                p_Control.ResumeLayout();
            }
        }

        /// <summary>
        /// Cette fonction permet de récupérer les ressources d'un contrôle utilisateur.
        /// </summary>
        /// <param name="p_UserControl">Le pointeur vers le contrôle utilisateur.</param>
        private void RecurUserControl(UserControl p_UserControl)
        {
            ResourceManager p_Resources = new ResourceManager(p_UserControl.GetType());

            ToolTip p_ToolTip = GetToolTip(p_UserControl);

            RecurControls(p_UserControl, p_Resources, p_ToolTip);
            RecurNonControls(p_UserControl, p_Resources);
        }

        /// <summary>
        /// Cette fonction permet de récupérer les objets qui ne sont pas des contrôles.
        /// </summary>
        /// <param name="p_ContainerControl">Le pointeur vers le conteneur d'objets du contrôle.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void RecurNonControls(ContainerControl p_ContainerControl, ResourceManager p_Resources)
        {
            FieldInfo[] p_FieldInfo = p_ContainerControl.GetType().GetFields(BindingFlags.NonPublic    |
                                                                             BindingFlags.Instance     |
                                                                             BindingFlags.Public);

            for (int i = 0; i < p_FieldInfo.Length; i++)
            {
                object p_Object     = p_FieldInfo[i].GetValue(p_ContainerControl);
                string s_FieldName  = p_FieldInfo[i].Name;

                if (p_Object is MenuItem)
                {
                    MenuItem p_MenuItem = (MenuItem)p_Object;

                    p_MenuItem.Enabled      = (bool)(GetSafeValue(p_Resources, s_FieldName + ".Enabled", p_MenuItem.Enabled));
                    p_MenuItem.Shortcut     = (Shortcut)(GetSafeValue(p_Resources, s_FieldName + ".Shortcut", p_MenuItem.Shortcut));
                    p_MenuItem.ShowShortcut = (bool)(GetSafeValue(p_Resources, s_FieldName + ".ShowShortcut", p_MenuItem.ShowShortcut));
                    p_MenuItem.Text         = (string)GetSafeValue(p_Resources, s_FieldName + ".Text", p_MenuItem.Text);
                    p_MenuItem.Visible      = (bool)(GetSafeValue(p_Resources, s_FieldName + ".Visible", p_MenuItem.Visible));
                }

                if (p_Object is ToolStripMenuItem)
                {
                    ToolStripMenuItem p_ToolStripMenuItem = (ToolStripMenuItem)p_Object;

                    p_ToolStripMenuItem.Enabled             = (bool)(GetSafeValue(p_Resources, s_FieldName + ".Enabled", p_ToolStripMenuItem.Enabled));
                    p_ToolStripMenuItem.ShortcutKeys        = (Keys)(GetSafeValue(p_Resources, s_FieldName + ".ShortcutKeys", p_ToolStripMenuItem.ShortcutKeys));
                    p_ToolStripMenuItem.ShowShortcutKeys    = (bool)(GetSafeValue(p_Resources, s_FieldName + ".ShowShortcutKeys", p_ToolStripMenuItem.ShowShortcutKeys));
                    p_ToolStripMenuItem.Text                = (string)GetSafeValue(p_Resources, s_FieldName + ".Text", p_ToolStripMenuItem.Text);
                    p_ToolStripMenuItem.BackgroundImage     = (Image)(GetSafeValue(p_Resources, s_FieldName + ".BackgroundImage", p_ToolStripMenuItem.BackgroundImage));
                    p_ToolStripMenuItem.Image               = (Image)(GetSafeValue(p_Resources, s_FieldName + ".Image", p_ToolStripMenuItem.Image));
                }

                if (p_Object is StatusBarPanel)
                {
                    StatusBarPanel p_Panel = (StatusBarPanel)p_Object;

                    p_Panel.Alignment   = (HorizontalAlignment)(GetSafeValue(p_Resources, s_FieldName + ".Alignment", p_Panel.Alignment));
                    p_Panel.Icon        = (Icon)(GetSafeValue(p_Resources, s_FieldName + ".Icon", p_Panel.Icon));
                    p_Panel.MinWidth    = (int)(GetSafeValue(p_Resources, s_FieldName + ".MinWidth", p_Panel.MinWidth));
                    p_Panel.Text        = (string)(GetSafeValue(p_Resources, s_FieldName + ".Text", p_Panel.Text));
                    p_Panel.ToolTipText = (string)(GetSafeValue(p_Resources, s_FieldName + ".ToolTipText", p_Panel.ToolTipText));
                    p_Panel.Width       = (int)(GetSafeValue(p_Resources, s_FieldName + ".Width", p_Panel.Width));
                }

                if (p_Object is ColumnHeader)
                {
                    ColumnHeader p_Header = (ColumnHeader)p_Object;

                    p_Header.Text       = (string)(GetSafeValue(p_Resources, s_FieldName + ".Text", p_Header.Text));
                    p_Header.TextAlign  = (HorizontalAlignment)(GetSafeValue(p_Resources, s_FieldName + ".TextAlign", p_Header.TextAlign));
                    p_Header.Width      = (int)(GetSafeValue(p_Resources, s_FieldName + ".Width", p_Header.Width));
                }

                if (p_Object is ToolBarButton)
                {
                    ToolBarButton p_Button = (ToolBarButton)p_Object;

                    p_Button.Enabled        = (bool)(GetSafeValue(p_Resources, s_FieldName + ".Enabled", p_Button.Enabled));
                    p_Button.ImageIndex     = (int)(GetSafeValue(p_Resources, s_FieldName + ".ImageIndex", p_Button.ImageIndex));
                    p_Button.Text           = (string)(GetSafeValue(p_Resources, s_FieldName + ".Text", p_Button.Text));
                    p_Button.ToolTipText    = (string)(GetSafeValue(p_Resources, s_FieldName + ".ToolTipText", p_Button.ToolTipText));
                    p_Button.Visible        = (bool)(GetSafeValue(p_Resources, s_FieldName + ".Visible", p_Button.Visible));
                }
            }
        }

        #endregion

        #region Fonctions de rechargement des ressources

        /// <summary>
        /// Cette fonction permet de restaurer les propriétés communes d'un contrôle dans un nouveau language.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadControlCommonProperties(Control p_Control, ResourceManager p_Resources)
        {
            SetProperty(p_Control, "AccessibleDescription", p_Resources);
            SetProperty(p_Control, "AccessibleName", p_Resources);
            SetProperty(p_Control, "BackgroundImage", p_Resources);
            SetProperty(p_Control, "Font", p_Resources);
            SetProperty(p_Control, "ImeMode", p_Resources);
            SetProperty(p_Control, "RightToLeft", p_Resources);
            SetProperty(p_Control, "Size", p_Resources);

            if (!(p_Control is Form))
            {
                SetProperty(p_Control, "Anchor", p_Resources);
                SetProperty(p_Control, "Dock", p_Resources);
                SetProperty(p_Control, "Enabled", p_Resources);
                SetProperty(p_Control, "Location", p_Resources);
                SetProperty(p_Control, "TabIndex", p_Resources);
                SetProperty(p_Control, "Visible", p_Resources);
            }

            if (p_Control is ScrollableControl)
            {
                ReloadScrollableControlProperties((ScrollableControl)p_Control, p_Resources);

                if (p_Control is Form)
                {
                    ReloadFormProperties((Form)p_Control, p_Resources);
                }
            }
        }

        /// <summary>
        /// Cette fonction permet de restaurer les propriétés spécifiques à un contrôle dans un nouveau language.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        protected virtual void ReloadControlSpecificProperties(Control p_Control, ResourceManager p_Resources)
        {
            SetProperty(p_Control, "ImageIndex", p_Resources);
            SetProperty(p_Control, "ToolTipText", p_Resources);
            SetProperty(p_Control, "IntegralHeight", p_Resources);
            SetProperty(p_Control, "ItemHeight", p_Resources);
            SetProperty(p_Control, "MaxDropDownItems", p_Resources);
            SetProperty(p_Control, "MaxLength", p_Resources);
            SetProperty(p_Control, "Appearance", p_Resources);
            SetProperty(p_Control, "CheckAlign", p_Resources);
            SetProperty(p_Control, "FlatStyle", p_Resources);
            SetProperty(p_Control, "ImageAlign", p_Resources);
            SetProperty(p_Control, "Indent", p_Resources);
            SetProperty(p_Control, "Multiline", p_Resources);
            SetProperty(p_Control, "BulletIndent", p_Resources);
            SetProperty(p_Control, "RightMargin", p_Resources);
            SetProperty(p_Control, "ScrollBars", p_Resources);
            SetProperty(p_Control, "WordWrap", p_Resources);
            SetProperty(p_Control, "ZoomFactor", p_Resources);
            SetProperty(p_Control, "ButtonSize", p_Resources);
            SetProperty(p_Control, "DropDownArrows", p_Resources);
            SetProperty(p_Control, "ShowToolTips", p_Resources);
            SetProperty(p_Control, "Wrappable", p_Resources);
            SetProperty(p_Control, "AutoSize", p_Resources);
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour un contrôle déroulable.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadScrollableControlProperties(ScrollableControl p_Control, ResourceManager p_Resources)
        {
            SetProperty(p_Control, "AutoScroll", p_Resources);
            SetProperty(p_Control, "AutoScrollMargin", p_Resources);
            SetProperty(p_Control, "AutoScrollMinSize", p_Resources);
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour les contrôles sélectionnés.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadTextForSelectedControls(Control p_Control, ResourceManager p_Resources)
        {
            if (p_Control is AxHost ||
                p_Control is ButtonBase ||
                p_Control is GroupBox ||
                p_Control is Label ||
                p_Control is ScrollableControl ||
                p_Control is StatusBar ||
                p_Control is TabControl ||
                p_Control is ToolBar)
            {
                p_Control.Text = (string)GetSafeValue(p_Resources, p_Control.Name + ".Text", p_Control.Text);
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour une liste.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadListItems(Control p_Control, ResourceManager p_Resources)
        {
            if (p_Control is ComboBox)
            {
                ReloadComboBoxItems((ComboBox)p_Control, p_Resources);
            }
            else if (p_Control is ListBox)
            {
                ReloadListBoxItems((ListBox)p_Control, p_Resources);
            }
            else if (p_Control is DomainUpDown)
            {
                ReloadUpDownItems((DomainUpDown)p_Control, p_Resources);
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour une boîte combinée.
        /// </summary>
        /// <param name="p_ComboBox">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadComboBoxItems(ComboBox p_ComboBox, ResourceManager p_Resources)
        {
            if (p_ComboBox.Items.Count > 0)
            {
                int i_SelectedIndex = p_ComboBox.SelectedIndex;

                ReloadItems(p_ComboBox.Name, p_ComboBox.Items, p_ComboBox.Items.Count, p_Resources);

                if (!p_ComboBox.Sorted)
                {
                    p_ComboBox.SelectedIndex = i_SelectedIndex;
                }
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour une liste déroulante.
        /// </summary>
        /// <param name="p_ListBox">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadListBoxItems(ListBox p_ListBox, ResourceManager p_Resources)
        {
            if (p_ListBox.Items.Count > 0)
            {
                int[] i_SelectedItems = new int[p_ListBox.SelectedIndices.Count];

                p_ListBox.SelectedIndices.CopyTo(i_SelectedItems, 0);
                ReloadItems(p_ListBox.Name, p_ListBox.Items, p_ListBox.Items.Count, p_Resources);

                if (!p_ListBox.Sorted)
                {
                    for (int i = 0; i < i_SelectedItems.Length; i++)
                    {
                        p_ListBox.SetSelected(i_SelectedItems[i], true);
                    }
                }
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour une liste haut/bas.
        /// </summary>
        /// <param name="p_DomainUpDown">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadUpDownItems(DomainUpDown p_DomainUpDown, ResourceManager p_Resources)
        {
            if (p_DomainUpDown.Items.Count > 0)
            {
                int i_SelectedIndex = p_DomainUpDown.SelectedIndex;

                ReloadItems(p_DomainUpDown.Name, p_DomainUpDown.Items, p_DomainUpDown.Items.Count, p_Resources);

                if (!p_DomainUpDown.Sorted)
                {
                    p_DomainUpDown.SelectedIndex = i_SelectedIndex;
                }
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour un arbre de données.
        /// </summary>
        /// <param name="p_TreeView">Le pointeur vers le contrôle concerné.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadTreeViewNodes(TreeView p_TreeView, ResourceManager p_Resources)
        {
            if (p_TreeView.Nodes.Count > 0)
            {
                string s_ResourceName = p_TreeView.Name + ".Nodes";

                TreeNode[] newNodes = new TreeNode[p_TreeView.Nodes.Count];
                newNodes[0] = (TreeNode)p_Resources.GetObject(s_ResourceName,
                                                              Thread.CurrentThread.CurrentUICulture);

                // VS2002 generates node resource names with additional ".Nodes" string
                if (newNodes[0] == null)
                {
                    s_ResourceName += ".Nodes";
                    newNodes[0] = (TreeNode)p_Resources.GetObject(s_ResourceName,
                                                                  Thread.CurrentThread.CurrentUICulture);
                }

                Debug.Assert(newNodes[0] != null);

                for (int i = 1; i < p_TreeView.Nodes.Count; i++)
                {
                    newNodes[i] = (TreeNode)p_Resources.GetObject(s_ResourceName + i.ToString(),
                                                                  Thread.CurrentThread.CurrentUICulture);
                }

                p_TreeView.Nodes.Clear();
                p_TreeView.Nodes.AddRange(newNodes);
            }
        }

        /// <summary>
        /// Cette fonction permet de recharger les ressources pour une liste d'objets.
        /// </summary>
        /// <param name="ControlName">Le nom du contrôle</param>
        /// <param name="p_List">Le pointeur vers la liste d'objets.</param>
        /// <param name="ItemsNumber">Le nombre d'objets contenus dans la liste.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadItems(string ControlName, IList p_List, int ItemsNumber, ResourceManager p_Resources)
        {
            string s_ResourceName   = ControlName + ".Items";
            object p_Object         = p_Resources.GetString(s_ResourceName,
                                                            Thread.CurrentThread.CurrentUICulture);

            // VS2002 generates item resource name with additional ".Items" string
            if (p_Object == null)
            {
                s_ResourceName += ".Items";
                p_Object = p_Resources.GetString(s_ResourceName, Thread.CurrentThread.CurrentUICulture);
            }

            if (p_Object != null)
            {
                p_List.Clear();
                Debug.Assert(p_Object != null);
                p_List.Add(p_Object);

                for (int i = 1; i < ItemsNumber; i++)
                {
                    p_List.Add(p_Resources.GetString(s_ResourceName + i,
                               Thread.CurrentThread.CurrentUICulture));
                }
            }
        }

        /// <summary>
        /// Cette fonction permet de mettre à jour les propriétés d'un formulaire.
        /// </summary>
        /// <param name="p_Form">Le pointeur vers le formulaire.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void ReloadFormProperties(Form p_Form, ResourceManager p_Resources)
        {
            SetProperty(p_Form, "AutoScaleBaseSize", p_Resources);
            SetProperty(p_Form, "Icon", p_Resources);
            SetProperty(p_Form, "MaximumSize", p_Resources);
            SetProperty(p_Form, "MinimumSize", p_Resources);
        }

        #endregion

        #region Fonctions set

        /// <summary>
        /// Cette fonction permet l'inscription d'une propriété dans un contrôle.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <param name="PropertyName">Le nom de la propriété.</param>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        private void SetProperty(Control p_Control, string PropertyName, ResourceManager p_Resources)
        {
            try
            {
                PropertyInfo p_PropertyInfo = p_Control.GetType().GetProperty(PropertyName);

                if (p_PropertyInfo != null)
                {
                    string s_ControlName = p_Control.Name;

                    if (p_Control is Form)
                    {
                        s_ControlName = "$this";
                    }

                    object p_Object = p_Resources.GetObject(s_ControlName + "." + PropertyName,
                                                            Thread.CurrentThread.CurrentUICulture);

                    if (p_Object != null)
                    {
                        p_PropertyInfo.SetValue(p_Control,
                                                Convert.ChangeType(p_Object, p_PropertyInfo.PropertyType),
                                                null);
                    }
                }
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class Culture -> Function SetProperty failed. Cause : " + ex.Message);
            }
        }

        #endregion

        #region Fonctions Get

        /// <summary>
        /// Cette fonction permet d'obtenir l'info bulle pour un contrôle spécifique.
        /// </summary>
        /// <param name="p_Control">Le pointeur vers le contrôle concerné.</param>
        /// <returns>Le pointeur vers l'info bulle du contrôle.</returns>
        private ToolTip GetToolTip(Control p_Control)
        {
            Debug.Assert(p_Control is Form || p_Control is UserControl);

            FieldInfo[] p_FieldInfo =
                p_Control.GetType().GetFields(BindingFlags.NonPublic |
                                               BindingFlags.Instance |
                                               BindingFlags.Public);

            for (int i = 0; i < p_FieldInfo.Length; i++)
            {
                object p_Object = p_FieldInfo[i].GetValue(p_Control);

                if (p_Object is ToolTip)
                {
                    return (ToolTip)p_Object;
                }
            }

            return null;
        }

        /// <summary>
        /// Cette fonction permet d'obtenir une valeur de façon sûre.
        /// </summary>
        /// <param name="p_Resources">Le pointeur vers le gestionnaire de ressources.</param>
        /// <param name="Name">La clé de la valeur.</param>
        /// <param name="CurrentValue">La valeur utilisée actuellement.</param>
        /// <returns></returns>
        private object GetSafeValue(ResourceManager p_Resources, string Name, object CurrentValue)
        {
            object NewValue = p_Resources.GetObject(Name, Thread.CurrentThread.CurrentUICulture);

            if (NewValue == null)
            {
                Trace.WriteLine
                    (string.Format("Class Culture -> Function GetSafeValue cannot find resource for {0}. Using current value.",
                                   Name));

                return CurrentValue;
            }

            return NewValue;
        }

        #endregion

        #endregion
    }
}
