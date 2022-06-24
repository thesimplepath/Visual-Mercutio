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
 String redirect=(String)request.getParameter( "REDIRECT" );

 System.out.println("Envoi du livrable...");

 int delividret=delivid;
try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;
	
	//process delivs
	rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE delivid="+delivid+" AND procidsrc="+procid);
	if (rs.next()==true)
	{			
		int proctrgid=rs.getInt("procidtrg");

		//to do list for laterals
		//new lateral
		if (lat==1)
		{
			PsWf wf=new PsWf();			
			delividret=wf.getLateralReturn(procid,delivid);
			conn.sqlExecR("INSERT INTO pdelivlateralstate VALUES("+procid+","+caseid+","+transid+","+delividret+",0,"+conn.now()+")");
		}
		else
		{
			rs=conn.sqlQueryR("SELECT * FROM pdelivlateralstate WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
			if (rs.next()==true)
			{
				System.out.println("Retour de livrable !!!");
				conn.sqlExecR("UPDATE pdelivlateralstate set openclose=1 WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
			}
			
		}

		//process history
		conn.sqlExecR("INSERT INTO pproctransfrom VALUES ("+proctrgid+","+caseid+","+transid+","+procid+")");

		//change status to "done" (except for laterals)
		if (lat==0)
		{
			//conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		}

		boolean returnLateral=false;
		rs=conn.sqlQueryR("SELECT count(*) FROM pproctrans WHERE procid="+proctrgid+" AND caseid="+caseid+" AND transid="+transid);
		if (rs.next()==true)
			returnLateral=true;
		if (returnLateral==true) 
			System.out.println("Fin d'execution du retour lateral");//TODO
		rs=conn.sqlQueryR("SELECT * FROM pproctrans WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		//if (rs.next()==false)
		conn.sqlExecR("INSERT INTO pproctrans VALUES("+proctrgid+","+caseid+","+transid+",0,"+userid+",0,"+procid+")");
		//else	{/*NA*/}
	}
	
	//register click of deliv
	System.out.println("Ack deliv");
	if (lat==1)
		delivid=delividret;

	conn.sqlExecR("INSERT INTO pdelivstatus VALUES("+caseid+","+procid+","+transid+","+delivid+",1,"+conn.now()+")");
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