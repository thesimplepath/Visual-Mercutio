<html>
<%@ page import="java.sql.*,PsApp,PsDbMgr,PsDbConn,PsConfig" %>
<head>
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

</head>

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on top.jsp
function delayedDisplay()
{
	var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)";
	var info2="Welcome...";
	var tabno=0;
	top.showTabText(tabno,info1,info2);
}
//document.onload=delayedDisplay();
</script>
<!-- ------------------------------------ //-->

<%
 String username=(String)session.getAttribute("USERNAME");
 if (username==null) return;
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 PsApp.init();

 System.out.println("JDBCDRIVER="+PsConfig.get("JDBCDRIVER")+"*");
 System.out.println("JDBCDNS="+PsConfig.get("JDBCDNS")+"*");
 System.out.println("JDBCLOGIN="+PsConfig.get("JDBCLOGIN")+"*");
 System.out.println("JDBCPASSWD="+PsConfig.get("JDBCPASSWD")+"*");

 PsDbConn conn=PsDbMgr.newConnection();
 ResultSet rs;

 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid<90");
 rs.next();
 int nbrCaseAll=rs.getInt("cnt");

 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid<=6 AND statusid>=3");
 rs.next();
 int nbrCaseWait=rs.getInt("cnt");

 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid=1");
 rs.next();
 int nbrCaseLock=rs.getInt("cnt");
%>

<body onload="delayedDisplay();">
<%=PsConfig.get("WELCOME_SCREEN")%>
<br>
<TABLE width="100%" border=0>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
        <TR class=BgL>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="87%"><FONT class=menu>Statistiques</FONT></TD>
          <TD width="10%" class=BgL><FONT class=menu>&nbsp;</FONT></TD>
	</TR>
	<TR>
 	  <TD>&nbsp;</TD>
 	  <TD>Nombre de cas:</TD>
 	  <TD align=right><%=nbrCaseAll%></TD>
	</TR>
	<TR>
 	  <TD>&nbsp;</TD>
 	  <TD>Nombre de cas en attente:</TD>
 	  <TD align=right><%=nbrCaseWait%></TD>
	</TR>
	<TR>
 	  <TD>&nbsp;</TD>
 	  <TD>Nombre de cas en cours de travail:</TD>
 	  <TD align=right><%=nbrCaseLock%></TD>
	</TR>	
      </TABLE>
  </TR>
</TABLE>

</body>
</html>