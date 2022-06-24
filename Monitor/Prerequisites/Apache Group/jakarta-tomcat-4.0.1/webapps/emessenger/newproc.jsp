<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsConv,PsWorkGroup" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
<script language=JavaScript src="js/pss.js"></script>
<SCRIPT language=javascript>
top.showTabText(4,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","");
</SCRIPT>
</head>
<BODY>
<TABLE width="100%" border=0 cellSpacing=0 cellPadding=0>
  <TBODY>
  <TR class=Bg>
    <TD noWrap width="15%"><A class=menu><FONT class=menu></FONT></A>&nbsp;</TD>
    <TD noWrap width="85%"><A class=menu><FONT class=menu>Sélection d'un point de démarrage</FONT></A>&nbsp;</TD></TR>
  <TR class=Bg>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD class=menu noWrap width="85%"><DIV align=right>Nouveau processus</DIV></TD></TR>
  <TR class=Bg>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD class=NormalBlack width="85%">Pour démarrer un nouveau processus, veuillez sélectionner un modèle ci-dessous. Vous pourrez ensuite naviguer au sein du modèle en sélectionnant les symboles de processus, de page et de porte. </TD>
  </TR>
  </TBODY>
</TABLE>
<br>
<br>
<center>
<table cellSpacing=0 cellPadding=0 width="100%">
<tr>
 <td valign=bottom width="11%">&nbsp;</td>
 <td class=Bg width="89%">
  <table border=0 cellSpacing=0 cellPadding=0 width="100%">
   <tr>
    <TD width="26" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif" border=0></TD>
    <TD nobr><font class=swb>&nbsp;Choisir un modèle:</font></td>
   </tr>
  </table>
 </td>
</tr>

<tr>
<td width="11%">&nbsp;</td>
<td width="89%">
<table class=Mtable cellSpacing=0 cellPadding=0 width="100%">
<tr >
<td width=26>&nbsp;</td>
<td width="10%" nowrap>
<a class=menu>Version</a>
</td>
<td width="10%" nowrap>
<a class=menu>Mise-à-jour</a>
</td>
<td nowrap>
<a class=menu>Nom du modèle</a>
</td>
</tr>

<%
 PsApp.init();

try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	ResultSet rs;
	ResultSet rs2;

	rs=conn.sqlQueryR("SELECT * FROM pmodel GROUP BY modelref");
	while (rs.next())
	{
		rs2=conn2.sqlQueryR("SELECT * FROM pmodel WHERE modelid="+rs.getString("modelid"));
		if (rs2.next()==true)
		{
%>

<tr>
<td valign=bottom width="2%"><a href="bpml.jsp?MODELID=<%=rs.getString("modelid")%>"><img src="img/arr.gif" border="0"></a></td>
<td valign=bottom>
<%=rs2.getInt("versionno")%>
</td>
<td valign=bottom>
<%=rs2.getString("pubdate")%>
</td>
<td valign=bottom>
<a title="Model Reference: <%=rs.getString("modelref")%>" href="public/1/<%=PsConv.c4FS(rs.getString("modelname").trim())%>.htm">
<%=rs.getString("modelname")%>
</a>
</td>
</tr>

<%
		}
	}		

    }
catch (SQLException e)
    {
	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
    }
%>
</td>
</tr>
</table></center>

</body>
</html>