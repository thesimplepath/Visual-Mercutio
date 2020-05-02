using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Eptteammanual
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private int              m_WkgID;
        private int              m_CalMonth;
        private int              m_CalYear;
        private int              m_EptValue;

        /// getter/setter
        public int WkgID    {get{return m_WkgID;}    set{m_WkgID    = value;}}
        public int CalMonth {get{return m_CalMonth;} set{m_CalMonth = value;}}
        public int CalYear  {get{return m_CalYear;}  set{m_CalYear  = value;}}
        public int EptValue {get{return m_EptValue;} set{m_EptValue = value;}}

        public Eptteammanual()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Load current ept team manual
        /// </summary>
        public void LoadEptteammanual(int calmonth, int calyear, int wkgid)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                query  = "SELECT * FROM eptteammanual WHERE wkgid = " + wkgid;
                query += " AND calmonth = " + calmonth;
                query += " AND calyear = " + calyear;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("eptteammanual not found.");
                else
                {
                    m_WkgID    = wkgid;
                    m_CalMonth = calmonth;
                    m_CalYear  = calyear;
                    m_EptValue = Convert.ToInt32(ds.Tables[0].Rows[0]["eptvalue"]);
                }
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Update the current ept team manual. Insert if not exist
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlDataAdapter adapter = new MySqlDataAdapter();
                MySqlCommand     cmd     = new MySqlCommand();
                String           query;

                query  = "SELECT * FROM eptteammanual WHERE wkgid = " + m_WkgID;
                query += " AND calmonth = "                           + m_CalMonth;
                query += " AND calyear = "                            + m_CalYear;

                m_Connection.Open();

                cmd.CommandText = query;
                cmd.Connection  = m_Connection;

                adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();
                adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                {
                    // insert
                    query  = "INSERT INTO eptteammanual (wkgid, calmonth, calyear, eptvalue)";
                    query += " VALUES (" + m_WkgID + "," + m_CalMonth + "," + m_CalYear + "," + m_EptValue + ")";
                }
                else
                {
                    // update
                    query  = "UPDATE eptteammanual SET eptvalue = " + m_EptValue;
                    query += " WHERE wkgid = "                      + m_WkgID;
                    query += " AND calmonth = "                     + m_CalMonth;
                    query += " AND calyear = "                      + m_CalYear;
                }

                // execute query
                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                m_Connection.Close();
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }
    }
}
