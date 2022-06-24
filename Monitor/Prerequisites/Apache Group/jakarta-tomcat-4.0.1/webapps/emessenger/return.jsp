<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsDebug,PsWorkGroup" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>

<script language=JavaScript>
<!--
//-->
</script>
</head>

<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int modelid=1;
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 String redirect=	(String)request.getParameter( "REDIRECT" );
 String msg=		(String)request.getParameter( "MSG" );

out.println("Retour a l'envoyeur...<br>");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	ResultSet rs;
	ResultSet rs2;

	rs=conn.sqlQueryR("SELECT * FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

	boolean foundParent=false;

	while (rs.next())
	{			
		foundParent=true;

		//process history
		conn2.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=0 WHERE procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);		
		PsDebug.log("Return.jsp: Sent to "+rs.getInt("refprocid"));

		//text
		 if (msg!=null && msg.length()>0)
		 {
			rs2=conn2.sqlQueryR("SELECT * FROM pproctranstxt WHERE modelid="+modelid+" AND procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);
			if (rs2.next()==true)	
				conn2.sqlExec("UPDATE pproctranstxt SET msg='"+PsDbConn.cnv_sql(msg)+"' WHERE modelid="+modelid+" AND procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);	
			else
				conn2.sqlExec("INSERT INTO pproctranstxt VALUES ("+modelid+","+rs.getInt("refprocid")+","+caseid+","+transid+",'"+PsDbConn.cnv_sql(msg)+"')");
		}
	}
	if (foundParent==true)
	{
		out.println("Remove current process "+procid+"<br>");
		conn2.sqlExecR("DELETE FROM pproctrans WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM pdelivstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM ptaskstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM preferencestatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		conn2.sqlExecR("DELETE FROM psystemstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

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

out.println("<script language=JavaScript>");
out.println("<!--");
out.println("document.location=\""+redirect+"\";");
out.println("//-->");
out.println("</script>");
%>
</body>
</html>