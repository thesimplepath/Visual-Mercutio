<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup" %>
 <jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<body>
<%
 PsApp.init();
 String redirect="index.htm";
 String username=(String)session.getAttribute("USERNAME");
 if (username!=null)
 {
	 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
	try {
			PsDbConn conn=PsDbMgr.newConnection();	
			//unlock every locked cases
			conn.sqlExecR("UPDATE pproctrans SET statusid=2 WHERE statusid=1 AND emplid="+userid);
	    }
	catch (SQLException e)
	    {
			PsDebug.fail("setdecision.jsp: SQLException: "+e.getMessage());
	    }
 }
//logout
session.setAttribute("USERNAME",null);
session.setAttribute("USERID",null);
session.invalidate();
%>

<script language=JavaScript>
<!--
document.location="<%=redirect%>";
//-->
</script>

</body>
</html>