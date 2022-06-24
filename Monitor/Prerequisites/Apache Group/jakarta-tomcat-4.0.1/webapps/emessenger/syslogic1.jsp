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
<script language=javaScript src="js/tree.js"></script>
<script language=JavaScript>
<!--
 var m=new oMenu;
<%
 PsApp.init();
 
 try {
	PsDbConn co=PsDbMgr.newConnection();
	ResultSet rs=co.sqlQueryR("SELECT * FROM psystem ORDER BY systemid");
	while (rs.next())
	{
		String lnk="syslogic2.jsp?SYSTEMID="+rs.getInt("systemid");		out.println("m.add("+rs.getInt("systemid")+","+rs.getInt("systemparent")+",\""+rs.getString("systemtitle")+"\",\""+lnk+"\");");
	}	

 }
 catch (SQLException e)
 {
   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
 }

%>
//-->
</script>
</head>

<body text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT="0" MARGINWIDTH="0">
<script language=JavaScript>
<!--
 m.setTarget("usr");
 m.setIconDocument("img/doc.gif");
 m.setIconCollapse("img/close.gif");
 m.setIconExpand("img/open.gif");

 m.gen(true);
//-->
</script>
</body>
</html>