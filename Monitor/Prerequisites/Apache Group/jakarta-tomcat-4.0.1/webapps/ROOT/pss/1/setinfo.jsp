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
 int delivid=   Integer.valueOf(request.getParameter( "DELIVID" )).intValue();
 int infoid=    Integer.valueOf(request.getParameter( "INFOID" )).intValue(); 
 String redir=			request.getParameter( "REDIR" );
System.out.println(redir+"="+infoid);

try {
	PsDbConn conn=PsDbMgr.newConnection();	
	if (infoid>=0)
	{
		conn.sqlExecR("INSERT INTO pinfostatus VALUES("+caseid+","+procid+","+transid+","+delivid+","+infoid+",+1,"+conn.now()+")");
	}
	else
	{
		//TODO: set all attributes	
	}
	
	out.println("<script language=JavaScript>");
	out.println("<!--");
//	out.println("alert(\""+redir+"\");");
	out.println("document.location=\""+redir+"\";");
	out.println("//-->");
	out.println("</script>");

    }
catch (SQLException e)
    {
	PsDebug.fail("setinfo.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>