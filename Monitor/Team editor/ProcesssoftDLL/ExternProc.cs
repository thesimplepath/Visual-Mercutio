using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class ExternProc
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private String           m_ExternProcDesc;
        private String           m_ExternProcTrans;
        private String           m_ModelRef;
        private int              m_ExternProcID;
        private int              m_SystemID;
        private int              m_ProcStableID;

        /// getter/setter
        public int    ExternProcID    {get{return m_ExternProcID;}    set{m_ExternProcID    = value;}}
        public int    SystemID        {get{return m_SystemID;}        set{m_SystemID        = value;}}
        public int    ProcStableID    {get{return m_ProcStableID;}    set{m_ProcStableID    = value;}}
        public String ExternProcDesc  {get{return m_ExternProcDesc;}  set{m_ExternProcDesc  = value;}}
        public String ExternProcTrans {get{return m_ExternProcTrans;} set{m_ExternProcTrans = value;}}
        public String ModelRef        {get{return m_ModelRef;}        set{m_ModelRef        = value;}}

        public ExternProc()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               =  (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString =  m_ConnectionStr;
            m_ExternProcID                = -1;
        }

        /// <summary>
        /// Load the current extern proc
        /// </summary>
        public void Load(int externProcID)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                m_Connection.Open();

                query = "SELECT * FROM externproc WHERE externprocid = " + externProcID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("ExternProc with ID=" + externProcID + " not found.");
                else
                {
                    m_ExternProcID    = externProcID;
                    m_SystemID        = Convert.ToInt32 (ds.Tables[0].Rows[0]["systemID"]);
                    m_ProcStableID    = Convert.ToInt32 (ds.Tables[0].Rows[0]["procstableid"]);
                    m_ExternProcDesc  = Convert.ToString(ds.Tables[0].Rows[0]["externprocdesc"]);
                    m_ModelRef        = Convert.ToString(ds.Tables[0].Rows[0]["modelref"]);
                    m_ExternProcTrans = Convert.ToString(ds.Tables[0].Rows[0]["externproctrans"]);
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

                sql = "INSERT INTO externproc(systemid, procstableid, externprocdesc, modelref, externproctrans) values(";
                sql += m_SystemID;
                sql += ",";
                sql += m_ProcStableID;
                sql += ",'";
                sql += SQL.escapeString(m_ExternProcDesc);
                sql += "','";
                sql += SQL.escapeString(m_ModelRef);
                sql += "','";
                sql += SQL.escapeString(m_ExternProcTrans);
                sql += "')";

                cmd.CommandText = sql;

                cmd.ExecuteNonQuery();

                sql = "SELECT @@identity lastid";

                cmd.CommandText = sql ;
                newID = Convert.ToInt32(cmd.ExecuteScalar());

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
        /// Update the extern proc into database
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE externProc SET systemID =" + m_SystemID;
                query += " ,procstableid = "                + m_ProcStableID;
                query += " ,externprocdesc = '"             + SQL.escapeString(m_ExternProcDesc)  + "'";
                query += " ,externproctrans = '"            + SQL.escapeString(m_ExternProcTrans) + "'";
                query += " ,modelref = '"                   + SQL.escapeString(m_ModelRef)        + "'";
                query += " WHERE externprocid = "           + m_ExternProcID;

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
        /// Get list of extern systems
        /// </summary>
        public DataSet getListMapping(int systemID, String modelRef)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT DISTINCT attr.mvalue procname, p.procstableid, extp.externproctrans, extp.externprocid, extp.externprocdesc";
                query += " FROM pproc p JOIN pmodel m ON m.modelid = p.modelid";
                query += " JOIN ppdattr attr ON attr.pdattribid = p.pdattribid";
                query += " LEFT JOIN externproc extp ON p.procstableid = extp.procstableid";
                query += " AND extp.systemid = " + systemID;
                query += " WHERE m.modelref = '" + modelRef + "'";
                query += " AND attr.attribdefid = 1310721 ORDER BY procstableid";

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
