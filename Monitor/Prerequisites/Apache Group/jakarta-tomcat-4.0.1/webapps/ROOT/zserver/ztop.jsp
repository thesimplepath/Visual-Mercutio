<html>
<head>
<%@ page import="PsDebug,PsConfig" %>
<%@ page session="true" %>
<META HTTP-EQUIV="Content-type" CONTENT="text/html; charset=UTF-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/main.css" rel="styleSheet" type="text/css">
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
<%
String p10="img/"+userskin+"/menu.off.on.separator.gif";
String p0="img/"+userskin+"/menu.on.bg.gif";
String p01="img/"+userskin+"/menu.on.off.separator.gif";
String p1="img/"+userskin+"/menu.off.bg.gif";
String p11="img/"+userskin+"/menu.off.off.separator.gif";

String p1E="img/"+userskin+"/menu.off.end.gif";
String p0E="img/"+userskin+"/menu.on.end.gif";
String pE="img/"+userskin+"/menu.end.bg.gif";

String p1S="img/"+userskin+"/lgo_hm_129x36.off.gif";
String p0S="img/"+userskin+"/lgo_hm_129x36.on.gif";

int tab= 	Integer.valueOf(request.getParameter( "TAB" )).intValue();
//PsDebug.log("top.jsp tab selection="+tab);
String AA,BB,CC;
int ZZ;

String L1=(String)request.getParameter( "L1" );
String L2=(String)request.getParameter( "L2" );

%>
<script language=JavaScript>
//lock
top._top_loaded=false;
</script>
</head>
<BODY>
<TABLE class=Bg width="100%" border=0>
  <TBODY>
  <TR>
    <TD noWrap width="15%" height=51>&nbsp;</TD>
    <TD noWrap width="85%" height=51><A class=menu><FONT 
      class=TitleLineBg>ProcessSoft's ZServer</FONT></TD></TR>
  <TR>
    <TD noWrap width="15%">&nbsp;</TD>
    <TD noWrap width="85%">&nbsp;</TD></TR></TBODY></TABLE>
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
  <TBODY>
  <TR> 
<%ZZ=0;if (tab==ZZ) {AA=p0S;BB=p0;CC=p01;} else {AA=p1S;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD vAlign=top width=129><IMG height=36 src="<%=AA%>" width=129 align=top></TD>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=120 href="zacceuil.jsp" target=doc><FONT class=menu>Acceuil</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=1;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=menu tabIndex=121 href="zbrowse.jsp?PATH=" target=doc><FONT class=menu>Explorateur<br>de fichiers</FONT></A>&nbsp;</TD>
    <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=2;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=swnub tabIndex=124 href="zdirmap.jsp" target=doc><FONT class=menu>Authorisation<BR>d'accès</FONT></A>&nbsp;</TD>
   <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=3;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=swnub tabIndex=124 href="zusermgt.jsp" target=doc><FONT class=menu>Gestion<BR>Utilisateurs</FONT></A>&nbsp;</TD>
   <TD><IMG height=36 src="<%=CC%>" width=28></TD>
<%ZZ=4;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}%>
    <TD noWrap background=<%=BB%>>
	<A class=swnub tabIndex=124 href="zconfig.jsp?MODE=0" target=doc><FONT class=menu>Configuration<BR>Server</FONT></A>&nbsp;</TD>
   <TD><IMG height=36 src="<%=AA%>" width=11></TD>

    <TD noWrap align=middle background=<%=pE%> class=Bg>&nbsp;&nbsp;&nbsp;&nbsp;
      <A class=swnub tabIndex=125 href="customize.jsp" target="doc"><FONT class=swnu>Personaliser</FONT></A> 
      |
      <A class=swnub tabIndex=125 href="logout.jsp" target=_top><FONT class=swnu>Logout</FONT></A>
    </TD>
    <TD noWrap align=right width="100%" background=<%=pE%> class=Bg>&nbsp;</TD>
</TR>
</TBODY></TABLE>
<TABLE class=BgL width="100%" border=0>
  <TBODY>
  <TR valign=top >
    <TD noWrap width="15%" valign=top nobr><A class=menu><FONT class=menu>
<script language=JavaScript>
document.write(unescape("<%=L1%>"));
</script>
</FONT></A>&nbsp;</TD>
  </TR>
  <TR valign=top >
    <TD noWrap width="15%" nobr valign=top ><A class=menu><FONT class=menu>
<script language=JavaScript>
document.write(unescape("<%=L2%>"));
</script>
</FONT></A>&nbsp;</TD>
  </TR></TBODY></TABLE>


<DIV align=right id=TIMER name=TIMERDIV style="position:absolute;right:20px;top=10px;width:200px;height=50px;" ></DIV>

<Script language=JavaScript>
<!--
top.currentTab=<%=tab%>;

// manage clock display
function writeObj(id,text)
{
  if (document.getElementById)
	{
		x = document.getElementById(id);
		x.innerHTML = text;
	}
	else if (document.all)
	{
		x = document.all[id];
		x.innerHTML = text;
	}
	else if (document.layers)
	{
		x = document.layers[id];
		x.document.open();
		x.document.write(text);
		x.document.close();
	}

}
function format2(num)
{
	var ret="";
	if (num<=9)
		ret="0";
	ret=ret+num;
	return ret;		

}
function displayTimer()
{
	var monthList=new Array("Jan","Fev","Mar","Avr","Mai","Jui","Juil","Aou","Sep","Oct","Nov","Dec");
	var today = new Date();  
	dis=format2(today.getHours())+":"+format2(today.getMinutes())+":"+format2(today.getSeconds());
	dis=dis+"<br>";
	dis=dis+today.getDate()+" "+monthList[today.getMonth()]+" "+today.getYear();
	writeObj("TIMER","<FONT class=menu>"+dis+"</font>");

	setTimeout("displayTimer()",  1000);
}

setTimeout("displayTimer()",  1000);
//-->
</script>

<script language=JavaScript>
//unlock
top._top_loaded=true;
</script>

</body>
</html>