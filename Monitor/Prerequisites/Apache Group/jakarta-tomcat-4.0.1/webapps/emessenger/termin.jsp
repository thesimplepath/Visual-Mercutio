<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
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


	//manage dynamic attributes
	 PsDebug.log("Save dynamic attributs");
	 int nbr=	Integer.valueOf(request.getParameter( "NBR_INPUT" )).intValue(); 
	
	 for (int i=1;i<=nbr;i++)
	 {
		int modelid=1;
		String attribdefid=request.getParameter( "CTL2_"+i );
		String mval=request.getParameter( "CTL_"+i );
		conn.sqlExec("INSERT INTO pinputdata VALUES("+modelid+","+procid+","+attribdefid+","+caseid+","+transid+",'"+mval+"',"+conn.now()+")");
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