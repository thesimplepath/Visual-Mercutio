<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>
<%@ page import="PsWf" %>

<html>
<head>
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>
</head>

<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

 String redirect=(String)request.getParameter( "REDIRECT" );

try {
	PsDbConn conn=PsDbMgr.newConnection();

	//check approval (all mandatory delivs must have been completed)	
	//TODO

	//terminate the current procedure	
	conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
    }
catch (SQLException e)
    {
	PsDebug.fail("deliv.jsp: SQLException: "+e.getMessage());
    }

out.println("<script language=JavaScript>");
out.println("<!--");
out.println("document.location=\""+redirect+"\";");
out.println("//-->");
out.println("</script>");

%>
</body>
</html>