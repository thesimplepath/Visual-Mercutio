<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
<link href="css/main.css" rel="styleSheet" type="text/css"> 
<link href="css/tree.css" rel="styleSheet" type="text/css"> 
<script language=javaScript src="js/tree.js"></script>
<script language=JavaScript>
<!--
 var m=new oMenu;
<%

//session check
 String username=(String)session.getAttribute( "USERNAME");
 int    userrole;
 if (username==null) 
   out.println("alert('Not logged');");
 else
   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();


 PsApp.init();
 
 try {
	String lnk;
	PsDbConn co=PsDbMgr.newConnection();
	ResultSet rs=co.sqlQueryR("select * from pmenuitem where menuid=1 order by itemid");
	while (rs.next())
	{
		lnk="\""+rs.getString("ilink")+"\"";
		if (rs.getInt("linkorgroup")==0)
			lnk="null";
				
		out.println("m.add("+rs.getInt("itemid")+","+rs.getInt("parentid")+",\""+rs.getString("iname")+"\","+lnk+");");
	}	

 }
 catch (SQLException e)
 {
   PsDebug.fail("wkgmenu: "+e.getMessage());
 }

%>
//-->
</script>
</head>

<body topmargin=0>
<h2>eMessenger<hr></h2>
<script language=JavaScript>
<!--
 m.setIconDocument("img/doc.gif");
 m.setIconCollapse("img/open.gif");
 m.setIconExpand("img/close.gif");

 m.gen(true);
//-->
</script>
</body>
</html>