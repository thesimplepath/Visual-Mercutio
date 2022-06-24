<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<html>
<SCRIPT LANGUAGE="JavaScript">
<!--	
<%
  PsApp.init();

  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();

  int mode=             Integer.valueOf(request.getParameter( "MODE" )).intValue();
  int procid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
  String redir= request.getParameter("REDIRECT");
 try {
	PsDbConn conn=PsDbMgr.newConnection();
	if (mode==0)
		conn.sqlExecR("UPDATE pproctrans SET statusid="+statusid+",emplid="+userid+" WHERE procid="+procid);
	if (mode==1)
		conn.sqlExecR("UPDATE pproctrans SET statusid="+statusid+",emplid="+userid+" WHERE procid="+procid+" AND transid="+transid);

	out.println("var sUrl = \""+redir+"\";");
    }
 catch (SQLException e)
    {
	PsDebug.fail("statustrans.jsp: SQLException: "+e.getMessage());
    }
%>

document.location = sUrl;
// --> 
</SCRIPT>

<body></body></html>