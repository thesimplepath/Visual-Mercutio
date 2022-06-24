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
<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 String redirect="index.htm";
try {
	PsDbConn conn=PsDbMgr.newConnection();	
	//unlock every locked cases
	conn.sqlExecR("UPDATE pproctrans SET statusid=2 WHERE statusid=1 AND emplid="+userid);
    }
catch (SQLException e)
    {
	PsDebug.fail("setdecision.jsp: SQLException: "+e.getMessage());
    }

//logout
session.setAttribute("USERNAME",null);
session.setAttribute("USERID",null);

out.println("<script language=JavaScript>");
out.println("<!--");
out.println("document.location=\""+redirect+"\";");
out.println("//-->");
out.println("</script>");
%>
</body>
</html>