/********************************************************************************************************
 *                                             Classe WordInstance                                      *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 1er avril 2007                                                                         *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe permet de gérer un fichier de configuration pour le programme. Elle crée le fichier,    *
 * et permet la lecture ou l'inscription des paires clés/valeurs dans celui-ci.                         *
 ********************************************************************************************************/

using System;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;

namespace ReportsTool.FilesManager
{
    public class ConfigFile
    {
        #region Définition du Singleton de la classe

        /// <summary>
        /// La seule et unique instance de la classe ConfigFile.
        /// </summary>
        protected static readonly ConfigFile p_Instance = new ConfigFile();

        #endregion

        #region Variables globales

        private string s_Filename       = "Config.ini";
        private string s_ReservedChar   = "#";
        private string s_OpenKey        = "[";
        private string s_CloseKey       = "]";

        #endregion

        #region Constructeur(s) / Destructeur

        /// <summary>
        /// Le constructeur est privé, ce qui interdit la construction d'une autre instance pour cette classe.
        /// </summary>
        private ConfigFile()
        {
        }

        #endregion

        #region Propriétés de la classe

        /// <summary>
        /// Retourne un pointeur sur l'instance unique de la classe.
        /// </summary>
        public static ConfigFile Instance
        {
            get
            {
                return p_Instance;
            }
        }

        #endregion

        #region Fonctions publiques

        /// <summary>
        /// Cette fonction permet de déterminer si le fichier de configuration a déjà été crée.
        /// </summary>
        /// <returns>True si le fichier est crée, sinon False.</returns>
        public bool Exists()
        {
            return File.Exists(s_Filename);
        }

        /// <summary>
        /// Cette fonction permet de créer un fichier de configuration, vide.
        /// </summary>
        public void Create()
        {
            try
            {
                File.Create(s_Filename);
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Create failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_CREATE_INI_FILE") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction permet de lire une valeur dans le fichier.
        /// </summary>
        /// <param name="Key">La clé correspondant à la valeur à lire.</param>
        /// <returns>La valeur de la clé.</returns>
        public string Read(string Key)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                while (oFileReader.Peek() != -1)
                {
                    string theLine = oFileReader.ReadLine();

                    if (theLine.Contains(FormatKey(Key)))
                    {
                        string[] theValues = theLine.Split('=');

                        oFileReader.Close();
                        oReadStream.Close();

                        return theValues[theValues.Length - 1];
                    }
                }

                oFileReader.Close();
                oReadStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Read failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_READ_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }

            return "";
        }

        /// <summary>
        /// Cette fonction permet d'écrire une paire clé/valeur dans le fichier de configuration.
        /// Si la clé existe déjà dans le fichier, celle-ci est simplement mise à jour.
        /// </summary>
        /// <param name="Key">La clé, sans les caractères [ et ].</param>
        /// <param name="Value">La valeur à attribuer à la clé.</param>
        public void Write(string Key, string Value)
        {
            try
            {
                if (Key.Contains(s_ReservedChar) || Key.Contains(s_OpenKey) || Key.Contains(s_CloseKey))
                {
                    throw new Exception(InsertString("IDS_WRONG_KEY_FORMAT", FormatKey(Key)));
                }

                if (Value.Contains(s_ReservedChar) || Value.Contains(s_OpenKey) || Value.Contains(s_CloseKey))
                {
                    throw new Exception(InsertString("IDS_WRONG_VALUE_FORMAT", Value));
                }

                if (KeyExist(Key) == false)
                {
                    WriteNewLine(Key, Value);
                }
                else
                {
                    OverWrite(Key, Value);
                }
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Write failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Fonctions privées

        /// <summary>
        /// Cette fonction permet de déterminer si une clé existe dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La clé, sans les caractères [ et ].</param>
        /// <returns>true si la clé existe, sinon false.</returns>
        private bool KeyExist(string Key)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                while (oFileReader.Peek() != -1)
                {
                    string theLine = oFileReader.ReadLine();

                    if (theLine.Contains(FormatKey(Key)))
                    {
                        oFileReader.Close();
                        oReadStream.Close();

                        return true;
                    }
                }

                oFileReader.Close();
                oReadStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function KeyExist failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }

            return false;
        }

        /// <summary>
        /// Cette fonction permet d'écrire une nouvelle paire clé/valeur dans le fichier.
        /// </summary>
        /// <param name="Key">La clé, sans les caractères [ et ].</param>
        /// <param name="Value">La valeur de la clé.</param>
        private void WriteNewLine(string Key, string Value)
        {
            try
            {
                FileStream oWriteStream = new FileStream(s_Filename,
                                                         FileMode.Append,
                                                         FileAccess.Write,
                                                         FileShare.None);

                StreamWriter oFileWriter = new StreamWriter(oWriteStream, System.Text.Encoding.Default);

                oFileWriter.WriteLine(FormatKey(Key) + "=" + Value);

                oFileWriter.Close();
                oWriteStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function WriteLine failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction permet de mettre à jour une valeur pour une clé existante dans le fichier.
        /// </summary>
        /// <param name="Key">La clé, sans les caractères [ et ].</param>
        /// <param name="Value">La valeur de la clé à mettre à jour.</param>
        private void OverWrite(string Key, string Value)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                string s_FileContent = "";

                while (oFileReader.Peek() != -1)
                {
                    s_FileContent += oFileReader.ReadLine() + s_ReservedChar;
                }

                oFileReader.Close();
                oReadStream.Close();

                File.Delete(s_Filename);

                string[] s_File = s_FileContent.Split(s_ReservedChar.ToCharArray());

                FileStream oWriteStream = new FileStream(s_Filename,
                                                         FileMode.OpenOrCreate,
                                                         FileAccess.Write,
                                                         FileShare.None);

                StreamWriter oFileWriter = new StreamWriter(oWriteStream, System.Text.Encoding.Default);

                for (int i = 0; i < s_File.Length - 1; i++)
                {
                    if (s_File[i].Contains(FormatKey(Key)))
                    {
                        oFileWriter.WriteLine(FormatKey(Key) + "=" + Value);
                    }
                    else
                    {
                        oFileWriter.WriteLine(s_File[i]);
                    }
                }

                oFileWriter.Close();
                oWriteStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function OverWrite failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction retourne une clé formatée.
        /// </summary>
        /// <param name="Key">La clé à formater.</param>
        /// <returns>La clé formatée.</returns>
        private string FormatKey(string Key)
        {
            return s_OpenKey + Key + s_CloseKey;
        }

        /// <summary>
        /// Cette fonction permet de remplaçer la valeur %s par un mot ou une phrase dans une chaîne de caractères.
        /// </summary>
        /// <param name="ID">L'ID de la chaîne à charger.</param>
        /// <param name="Value">La valeur de remplacement pour %s.</param>
        /// <returns></returns>
        private string InsertString(string ID, string Value)
        {
            return Culture.Culture.Instance.GetStr(ID).Replace("%s", Value);
        }

        #endregion
    }
}
