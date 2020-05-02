using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Pemployeetitle
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private string           m_EmployeeTitle;
        private int              m_EmployeeTitleID;

        /// getter/setter
        public int    EmployeeTitleID{get{return m_EmployeeTitleID;} set{m_EmployeeTitleID = value;}}
        public string EmployeeTitle  {get{return m_EmployeeTitle;}   set{m_EmployeeTitle   = value;}}

        public Pemployeetitle()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
        }

        /// <summary>
        /// load a specific employee title from database
        /// </summary>
        public void loadEmployeeTitle(int id)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                m_Connection.ConnectionString = m_ConnectionStr;

                m_Connection.Open();

                query = "SELECT * FROM EMPLOYEETITLE WHERE employeetitleID = " + id;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("EmployeeTitle with id=" + id + " not found.");
                else
                {
                    m_EmployeeTitleID = id;
                    m_EmployeeTitle   = (String)ds.Tables[0].Rows[0]["employeetitle"];
                }

                m_Connection.Close();
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Get the employee title list
        /// </summary>
        public DataSet getList()
        {
            try
            {
                string query;

                m_Connection.ConnectionString = m_ConnectionStr;

                m_Connection.Open();

                query = "SELECT * FROM EMPLOYEETITLE";

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
