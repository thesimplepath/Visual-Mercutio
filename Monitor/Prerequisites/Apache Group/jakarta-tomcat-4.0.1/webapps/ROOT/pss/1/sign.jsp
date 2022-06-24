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
	int doublesign=0;
	ResultSet rs=conn.sqlQueryR("SELECT * FROM pproc WHERE procid="+procid);
	if (rs.next()==true)
		doublesign=rs.getInt("doublesign");

	rs=conn.sqlQueryR("SELECT * FROM pdoublesign WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
	if (rs.next()==true)
	{
		int signstate=rs.getInt("signstate");
		if (signstate==1)
		{
		//2nd signature
		conn.sqlExec("UPDATE pdoublesign SET signempl2="+userid+",signdate2="+conn.now()+",signstate=2 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

		//terminate the current procedure	
		conn.sqlExec("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

		}
	}
	else
	{
		//fist signature
		conn.sqlExec("INSERT into pdoublesign VALUES("+procid+","+caseid+","+transid+",-1,"+userid+","+conn.now()+",-1,"+conn.now()+",1)");

		//attente signature
		int st=5;
		if (doublesign==2)
			st=6;
		conn.sqlExec("UPDATE pproctrans SET emplid="+userid+",statusid="+st+" WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
	}
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