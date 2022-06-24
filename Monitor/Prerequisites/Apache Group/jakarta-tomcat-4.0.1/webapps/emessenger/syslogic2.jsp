<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsConv" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

</head>
<%
 PsApp.init();
 
 try {
  PsDbConn co;
  ResultSet rs;
  co=PsDbMgr.newConnection();	

  String systemid=request.getParameter( "SYSTEMID" );
  String mode=request.getParameter( "MODE" );
  String cmd=request.getParameter("CMD");
  String par=request.getParameter("PAR");
  String dir=request.getParameter("DIR");
  String sysname="";
  if (mode!=null)
  {
   	if (mode.equals("1")==true)
	{
		//update		
		co.sqlExec("UPDATE psystem set command='"+PsConv.c4JS(cmd)+"',parameters='"+PsConv.c4JS(par)+"',directory='"+PsConv.c4JS(dir)+"' WHERE systemid="+systemid);
	} 

  }

  rs=co.sqlQueryR("SELECT systemtitle FROM psystem WHERE systemid="+systemid);
  if (rs.next()==true)
  sysname=rs.getString("systemtitle");	


%>
<body>
<TABLE width="100%" border=0>
<tr class=Bg><td>
<a class=swb><%=sysname%></a>
</td></tr></table>

<%
	rs=co.sqlQueryR("SELECT * FROM psystem WHERE systemid="+systemid);

	if (rs.next()==true)
	{
%>
<table class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
<tr>
<td width=16> </td>
<td>Identificateur :</td><td><input readonly type=text style="width:100%;" value="<%=rs.getString("clsid")%>"></td>
</tr>
<tr>
<td width=16> </td>
<td>Titre Système :</td><td><input readonly type=text style="width:100%;" value="<%=rs.getString("systemtitle")%>"></td>
</tr>
<tr>
<td width=16> </td>
<td>Commande :</td><td><input name=CMD type=text style="width:100%;" value="<%=rs.getString("command")%>"></td>
</tr>
<tr>
<td width=16> </td>
<td>Parametre :</td><td><input name=PAR type=text style="width:100%;" value="<%=rs.getString("parameters")%>"></td>
</tr>
<tr>
<td width=16> </td>
<td>Répertoire :</td><td><input name=DIR type=text style="width:100%;" value="<%=rs.getString("directory")%>"></td>
</tr>
<tr>
<tr>
<td width=16> </td>
<td>&nbsp;</td><td><input type=button class=sbttn value=Sauver les modifications onclick="javascript:document.location='syslogic2.jsp?MODE=1&SYSTEMID=<%=systemid%>&CMD='+escape(CMD.value)+'&PAR='+escape(PAR.value)+'&DIR='+escape(DIR.value);"></td>
</tr>
</table>

<%
	}
%>
</body>
<%
 }
 catch (SQLException e)
 {
   PsDebug.fail("syslogic2.jsp: "+e.getMessage());
 }

%>
</html>