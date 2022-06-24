import java.lang.* ;
import java.util.* ;
import java.io.* ;
import java.sql.* ;
import java.text.* ;

import org.w3c.dom.Document;
import org.w3c.dom.*;
import org.xml.sax.InputSource ;

import javax.xml.parsers.* ;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 *
 * <p>Title: MessageSOAP</p>
 *
 * <p>Description: expose a method through SOAP in order add new messages (with deliverable) for external system into eMessenger</p>
 *
 * <p>Copyright: Copyright (c) 2006</p>
 *
 * <p>Company: (March 2006) Cédric Michelet - Institut Icare</p>
 *
 * @author not attributable
 * @version 1.0
 */
public class MessagesSOAP
{
     protected int _current_error ; //error to return
     protected Connection _conn = null ;
     protected DateFormat _df ; //to format from string to java.sql.date
     //info to connect to the database
     protected String _className ;
     protected String _database ;
     protected String _user ;
     protected String _pwd ;
     protected String _alias;

      //list of errors
      static public int ERROR_NO_ERROR=0 ;
      static public int ERROR_UNKNOW_ERROR=1 ;
      static public int ERROR_STATUT_NOT_VALID=2 ;
      static public int ERROR_TIME_STAMP_PROC_NOT_VALID=3 ;
      static public int ERROR_MESSAGE_DELIV_DOUBLECONTROL_NOT_VALID=4 ;
      static public int ERROR_MESSAGE_DELIV_TIMESTAMP_NOT_VALID=5 ;


      /**
       * Allow to insert 1 message (with n deliverables) into the database.
       * The parameter is an XML-file into a string
       * @param messagesAsXML String
       * @return int
       */
      public int sendMessage(String messagesAsXML, String sAlias)
        {
          NodeList listOfElements, listOfElementsMsg, listOfAttributes ;
          Node element ;
          String ExternDelivTrans, ExternUserID, TimestampDeliv, DoubleControl ;
          int message_id ;
		  
		  _alias = sAlias;

        try
        {
                //load the database connection info
                this.loadConfig();
                //open a connection to the database
                _conn = this.getConnection() ;

                _current_error = this.ERROR_UNKNOW_ERROR ;

                //set connection in transaction mode
                _conn.setAutoCommit(false);

                //_df = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss") ;
				_df = new SimpleDateFormat("yyyyMMdd HHmmss") ;

                //load the xml reader
                DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
                Document doc = docBuilder.parse(new InputSource(new StringReader(messagesAsXML)));

                 // normalize text representation
                doc.getDocumentElement().normalize();

                /*****message******/
                listOfElementsMsg = doc.getElementsByTagName("message");
				
				for(int j=0; j<listOfElementsMsg.getLength(); j++)
					{
				
	                //NamedNodeMap attr = listOfElements.item(0).getAttributes();
					NamedNodeMap attr = listOfElementsMsg.item(j).getAttributes();
	                message_id = this.addMessage(getAttributeText(attr, "externmessageid"),getAttributeText(attr, "externsystemid"),getAttributeText(attr, "externprocid"),getAttributeText(attr, "externuserid"),getAttributeText(attr, "timestampproc"),getAttributeText(attr, "messagetime"),getAttributeText(attr, "statut"),getAttributeText(attr, "caseid"),getAttributeText(attr, "caseidremark"),getAttributeText(attr,"externprestationid")) ;
	
	                /*****message deliv*****/
	                listOfElements = listOfElementsMsg.item(j).getChildNodes();
	
	                for(int i=0; i<listOfElements.getLength(); i++)
	               		{
	                        element = listOfElements.item(i);
	                        if(element.getNodeType() == Node.ELEMENT_NODE)
	                        {
	                                ExternDelivTrans = element.getAttributes().getNamedItem("externdelividint").getNodeValue() ;
	                                ExternUserID = element.getAttributes().getNamedItem("externuserid").getNodeValue() ;
	                                TimestampDeliv = element.getAttributes().getNamedItem("timestampdeliv").getNodeValue() ;
	                                DoubleControl = element.getAttributes().getNamedItem("doublecontrol").getNodeValue() ;
	                                this.addDeliv(message_id, ExternDelivTrans, ExternUserID, TimestampDeliv, DoubleControl) ;
	                        }
	                	}
						
					_conn.commit() ;
					}
				

                _conn.close() ;

                return ERROR_NO_ERROR ;
                }
        catch(Exception e)
                {
                  try
                  {
                    //close connection if needed
                    if (_conn != null) {
                      _conn.rollback();
                      _conn.close();
                    }
                  }
                  catch (Exception ex) {}

                System.out.println("ERROR : " + e.getMessage()) ;
                return _current_error ;
                }
        }

        /**
       * Gets the text from an attribute map.
       */
      private String getAttributeText(NamedNodeMap map, String attr) {
          Node node = map.getNamedItem(attr);
          if(node != null)
              return node.getNodeValue();
          else
              return null;
      }

      /**
       * Add a new message into the database
       * @param ExternMessageID String
       * @param ExternSystemID String
       * @param ExternProcID String
       * @param ExternUserID String
       * @param TimestampProc String
       * @param MessageTime String
       * @param Statut String
       * @param CaseID String
       * @param CaseIDRemark String
       * @return int
       * @throws Exception
       */
      protected int addMessage(String ExternMessageID, String ExternSystemID, String ExternProcTrans, String ExternUserID, String TimestampProc, String MessageTime, String Statut, String CaseID, String CaseIDRemark, String ExternPrestationID) throws Exception
      {
        //int l_ExternMessageID ;
        //int l_ExternProcID ;
        int l_ExternSystemID ;
        int l_Statut ;
        int l_CaseID ;
		int l_ExternPrestationID;
        java.sql.Timestamp d_TimeStampProc ;
        java.sql.Timestamp d_MessageTime ;
        PreparedStatement ps ;
        ResultSet rs ;
        int id_message ;

        System.out.println("Message : " + ExternMessageID + " " + ExternSystemID + " " + ExternProcTrans + " " + ExternUserID + " " + TimestampProc + " " + MessageTime + " " + Statut + " " + CaseID + " " + CaseIDRemark+ " " + ExternPrestationID) ;
		
		/*if (true)
			return -1;*/
		
        //convert into int the param as string
        //l_ExternMessageID = Integer.parseInt(ExternMessageID);
        //l_ExternProcID = Integer.parseInt(ExternProcID);
        l_ExternSystemID = Integer.parseInt(ExternSystemID) ;
        l_Statut = Integer.parseInt(Statut);
        l_CaseID = Integer.parseInt(CaseID);
		l_ExternPrestationID = Integer.parseInt(ExternPrestationID);

        //*************check the params
        if (l_Statut < 0 || l_Statut > 2)
           {
               _current_error = ERROR_STATUT_NOT_VALID ;
               throw new Exception("Statut is not valid : " + Statut) ;
             }
          try {
            d_TimeStampProc = new java.sql.Timestamp(_df.parse(TimestampProc).getTime()) ;
          }
          catch (ParseException pe) {
            _current_error= ERROR_TIME_STAMP_PROC_NOT_VALID;
            throw new Exception("Timestamp is not valid : " + TimestampProc) ;
          }
          try {
            d_MessageTime = new java.sql.Timestamp(_df.parse(MessageTime).getTime());
          }
          catch (ParseException pe) {
            _current_error = ERROR_TIME_STAMP_PROC_NOT_VALID;
            throw new Exception("Messagetime is not valid : " + MessageTime) ;
          }

          //******************insert the message
           ps = _conn.prepareStatement("insert into MESSAGE(ExternMessageID,ExternSystemID,ExternProcTrans,ExternUserID,TimeStampProc,MessageTime,Statut,CaseID,CaseIDRemark,MessageErrorID,PrestationID) values(?,?,?,?,?,?,?,?,?,null,?)");

          //ps.setInt(1, l_ExternMessageID);
		  ps.setString(1, ExternMessageID);
          ps.setInt(2, l_ExternSystemID);
          ps.setString(3, ExternProcTrans);
		  //ps.setInt(3, l_ExternProcID);
          if (ExternUserID.length() > 100)
            ps.setString(4, ExternUserID.substring(0, 100));
          else
            ps.setString(4, ExternUserID);
          ps.setTimestamp(5, d_TimeStampProc);
          ps.setTimestamp(6, d_MessageTime);
          ps.setInt(7, l_Statut);
          ps.setInt(8, l_CaseID);
          if (CaseIDRemark.length() > 255)
            ps.setString(9, CaseIDRemark.substring(0, 255));
          else
            ps.setString(9, CaseIDRemark);
			
		  ps.setInt(10, l_ExternPrestationID);

          if (ps.executeUpdate() != 1)
            throw new Exception("Error of insertion in table MESSAGE.");

          ps.close();
          ps = null;

          //get back id
          ps = _conn.prepareStatement("select last_insert_id()");
          rs = ps.executeQuery();
          if (!rs.next()) {
            throw new SQLException("Could not retrieve autoincrement ID after INSERT");
          }

          id_message = rs.getInt(1);

          rs.close();
          rs = null;
          ps.close();
          ps = null;

          return id_message ;
      }

      /**
       * Add a deliverable into the database
       * @param IdMessageInterne int
       * @param ExternDelivID String
       * @param ExternUserID String
       * @param TimestampDeliv String
       * @param DoubleControl String
       * @throws Exception
       */
      protected void addDeliv(int IdMessageInterne, String ExternDelivTrans, String ExternUserID, String TimestampDeliv, String DoubleControl) throws Exception
      {
        PreparedStatement ps ;
        java.sql.Timestamp d_Time ;
        //int l_ExternDelivID ;
        int l_DoubleControl ;

        System.out.println("Deliv : " + IdMessageInterne + " " +  ExternDelivTrans + " " +  ExternUserID + " " +  TimestampDeliv + " " +  DoubleControl) ;

		/*if (true)
			return ;*/
		
        //convert to int the string param
        //l_ExternDelivID = Integer.parseInt(ExternDelivID) ;
        l_DoubleControl = Integer.parseInt(DoubleControl) ;

        //*****check params
        if(l_DoubleControl < 0 || l_DoubleControl >2)
        {
           _current_error = ERROR_MESSAGE_DELIV_DOUBLECONTROL_NOT_VALID ;
           throw new Exception("Double control not valid : " + DoubleControl) ;
        }

        //insert
        ps = _conn.prepareStatement("insert into MESSAGEDELIV(IdMessageInterne,ExternDelivTrans,ExternUserID,TimestampDeliv,DoubleControl,MessageErrorID) values(?,?,?,?,?,null)");
        ps.setInt(1, IdMessageInterne) ;
        //ps.setInt(2, l_ExternDelivID);
		ps.setString(2, ExternDelivTrans);
        if (ExternUserID.length() > 100)
          ps.setString(3, ExternUserID.substring(0,100));
        else
          ps.setString(3, ExternUserID);
         d_Time = new java.sql.Timestamp(_df.parse(TimestampDeliv).getTime()) ;
         ps.setTimestamp(4, d_Time) ;
         ps.setInt(5, l_DoubleControl);
         ps.executeQuery() ;
      }

      /**
       * Create a new connection to the database
       * @return Connection
       * @throws Exception
       */
      protected Connection getConnection() throws Exception
          {
              Class.forName(_className);
			  
			  System.out.println("className : " + _className) ;
    			System.out.println("alias récupéré : " + _database) ;
    			System.out.println("user récupéré : " + _user) ;
    			System.out.println("pwd récupéré : " + _pwd) ;
			  
              return DriverManager.getConnection(_database, _user + ":" + _pwd, "");
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
      //before reading, make sure that if something wrong happens, we have at least default value
      _className = "org.gjt.mm.mysql.Driver";
	  //_className = "com.mysql.jdbc.Driver";
      _database = "jdbc:mysql://localhost/mercutio2";
      _user = "root";
      _pwd = "";
	  
      try{
        //File f = new File("configMessagesSOAP.ini") ;
		File f = new File("alias.ini") ;
        //if the file exists, read the different information
        if (f.exists()) {
/*          FileInputStream fis = new FileInputStream(f);
          BufferedReader br = new BufferedReader(new InputStreamReader(fis));
          _className = br.readLine();
          _database = br.readLine();
          _user = br.readLine();
          _pwd = br.readLine();
          br.close();
          fis.close();
		  */
		  
		  Properties p = new Properties();
		    p.load(new FileInputStream(f));
			
			// to do : récupérer le host depuis le fichier avec les alians
			//String currentHost = "jdbc:mysql://localhost:3306/mercutio2" ;
			_user = p.getProperty("user");
			_pwd = p.getProperty("pwd");
			_database = p.getProperty(_alias);
        }
        else {
          System.out.println("config file (alias.ini) not found. Default values have been loaded.");
        }
        f = null ;
      }
      catch(Exception e)
      {
        System.out.println("Error loading config file (configMessagesSOAP.ini) :" + e.getMessage()) ;
        System.out.println("Default values have been loaded.");
      }
    }
}
