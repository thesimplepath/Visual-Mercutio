using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{

    public class ExternDeliv
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private String           m_ExternDelivDesc;
        private String           m_ExternDelivTrans;
        private int              m_ExternDelivID;
        private int              m_ExternProcID;
        private int              m_DelivStableID;

        /// getter/setter
        public int    ExternDelivID    {get{return m_ExternDelivID;}    set{m_ExternDelivID    = value;}}
        public int    ExernProcID      {get{return m_ExternProcID;}     set{m_ExternProcID     = value;}}
        public int    DelivStableID    {get{return m_DelivStableID;}    set{m_DelivStableID    = value;}}
        public String ExternDelivDesc  {get{return m_ExternDelivDesc;}  set{m_ExternDelivDesc  = value;}}
        public String ExternDelivTrans {get{return m_ExternDelivTrans;} set{m_ExternDelivTrans = value;}}

        public ExternDeliv()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               =  (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString =  m_ConnectionStr;
            m_ExternDelivID               = -1;
        }

        /// <summary>
        /// Load the current extern deliv
        /// </summary>
        public void Load(int externDelivID)
        {
            try
            {
                DataSet ds = new DataSet();
                string  query;

                m_Connection.Open();

                query = "SELECT * FROM externdeliv WHERE externdelivid = " + externDelivID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count == 0)
                    throw new Exception("ExternDeliv with ID=" + externDelivID + " not found.");
                else
                {
                    m_ExternDelivID    = externDelivID;
                    m_ExternProcID     = Convert.ToInt32 (ds.Tables[0].Rows[0]["externprocid"]);
                    m_DelivStableID    = Convert.ToInt32 (ds.Tables[0].Rows[0]["delivstableid"]);
                    m_ExternDelivDesc  = Convert.ToString(ds.Tables[0].Rows[0]["externdelivdesc"]);
                    m_ExternDelivTrans = Convert.ToString(ds.Tables[0].Rows[0]["externdelivtrans"]);
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

                sql = "INSERT INTO externdeliv(externprocid, delivstableid, externdelivdesc, externdelivtrans) values(";
                sql += m_ExternProcID;
                sql += ",";
                sql += m_DelivStableID;
                sql += ",'";
                sql += SQL.escapeString(m_ExternDelivDesc);
                sql += "','";
                sql += SQL.escapeString(m_ExternDelivTrans);
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
        /// Update the extern deliv into database
        /// </summary>
        public void Update()
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query  = "UPDATE externDeliv SET externprocID =" + m_ExternProcID;
                query += " ,delivstableid = "                    + m_DelivStableID;
                query += " ,externdelivdesc = '"                 + SQL.escapeString(m_ExternDelivDesc)  + "'";
                query += " ,externdelivtrans = '"                + SQL.escapeString(m_ExternDelivTrans) + "'";
                query += " WHERE externdelivid = "               + m_ExternDelivID;

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
        /// Get list of extern mapping deliv systems
        /// </summary>
        public DataSet getListMapping(int systemID, String modelRef)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "select distinct attr.mvalue procname, extd.externdelivid, d.delivname, d.delivstableid, extd.externdelivtrans, extd.externdelivdesc, extp.externprocid";
                query += " from pproc p join pmodel m on m.modelid = p.modelid";
                query += " join pdeliv d on d.procidsrc = p.procid";
                query += " left join externdeliv extd on d.delivstableid = extd.delivstableid";
                query += " join ppdattr attr on attr.pdattribid = p.pdattribid";
                query += " join externproc extp on p.procstableid = extp.procstableid and extp.systemid =" + systemID;
                query += " WHERE m.modelref = '" + modelRef + "'";
                query += " and attr.attribdefid = 1310721";

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
