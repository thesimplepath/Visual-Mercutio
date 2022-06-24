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
 int delivid=	Integer.valueOf(request.getParameter( "DELIVID" )).intValue();

 int lat=	Integer.valueOf(request.getParameter( "LATERAL" )).intValue(); //0=no,1=yes
 

out.println("Envoi du livrable...<br>");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;

	rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE delivid="+delivid+" AND procidsrc="+procid);

	if (rs.next()==true)
	{			

		int proctrgid=rs.getInt("procidtrg");

		//to do list for laterals
		//new lateral
		if (lat==1)
		{
			PsWf wf=new PsWf();			
			int delividret=wf.getLateralReturn(procid,delivid);
			conn.sqlExecR("INSERT INTO pdelivlateralstate VALUES("+procid+","+caseid+","+transid+","+delividret+",0,"+conn.now()+")");
		}
		else
		{
			rs=conn.sqlQueryR("SELECT * FROM pdelivlateralstate WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
			if (rs.next()==true)
			{
out.println("<h1>Retour de livrable !!!</h1>");
				conn.sqlExecR("UPDATE pdelivlateralstate set openclose=1 WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
			}
			
		}
		//process history
		conn.sqlExecR("INSERT INTO pproctransfrom VALUES ("+proctrgid+","+caseid+","+transid+","+procid+")");

		//change status to "done" (except for laterals)
		if (lat==0)
			conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);

		boolean returnLateral=false;
		rs=conn.sqlQueryR("SELECT count(*) FROM pproctrans WHERE procid="+proctrgid+" AND caseid="+caseid+" AND transid="+transid);
		if (rs.next()==true)
			returnLateral=true;
if (returnLateral==true) out.println("Fin d'execution du retour lateral<br>");//TODO

		conn.sqlExecR("INSERT INTO pproctrans VALUES("+proctrgid+","+caseid+","+transid+",0,"+userid+",0,"+procid+")");

	}
    }
catch (SQLException e)
    {
	PsDebug.fail("deliv.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>