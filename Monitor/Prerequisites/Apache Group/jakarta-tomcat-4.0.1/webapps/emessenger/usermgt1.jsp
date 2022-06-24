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
	int maxWkgId=-1;
	PsDbConn co=PsDbMgr.newConnection();
	ResultSet rs=co.sqlQueryR("SELECT * FROM pworkgroup ORDER BY wkgid");
	while (rs.next())
	{
		String lnk="usermgt2.jsp?WKGID="+rs.getInt("wkgid");
		if (maxWkgId<rs.getInt("wkgid")) 
			maxWkgId=rs.getInt("wkgid")+1;		
		out.println("m.add("+rs.getInt("wkgid")+","+rs.getInt("wkgparent")+",\""+rs.getString("wkgname")+"\",\""+lnk+"\");");
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

<body>
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