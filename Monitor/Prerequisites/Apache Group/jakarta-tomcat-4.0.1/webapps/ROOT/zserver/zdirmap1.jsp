<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,ZsrvDirTreeJS" %>
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
 ZsrvDirTreeJS dtjs=new ZsrvDirTreeJS(); 

 String res=dtjs.recScanDirJS("zdirmap",1,0,PsConfig.get("ZSERVER_ROOT"));

 out.println(res);

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