<html>
<%@ page import="PsDebug,PsConfig" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<script language=Javascript>
top.showTabText(3,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","Assignation d'utilisateurs aux groupes");
</script>

<body>
<TABLE width="100%" border=0>
<TR class=Bg>
<TD width="15%">&nbsp;</TD>
<TD width="85%">
<FONT class=menu>
<a href="zusermgt2.jsp" class=menu target="usr"><FONT class=menu>Gestion des groupes de travail</font></a> | <a href="usermgt3.jsp" class=menu target="usr"><FONT class=menu>Gestion des utilisateurs</font></a> | <font color=#808080>Repertoire d'entreprise</font>
</FONT>
</TD>
</TR>
</TABLE>
</body>
</html>