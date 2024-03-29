package ch.processsoft;

import java.io.*;
import java.sql.*;
import java.util.*;

/**
* <p>Title: BatchMessages</p>
* <p>Description: get all the messages with deliverables in the queue (posted via SOAP) and write them in the correct eMessenger tables</p>
* <p>Copyright: Copyright (c) 2006</p>
* <p>Company: (March 2006) C�dric Michelet - Institut Icare</p>
* @author C�dric Michelet
* @version 1.0
* @author Auxilio Moren
* @version 1.1
* 
*/
public class BatchMessages
{
  protected String _configFilePath ;
  private int _lastProcID=0 ;

  // info to connect to the database
  protected String _className ;
  protected String _database ;
  protected String _user ;
  protected String _pwd ;
  protected String _alias;
    
  // statements
  protected PreparedStatement _psNewMessage=null ;
  protected PreparedStatement _psAddProcLog=null ;
  protected PreparedStatement _psAddDelivLog=null ;
  protected PreparedStatement _psGetProcID=null ;
  protected PreparedStatement _psGetDelivID=null ;
  protected PreparedStatement _psGetMessageDeliv=null ;
  protected PreparedStatement _psGetWkgID=null ;
  protected PreparedStatement _psGetLastID=null ;
  protected PreparedStatement _psUpdErrorMessage=null ;
  protected PreparedStatement _psUpdErrorDeliv=null ;
  protected PreparedStatement _psDelMessage=null ;
  protected PreparedStatement _psDelDeliv=null ;
  protected PreparedStatement _psAddMessageLog=null ;
  protected PreparedStatement _psAddMessageDelivLog=null ;
  protected PreparedStatement _psGetProcStandardTime=null ;
  protected PreparedStatement _psGetDelivStandardTime=null;
  protected PreparedStatement _psGetModelID=null ;
  protected PreparedStatement _psGetProcStableID=null;
  protected PreparedStatement _psGetDelivStableID=null;
  protected PreparedStatement _psGetInternalPrestationID=null;

  // set error to message
  protected int _error_currentError ;
  protected long _error_IdMessageInterne ;
  protected long _error_MessageDelivID ;

  // list of errors
  static public int ERROR_NO_ERROR=0 ;
  static public int ERROR_PROCID_NOT_FOUND=1 ;
  static public int ERROR_WKGID_NOT_FOUND=2 ;
  static public int ERROR_DELIVID_NOT_FOUND=3 ;
  static public int ERROR_WKGID_DELIV_NOT_FOUND=4 ;
  static public int ERROR_EXTERNPROCID_NOT_FOUND=5;
  static public int ERROR_EXTERNDELIVID_NOT_FOUND=6;
  static public int ERROR_PRESTATIONID_NOT_FOUND=7;
  static public int ERROR_MODELID_NOT_FOUND=8;

  /**
  * Constructor
  * @param ConfigFilePath
  */
  public BatchMessages(String ConfigFilePath, String Alias)
  {
    _configFilePath = ConfigFilePath;
    _alias = Alias;
  }

  public void run() throws Exception
  {
    Connection conn = null ;

    try
    {
      // load the database connection info
      this.loadConfig();

      // open a connection to the database
      conn = this.getConnection() ;

      // set in transaction mode
      conn.setAutoCommit(false) ;

      //create the statements
      this.createStatements(conn) ;

      // treat all the new arrived messages
      boolean hasNext = true ;
      while (hasNext)
      {
        hasNext = this.treatNextMessage(conn) ;
      }

      // close all statement
      this.deleteStatements() ;

      conn.close() ;
      conn = null ;
    }
    catch(Exception e)
    {
      this.deleteStatements() ;

      if (conn != null)
      {
        conn.close() ;
        conn = null ;
      }

      throw e;
    }
  }

  /**
  * Create the Prepared Statement
  * @param conn
  * @throws SQLException
  */
  protected void createStatements(Connection conn) throws SQLException
  {
    if (_psNewMessage == null)
      _psNewMessage = conn.prepareStatement("select * from MESSAGE where MessageErrorID is null LIMIT 0,1");

    if (_psAddProcLog == null)
      _psAddProcLog = conn.prepareStatement("insert into PROCLOG(ProcID,ExternSystemID,IdMessageInterne,WkgID,MessageTime,TempsStandard,CaseID, PrestationID, statut) values(?,?,?,?,?,?,?,?,?)");

    if (_psAddDelivLog == null)
      _psAddDelivLog = conn.prepareStatement("insert into DELIVLOG(IdProcLog,DelivID,MessageDelivID,WkgID,TempsStandard) values(?,?,?,?,?)");

    if (_psGetProcID == null)
      _psGetProcID = conn.prepareStatement("SELECT procid FROM pproc WHERE modelid = ? AND procstableid = ?");

    if (_psGetDelivID == null)
      _psGetDelivID = conn.prepareStatement("SELECT delivid FROM pdeliv WHERE modelid = ? AND delivstableid = ?");

    if (_psGetWkgID == null)
      _psGetWkgID = conn.prepareStatement("select w.wkgid from pworkgroup w join pproc p on p.wkgid=w.wkgparent join employeeaile ea on w.wkgid=ea.wkgid join externuser ext on ext.emplid = ea.emplid where p.procid= ? and FIND_IN_SET(?, ext.externuser) and ea.startdate <= ? and ea.enddate >= ? and ext.externsystemid = ? and w.wkgtype = 1 ");

    if (_psGetLastID == null)
      _psGetLastID = conn.prepareStatement("select last_insert_id()");

    if (_psUpdErrorMessage == null)
      _psUpdErrorMessage = conn.prepareStatement("update MESSAGE set MessageErrorID=? where IdMessageInterne=?");

    if (_psUpdErrorDeliv == null)
      _psUpdErrorDeliv = conn.prepareStatement("update MESSAGEDELIV set MessageErrorID=? where MessageDelivID=?");

    if (_psGetMessageDeliv == null)
      _psGetMessageDeliv = conn.prepareStatement("select MESSAGEDELIV.*, MESSAGE.externproctrans, MESSAGE.ExternSystemID from MESSAGEDELIV, MESSAGE where MESSAGEDELIV.IdMessageInterne=? AND MESSAGEDELIV.idMessageInterne = MESSAGE.idMEssageInterne");

    if (_psDelMessage == null)
      _psDelMessage = conn.prepareStatement("delete from MESSAGE where IdMessageInterne=?");

    if (_psDelDeliv == null)
      _psDelDeliv = conn.prepareStatement("delete from MESSAGEDELIV where IdMessageInterne=?");

    if(_psAddMessageLog == null)
      _psAddMessageLog = conn.prepareStatement("insert into MESSAGELOG(IDMessageInterne,ExternMessageID,ExternSystemID,ExternProcTrans,ExternUserID,TimeStampProc,MessageTime,Statut,CaseID,CaseIDRemark,PrestationID) values(?,?,?,?,?,?,?,?,?,?,?)");

    if (_psAddMessageDelivLog == null)
      _psAddMessageDelivLog = conn.prepareStatement("insert into MESSAGEDELIVLOG(MessageDelivID, IdMessageInterne,ExternDelivTrans,ExternUserID,TimestampDeliv,DoubleControl) values(?,?,?,?,?,?)");

    if (_psGetProcStandardTime == null)
      _psGetProcStandardTime = conn.prepareStatement("SELECT ppdattr.mvalue FROM ppdattr, pproc, pmodel WHERE pproc.pdattribid = ppdattr.pdattribid and ppdattr.attribdefid = 18350082 and pproc.procid = ? and pmodel.modelid = pproc.modelid and pmodel.modelid = ppdattr.modelid");

    if (_psGetDelivStandardTime == null)
      _psGetDelivStandardTime = conn.prepareStatement("SELECT ppdattr.mvalue FROM ppdattr, pdeliv, pmodel WHERE pdeliv.pdattribid = ppdattr.pdattribid and ppdattr.attribdefid = 15728641 and pdeliv.delivid = ? and pmodel.modelid = pdeliv.modelid and pmodel.modelid = ppdattr.modelid");

    if (_psGetModelID == null)
      _psGetModelID = conn.prepareStatement("SELECT pmodel.modelid FROM pmodel, externproc WHERE externproc.externproctrans = ? AND pmodel.modelref = externproc.modelref AND pmodel.isvalid = 1 AND pmodel.startdate <= ? AND (isnull(pmodel.enddate) OR pmodel.enddate >= ?)");

    if (_psGetProcStableID == null)
      _psGetProcStableID = conn.prepareStatement("SELECT procstableid FROM ExternProc WHERE ExternProcTrans = ?");

    if (_psGetDelivStableID == null)
      _psGetDelivStableID = conn.prepareStatement("SELECT delivstableid FROM ExternDeliv WHERE ExternDelivTrans = ?");

    if (_psGetInternalPrestationID == null)
      _psGetInternalPrestationID = conn.prepareStatement("SELECT * FROM externprestation WHERE externsystemID = ? AND externprestation = ?");
  }
	
  /**
  * Release the prepared statements
  */
  protected void deleteStatements() 
  {
    try
    {
      if (_psNewMessage != null)
      {
        _psNewMessage.close();
        _psNewMessage = null;
      }

      if (_psAddProcLog != null)
      {
        _psAddProcLog.close();
        _psAddProcLog = null;
      }

      if (_psAddDelivLog != null)
      {
        _psAddDelivLog.close();
        _psAddDelivLog = null;
      }

      if (_psGetProcID != null)
      {
        _psGetProcID.close();
        _psGetProcID = null;
      }

      if (_psGetDelivID != null)
      {
        _psGetDelivID.close();
        _psGetDelivID = null;
      }

      if (_psGetWkgID != null)
      {
        _psGetWkgID.close();
        _psGetWkgID = null;
      }

      if (_psGetLastID != null)
      {
        _psGetLastID.close();
        _psGetLastID = null;
      }

      if (_psUpdErrorMessage != null)
      {
        _psUpdErrorMessage.close();
        _psUpdErrorMessage = null;
      }

      if (_psUpdErrorDeliv != null)
      {
        _psUpdErrorDeliv.close();
        _psUpdErrorDeliv = null;
      }

      if (_psGetMessageDeliv != null)
      {
        _psGetMessageDeliv.close();
        _psGetMessageDeliv = null;
      }

      if (_psDelMessage != null)
      {
        _psDelMessage.close();
        _psDelMessage = null;
      }

      if(_psDelDeliv != null)
      {
        _psDelDeliv.close();
        _psDelDeliv = null;
      }

      if (_psAddMessageLog != null)
      {
        _psAddMessageLog.close();
        _psAddMessageLog = null;
      }

      if (_psAddMessageDelivLog != null)
      {
        _psAddMessageDelivLog.close();
        _psAddMessageDelivLog = null;
      }

      if (_psGetProcStandardTime != null)
      {
        _psGetProcStandardTime.close();
        _psGetProcStandardTime = null;
      }

      if (_psGetDelivStandardTime != null)
      {
        _psGetDelivStandardTime.close();
		_psGetDelivStandardTime = null;
      }

      if (_psGetModelID != null)
      {
        _psGetModelID.close();
        _psGetModelID = null;
      }

      if (_psGetProcStableID != null)
      {
        _psGetProcStableID.close();
        _psGetProcStableID = null;
      }

      if (_psGetDelivStableID != null)
      {
        _psGetDelivStableID.close();
        _psGetDelivStableID = null;
      }

      if (_psGetInternalPrestationID != null)
      {
        _psGetInternalPrestationID.close();
        _psGetInternalPrestationID = null;
      }
    }
    catch(Exception e)
    {
      // do nothing, because clausing the statement is not
      // so important when quitting the application
    }
  }

  /**
  * Check if we have a new message and treat it.
  * @param conn
  * @return return if there was a new message to treat
  */
  protected boolean treatNextMessage(Connection conn) throws SQLException
  {
    ResultSet rs;
    long IdProcLog;
    boolean ok;

    // reset the error system
    _error_currentError = ERROR_NO_ERROR;
    _error_IdMessageInterne = -1;
    _error_MessageDelivID = -1;

    // check if we have a new new message to treat
    rs = _psNewMessage.executeQuery();

    if (rs.next())
    {
      try
      {
        // archive the message and deliverables
        this.archiveInformation(rs);

        // add the message
        IdProcLog = this.addProcLog(rs.getLong("IdMessageInterne"), rs.getInt("ExternSystemID"), rs.getString("ExternProcTrans"), rs.getString("ExternUserID"), rs.getTimestamp("TimeStampProc"), rs.getTimestamp("MessageTime"), rs.getInt("CaseID"), rs.getInt("PrestationID"), rs.getInt("statut"));

        // does a validation error occured ?
        if (IdProcLog == -1)
        {
          // cancel previous database actions
          conn.rollback();

          // add the error into the database
          this.addError(conn);

          return true;
        }

        // add the deliverables
        ok = this.addDelivLog(IdProcLog, rs.getLong("IdMessageInterne"));

        // are all deliverables correctly inputed
        if (!ok)
        {
          // cancel previous database actions
          conn.rollback();

          // add the error into the database
          this.addError(conn);

          return true;
        }

        // remove from the input table
        this.deleteFromInput(rs.getLong("IdMessageInterne"));

        // commit the transaction
        conn.commit();

        rs.close();
        rs = null;

        return true;
      }
      catch(SQLException e)
      {
        // an error occured during the process
        // cancel all database action
        conn.rollback();
        rs.close();
        rs = null;

        // stop the process
        throw e;
      }
    }

    rs.close();
    rs = null;

    return false;
  }

  /**
  * Add the message in ProcLog with the correct params.
  * Return the id of the new message created or -1 if an error occured
  * @param IdMessageInterne
  * @param ExternSystemID
  * @param ExternProcID
  * @param TimeStampProc
  * @param MessageTime
  * @param CaseID
  * @return
  */
  protected long addProcLog(long IdMessageInterne, int ExternSystemID, String ExternProcTrans, String ExternUserID, Timestamp TimeStampProc, Timestamp MessageTime, int CaseID, int ExternPrestationID, int Status) throws SQLException
  {
    int IdProcLog;
    int ProcID;
    int ProcStableID;
    int WkgID;
    int ModelID;
    int InternalPrestationID;
    float TempsStandard;
    ResultSet rs;

    // first we get the modelid from the ExternProcID and TimeStamp
    ModelID = getModelID(ExternProcTrans, TimeStampProc);

    System.out.println("Modelid : " + ModelID);

    // if we didn't find a correct ProcStableID
    if (ModelID == -1)
    {
      // set the error
      _error_currentError = ERROR_MODELID_NOT_FOUND;
      _error_IdMessageInterne = IdMessageInterne;
      return -1;
    }

    // we get the internal procstableid from the externprocid using the mapping table ExternProc
    _psGetProcStableID.setString(1, ExternProcTrans);
    rs = _psGetProcStableID.executeQuery();

    if (rs.next())
      ProcStableID = rs.getInt("procstableid");
    else
      ProcStableID = -1;

    rs.close();
    rs = null;

    // if we didn't find a correct ProcStableID
    if (ProcStableID == -1)
    {
      // set the error
      _error_currentError = ERROR_EXTERNPROCID_NOT_FOUND;
      _error_IdMessageInterne = IdMessageInterne;
      return -1;
    }

    // find the internal procid
    _psGetProcID.setInt(1, ModelID);
    _psGetProcID.setInt(2, ProcStableID);

    rs = _psGetProcID.executeQuery();

    if (rs.next())
      ProcID = rs.getInt("ProcID");
    else
      ProcID = -1;

    rs.close();
    rs = null;

    // if we didn't find a correct ProcID
    if (ProcID == -1)
    {
      // set the error
      _error_currentError = ERROR_PROCID_NOT_FOUND;
      _error_IdMessageInterne = IdMessageInterne;

      return -1;
    }

    // archive for use in "add deliverables"
    _lastProcID = ProcID;
		
    // find the wkgid
    System.out.println("procid : " + ProcID + ";" + ExternUserID + ";" + TimeStampProc + ";" + ExternSystemID);

    WkgID = this.getWkgID(ProcID, ExternUserID, TimeStampProc, ExternSystemID);

    // if we didn't find a correct WkgID
    if (WkgID == -1)
    {
      // set the error
      _error_currentError = ERROR_WKGID_NOT_FOUND;
      _error_IdMessageInterne = IdMessageInterne;

      return -1;
    }
		
    // find the tempsstandard ONLY if status = 1 (final)
    if (Status == 1)
    {
      _psGetProcStandardTime.setInt(1, ProcID);
      rs = _psGetProcStandardTime.executeQuery();

      if(rs.next())
        TempsStandard = rs.getFloat("mvalue");
      else
        TempsStandard = 0;

      rs.close();
      rs = null;
    }
    else
      TempsStandard = 0;

    _psGetInternalPrestationID.setInt(1, ExternSystemID);
    _psGetInternalPrestationID.setInt(2, ExternPrestationID);
    rs = _psGetInternalPrestationID.executeQuery();

    if(rs.next())
      InternalPrestationID = rs.getInt("prestationid");
    else
      InternalPrestationID = -1;

    rs.close();
    rs = null;

    System.out.println("internalprestationID : " + InternalPrestationID);

    // if we didn't find a correct InternalPrestationID
    if (InternalPrestationID == -1)
    {
      // set the error
      _error_currentError = ERROR_PRESTATIONID_NOT_FOUND;
      _error_IdMessageInterne = IdMessageInterne;

      return -1;
    }

    //add to the database
    _psAddProcLog.setInt(1, ProcID);
    _psAddProcLog.setInt(2, ExternSystemID);
    _psAddProcLog.setLong(3, IdMessageInterne);
    _psAddProcLog.setInt(4, WkgID);
    _psAddProcLog.setTimestamp(5, MessageTime);
    _psAddProcLog.setFloat(6, TempsStandard);
    _psAddProcLog.setInt(7, CaseID);
    _psAddProcLog.setInt(8, InternalPrestationID);
    _psAddProcLog.setInt(9, Status);

    _psAddProcLog.execute();

    //get the new id
    rs = _psGetLastID.executeQuery();

    if (!rs.next())
    {
      throw new SQLException("Could not retrieve autoincrement ID after INSERT");
    }

    IdProcLog = rs.getInt(1);

    return IdProcLog;
  }
	
  /**
  * Add the messageDeliv linked to a message to the DelivLog table
  * Return if all the deliv where correctly added
  * @param IdProcLog
  * @param IdMessageInterne
  * @return
  * @throws SQLException
  */
  protected boolean addDelivLog(long IdProcLog, long IdMessageInterne) throws SQLException
  {
    int DelivID;
    int ModelID;
    int DelivStableID;
    float TempsStandard;
    int WkgID;
    ResultSet rs;
    ResultSet rs2;

    _psGetMessageDeliv.setLong(1, IdMessageInterne);
    rs = _psGetMessageDeliv.executeQuery();

    while (rs.next())
    {
      // get the corresponding modelid for the deliverable
      ModelID = getModelID(rs.getString("ExternProcTrans"), rs.getTimestamp("TimestampDeliv"));

      // we get the internal procstableid from the externprocid using the mapping table ExternProc
      _psGetDelivStableID.setString(1, rs.getString("ExternDelivTrans"));
      rs2 = _psGetDelivStableID.executeQuery();

      if (rs2.next())
        DelivStableID = rs2.getInt("delivstableid");
      else
        DelivStableID = -1;

      rs2.close();
      rs2 = null;

      // if we didn't find a correct DelivStableID
      if (DelivStableID == -1)
      {
        // set the error
        _error_currentError = ERROR_EXTERNDELIVID_NOT_FOUND;
        _error_IdMessageInterne = IdMessageInterne;

        return false;
      }

      // find the internal procid
      _psGetDelivID.setInt(1, ModelID);
      _psGetDelivID.setInt(2, DelivStableID);

      rs2 = _psGetDelivID.executeQuery();

      if (rs2.next())
        DelivID = rs2.getInt("DelivID");
      else
        DelivID = -1;

      rs2.close();
      rs2 = null;

      // if we didn't find a correct DelivID
      if (DelivID == -1)
      {
        // set the error
        _error_currentError = ERROR_DELIVID_NOT_FOUND;
        _error_IdMessageInterne = IdMessageInterne;
        _error_MessageDelivID = rs.getLong("MessageDelivID");

        rs.close();
        rs = null;

        return false;
      }

      // find the wkgid
      WkgID = this.getWkgID(_lastProcID, rs.getString("ExternUserID"), rs.getTimestamp("TimestampDeliv"), rs.getInt("ExternSystemID"));

      // find the wkgid
      System.out.println("wkgdeliv : " + _lastProcID + ";" + rs.getString("ExternUserID") + ";" + rs.getTimestamp("TimestampDeliv") + ";" + rs.getInt("ExternSystemID"));

      // if we didn't find a correct WkgID
      if (WkgID == -1)
      {
        // set the error
        _error_currentError = ERROR_WKGID_DELIV_NOT_FOUND;
        _error_IdMessageInterne = IdMessageInterne;
        _error_MessageDelivID = rs.getLong("MessageDelivID");

        rs.close();
        rs = null;

        return false;
      }

      // find the tempsstandard
      _psGetDelivStandardTime.setInt(1, DelivID);
      rs2 = _psGetDelivStandardTime.executeQuery();

      if(rs2.next())
        TempsStandard = rs2.getFloat("mvalue");
      else
        TempsStandard = 0;

      rs2.close();
      rs2 = null;

      // add to the database
      _psAddDelivLog.setLong(1, IdProcLog);
      _psAddDelivLog.setInt(2, DelivID);
      _psAddDelivLog.setLong(3, rs.getLong("MessageDelivID"));
      _psAddDelivLog.setInt(4, WkgID);
      _psAddDelivLog.setFloat(5, TempsStandard);
      _psAddDelivLog.execute();
    }

    rs.close();
    rs = null;

    return true;
  }

  /**
  * Return the workgoupid for a specific ProcID and User
  * The ExternUserID is a list of users separated by semi-colon ;
  * Take in account for the check, only the first user
  * @param ProcID
  * @param ExternUserID
  * @return
  */
  protected int getWkgID(int ProcID, String ExternUserID, Timestamp timestamp, int ExternSystemID) throws SQLException
  {
    int WkgID;
    ResultSet rs;

    if (ExternUserID.equals(""))
      return -1;
    else
    {
      // the list of users is separated by semi-colon
      String[] usersList = ExternUserID.split(";");

      if (usersList.length == 0)
        return -1;
      else
      {
        // extract the first user
        String EmplID = usersList[0];

        _psGetWkgID.setInt(1, ProcID);
        _psGetWkgID.setString(2,EmplID);
        _psGetWkgID.setTimestamp(3,timestamp);
        _psGetWkgID.setTimestamp(4,timestamp);
        _psGetWkgID.setInt(5,ExternSystemID);
        rs = _psGetWkgID.executeQuery();

        if (rs.next())
          WkgID = rs.getInt("wkgid");
        else
          WkgID = -1;

        rs.close ();
        rs = null;
      }
    }	

    return WkgID;
  }

  /**
  * Return the modelid corresponding to the ExternProcID and Timestamp
  * @param ExternProcID
  * @param timestamp
  * @return
  */
  protected int getModelID(String externProcTrans, Timestamp timestamp) throws SQLException
  {
    int ModelID;
    ResultSet rs;

    _psGetModelID.setString(1, externProcTrans);
    _psGetModelID.setTimestamp(2,timestamp);
    _psGetModelID.setTimestamp(3,timestamp);
    rs = _psGetModelID.executeQuery();

    if (rs.next())
      ModelID = rs.getInt("modelid");
    else
      ModelID = -1;

    rs.close();
    rs = null;

    return ModelID;
  }

  /**
  * Copy the from MESSAGE to MESSAGELOG and from MESSAGEDELIV to MESSAGEDELIVLOG
  * @param rs
  * @throws SQLException
  */
  protected void archiveInformation(ResultSet rs) throws SQLException
  {
    ResultSet rs2;

    // store the message
    _psAddMessageLog.setLong(1, rs.getLong("IdMessageInterne"));
    _psAddMessageLog.setString(2, rs.getString("ExternMessageID"));
    _psAddMessageLog.setInt(3, rs.getInt("ExternSystemID"));
    _psAddMessageLog.setString(4, rs.getString("ExternProcTrans"));
    _psAddMessageLog.setString(5, rs.getString("ExternUserID"));
    _psAddMessageLog.setTimestamp(6, rs.getTimestamp("TimeStampProc"));
    _psAddMessageLog.setTimestamp(7, rs.getTimestamp("MessageTime"));
    _psAddMessageLog.setInt(8, rs.getInt("Statut"));
    _psAddMessageLog.setInt(9, rs.getInt("CaseID"));
    _psAddMessageLog.setString(10, rs.getString("CaseIDRemark"));
    _psAddMessageLog.setInt(11, rs.getInt("PrestationID"));
    _psAddMessageLog.execute();

    // store all the deliv
    _psGetMessageDeliv.setLong(1, rs.getLong("IdMessageInterne"));
    rs2 = _psGetMessageDeliv.executeQuery();

    while(rs2.next())
    {
      _psAddMessageDelivLog.setLong(1, rs2.getLong("MessageDelivID"));
      _psAddMessageDelivLog.setLong(2, rs2.getLong("IdMessageInterne"));
      _psAddMessageDelivLog.setString(3, rs2.getString("ExternDelivTrans"));
      _psAddMessageDelivLog.setString(4, rs2.getString("ExternUserID"));
      _psAddMessageDelivLog.setTimestamp(5, rs2.getTimestamp("TimestampDeliv"));
      _psAddMessageDelivLog.setInt(6, rs2.getInt("DoubleControl"));
      _psAddMessageDelivLog.execute();
    }

    rs2.close();
    rs2 = null;
  }

  /**
  * Delete message and deliverable for the input table (SOAP)
  * @param IdMessageInterne
  */
  protected void deleteFromInput(long IdMessageInterne) throws SQLException
  {
    _psDelMessage.setLong(1, IdMessageInterne);
    _psDelMessage.execute();

    _psDelDeliv.setLong(1, IdMessageInterne);
    _psDelDeliv.execute();
  }

  /**
  * Write the current error into the database linked
  * to the correct message or deliverable
  */
  protected void addError(Connection conn) throws SQLException
  {
    try
    {
      if (_error_IdMessageInterne != -1)
      {
        _psUpdErrorMessage.setInt(1, _error_currentError);
        _psUpdErrorMessage.setLong(2, _error_IdMessageInterne);
        _psUpdErrorMessage.execute();
      }

      if (_error_IdMessageInterne != -1)
      {
        _psUpdErrorDeliv.setInt(1, _error_currentError);
        _psUpdErrorDeliv.setLong(2, _error_MessageDelivID);
        _psUpdErrorDeliv.execute();
      }

      conn.commit();
    }
    catch(SQLException e)
    {
      conn.rollback();
      throw e;
    }
  }

  /**
  * Create a new connection to the database
  * @return Connection
  * @throws ClassNotFoundException 
  * @throws SQLException 
  * @throws Exception
  */
  protected Connection getConnection() throws ClassNotFoundException, SQLException
  {
    Class.forName(_className);
    return DriverManager.getConnection(_database, _user, _pwd);
  }

  /**
  * Load the connection parameter from a file. The file must be located into the bin directory
  * and called configMEssagesSOAP.ini.
  * It's a text file with a new line for each information :
  * - database driver (default : org.gjt.mm.mysql.Driver)
  * - database connection string (default : jdbc:mysql://localhost/mercutio2)
  * - user name (default : root)
  * - password (default : <empty>)
  */
  protected void loadConfig()
  {
    // before reading, make sure that if something wrong happens, we have at least default value
    _className = "org.gjt.mm.mysql.Driver";
    _database = "jdbc:mysql://localhost/mercutio2";
    _user = "root";
    _pwd = "";

    try
    {
      File f = new File(_configFilePath);

      // if the file exists, read the different information
      if (f.exists())
      {
        Properties p = new Properties();
        p.load(new FileInputStream(f));

        // todo r�cup�rer le host depuis le fichier avec les alians
        _user = p.getProperty("user");
        _pwd = p.getProperty("pwd");
        _database = p.getProperty(_alias);
      }
      else
      {
        System.out.println("config file (" + _configFilePath + ") not found. Default values have been loaded.");
      }

      f = null;
    }
    catch(Exception e)
    {
      System.out.println("Error loading config file (" + _configFilePath + ") :" + e.getMessage());
      System.out.println("Default values have been loaded.");
    }
  }

  /**
  * @param args
  */
  public static void main(String[] args)
  {
    if (args.length != 2)
    {
      System.out.println("Please give 2 parameter (.bat [config_alias_file_path] [alias] ).");
      System.out.println("config_alias_file_path : path of the ini file containing the database and alias info.");
      System.out.println("alias : name of the database alias key");
      System.exit(0);
    }

    BatchMessages bm = new BatchMessages(args[0], args[1]);

    // treat all the new arrived messages
    try
    {
      bm.run();
    }
    catch (Exception e)
    {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }

    bm = null;
  }
}
