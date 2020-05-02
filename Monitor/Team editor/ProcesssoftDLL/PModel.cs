using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class PModel
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;
        private string           m_ModelRef;
        private string           m_ModelName;
        private int              m_ModelID;

        /// getter/setter
        public int    ModelID  {get{return m_ModelID;}   set{m_ModelID   = value;}}
        public string ModelRef {get{return m_ModelRef;}  set{m_ModelRef  = value;}}
        public string ModelName{get{return m_ModelName;} set{m_ModelName = value;}}

        public PModel()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Get list of pmodel
        /// </summary>
        public DataSet getList()
        {
            try
            {
                string query;

                m_Connection.Open();

                query = "SELECT * FROM PMODEL";

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
        /// Get the list of valid model with serveral info
        /// </summary>
        /// <returns>the list of valid model with serveral info</returns>
        public DataSet getListForComboBox()
        {
            try
            {
                string query;

                m_Connection.Open();

                query = "select concat(substring(startdate,1,10), ' / ' , trim(modelname)) model, modelid  from pmodel where isvalid = 1";

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
        /// Get list of pmodel
        /// </summary>
        public DataSet getListOfModelRef()
        {
            try
            {
                string query;

                m_Connection.Open();

                query = "SELECT modelref, modelname FROM pmodel GROUP BY modelref, modelname";

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
