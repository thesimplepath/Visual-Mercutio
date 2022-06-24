<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>

<html>
<head>
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>
<script language=JavaScript>
<!--
<%
//session check
 String xusername=(String)session.getAttribute( "USERNAME");
 int    userrole;
 if (xusername==null) 
   out.println("alert('Not logged');");
 else
   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
%>
//-->
</script>

<script language=JavaScript>
<!--
//-->
</script>
</head>

<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

out.println("Remise au chef...<br>");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;
	conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=0,chiefflag=1 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
    }
catch (SQLException e)
    {
	PsDebug.fail("chiefflag.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>