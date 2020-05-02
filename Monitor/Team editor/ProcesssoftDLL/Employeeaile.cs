using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Employeeaile
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private DateTime         m_StartDate;
        private DateTime         m_EndDate;
        private string           m_ConnectionStr;
        private string           m_Motif;
        private Single           m_Taux;
        private int              m_EmployeeAileID;
        private int              m_EmplID;
        private int              m_WkgID;
        private int              m_AileCriteriaID;

        /// getter/setter
        public int      EmplID         {get{return m_EmplID;}         set{m_EmplID         = value;}}
        public int      WkgID          {get{return m_WkgID;}          set{m_WkgID          = value;}}
        public int      EmployeeaileID {get{return m_EmployeeAileID;} set{m_EmployeeAileID = value;}}
        public int      AileCriteriaID {get{return m_AileCriteriaID;} set{m_AileCriteriaID = value;}}
        public string   Motif          {get{return m_Motif;}          set{m_Motif          = value;}}
        public Single   Taux           {get{return m_Taux;}           set{m_Taux           = value;}}
        public DateTime StartDate      {get{return m_StartDate;}      set{m_StartDate      = value;}}
        public DateTime EndDate        {get{return m_EndDate;}        set{m_EndDate        = value;}}

        public Employeeaile()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Delete the specific EmployeeAile and update AILE table
        /// </summary>
        public void Delete()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query = "DELETE FROM employeeaile WHERE employeeaileid = " + m_EmployeeAileID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                m_Connection.Close();

                // update AILE table
                Aile oAile = new Aile();
                oAile.Update(m_EmplID, m_WkgID);

            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Load a specific employee aile from database
        /// </summary>
        public void loadEmployeeAILE(int iEmployeeaileID)
        {
            try
            {
                string  query;
                DataSet ds = new DataSet();

                m_Connection.Open();

                query  = "SELECT EMPAILE.*, EMP.fname, EMP.lname, aile.ailecriteria, TEAM.wkgname FROM employeeaile EMPAILE, pemployee EMP, ailecriteria AILE, pworkgroup TEAM WHERE EMPAILE.employeeaileid = " + iEmployeeaileID;
                query += " AND EMPAILE.emplid = EMP.emplid";
                query += " AND EMPAILE.ailecriteriaID = AILE.ailecriteriaID";
                query += " AND TEAM.wkgid = EMPAILE.wkgid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                {
                    throw new Exception("Employeeaile with ID=" + iEmployeeaileID + " not found.");
                }
                else
                {
                    m_EmployeeAileID = iEmployeeaileID;
                    m_EmplID         = Convert.ToInt32(ds.Tables[0].Rows[0]["emplid"]);
                    m_WkgID          = Convert.ToInt32(ds.Tables[0].Rows[0]["wkgid"]);
                    m_AileCriteriaID = Convert.ToInt32(ds.Tables[0].Rows[0]["ailecriteriaID"]);
                    m_Motif          = (String)ds.Tables[0].Rows[0]["motif"];
                    m_StartDate      = (DateTime)ds.Tables[0].Rows[0]["startdate"];
                    m_EndDate        = (DateTime)ds.Tables[0].Rows[0]["enddate"];
                    m_Taux           = Convert.ToSingle(ds.Tables[0].Rows[0]["taux"]);
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
        /// Update the employee aile into database and update AILE table
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE employeeaile SET ailecriteriaid =" + m_AileCriteriaID;
                query += " ,wkgid = "                               + m_WkgID;
                query += " ,motif = '"                              + SQL.escapeString(m_Motif) + "'";
                query += " ,taux = "                                + m_Taux;
                query += " ,startdate = '"                          + m_StartDate.Year + "." + m_StartDate.Month + "." + m_StartDate.Day + "'";
                query += " ,enddate = '"                            + m_EndDate.Year   + "." + m_EndDate.Month   + "." + m_EndDate.Day   + "'";
                query += " WHERE employeeaileID = "                 + m_EmployeeAileID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                m_Connection.Close();

                // update AILE table
                Aile oAile = new Aile();
                oAile.Update(m_EmplID, m_WkgID);

            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Add the current object in the database and update AILE table
        /// </summary>
        public void Add()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                String       sql;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                sql = "insert into employeeaile(wkgid, emplid, ailecriteriaID, motif, taux, startdate, enddate) values(";
                sql += m_WkgID;
                sql += ",";
                sql += m_EmplID;
                sql += ",";
                sql += m_AileCriteriaID;
                sql += ",'";
                sql += SQL.escapeString(m_Motif);
                sql += "',";
                sql += m_Taux;
                sql += ",'";
                sql += m_StartDate.Year + "." + m_StartDate.Month + "." + m_StartDate.Day;
                sql += "','";
                sql += m_EndDate.Year   + "." + m_EndDate.Month   + "." + m_EndDate.Day;
                sql += "')";

                cmd.CommandText = sql;

                cmd.ExecuteNonQuery();

                m_Connection.Close();

                // update AILE table
                Aile oAile = new Aile();
                oAile.Update(m_EmplID, m_WkgID);
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Get list of employee aile by emplID
        /// </summary>
        public DataSet GetListByEmplID(int eID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT EMPAILE.*, AILE.ailecriteria, TEAM.wkgname FROM employeeaile EMPAILE, ailecriteria AILE, pworkgroup TEAM WHERE EMPAILE.ailecriteriaID = AILE.ailecriteriaID";
                query += " AND EMPAILE.emplid = " + eID;
                query += " AND TEAM.wkgid = EMPAILE.wkgid";

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
