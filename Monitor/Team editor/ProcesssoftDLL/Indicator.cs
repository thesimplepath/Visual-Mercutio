using System;
using MySql.Data.MySqlClient;
using System.Data;

namespace ProcesssoftDLL
{
    public class Indicator
    {
        private MySqlConnection  m_Connection;
        private MySqlDataAdapter m_Adapter;
        private string           m_ConnectionStr;

        public Indicator()
        {
            m_Connection = new MySqlConnection();
            m_Adapter    = new MySqlDataAdapter();

            System.Configuration.AppSettingsReader confAppSettings = new System.Configuration.AppSettingsReader();

            m_ConnectionStr               = (string)confAppSettings.GetValue("Processsoft.ConnectionString", typeof(string));
            m_Connection.ConnectionString = m_ConnectionStr;

        }

        /// <summary>
        /// Get list of Initial deliverable for MODELREF
        /// </summary>
        public DataSet GetInitialDelivList(String modelRef)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT DISTINCT pdeliv.delivname, pdeliv.delivstableid FROM pdeliv, pproc, pmodel";
                query += " WHERE pdeliv.procidsrc = pproc.procid";
                query += " AND pproc.proctype = 0";
                query += " AND pdeliv.modelid = pmodel.modelid";
                query += " AND pmodel.modelref = '" + modelRef + "'";

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
        /// Get list of procedure for MODELID
        /// </summary>
        public DataSet GetProcList(int modelID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT DISTINCT ppdattr.mvalue procname, procid FROM  pproc, ppdattr";
                query += " WHERE pproc.pdattribid = ppdattr.pdattribid";
                query += " AND ppdattr.attribdefid = 1310721";
                query += " AND pproc.modelid = " + modelID;

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
        /// Get list of process for MODELID
        /// </summary>
        public DataSet GetProcessList(int modelID)
        {
            try
            {
                string query;

                m_Connection.Open();

                query  = "SELECT DISTINCT ppdattr.mvalue processname, procid processid FROM  pproc, ppdattr";
                query += " WHERE pproc.pdattribid = ppdattr.pdattribid";
                query += " AND pproc.proctype = 4";
                query += " AND ppdattr.attribdefid = 1310721";
                query += " AND pproc.modelid = " + modelID;

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

        public DataSet QueryIndicatorNbrCasTraite(int processID, int year)
        {
            try
            {
                DataSet      ds                                = new DataSet();
                DataSet      dsForecastQuantity                = new DataSet();
                DataSet      dsPrestation                      = new DataSet();
                DataSet      dsProducedQuantity                = new DataSet();
                MySqlCommand cmd                               = new MySqlCommand();
                String       query, lstPrincipDelivName        = "";
                int          nbMonthProduced, posMonthProduced = 0;
                int          processStableID                   = 0;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query = "DELETE FROM indicnbrcastraite";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get the procstableid from procid
                query = " SELECT DISTINCT procstableid FROM pproc WHERE procid = " + processID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count > 0)
                    processStableID = Convert.ToInt32(ds.Tables[0].Rows[0]["procstableid"]);

                ds.Clear();
                ds.Reset();

                // get the name list of principal delivrables
                query  = "select * from ppdattr, pproc";
                query += " where pproc.pdattribid = ppdattr.pdattribid";
                query += " and procid = " + processID;
                query += " and pproc.modelid = ppdattr.modelid";
                query += " and attribdefid = 76021765"; // constant from conceptor

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                for (int i = 0; i < ds.Tables[0].Rows.Count; ++i)
                {
                    lstPrincipDelivName += ds.Tables[0].Rows[i]["mvalue"];

                    if (i != ds.Tables[0].Rows.Count - 1)
                        lstPrincipDelivName += "','";
                }

                ds.Clear();
                ds.Reset();

                // get the forecast quantity (sum of all deliverable -principal- for the process
                query  = "select pattribdef.attribdefname monthdescription, sum(round(ppdattr.mvalue)) quantity from pproc, pdeliv, ppdattr, pattribdef";
                query += " where ppdattr.pdattribid = pdeliv.pdattribid";
                query += " AND ppdattr.attribdefid in (49807362,49807363,49807364,49807365,49807366,49807367,49807368,49807369,49807370,49807371,49807372,49807373)";
                query += " and pdeliv.procidtrg = pproc.procid";
                query += " and pdeliv.modelid = ppdattr.modelid";
                query += " and pproc.procidprocessus = " + processID;
                query += " and pdeliv.modelid = pproc.modelid";
                query += " AND pattribdef.attribdefid = ppdattr.attribdefid";
                query += " AND pdeliv.delivname in ('"   + lstPrincipDelivName + "')";
                query += " GROUP BY monthdescription";
                query += " ORDER BY ppdattr.attribdefid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsForecastQuantity);

                // get the list of prestations with their % for this process
                query  = "select * from ppdattr, pproc";
                query += " where pproc.pdattribid = ppdattr.pdattribid";
                query += " and procid = " + processID;
                query += " and pproc.modelid = ppdattr.modelid";
                query += " and attribdefid in (73400321, 73400322)"; //constants from Conceptor (prestation name / prestation %)
                query += " order by prow";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsPrestation);

                 // cycle prestations
                for (int i = 0; i < dsPrestation.Tables[0].Rows.Count; ++i)
                {
                    // get the sum produced for that prestation
                    query  = "select month(messagetime) monthid, count(delivlogid) quantity from proclog, delivlog, pdeliv, pprestations";
                    query += " where proclog.idproclog = delivlog.idproclog";
                    query += " and delivlog.delivid = pdeliv.delivid";
                    query += " and pdeliv.delivname in ('"           + lstPrincipDelivName + "')";
                    query += " and proclog.prestationID = pprestations.prestationid";
                    query += " and pprestations.prestationtitle = '" + dsPrestation.Tables[0].Rows[i]["mvalue"] + "'";
                    query += " and year(messagetime) = "             + year ;
                    query += " group by monthid";
                    query += " order by monthid";

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                    dsProducedQuantity.Clear();
                    dsProducedQuantity.Reset();

                    m_Adapter.Fill(dsProducedQuantity);

                    nbMonthProduced = dsProducedQuantity.Tables[0].Rows.Count;
                    posMonthProduced = 0;

                    // cycle month
                    for (int j = 1; j <= 12; ++j)
                    {
                        // reference
                        query  = "INSERT INTO indicnbrcastraite (monthid, monthdesc, prestation, typequantity, quantity) VALUES (";
                        query += j;
                        query += " ,'" + dsForecastQuantity.Tables[0].Rows[j-1]["monthdescription"] + "'";
                        query += " ,'" + dsPrestation.Tables[0].Rows[i]["mvalue"]                   + "'";
                        query += " ,'Référence'";

                        // go to next record to get the % for this prestation (results are differents row in the same table)
                        ++i;

                        query += " , " + Convert.ToDecimal(dsForecastQuantity.Tables[0].Rows[j-1]["quantity"]) * Convert.ToDecimal(dsPrestation.Tables[0].Rows[i]["mvalue"]);
                        query += ")";

                        // go back to the previous record
                        --i;

                        cmd.CommandText = query;
                        cmd.ExecuteNonQuery();

                        // produced
                        query  = "INSERT INTO indicnbrcastraite (monthid, monthdesc, prestation, typequantity, quantity) VALUES (";
                        query += j;
                        query += " ,'" + dsForecastQuantity.Tables[0].Rows[j - 1]["monthdescription"] + "'";
                        query += " ,'" + dsPrestation.Tables[0].Rows[i]["mvalue"] + "'";
                        query += " ,'Réalisé'";

                        if (nbMonthProduced > 0 && posMonthProduced < nbMonthProduced && j == Convert.ToInt32(dsProducedQuantity.Tables[0].Rows[posMonthProduced]["monthid"]))
                        {
                            query += " , " + dsProducedQuantity.Tables[0].Rows[posMonthProduced]["quantity"];
                            ++posMonthProduced;
                        }
                        else
                            query += " , 0";

                        query += ")";

                        cmd.CommandText = query;
                        cmd.ExecuteNonQuery();
                    }

                    // go 1 step forward to go to the next "prestation name" (avoid the prestation % record)
                    ++i;
                }

                ds.Clear();
                ds.Reset();

                query = "SELECT * FROM indicnbrcastraite";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

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

        public DataSet QueryIndicatorCasProcTeam(int procid, int year)
        {
            try
            {
                DataSet      dsTeam             = new DataSet();
                DataSet      dsForecastQuantity = new DataSet();
                DataSet      dsProducedQuantity = new DataSet();
                DataSet      ds                 = new DataSet();
                MySqlCommand cmd                = new MySqlCommand();
                Pworkgroup   pWorkgroup         = new Pworkgroup();
                string       query;
                string       delivNameSrcList;
                int          nbMonthProduced, posMonthProduced;
                int          procstableID       = 0;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query = "DELETE FROM indiccasprocteam";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get the procstableid from procid
                query = " SELECT DISTINCT procstableid FROM pproc WHERE procid = " + procid;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count > 0)
                    procstableID = Convert.ToInt32(ds.Tables[0].Rows[0]["procstableid"]);

                ds.Clear();
                ds.Reset();

                // get livrabletrg from procedure
                query  = "select replace(ppdattr.mvalue, ';', \"','\") mvalue from ppdattr, pproc";
                query += " where ppdattr.pdattribid = pproc.pdattribid";
                query += " and pproc.procid = " + procid;
                query += " and ppdattr.attribdefid = 31457282";
                query += " and pproc.modelid = ppdattr.modelid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                delivNameSrcList = ds.Tables[0].Rows[0]["mvalue"].ToString();

                ds.Clear();
                ds.Reset();

                // get the forecast quantity for the procedure
                query  = "select pattribdef.attribdefname monthdescription, sum(round(ppdattr.mvalue)) quantity from pproc, pdeliv, ppdattr, pattribdef";
                query += " where ppdattr.pdattribid = pdeliv.pdattribid";
                query += " AND ppdattr.attribdefid in (49807362,49807363,49807364,49807365,49807366,49807367,49807368,49807369,49807370,49807371,49807372,49807373)";
                query += " and pproc.procid = " + procid;
                query += " and pdeliv.procidtrg = pproc.procid";
                query += " and pdeliv.modelid = ppdattr.modelid";
                query += " and pdeliv.modelid = pproc.modelid";
                query += " AND pattribdef.attribdefid = ppdattr.attribdefid";
                query += " AND pdeliv.delivname in ('" + delivNameSrcList + "')";
                query += " GROUP BY monthdescription";
                query += " ORDER BY ppdattr.attribdefid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsForecastQuantity);

                // get the list of team by procid
                dsTeam = pWorkgroup.GetListTeamByProcID(procid);

                // cycle teams
                for (int i = 0; i < dsTeam.Tables[0].Rows.Count; ++i)
                {
                    // get the sum produced by team for that procedure
                    query  = "select month(messagetime) monthid, count(idproclog) quantity from proclog, pproc";
                    query += " where proclog.procid = pproc.procid";
                    query += " and pproc.procstableid = " + procstableID;
                    query += " and year(messagetime) = "  + year ;
                    query += " and proclog.statut = 1";
                    query += " and proclog.wkgid = "      + dsTeam.Tables[0].Rows[i]["wkgid"];
                    query += " group by monthid";
                    query += " order by monthid";

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                    dsProducedQuantity.Clear();
                    dsProducedQuantity.Reset();

                    m_Adapter.Fill(dsProducedQuantity);

                    nbMonthProduced = dsProducedQuantity.Tables[0].Rows.Count;
                    posMonthProduced = 0;

                    // cycle month
                    for (int j = 1; j <= 12; ++j)
                    {
                        // reference
                        query  = "INSERT INTO indiccasprocteam (monthid, monthdesc, team, typequantity, quantity) VALUES (";
                        query += j;
                        query += " ,'" + dsForecastQuantity.Tables[0].Rows[j-1]["monthdescription"] + "'";
                        query += " ,'" + dsTeam.Tables[0].Rows[i]["wkgname"] + "'";
                        query += " ,'Référence'";
                        query += " , " + Convert.ToDecimal(dsForecastQuantity.Tables[0].Rows[j-1]["quantity"]) * Convert.ToInt32(dsTeam.Tables[0].Rows[i]["wkgpercent"]) / 100;
                        query += ")";

                        cmd.CommandText = query;
                        cmd.ExecuteNonQuery();

                        // produced
                        query  = "INSERT INTO indiccasprocteam (monthid, monthdesc, team, typequantity, quantity) VALUES (";
                        query += j;
                        query += " ,'" + dsForecastQuantity.Tables[0].Rows[j - 1]["monthdescription"] + "'";
                        query += " ,'" + dsTeam.Tables[0].Rows[i]["wkgname"] + "'";
                        query += " ,'Réalisé'";

                        if (nbMonthProduced > 0 && posMonthProduced < nbMonthProduced && j == Convert.ToInt32(dsProducedQuantity.Tables[0].Rows[posMonthProduced]["monthid"]))
                        {
                            query += " , " + dsProducedQuantity.Tables[0].Rows[posMonthProduced]["quantity"];
                            ++posMonthProduced;
                        }
                        else
                            query += " , 0";

                        query += ")";

                        cmd.CommandText = query;
                        cmd.ExecuteNonQuery();
                    }

                }

                ds.Clear();
                ds.Reset();

                query = "SELECT * FROM indiccasprocteam";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

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

        public DataSet QueryIndicatorStock(int processID, int year)
        {
            try
            {
                DataSet      ds                         = new DataSet();
                DataSet      dsForecastQuantity         = new DataSet();
                DataSet      dsProducedQuantity         = new DataSet();
                MySqlCommand cmd                        = new MySqlCommand();
                String       query, lstPrincipDelivName = "";
                int          processStableID            = 0;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query = "UPDATE indicstock SET produced = 0, forecast = 0";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get the procstableid from procid
                query = " SELECT DISTINCT procstableid FROM pproc WHERE procid = " + processID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count > 0)
                    processStableID = Convert.ToInt32(ds.Tables[0].Rows[0]["procstableid"]);

                ds.Clear();
                ds.Reset();

                // get the name list of principal delivrables
                query  = "select * from ppdattr, pproc";
                query += " where pproc.pdattribid = ppdattr.pdattribid";
                query += " and procid = " + processID;
                query += " and pproc.modelid = ppdattr.modelid";
                query += " and attribdefid = 76021765"; // constant from conceptor

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                for (int i = 0; i < ds.Tables[0].Rows.Count; ++i)
                {
                    lstPrincipDelivName += ds.Tables[0].Rows[i]["mvalue"];

                    if (i != ds.Tables[0].Rows.Count - 1)
                        lstPrincipDelivName += "','";
                }

                ds.Clear();
                ds.Reset();

                // get the forecast quantity (sum of all deliverable -principal- for the process
                query  = "select pattribdef.attribdefname monthdescription, sum(round(ppdattr.mvalue)) quantity from pproc, pdeliv, ppdattr, pattribdef";
                query += " where ppdattr.pdattribid = pdeliv.pdattribid";
                query += " AND ppdattr.attribdefid in (49807362,49807363,49807364,49807365,49807366,49807367,49807368,49807369,49807370,49807371,49807372,49807373)";
                query += " and pdeliv.procidtrg = pproc.procid";
                query += " and pdeliv.modelid = ppdattr.modelid";
                query += " and pproc.procidprocessus = " + processID;
                query += " and pdeliv.modelid = pproc.modelid";
                query += " AND pattribdef.attribdefid = ppdattr.attribdefid";
                query += " AND pdeliv.delivname in ('"   + lstPrincipDelivName + "')";
                query += " GROUP BY monthdescription";
                query += " ORDER BY ppdattr.attribdefid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsForecastQuantity);

                query  = "select month(messagetime) monthid, count(delivlogid) quantity from proclog, delivlog, pdeliv";
                query += " where proclog.idproclog = delivlog.idproclog";
                query += " and delivlog.delivid = pdeliv.delivid";
                query += " and pdeliv.delivname in ('" + lstPrincipDelivName + "')";
                query += " and year(messagetime) = "   + year ;
                query += " group by monthid";
                query += " order by monthid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsProducedQuantity);

                // update new records produced value from monitor
                for (int i = 0; i < dsProducedQuantity.Tables[0].Rows.Count; ++i)
                {
                    query  = "UPDATE indicstock SET produced = " + dsProducedQuantity.Tables[0].Rows[i]["quantity"];
                    query += " WHERE monthid = "                 + dsProducedQuantity.Tables[0].Rows[i]["monthid"];

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }

                // update new records forecast value from conceptor
                for (int i = 0; i < dsForecastQuantity.Tables[0].Rows.Count; ++i)
                {
                    query  = "UPDATE indicstock SET forecast = " + dsForecastQuantity.Tables[0].Rows[i]["quantity"];
                    query += " WHERE month = '"                  + dsForecastQuantity.Tables[0].Rows[i]["monthdescription"] + "'";

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }

                ds.Clear();
                ds.Reset();

                query = "SELECT * FROM indicstock";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

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

        public void AddLabel(int year, string label)
        {
            try
            {
                MySqlCommand cmd = new MySqlCommand();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete old value
                query           = "DELETE FROM indiclabel";
                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // insert new label
                query = "INSERT INTO indiclabel (labelyear, labeltext) VALUES (" + year + ",'" + label + "')";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                m_Connection.Close();
                throw (e);
            }
        }

        public DataSet QueryIndicatorProductivityTeam(int wkgID, int year, int modelID, int flagManual)
        {
            try
            {
                DataSet      ds         = new DataSet();
                DataSet      dsManual   = new DataSet();
                DataSet      dsAuto     = new DataSet();
                DataSet      dsProduced = new DataSet();
                MySqlCommand cmd        = new MySqlCommand();
                Pworkgroup   pWorkgroup = new Pworkgroup();
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                // delete of old records
                query = "UPDATE indicproducteam SET forecast = 0, produced = 0";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // check if we have to take the Manual calendar or Auto-Calculated Calendar of the team
                if (flagManual == 0)
                {
                    // auto-calculated calendar
                    Calendar cal        = new Calendar();
                    dsAuto              = cal.GetDataSetEptTeamAuto(year, wkgID);
                    int      indexTotal = dsAuto.Tables[0].Rows.Count - 1;

                    for (int j = 1; j <= 12; ++j)
                    {
                        query  = "UPDATE indicproducteam SET forecast = " + dsAuto.Tables[0].Rows[indexTotal]["Month" + j].ToString();
                        query += " WHERE monthid = " + j;

                        cmd.CommandText = query;
                        cmd.ExecuteNonQuery();
                    }

                    cal = null;
                }
                else
                {
                    // manual calendar
                    Calendar cal = new Calendar();
                    dsManual     = cal.GetDataSetEptTeamManual(year, wkgID);

                    for (int i = 0; i < dsManual.Tables[0].Rows.Count; ++i)
                        for (int j = 1; j <= 12; ++j)
                        {
                            query  = "UPDATE indicproducteam SET forecast = " + dsManual.Tables[0].Rows[i]["Month" + j].ToString();
                            query += " WHERE monthid = " + j;

                            cmd.CommandText = query;
                            cmd.ExecuteNonQuery();
                        }
                }

                // get the produced charge for the year and team
                query  = "select month(messagetime) monthid, sum(tempsstandard) quantity from proclog, pproc";
                query += " where proclog.procid = pproc.procid";
                query += " and year(messagetime) = " + year;
                query += " and proclog.wkgid = "     + wkgID;
                query += " group by monthid";
                query += " order by monthid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);
                m_Adapter.Fill(dsProduced);

                // update the produced charge value
                for (int i = 0; i < dsProduced.Tables[0].Rows.Count; ++i)
                {
                    query  = "UPDATE indicproducteam SET produced = " + dsProduced.Tables[0].Rows[i]["quantity"];
                    query += " WHERE monthid = "                      + dsProduced.Tables[0].Rows[i]["monthid"];

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }

                // query the new table and return the results
                ds.Clear();
                ds.Reset();

                query = "SELECT * FROM indicproducteam";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

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

        public DataSet QueryIndicatorChargeTeam(int wkgID, int year, int modelID)
        {
            try
            {
                DataSet      dsProc                 = new DataSet();
                DataSet      dsForecastCharge       = new DataSet();
                DataSet      dsProducedCharge       = new DataSet();
                DataSet      ds                     = new DataSet();
                MySqlCommand cmd                    = new MySqlCommand();
                Pworkgroup   pWorkgroup             = new Pworkgroup();
                int          curDelivID, curPercent = 0 ;
                Decimal[]    arrayForecastCharge    = new Decimal[13] ;
                string       query;

                m_Connection.Open();

                cmd.Connection = m_Connection;

                for (int i = 1; i <= 12; ++i)
                    arrayForecastCharge[i] = 0;

                // delete of old records
                query = "UPDATE indicchargeteam SET forecast = 0, produced = 0";

                cmd.CommandText = query;
                cmd.ExecuteNonQuery();

                // get the % of the team in the group
                query = " select * from pworkgroup where wkgID = " + wkgID;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(ds);

                if (ds.Tables[0].Rows.Count != 0)
                    curPercent = Convert.ToInt32(ds.Tables[0].Rows[0]["wkgpercent"]);

                // get procid and procstableid and total charge for procedure for each procedures linked with current team
                query  = "select pproc.*, ppdattr.mvalue activation, ppdattr2.mvalue charge from pproc, pworkgroup, ppdattr, ppdattr ppdattr2";
                query += " where pproc.wkgid = pworkgroup.wkgparent";
                query += " and pproc.pdattribid = ppdattr.pdattribid";
                query += " and pproc.pdattribid = ppdattr2.pdattribid";
                query += " and ppdattr.modelid = pproc.modelid";
                query += " and ppdattr2.modelid = pproc.modelid";
                query += " and ppdattr.attribdefid = 36700161";  // constant from conceptor -> number of activation
                query += " and ppdattr2.attribdefid = 36700163"; // constant from conceptor -> charge in days
                query += " and pworkgroup.wkgid = " + wkgID;
                query += " and pproc.proctype = 2";              // only standard procedure. not start / not end
                query += " and pproc.modelid = "    + modelID ;

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                m_Adapter.Fill(dsProc) ;

                // for each procedure
                for (int i = 0; i < dsProc.Tables[0].Rows.Count; ++i)
                {
                    // get one of the deliverables (out)
                    query = "select * from pdeliv where procidsrc = " + dsProc.Tables[0].Rows[i]["procid"] + "  and lateral = 0";

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

                    ds.Clear();
                    ds.Reset();

                    m_Adapter.Fill(ds);

                    if (ds.Tables[0].Rows.Count != 0)
                        curDelivID = Convert.ToInt32(ds.Tables[0].Rows[0]["delivid"]);
                    else
                        curDelivID = 0;

                    // get the charge distribution by month using the %
                    query  = "select pattribdef.attribdefname monthdescription, sum(round(ppdattrdeliv.mvalue)) / " + dsProc.Tables[0].Rows[i]["activation"] + " * " + dsProc.Tables[0].Rows[i]["charge"] + " charge";
                    query += " from pdeliv, ppdattr ppdattrdeliv, pattribdef";
                    query += " where ppdattrdeliv.pdattribid = pdeliv.pdattribid";
                    query += " AND ppdattrdeliv.attribdefid in (49807362,49807363,49807364,49807365,49807366,49807367,49807368,49807369,49807370,49807371,49807372,49807373)"; // constant month from conceptor
                    query += " and pdeliv.modelid = ppdattrdeliv.modelid";
                    query += " AND pattribdef.attribdefid = ppdattrdeliv.attribdefid";
                    query += " AND pdeliv.delivid = " + curDelivID;
                    query += " GROUP BY monthdescription";
                    query += " ORDER BY ppdattrdeliv.attribdefid";

                    dsForecastCharge.Clear();
                    dsForecastCharge.Reset();

                    m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);
                    m_Adapter.Fill(dsForecastCharge);

                    // add to the total forcast
                    for (int j = 0; j < dsForecastCharge.Tables[0].Rows.Count; ++j)
                        // curPercent = percent of the team in the group
                        arrayForecastCharge[j + 1] += Convert.ToDecimal(dsForecastCharge.Tables[0].Rows[j]["charge"]) * curPercent / 100;
                }

                // update the forecast charge value
                for (int i = 1; i <= 12; ++i)
                {
                    query  = "UPDATE indicchargeteam SET forecast = " + arrayForecastCharge[i];
                    query += " WHERE monthid = " + i;

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }

                // get the produced charge for the year and team
                query  = "select month(messagetime) monthid, sum(tempsstandard) quantity from proclog, pproc";
                query += " where proclog.procid = pproc.procid";
                query += " and year(messagetime) = " + year;
                query += " and proclog.wkgid = "     + wkgID;
                query += " group by monthid";
                query += " order by monthid";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);
                m_Adapter.Fill(dsProducedCharge);

                // update the produced charge value
                for (int i = 0; i < dsProducedCharge.Tables[0].Rows.Count; ++i)
                {
                    query  = "UPDATE indicchargeteam SET produced = " + dsProducedCharge.Tables[0].Rows[i]["quantity"];
                    query += " WHERE monthid = "                      + dsProducedCharge.Tables[0].Rows[i]["monthid"];

                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }

                // query the new table and return the results
                ds.Clear();
                ds.Reset();

                query = "SELECT * FROM indicchargeteam";

                m_Adapter.SelectCommand = new MySqlCommand(query, m_Connection);

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
