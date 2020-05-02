using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class ExternPrestation
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private String           m_ExternPrestation;
        private int              m_ExternPrestationID;
        private int              m_ExternSystemID;
        private int              m_PrestationID;

        /// getter/setter
        public int    ExternPrestationID    {get{return m_ExternPrestationID;} set{m_ExternPrestationID = value;}}
        public int    ExternSystemID        {get{return m_ExternSystemID;}     set{m_ExternSystemID     = value;}}
        public int    PrestationID          {get{return m_PrestationID;}       set{m_PrestationID       = value;}}
        public String ExternPrestationValue {get{return m_ExternPrestation;}   set{m_ExternPrestation   = value;}}

        public ExternPrestation()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               =  (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString =  m_ConnectionStr;
            m_ExternPrestationID          = -1;
        }

        /// <summary>
        /// Load the current extern prestation
        /// </summary>
        public void Load(int externPrestationID)
        {
            try
            {
                string query;
                DataSet ds = new DataSet();

                m_Connection.Open();

                query = "SELECT * FROM externprestation WHERE externprestationid = " + externPrestationID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("ExternPrestation with ID=" + externPrestationID + " not found.");
                else
                {
                    m_ExternPrestationID = externPrestationID;
                    m_ExternSystemID     = Convert.ToInt32 (ds.Tables[0].Rows[0]["externsystemID"]);
                    m_PrestationID       = Convert.ToInt32 (ds.Tables[0].Rows[0]["prestationid"]);
                    m_ExternPrestation   = Convert.ToString(ds.Tables[0].Rows[0]["externprestation"]);
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
        /// Add the current object in the database and return the last added ID
        /// </summary>
        public int Add()
        {
            try
            {
                MySqlCommand cmd   =  new MySqlCommand();
                int          newID = -1;
                String       sql;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                sql  = "INSERT INTO externprestation(externsystemid, prestationid, externprestation) values(";
                sql += m_ExternSystemID;
                sql += ",";
                sql += m_PrestationID;
                sql += ",'";
                sql += SQL.escapeString(m_ExternPrestation);
                sql += "')";

                cmd.CommandText = sql;

                cmd.ExecuteNonQuery();

                sql = "SELECT @@identity lastid";

                cmd.CommandText = sql;
                newID           = Convert.ToInt32(cmd.ExecuteScalar());

                m_Connection.Close();

                return newID;
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Update the externPrestation into database
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE externPrestation SET externsystemid =" + m_ExternSystemID;
                query += " ,prestationid = "                            + m_PrestationID;
                query += " ,externprestation = '"                       + SQL.escapeString(m_ExternPrestation) + "'";
                query += " WHERE externprestationid = "                 + m_ExternPrestationID;

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

        /// <summary>
        /// Get list of extern prestations
        /// </summary>
        public DataSet getListMapping(int systemID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT extp.externprestationid, p.prestationid, p.prestationTitle, extp.externprestation";
                query += " FROM pprestations p LEFT JOIN externprestation  extp ON  p.prestationid = extp.prestationid AND extp.externsystemid = " + systemID;

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
