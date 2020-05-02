using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Pworkgroup
    {
        public enum IEType
        {
            IE_T_Workgroup = 0,
            IE_T_Team      = 1
        };

        public enum IEEPT
        {
            IE_E_CalculatedBySystem = 0,
            IE_E_Manual             = 1
        } ;

        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private string           m_WkgName;
        private string           m_Mission;
        private string           m_Vocation;
        private string           m_Street;
        private string           m_NpaLocality;
        private string           m_Municipality;
        private string           m_Country;
        private string           m_Email;
        private string           m_CreationDate;
        private string           m_Phone;
        private int              m_WkgID;
        private int              m_WkgParentID;
        private int              m_EptFlag;
        private int              m_WkgType;
        private int              m_WkgPercent;

        /// getter/setter
        public int    WkgID        {get{return m_WkgID;}        set{m_WkgID        = value;}}
        public int    WkgParentID  {get{return m_WkgParentID;}  set{m_WkgParentID  = value;}}
        public string WkgName      {get{return m_WkgName;}      set{m_WkgName      = value;}}
        public int    EptFlag      {get{return m_EptFlag;}      set{m_EptFlag      = value;}}
        public int    WkgType      {get{return m_WkgType;}      set{m_WkgType      = value;}}
        public int    WkgPercent   {get{return m_WkgPercent;}   set{m_WkgPercent   = value;}}
        public string Mission      {get{return m_Mission;}      set{m_Mission      = value;}}
        public string Vocation     {get{return m_Vocation;}     set{m_Vocation     = value;}}
        public string Street       {get{return m_Street;}       set{m_Street       = value;}}
        public string NpaLocality  {get{return m_NpaLocality;}  set{m_NpaLocality  = value;}}
        public string Municipality {get{return m_Municipality;} set{m_Municipality = value;}}
        public string Country      {get{return m_Country;}      set{m_Country      = value;}}
        public string Email        {get{return m_Email;}        set{m_Email        = value;}}
        public string CreationDate {get{return m_CreationDate;} set{m_CreationDate = value;}}
        public string Phone        {get{return m_Phone;}        set{m_Phone        = value;}}

        public Pworkgroup()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        public DataSet GetListTeamByProcID(int procID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT DISTINCT pworkgroup.* FROM pproc, pworkgroup";
                query += " WHERE pproc.wkgid = pworkgroup.wkgparent";
                query += " AND wkgtype = "      + (int)Pworkgroup.IEType.IE_T_Team;
                query += " AND pproc.procid = " + procID;
                query += " ORDER BY wkgname";

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

        public DataSet GetListByType(int iType)
        {
            try
            {
                string query;

                m_Connection.Open();

                if (iType == (int)Pworkgroup.IEType.IE_T_Workgroup)
                {
                    query  = "SELECT * FROM pworkgroup WHERE wkgtype = " + iType;
                    query += " ORDER BY wkgname";
                }
                else
                {
                    query  = "SELECT pteam.*, pgroup.wkgname wkgparentname FROM pworkgroup pgroup, pworkgroup pteam WHERE pteam.wkgtype = " + iType;
                    query += " AND pteam.wkgparent = pgroup.wkgid";
                    query += " ORDER BY pteam.wkgname";
                }

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

        /// <summary>
        /// Load the specific workgroup
        /// </summary>
        public void LoadWorkgroup(int id)
        {
            try
            {
                string  query;
                DataSet ds = new DataSet();

                m_Connection.Open();

                query = "SELECT * FROM pworkgroup WHERE wkgid = " + id;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("Workgroup with id=" + id + " not found.");
                else
                {
                    m_WkgID   = id;
                    m_Country = (String)ds.Tables[0].Rows[0]["country"];

                    if (ds.Tables[0].Rows[0]["creationdate"] != null)
                        m_CreationDate = Convert.ToString(ds.Tables[0].Rows[0]["creationdate"]);
                    else
                        m_CreationDate = "";

                    m_Email        = (String)ds.Tables[0].Rows[0]["email"];
                    m_EptFlag      = Convert.ToInt32(ds.Tables[0].Rows[0]["eptflag"]);
                    m_Mission      = (String)ds.Tables[0].Rows[0]["mission"];
                    m_Municipality = (String)ds.Tables[0].Rows[0]["municipality"];
                    m_NpaLocality  = (String)ds.Tables[0].Rows[0]["npalocality"];
                    m_Street       = (String)ds.Tables[0].Rows[0]["street"];
                    m_Vocation     = (String)ds.Tables[0].Rows[0]["vocation"];
                    m_WkgName      = (String)ds.Tables[0].Rows[0]["wkgname"];
                    m_WkgParentID  = Convert.ToInt32(ds.Tables[0].Rows[0]["wkgparent"]);
                    m_WkgPercent   = Convert.ToInt32(ds.Tables[0].Rows[0]["wkgpercent"]);
                    m_WkgType      = Convert.ToInt32(ds.Tables[0].Rows[0]["wkgtype"]);
                    m_Phone        = (String)ds.Tables[0].Rows[0]["phone"];
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
        /// Update the workgroup into database
        /// </summary>
        public void Update()
        {
            try
            {
                DataSet      ds  = new DataSet();
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE pworkgroup SET wkgname = '" + m_WkgName                        + "'";
                query += " ,wkgpercent = "                   + m_WkgPercent;
                query += " ,eptflag = "                      + m_EptFlag;
                query += " ,mission = '"                     + SQL.escapeString(m_Mission)      + "'";
                query += " ,vocation = '"                    + SQL.escapeString(m_Vocation)     + "'";
                query += " ,street = '"                      + SQL.escapeString(m_Street)       + "'";
                query += " ,npalocality = '"                 + SQL.escapeString(m_NpaLocality)  + "'";
                query += " ,municipality = '"                + SQL.escapeString(m_Municipality) + "'";
                query += " ,country = '"                     + SQL.escapeString(m_Country)      + "'";
                query += " ,email = '"                       + SQL.escapeString(m_Email)        + "'";
                query += " ,wkgtype = "                      + m_WkgType;
                query += " ,phone = '"                       + SQL.escapeString(m_Phone)        + "'";
                query += " ,wkgparent = "                    + m_WkgParentID;
                query += " WHERE wkgid = "                   + m_WkgID;

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
        /// Add the workgroup into database
        /// </summary>
        public void Add()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                String       sql;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // get max id
                cmd.CommandText = "SELECT max(wkgid) FROM pworkgroup";
                m_WkgID         = (System.Int32)cmd.ExecuteScalar() + 1;

                sql  = "insert into pworkgroup(wkgid,wkgparent,wkgname,wkgpercent,eptflag,mission,vocation,street,npalocality,municipality,country,email,creationdate,wkgtype, phone) values(";
                sql += m_WkgID;
                sql += ",";
                sql += m_WkgParentID;
                sql += ",'";
                sql += SQL.escapeString(m_WkgName);
                sql += "',";
                sql += m_WkgPercent;
                sql += ",";
                sql += m_EptFlag;
                sql += ",'";
                sql += SQL.escapeString(m_Mission);
                sql += "','";
                sql += SQL.escapeString(m_Vocation);
                sql += "','";
                sql += SQL.escapeString(m_Street);
                sql += "','";
                sql += SQL.escapeString(m_NpaLocality);
                sql += "','";
                sql += SQL.escapeString(m_Municipality);
                sql += "','";
                sql += SQL.escapeString(m_Country);
                sql += "','";
                sql += SQL.escapeString(m_Email);
                sql += "','";
                sql += PDate.GetDateYYYYMMDD();
                sql += "',";
                sql += m_WkgType;
                sql += ",'";
                sql += SQL.escapeString(m_Phone);
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

        /// <summary>
        /// Get the percent total used by the group
        /// </summary>
        public int GetPercentForGroup(int pWkgID)
        {
            try
            {
                MySqlCommand cmd        = new MySqlCommand();
                int          sumPercent = 0;
                String       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query = "SELECT SUM(wkgpercent) as somme FROM PWORKGROUP where wkgParent = " + pWkgID;

                // get max id
                cmd.CommandText = query;

                sumPercent = Convert.ToInt32(cmd.ExecuteScalar());

                m_Connection.Close();

                return sumPercent;
            }
            catch (Exception)
            {
                m_Connection.Close();
                return 0;
            }
        }
    }
}
