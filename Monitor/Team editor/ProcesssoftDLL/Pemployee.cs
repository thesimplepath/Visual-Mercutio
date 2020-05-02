using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Pemployee
    {
        public enum IEFlagAsychronous
        {
            IE_FA_Denied  = 0,
            IE_FA_Allowed = 1
        };

        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private string           m_Login;
        private string           m_FName;
        private string           m_LName;
        private string           m_Email;
        private string           m_Phone;
        private string           m_Password;
        private int              m_EmplID;
        private int              m_EmployeeTitleID;
        private int              m_FlagAsynchronous;
        private int              m_RoleID;

        /// getter/setter
        public int    EmplID          {get{return m_EmplID;}           set{m_EmplID           = value;}}
        public string Login           {get{return m_Login;}            set{m_Login            = value;}}
        public int    EmployeeTitleID {get{return m_EmployeeTitleID;}  set{m_EmployeeTitleID  = value;}}
        public int    FlagAsynchronous{get{return m_FlagAsynchronous;} set{m_FlagAsynchronous = value;}}
        public int    RoleID          {get{return m_RoleID;}           set{m_RoleID           = value;}}
        public string FName           {get{return m_FName;}            set{m_FName            = value;}}
        public string LName           {get{return m_LName;}            set{m_LName            = value;}}
        public string Email           {get{return m_Email;}            set{m_Email            = value;}}
        public string Phone           {get{return m_Phone;}            set{m_Phone            = value;}}
        public string Password        {get{return m_Password;}         set{m_Password         = value;}}

        public Pemployee()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Add the current object in the database and get back the id
        /// </summary>
        public void add()
        {
            try
            {
                MD5Crypt     md5 = new MD5Crypt();
                MySqlCommand cmd = new MySqlCommand();
                String       sql;

                m_Connection.Open();

                cmd.Connection  = m_Connection;
                cmd.CommandText = "SELECT max(emplid) FROM pemployee";

                int nextID = (System.Int32)cmd.ExecuteScalar() + 1;
                m_EmplID   = Convert.ToInt32(nextID);

                sql = "insert into pemployee(emplid, employeetitleid, login, roleid,fname,lname,flagAsynchronous, email, phone) values(";
                sql += m_EmplID;
                sql += ",";
                sql += m_EmployeeTitleID;
                sql += ",'";
                sql += SQL.escapeString(m_Login);
                sql += "',";
                sql += m_RoleID;
                sql += ",'";
                sql += SQL.escapeString(m_FName);
                sql += "','";
                sql += SQL.escapeString(m_LName);
                sql += "',";
                sql += m_FlagAsynchronous;
                sql += ",'";
                sql += SQL.escapeString(m_Email);
                sql += "','";
                sql += SQL.escapeString(m_Phone);
                sql += "')";

                cmd.CommandText = sql ;

                cmd.ExecuteNonQuery();

                sql = "INSERT INTO pemppasswd (emplid, passwd) VALUES (";
                sql += m_EmplID;
                sql += ",'" ;
                sql += md5.GetMD5(m_Password) ;
                sql += "')" ;

                cmd.CommandText = sql ;

                cmd.ExecuteNonQuery() ;

                m_Connection.Close() ;
            }
            catch (Exception e)
            {
                m_EmplID = -1;
                throw(e);
            }
        }

        /// <summary>
        /// update the employee into database
        /// </summary>
        public void update()
        {
            try
            {
                MD5Crypt     md5 = new MD5Crypt();
                DataSet      ds  = new DataSet();
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE pemployee SET fname = '" + m_FName + "'";
                query += " ,lname = '"                    + SQL.escapeString(m_LName) + "'";
                query += " ,login = '"                    + SQL.escapeString(m_Login) + "'";
                query += " ,email = '"                    + SQL.escapeString(m_Email) + "'";
                query += " ,phone = '"                    + SQL.escapeString(m_Phone) + "'";
                query += " ,roleID = "                    + m_RoleID;
                query += " ,flagAsynchronous = "          + m_FlagAsynchronous;
                query += " ,employeetitleID = "           + m_EmployeeTitleID;
                query += " WHERE emplid = "               + m_EmplID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // set the password if changed
                if (m_Password != "")
                {
                    query  = "UPDATE pemppasswd SET passwd = '" + md5.GetMD5(m_Password) + "'";
                    query += " WHERE emplID = "                 + m_EmplID;

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
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
        /// load a specific employee from database
        /// </summary>
        public void loadEmployee(int id)
        {
            try
            {
                MD5Crypt md5 = new MD5Crypt();
                DataSet  ds  = new DataSet();
                string   query;

                m_Connection.Open();

                query = "SELECT * FROM PEMPLOYEE WHERE PEMPLOYEE.EMPLID = " + id;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("Employee with id=" + id + " not found.");
                else
                {
                    m_EmplID           = id;
                    m_FName            = (String)ds.Tables[0].Rows[0]["fname"];
                    m_LName            = (String)ds.Tables[0].Rows[0]["lname"];
                    m_Login            = (String)ds.Tables[0].Rows[0]["login"];
                    m_EmployeeTitleID  = Convert.ToInt32(ds.Tables[0].Rows[0]["employeeTitleID"]);
                    m_FlagAsynchronous = Convert.ToInt32(ds.Tables[0].Rows[0]["flagasynchronous"]);
                    m_RoleID           = Convert.ToInt32(ds.Tables[0].Rows[0]["roleid"]);
                    m_Email            = (String)ds.Tables[0].Rows[0]["email"];
                    m_Phone            = Convert.ToString(ds.Tables[0].Rows[0]["phone"]);
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
        /// Get list of employees
        /// </summary>
        public DataSet getList()
        {
            try
            {
                string query;

                m_Connection.Open();

                query = "SELECT * FROM PEMPLOYEE";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();

                m_Adapter.Fill(ds);

                m_Connection.Close();

                return ds;
            }
            catch(Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }
    }
}
