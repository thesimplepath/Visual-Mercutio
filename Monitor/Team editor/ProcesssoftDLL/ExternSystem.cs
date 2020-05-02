using System;
using System.Collections.Generic;
using System.Text;
using MySql.Data.MySqlClient;
using System.Data;
using System.Configuration;


namespace ProcesssoftDLL
{
    public class ExternSystem
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private string           m_ExternSystemDesc;
        private int              m_ExternSystemID;

        /// getter/setter
        public int    ExternSystemID  {get{return m_ExternSystemID;}   set{m_ExternSystemID   = value;}}
        public string ExternSystemDesc{get{return m_ExternSystemDesc;} set{m_ExternSystemDesc = value;}}

        public ExternSystem()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Get list of extern systems
        /// </summary>
        public DataSet getList()
        {
            try
            {
                string query;

                m_Connection.Open();

                query = "SELECT * FROM EXTERNSYSTEM";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();

                m_Adapter.Fill(ds);

                m_Connection.Close();

                return ds;
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }
    }
}
