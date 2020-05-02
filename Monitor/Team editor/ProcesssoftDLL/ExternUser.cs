using System;
using System.Collections.Generic;
using System.Text;
using MySql.Data.MySqlClient;
using System.Data;
using System.Configuration;


namespace ProcesssoftDLL
{

    public class ExternUser
    {
        public static String m_ChaineConnection;

        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private String           m_ExternUser;
        private int              m_ExternUserID;
        private int              m_ExternSystemID;
        private int              m_EmplID;

        /// getter/setter
        public int    ExternUserID   {get{return m_ExternUserID;}   set{m_ExternUserID   = value;}}
        public int    ExternSystemID {get{return m_ExternSystemID;} set{m_ExternSystemID = value;}}
        public int    EmplID         {get{return m_EmplID;}         set{m_EmplID         = value;}}
        public String ExternUserValue{get{return m_ExternUser;}     set{m_ExternUser     = value;}}

        public ExternUser()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               =  (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString =  m_ConnectionStr;
            m_ExternUserID                = -1;
        }

        /// <summary>
        /// Load the current extern user
        /// </summary>
        public void Load(int externUserID)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                m_Connection.Open();

                query = "SELECT * FROM externuser WHERE externuserid = " + externUserID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("ExternUser with ID=" + externUserID + " not found.");
                else
                {
                    m_ExternUserID   = externUserID;
                    m_ExternSystemID = Convert.ToInt32 (ds.Tables[0].Rows[0]["externsystemID"]);
                    m_EmplID         = Convert.ToInt32 (ds.Tables[0].Rows[0]["emplid"]);
                    m_ExternUser     = Convert.ToString(ds.Tables[0].Rows[0]["externuser"]);
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
                MySqlCommand cmd   = new MySqlCommand();
                int          newID = -1;
                String       sql;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                sql = "INSERT INTO externuser(externsystemid, emplid, externuser) values(";
                sql += m_ExternSystemID;
                sql += ",";
                sql += m_EmplID;
                sql += ",'";
                sql += SQL.escapeString(m_ExternUser);
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
        /// Update the externUser into database
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE externUser SET externsystemid =" + m_ExternSystemID;
                query += " ,emplid = "                            + m_EmplID;
                query += " ,externuser = '"                       + SQL.escapeString(m_ExternUser) + "'";
                query += " WHERE externuserid = "                 + m_ExternUserID;

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
        /// Get list of extern users
        /// </summary>
        public DataSet getListMapping(int systemID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT extu.externuserid, e.emplid, e.login, e.fname, e.lname, extu.externuser";
                query += " FROM pemployee e LEFT JOIN externuser  extu ON  e.emplid = extu.emplid AND extu.externsystemid = " + systemID;

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
