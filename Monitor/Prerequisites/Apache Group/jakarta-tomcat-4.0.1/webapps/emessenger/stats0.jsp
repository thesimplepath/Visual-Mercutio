<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<link href="css/tree.css" rel="styleSheet" type="text/css"> 

<body>
<TABLE width="100%">
<TR><TD width="2%">&nbsp;</TD>
<TD width="98%">
<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="96%"><NOBR><FONT class=menu>Statistiques:</FONT></NOBR></TD>
        </TR>
</TBODY>
</TABLE>
</TD></TR>
<TR><TD width="2%">&nbsp;</TD>
<TD>
<br>
<script language=javaScript src="js/tree.js"></script>
<script language=JavaScript>
<!--
 var m=new oMenu;
 m.add(1,0,'Analyse des stocks','stats100.jsp');

 m.setTarget("usr");
 m.setIconDocument("img/doc.gif");
 m.setIconCollapse("img/close.gif");
 m.setIconExpand("img/open.gif");

 m.gen(true);

-->
</script>
</TD>
</TR>
</TABLE>
</body>
</html>