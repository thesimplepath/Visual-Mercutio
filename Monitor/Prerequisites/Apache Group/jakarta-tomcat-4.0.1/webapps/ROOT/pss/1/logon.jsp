<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsAuthentication" %>

<html>
<head>
<%
 PsApp.init();
 
 session.setAttribute( "USERNAME",null);
 session.setAttribute( "USERROLE","-1");
 session.setAttribute( "USERID","-1");

 String mlogin=request.getParameter( "LOGIN" );
 String mpasswd=request.getParameter( "PASSWD" );

 PsAuthentication auth=new PsAuthentication();
 if (auth.logon(mlogin,mpasswd)==false)
 {
 	//not logged
 	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=index.html\">");
 }
 else
 {
 	//logged
 	session.setAttribute( "USERNAME",mlogin);
 	session.setAttribute( "USERROLE",String.valueOf(auth.getRole()));
	session.setAttribute( "USERID",  String.valueOf(auth.getId()));
	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=main.htm\">");
 }
%>

</head>
<body>
</body>
</html>