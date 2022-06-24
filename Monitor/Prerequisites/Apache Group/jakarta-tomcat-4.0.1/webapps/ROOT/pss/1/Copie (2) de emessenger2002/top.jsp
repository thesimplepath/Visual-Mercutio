<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<html>
<head>
<link href="css/main.css" rel="styleSheet" type="text/css"> 
<link href="css/global.css" rel="styleSheet" type="text/css"> 
<%
PsDebug.log("Document= top.jsp");

String p10="img/menu.off.on.separator.gif";
String p0="img/menu.on.bg.gif";
String p01="img/menu.on.off.separator.gif";
String p1="img/menu.off.bg.gif";
String p11="img/menu.off.off.separator.gif";

String p1E="img/menu.off.end.gif";
String p0E="img/menu.on.end.gif";
String pE="img/menu.end.bg.gif";

String p1S="img/lgo_hm_129x36.off.gif";
String p0S="img/lgo_hm_129x36.on.gif";

int tab= 	Integer.valueOf(request.getParameter( "TAB" )).intValue();
PsDebug.log("top.jsp tab selection="+tab);
String AA,BB,CC;
int ZZ;

String L1=(String)request.getParameter( "L1" );
String L2=(String)request.getParameter( "L2" );
%>
</head>
<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT="0" MARGINWIDTH="0">
<TABLE width="100%" bgColor=#336699 border=0>
  <TBODY>
  <TR>
    <TD noWrap width="15%" height=51>&nbsp;</TD>
    <TD noWrap width="85%" height=51><A class=menu><FONT 
      class=TitleLine><%out.println(PsConfig.get("COMPANY"));%><a href="aide.jsp">X</a> <a href="setdebug.jsp?DEBUG=0">0</a> <a href="setdebug.jsp?DEBUG=1">1</a> <a href="http://127.0.0.1:8080/emessenger2002/config.jsp?MODE=0" target=doc>C</a></FONT></A></TD></TR>
  <TR>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD noWrap width="85%">&nbsp;</TD></TR></TBODY></TABLE>
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
  <TBODY>
  <TR> 
<%ZZ=0;if (tab==ZZ) {AA=p0S;BB=p0;CC=p01;} else {AA=p1S;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD vAlign=top width=129><IMG height=36 src="<%=AA%>" width=129 align=top></TD>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=120 href="acceuil.html" target=doc><FONT class=menu>Accueil</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=1;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=121 href="listcase.jsp?MODE=0" target=doc><FONT class=menu>Boîte de<BR>travail</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=2;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=122 href="listcase.jsp?MODE=1" target=doc><FONT class=menu>Processus<BR>en cours</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=3;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=123 href="statproc.html" target=doc><FONT class=menu>Statistiques</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=4;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=swnub tabIndex=124 href="newproc.jsp" target=doc><FONT class=menu>Nouveau <BR>processus</FONT></A></TD>
   <TD><IMG height=36 src="<%=AA%>" width=11></TD>
    <TD noWrap align=middle background=<%=pE%> bgColor=#336699>&nbsp;&nbsp;&nbsp;&nbsp;
	<A class=swnub tabIndex=125 href="logout.jsp" target=_top><FONT class=swnu>Logout</FONT></A></TD>
    <TD noWrap align=right width="100%" background=<%=pE%> bgColor=#336699>&nbsp;</TD>
</TR></TBODY></TABLE>
<TABLE width="100%" bgColor=#93bee2 border=0>
  <TBODY>
  <TR>
    <TD noWrap width="15%"><A class=menu><FONT class=menu><%=L1%></FONT></A>&nbsp;</TD>
  </TR>
  <TR>
    <TD noWrap width="15%"><A class=menu><FONT class=menu><%=L2%></FONT></A>&nbsp;</TD>
  </TR></TBODY></TABLE>
<Script language=JavaScript>
<!--
function showTab(no)
{
  l1=escape("<%=L1%>");
  l2=escape("<%=L2%>");
  document.location="top.jsp?TAB="+no+"&L1="+l1+"&L2="+l2;
}

function showTabText(no,l1,l2)
{
  l1=escape(l1);
  l2=escape(l2);
  document.location="top.jsp?TAB="+no+"&L1="+l1+"&L2="+l2;
}

function showText(l1,l2)
{
  l1=escape(l1);
  l2=escape(l2);
  document.location="top.jsp?TAB=<%=tab%>&L1="+l1+"&L2="+l2;
}
//-->
</script>
</body>
</html>