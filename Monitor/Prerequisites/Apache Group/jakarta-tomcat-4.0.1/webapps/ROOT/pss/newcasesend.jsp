<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsAuthentication" %>
<html>
<body>
New transaction:<hr>
<%
  PsApp.init();

  String casename =     request.getParameter("CASENAME" );
  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
  String transname = 	request.getParameter( "TRANSNAME" );
  int parenttransid= 	Integer.valueOf(request.getParameter( "PARENTTRANSID" )).intValue();
  int empid= 		Integer.valueOf(request.getParameter( "EMPID" )).intValue();
  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
  int globalyn = 	Integer.valueOf(request.getParameter( "GLOBALYN" )).intValue();
  int qty = 		Integer.valueOf(request.getParameter( "QTY" )).intValue();

  int fromproc = 	Integer.valueOf(request.getParameter( "FROMPROC" )).intValue();

 try {
	PsDbConn conn=PsDbMgr.newConnection();
	int caseid=conn.nextVal("PCASE");
	int attribid=conn.nextVal("PATTRIB");
	String txindate=conn.now();

	conn.sqlExec("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+casename+"')");
	conn.sqlExec("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+transname+"',"+globalyn+","+attribid+",0)");
	conn.sqlExec("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+")");

  	for (int i=0;i<qty;i++)
	{
	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
	    int attribdefid=	Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
	    String mkey=	request.getParameter( "KEY"+i );
	    String mval=	request.getParameter( "VAL"+i );
	conn.sqlExec("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
	}	
    }
 catch (SQLException e)
    {
	PsDebug.fail("newcasesend.jsp: SQLException: "+e.getMessage());
    }
%>

</body></html>