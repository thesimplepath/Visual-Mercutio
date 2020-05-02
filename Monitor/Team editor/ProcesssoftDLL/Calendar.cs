using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Calendar
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;

        public Calendar()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;
        }

        /// <summary>
        /// Get the EPT calendar calculated dataset for a specified year and team
        /// </summary>
        public DataSet GetDataSetEptTeamManual(int iYear, int iWkgid)
        {
            try
            {
                DataSet ds         = new DataSet();
                DataSet calendarDS = new DataSet();
                DataRow dr;
                String  query;

                calendarDS.Tables.Add();

                calendarDS.Tables[0].Columns.Add("Team",    System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month1",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month2",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month3",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month4",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month5",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month6",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month7",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month8",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month9",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month10", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month11", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month12", System.Type.GetType("System.String"));

                // add the new empty line
                dr = calendarDS.Tables[0].NewRow();

                // get the name of the team
                query = "SELECT wkgname from pworkgroup WHERE wkgid = " + iWkgid;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                dr["Team"] = ds.Tables[0].Rows[0]["wkgname"];

                // get the current manual ept for the team
                query  = "SELECT * FROM eptteammanual";
                query += " WHERE calyear = " + iYear;
                query += " AND wkgid = "     + iWkgid;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                ds.Clear();
                ds.Reset();

                m_Adapter.Fill(ds);

                dr["Month1"]  = 0;
                dr["Month2"]  = 0;
                dr["Month3"]  = 0;
                dr["Month4"]  = 0;
                dr["Month5"]  = 0;
                dr["Month6"]  = 0;
                dr["Month7"]  = 0;
                dr["Month8"]  = 0;
                dr["Month9"]  = 0;
                dr["Month10"] = 0;
                dr["Month11"] = 0;
                dr["Month12"] = 0;

                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                    dr["Month" + (ds.Tables[0].Rows[i]["calmonth"])] = ds.Tables[0].Rows[i]["eptvalue"];

                calendarDS.Tables[0].Rows.Add(dr);

                return calendarDS;
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Get the EPT Calendar calculated Dataset for a specified year and team
        /// </summary>
        public DataSet GetDataSetEptTeamAuto(int iYear, int iWkgid)
        {
            try
            {
                DataSet ds         = new DataSet();
                DataSet dsTeam     = new DataSet();
                DataSet calendarDS = new DataSet();
                DataSet dsEmployee = new DataSet();
                DataRow dr, drTotal;
                String  query;

                calendarDS.Tables.Add();

                calendarDS.Tables[0].Columns.Add("Participant", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month1",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month2",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month3",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month4",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month5",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month6",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month7",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month8",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month9",      System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month10",     System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month11",     System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month12",     System.Type.GetType("System.String"));

                drTotal = calendarDS.Tables[0].NewRow();

                drTotal[1]  = 0;
                drTotal[2]  = 0;
                drTotal[3]  = 0;
                drTotal[4]  = 0;
                drTotal[5]  = 0;
                drTotal[6]  = 0;
                drTotal[7]  = 0;
                drTotal[8]  = 0;
                drTotal[9]  = 0;
                drTotal[10] = 0;
                drTotal[11] = 0;
                drTotal[12] = 0;

                // get employees list for the team
                query  = "SELECT DISTINCT pemp.emplid, fname, lname";
                query += " FROM pemployee pemp, aile";
                query += " WHERE aile.emplid = pemp.emplid";
                query += " AND aile.wkgid = "   + iWkgid;
                query += " AND aile.calyear = " + iYear;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsEmployee);

                // employees main loop
                int     curEmplid;
                decimal curEPT = 0;

                for (int i = 0; i < dsEmployee.Tables[0].Rows.Count; ++i)
                {
                    // add the new empty line
                    dr = calendarDS.Tables[0].NewRow();

                    dr["Participant"] = dsEmployee.Tables[0].Rows[i]["fname"] + " " + dsEmployee.Tables[0].Rows[i]["lname"];
                    curEmplid         = Convert.ToInt32(dsEmployee.Tables[0].Rows[i]["emplid"]) ;

                    query  = "SELECT DISTINCT cal.calmonth, ec.daysplanned, aip.taux tauxaip, aile.taux tauxaile, aile.wkgid";
                    query += " FROM calendar cal";
                    query += " LEFT JOIN aip ON cal.calmonth = aip.calmonth AND cal.calyear = aip.calyear AND aip.emplid = "              + curEmplid;
                    query += " LEFT JOIN employeecalendar ec ON cal.calmonth = ec.calmonth AND cal.calyear = ec.calyear AND ec.emplid = " + curEmplid;
                    query += " LEFT JOIN aile ON cal.calmonth = aile.calmonth AND cal.calyear = aile.calyear AND aile.emplid = "          + curEmplid + " AND aile.wkgid = " + iWkgid;
                    query += " WHERE cal.calyear = 2006";
                    query += " ORDER BY cal.calmonth";

                    ds.Reset();
                    ds.Clear();

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                    m_Adapter.Fill(ds);

                    for (int j = 0; j < 12; j++)
                    {
                        if (Convert.IsDBNull(ds.Tables[0].Rows[j]["daysplanned"]))
                            curEPT = 0;
                        else
                            curEPT = Convert.ToDecimal(ds.Tables[0].Rows[j]["daysplanned"]);

                        if (! Convert.IsDBNull(ds.Tables[0].Rows[j]["tauxaip"]))
                            curEPT = curEPT * Convert.ToDecimal(ds.Tables[0].Rows[j]["tauxaip"]);

                        if (Convert.IsDBNull(ds.Tables[0].Rows[j]["tauxaile"]))
                            curEPT = 0;
                        else
                            curEPT = curEPT * Convert.ToDecimal(ds.Tables[0].Rows[j]["tauxaile"]);

                        dr["Month" + (j + 1)] = decimal.Round(curEPT,2);

                        // mise à jour du total du mois
                        drTotal["Month" + (j + 1)] = Convert.ToDecimal(drTotal["Month" + (j + 1)]) + Convert.ToDecimal(dr["Month" + (j + 1)]);

                    }

                    calendarDS.Tables[0].Rows.Add(dr);
                }

                dr = calendarDS.Tables[0].NewRow();
                calendarDS.Tables[0].Rows.Add(dr);

                drTotal["Participant"] = "TOTAL";

                calendarDS.Tables[0].Rows.Add(drTotal);

                return calendarDS;
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        /// <summary>
        /// Get the Calendar Dataset for a specified year
        /// </summary>
        public DataSet GetDataSet(int iYear, int iEmplid)
        {
            try
            {
                DataSet ds         = new DataSet();
                DataSet dsTeam     = new DataSet();
                DataSet calendarDS = new DataSet();
                DataRow dr;
                String  query;

                calendarDS.Tables.Add();

                calendarDS.Tables[0].Columns.Add("Equipe",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Libelle", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month1",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month2",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month3",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month4",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month5",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month6",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month7",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month8",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month9",  System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month10", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month11", System.Type.GetType("System.String"));
                calendarDS.Tables[0].Columns.Add("Month12", System.Type.GetType("System.String"));

                // days available
                dr    = calendarDS.Tables[0].NewRow();
                query = "SELECT * FROM Calendar WHERE calyear = " + iYear + " ORDER BY calmonth";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                dr["Libelle"] = "Jours disponibles";

                for (int i = 0; i < ds.Tables[0].Rows.Count; ++i)
                    dr["Month" + (i + 1)] = ds.Tables[0].Rows[i]["daysavailable"];

                calendarDS.Tables[0].Rows.Add(dr);

                // employee expected presence
                dr    = calendarDS.Tables[0].NewRow();
                query = "SELECT * FROM employeecalendar WHERE calyear = " + iYear + " AND emplid = " + iEmplid + " ORDER BY calmonth";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                ds.Reset();
                m_Adapter.Fill(ds);

                dr["Libelle"] = "Présence prévue";

                for (int i = 0; i < ds.Tables[0].Rows.Count; ++i)
                    dr["Month" + (i + 1)] = ds.Tables[0].Rows[i]["daysplanned"];

                calendarDS.Tables[0].Rows.Add(dr);

                // update the empty presence
                for (int i = 0; i < 12; ++i)
                    if (Convert.ToString(calendarDS.Tables[0].Rows[1]["Month" + (i + 1)]) == "")
                        calendarDS.Tables[0].Rows[1]["Month" + (i + 1)] = calendarDS.Tables[0].Rows[0]["Month" + (i + 1)];

                // AIP value
                dr    = calendarDS.Tables[0].NewRow();
                query = "SELECT * FROM aip WHERE calyear = " + iYear + " AND emplid = " + iEmplid + " ORDER BY calmonth";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                ds.Reset();
                m_Adapter.Fill(ds);

                dr["Libelle"] = "AIP";

                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                    dr["Month" + ds.Tables[0].Rows[i]["calmonth"]] = ds.Tables[0].Rows[i]["taux"];

                calendarDS.Tables[0].Rows.Add(dr);

                // update the empty AIP (set to 1.0)
                for (int i = 0; i < 12; ++i)
                    if (Convert.ToString(calendarDS.Tables[0].Rows[2]["Month" + (i + 1)]) == "")
                        calendarDS.Tables[0].Rows[2]["Month" + (i + 1)] = "1.0";

                // corrected presence
                dr            = calendarDS.Tables[0].NewRow();
                dr["Libelle"] = "Capacité personnelle";

                for (int i = 0; i < 12; i++)
                    dr["Month" + (i + 1)] =
                            Decimal.Round((Convert.ToDecimal(calendarDS.Tables[0].Rows[1]["Month" + (i + 1)]) * Convert.ToDecimal(calendarDS.Tables[0].Rows[2]["Month" + (i + 1)])), 2);

                calendarDS.Tables[0].Rows.Add(dr);

                // team AILE
                query  = "SELECT DISTINCT PWORKGROUP.wkgid, PWORKGROUP.wkgname FROM AILE, PWORKGROUP WHERE calyear = " + iYear + " AND emplid = " + iEmplid;
                query += " AND AILE.wkgID = PWORKGROUP.wkgid";
                query += " ORDER BY calmonth";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsTeam);

                for (int j = 0; j < dsTeam.Tables[0].Rows.Count; ++j)
                {
                    dr            = calendarDS.Tables[0].NewRow();
                    dr["Equipe"]  = dsTeam.Tables[0].Rows[j]["wkgname"];
                    dr["Libelle"] = "Aile";

                    query  = "SELECT PWORKGROUP.wkgid, PWORKGROUP.wkgname, AILE.* FROM AILE, PWORKGROUP WHERE calyear = " + iYear + " AND emplid = " + iEmplid;
                    query += " AND AILE.wkgID = PWORKGROUP.wkgid";
                    query += " AND AILE.wkgID = " + dsTeam.Tables[0].Rows[j]["wkgid"];
                    query += " ORDER BY calmonth";

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                    ds.Clear();
                    m_Adapter.Fill(ds);

                    for (int i = 0; i < ds.Tables[0].Rows.Count; ++i)
                        dr["Month" + ds.Tables[0].Rows[i]["calmonth"]] = ds.Tables[0].Rows[i]["taux"];

                    calendarDS.Tables[0].Rows.Add(dr);

                    // update the empty AILE (set to 0.0)
                    for (int i = 0; i < 12; ++i)
                        if (Convert.ToString(calendarDS.Tables[0].Rows[calendarDS.Tables[0].Rows.Count - 1]["Month" + (i + 1)]) == "")
                            calendarDS.Tables[0].Rows[calendarDS.Tables[0].Rows.Count - 1]["Month" + (i + 1)] = "0.0";

                    // create the corrected presence line for the current team
                    dr            = calendarDS.Tables[0].NewRow();
                    dr["Libelle"] = "Capacité pour l'équipe";

                    for (int i = 0; i < 12; ++i)
                        dr["Month" + (i + 1)] =
                                Decimal.Round(Convert.ToDecimal(calendarDS.Tables[0].Rows[calendarDS.Tables[0].Rows.Count - 1]["Month" + (i + 1)]) * Convert.ToDecimal(calendarDS.Tables[0].Rows[3]["Month" + (i + 1)]), 2);

                    calendarDS.Tables[0].Rows.Add(dr);
                }

                return calendarDS;
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }
    }
}
