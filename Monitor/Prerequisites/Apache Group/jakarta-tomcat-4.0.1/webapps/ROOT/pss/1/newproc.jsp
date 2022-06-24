<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>
<html>
<head>
<LINK href="css/global.css" rel=STYLESHEET type="text/css">
<script language=JavaScript src="js/pss.js"></script>
<SCRIPT language=javascript>
top.menu.showTabText(4,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","");
</SCRIPT>
</head>
<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>
<TABLE width="100%" bgColor=#93bee2 border=0>
  <TBODY>
  <TR>
    <TD noWrap width="15%"><A class=menu><FONT class=menu></FONT></A>&nbsp;</TD>
    <TD noWrap width="85%"><A class=menu><FONT class=menu>Sélection d'un point 
      de démarrage</FONT></A>&nbsp;</TD></TR>
  <TR>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD class=menu noWrap width="85%">
      <DIV align=right>Nouveau processus</DIV></TD></TR>
  <TR>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD class=NormalBlack width="85%">Pour démarrer un nouveau processus, 
      veuillez sélectionner un point de démarrage du processus affiché 
      ci-dessous. Vous pouvez naviguer au sein du modèle en sélectionnant les 
      symboles de processus, de page et de porte. </TD></TR></TBODY></TABLE>
<br>
<br>
Choisir un processus start :<select name="CASE">
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;

	PsWorkGroup w=new PsWorkGroup();
 	Vector r=w.listProcStartGranted(username);
 	int l=r.size();
 	for (int i=0;i<l;i++)
 	{
		int proc=((Integer)r.elementAt(i)).intValue();
		rs=conn.sqlQueryR("select * from pproc,pmodel where pproc.proctype=0 and pproc.procid="+proc+" and pproc.modelid=pmodel.modelid order by modelname");
		rs.next();
		out.println("<option value=\""+proc+"\">"+rs.getString("modelname")+". #proc:"+proc+"</option>");
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
    }
%>
</select>

<input type=button onclick="javascript:document.location='newproc1.jsp?PROCID='+CASE.value;" value="Aller à...">
</body>
</html>