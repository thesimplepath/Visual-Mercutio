using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Employeecalendar
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private int              m_EmplID;
        private int              m_CalMonth;
        private int              m_CalYear;
        private int              m_DaysPlanned;

        /// getter/setter
        public int EmplID      {get{return m_EmplID;}      set{m_EmplID      = value;}}
        public int CalMonth    {get{return m_CalMonth;}    set{m_CalMonth    = value;}}
        public int CalYear     {get{return m_CalYear;}     set{m_CalYear     = value;}}
        public int DaysPlanned {get{return m_DaysPlanned;} set{m_DaysPlanned = value;}}

        public Employeecalendar()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Load current employee calendar
        /// </summary>
        public void LoadEmployeecalendar(int calmonth, int calyear, int emplid)
        {
            try
            {
                string query;
                DataSet ds = new DataSet();

                m_Connection.Open();

                query  = "SELECT * FROM employeecalendar WHERE emplid = " + emplid;
                query += " AND calmonth = "                               + calmonth;
                query += " AND calyear = "                                + calyear;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("employeecalendar not found.");
                else
                {
                    m_EmplID      = emplid;
                    m_CalMonth    = calmonth;
                    m_CalYear     = calyear;
                    m_DaysPlanned = Convert.ToInt32(ds.Tables[0].Rows[0]["daysplanned"]);
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
        /// Update the current employee calendar. Insert if not exist
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlDataAdapter adapter = new MySqlDataAdapter();
                MySqlCommand     cmd     = new MySqlCommand();
                String           query;

                query  = "SELECT * FROM employeecalendar WHERE emplid = " + m_EmplID;
                query += " AND calmonth = "                               + m_CalMonth;
                query += " AND calyear = "                                + m_CalYear;

                m_Connection.Open();

                cmd.CommandText = query;
                cmd.Connection  = m_Connection;

                adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();
                adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                {
                    // insert
                    query  = "INSERT INTO employeecalendar (emplid, calmonth, calyear, daysplanned)";
                    query += " VALUES (" + m_EmplID + "," + m_CalMonth + "," + m_CalYear + "," + m_DaysPlanned + ")";
                }
                else
                {
                    // update
                    query  = "UPDATE employeecalendar SET daysplanned = " + m_DaysPlanned;
                    query += " WHERE emplid = "                           + m_EmplID;
                    query += " AND calmonth = "                           + m_CalMonth;
                    query += " AND calyear = "                            + m_CalYear;

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
