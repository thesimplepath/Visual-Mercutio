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

out.println("Retour a l'envoyeur...<br>");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	ResultSet rs;

	rs=conn.sqlQueryR("SELECT * FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

	boolean foundParent=false;

	while (rs.next())
	{			
		foundParent=true;

		//process history
		conn2.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=0 WHERE procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);		
		out.println("Sent to "+rs.getInt("refprocid")+"<br>");
	}
	if (foundParent==true)
	{
		out.println("Remove current process "+procid+"<br>");
		conn2.sqlExecR("DELETE FROM pproctrans WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
	}
	else
	{
		out.println("Pas de procedure precedentes... retour du travail impossible!<br>");
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("return.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>