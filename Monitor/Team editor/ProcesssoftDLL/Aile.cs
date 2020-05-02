using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Aile
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;

        public Aile()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Delete all entries from AILE for emplid and wkgid
        /// </summary>
        public void Delete(int iEmplID, int iWkgID)
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                query = "DELETE FROM aile WHERE emplid = " + iEmplID;
                query = " AND wkgid = " + iWkgID;

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
        /// Update the current aile for employee and current wkgid
        /// </summary>
        public void Update(int iEmplID, int iWkgID)
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query  = "DELETE from AILE WHERE emplid = " + iEmplID;
                query += " AND wkgid = " + iWkgID;

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get current config aile for employee and current wkgid
                query  = "select emplid, wkgid, ailecriteriaid, taux, Month(startdate) smonth, Year(startdate) syear, Month(enddate) emonth, Year(enddate) eyear from employeeaile" ;
                query += " WHERE emplid = " + iEmplID;
                query += " AND wkgid = " + iWkgID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                DataSet ds = new DataSet();

                m_Adapter.Fill(ds);

                int startYear, endYear;
                int startMonth, endMonth ;

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
                                UpdateAile(iEmplID, iWkgID, startMonth, startYear, Convert.ToSingle(ds.Tables[0].Rows[i]["taux"])) ;
                                ++startMonth;
                            }
                        else
                            while (startMonth <= 12)
                            {
                                // update
                                UpdateAile(iEmplID, iWkgID, startMonth, startYear, Convert.ToSingle(ds.Tables[0].Rows[i]["taux"])) ;
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

        private void UpdateAile(int emplid, int wkgid, int month, int year, Single taux)
        {
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand     cmd     = new MySqlCommand();
            String           query;

            query  = "SELECT * FROM aile WHERE emplid = " + emplid;
            query += " AND wkgid = "                      + wkgid ;
            query += " AND calmonth = "                   + month;
            query += " AND calyear = "                    + year;

            cmd.CommandText = query;
            cmd.Connection  = m_Connection;

            adapter.SelectCommand = new MySqlCommand(query, m_Connection);

            DataSet ds = new DataSet();
            adapter.Fill(ds);

            if (ds.Tables[0].Rows.Count == 0)
            {
                // insert
                query = "INSERT INTO aile (emplid, wkgid, calmonth, calyear, taux)" ;
                query += " VALUES (" + emplid + "," + wkgid + "," + month + "," + year + "," + taux + ")";
            }
            else
            {
                // update
                query = "UPDATE aile SET taux = taux * " + taux;
                query += " WHERE emplid = "              + emplid;
                query += " AND wkgid = "                 + wkgid;
                query += " AND calmonth = "              + month;
                query += " AND calyear = "               + year;
            }

            // execute query
            cmd.CommandText = query;
            cmd.ExecuteNonQuery();
        }
    }
}
