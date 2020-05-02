using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Aip
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;

        public Aip()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Update the current aip for employee
        /// </summary>
        public void Update(int iEmplID)
        {
            try
            {
                string query;
                MySqlCommand cmd = new MySqlCommand();

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query = "DELETE from AIP WHERE emplid = " + iEmplID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get current config aip for employee
                query  = "select emplid, aipcriteriaid, taux, Month(startdate) smonth, Year(startdate) syear, Month(enddate) emonth, Year(enddate) eyear from employeeaip" ;
                query += " WHERE emplid = " + iEmplID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();

                m_Adapter.Fill(ds);

                int startYear,  endYear;
                int startMonth, endMonth;

                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    startYear  = Convert.ToInt32(ds.Tables[0].Rows[i]["syear"]);
                    endYear    = Convert.ToInt32(ds.Tables[0].Rows[i]["eyear"]);
                    startMonth = Convert.ToInt32(ds.Tables[0].Rows[i]["smonth"]);
                    endMonth   = Convert.ToInt32(ds.Tables[0].Rows[i]["emonth"]);

                    while (startYear <= endYear)
                    {
                        if (startYear == endYear)
                            while (startMonth <= endMonth)
                            {
                                // update
                                UpdateAip(iEmplID, startMonth, startYear, Convert.ToSingle(ds.Tables[0].Rows[i]["taux"])) ;

                                ++startMonth;
                            }
                        else
                            while (startMonth <= 12)
                            {
                                // update
                                UpdateAip(iEmplID, startMonth, startYear, Convert.ToSingle(ds.Tables[0].Rows[i]["taux"])) ;

                                ++startMonth;
                            }

                        startMonth = 1;
                        ++startYear;
                    }
                }

                m_Connection.Close();

            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        private void UpdateAip(int emplid, int month, int year, Single taux)
        {
            MySqlDataAdapter Adapter = new MySqlDataAdapter();
            MySqlCommand     cmd     = new MySqlCommand();
            String           query;

            query  = "SELECT * FROM aip WHERE emplid = " + emplid;
            query += " AND calmonth = "                  + month;
            query += " AND calyear = "                   + year;

            cmd.CommandText = query;
            cmd.Connection  = m_Connection;

            Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

            DataSet ds = new DataSet();
            Adapter.Fill(ds);

            if (ds.Tables[0].Rows.Count == 0)
            {
                // insert
                query  = "INSERT INTO aip (emplid, calmonth, calyear, taux)";
                query += " VALUES (" + emplid + "," + month + "," + year + "," + taux + ")";
            }
            else
            {
                // update
                query  = "UPDATE aip SET taux = taux * " + taux;
                query += " WHERE emplid = "              + emplid;
                query += " AND calmonth = "              + month;
                query += " AND calyear = "               + year;

            }

            // execute query
            cmd.CommandText = query;
            cmd.ExecuteNonQuery();
        }
    }
}
