<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDebug" %>
<%@ page session="true" %>
<body>
<%
 PsApp.init();
 boolean b=false;
 int debug = 	Integer.valueOf(request.getParameter( "DEBUG" )).intValue();
 if (debug>0) b=true;
 PsDebug.setMode(b);
%>
</body>
</html>