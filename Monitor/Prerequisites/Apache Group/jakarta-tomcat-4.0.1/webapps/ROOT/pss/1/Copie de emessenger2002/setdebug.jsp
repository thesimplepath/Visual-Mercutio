<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDebug" %>

<html>
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