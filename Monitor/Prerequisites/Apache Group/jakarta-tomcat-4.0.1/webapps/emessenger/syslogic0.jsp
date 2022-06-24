<html>
<%@ page import="PsDebug,PsConfig" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">


<body>
<TABLE width="100%" border=0>
<TR class=Bg>
<TD width="15%">&nbsp;</TD>
<TD width="85%">
<FONT class=menu>
<a class=menu target="usr"><FONT class=swb>Assignation d'applications aux Systèmes Logiques</FONT>
</TD>
</TR>
</TABLE>
</body>
</html>