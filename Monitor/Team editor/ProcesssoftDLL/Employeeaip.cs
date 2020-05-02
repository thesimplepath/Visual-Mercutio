using System;
using System.Collections.Generic;
using System.Text;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Employeeaip
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private DateTime         m_StartDate;
        private DateTime         m_EndDate;
        private string           m_ConnectionStr;
        private string           m_Motif;
        private Single           m_Taux;
        private int              m_EmployeeAipID;
        private int              m_EmplID;
        private int              m_AipCriteriaID;

        /// getter/setter
        public int      EmplID        {get{return m_EmplID;}        set{m_EmplID        = value;}}
        public int      EmployeeAipID {get{return m_EmployeeAipID;} set{m_EmployeeAipID = value;}}
        public int      AipCriteriaID {get{return m_AipCriteriaID;} set{m_AipCriteriaID = value;}}
        public string   Motif         {get{return m_Motif;}         set{m_Motif         = value;}}
        public Single   Taux          {get{return m_Taux;}          set{m_Taux          = value;}}
        public DateTime StartDate     {get{return m_StartDate;}     set{m_StartDate     = value;}}
        public DateTime EndDate       {get{return m_EndDate;}       set{m_EndDate       = value;}}

        public Employeeaip()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Delete the specific EmployeeAip and update AIP table
        /// </summary>
        public void Delete()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query = "DELETE FROM employeeaip WHERE employeeaipid = " + m_EmployeeAipID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                m_Connection.Close();

                // update AIP table
                Aip oAip = new Aip();
                oAip.Update(m_EmplID);
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Load a specific employeeAIP from database
        /// </summary>
        public void loadEmployeeAIP(int iEmployeeAipID)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                m_Connection.Open();

                query  = "SELECT EMPAIP.*, EMP.fname, EMP.lname, AIP.aipcriteria FROM employeeaip EMPAIP, pemployee EMP, aipcriteria AIP WHERE EMPAIP.employeeaipid = " + iEmployeeAipID;
                query += " AND EMPAIP.emplid = EMP.emplid";
                query += " AND EMPAIP.aipcriteriaID = AIP.aipcriteriaID";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("EmployeeAIP with ID=" + iEmployeeAipID + " not found.");
                else
                {
                    m_EmployeeAipID = iEmployeeAipID;
                    m_EmplID        = Convert.ToInt32(ds.Tables[0].Rows[0]["emplid"]);
                    m_AipCriteriaID = Convert.ToInt32(ds.Tables[0].Rows[0]["aipcriteriaID"]);
                    m_Motif         = (String)ds.Tables[0].Rows[0]["motif"];
                    m_StartDate     = (DateTime)ds.Tables[0].Rows[0]["startdate"];
                    m_EndDate       = (DateTime)ds.Tables[0].Rows[0]["enddate"];
                    m_Taux          = (Single)ds.Tables[0].Rows[0]["taux"];
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
        /// Update the employeeAIP into database and update AIP table
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE employeeaip SET aipcriteriaid =" + m_AipCriteriaID;
                query += " ,motif = '"                            + SQL.escapeString(m_Motif) + "'";
                query += " ,taux = "                              + m_Taux;
                query += " ,startdate = '"                        + m_StartDate.Year + "." + m_StartDate.Month + "." + m_StartDate.Day + "'";
                query += " ,enddate = '"                          + m_EndDate.Year   + "." + m_EndDate.Month   + "." + m_EndDate.Day   + "'";
                query += " WHERE employeeaipID = "                + m_EmployeeAipID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                m_Connection.Close();

                // update AIP table
                Aip oAip = new Aip();
                oAip.Update(m_EmplID);

            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Add the current object in the database and update AIP table
        /// </summary>
        public void Add()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                String       sql;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                sql  = "insert into employeeaip(emplid, aipcriteriaID, motif, taux, startdate, enddate) values(";
                sql += m_EmplID;
                sql += ",";
                sql += m_AipCriteriaID;
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
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        public DataSet GetListByEmplID(int eID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT EMPAIP.*, AIP.aipcriteria FROM employeeaip EMPAIP, aipcriteria AIP WHERE EMPAIP.aipcriteriaID = AIP.aipcriteriaID";
                query += " AND EMPAIP.emplid = " + eID;

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
