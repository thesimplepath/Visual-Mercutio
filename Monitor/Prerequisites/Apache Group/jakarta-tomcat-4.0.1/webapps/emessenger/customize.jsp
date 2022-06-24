<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<jsp:include page="checksession.jsp" flush="false" />

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on top.jsp
var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)";
var info2="";
var tabno=7;
top.showTabText(tabno,info1,info2);
</script>
<!-- ------------------------------------ //-->

</head>
<body>
<TABLE width="100%" border=0>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >

<form name=FRM action="customize.jsp" method=GET>
<table cellSpacing=0 cellPadding=0 width="100%">
 <tr class=Bg height=23 >
 <td width=23>&nbsp;<img src="img/<%=userskin%>/ard.gif">&nbsp;</td>
 <td><font class=swb>Paramètre</font></td>
 <td><font class=swf>Valeur</font></td>
 </tr>

<% 
  int mode=0;
  if (request.getParameter("MODE")!=null)
	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
  PsApp.init(); 

  //mode 1
  if (mode==1)
  {
	PsDebug.log("CUSTOMIZE.JSP customization updated...");
	PsDbConn conn=PsDbMgr.newConnection();
	String skin=request.getParameter("NO");
	ResultSet rs=conn.sqlQueryR("SELECT * FROM ppersonalize WHERE login='"+(String)session.getAttribute("USERNAME")+"'");
	if (rs.next()==false)
		conn.sqlExec("INSERT INTO ppersonalize VALUES ('"+(String)session.getAttribute("USERNAME")+"','"+skin+"',0)");
	else
		conn.sqlExec("UPDATE ppersonalize SET userskin='"+skin+"' WHERE login='"+(String)session.getAttribute("USERNAME")+"'");
	%>

	<%
  	//Set cookie
	 Cookie c = new Cookie("userskin", skin); 
	 response.addCookie(c); 
        %>

	<script language=JavaScript>
	top.document.location="logout.jsp";
	</script>
	<%
  }
%>
  <tr><td></td>
  <td><input type=radio name=NO value="1">Modèle de couleur <b>Messenger</b></td>
  <td><img src="img/skin1/preview.gif"></td></tr>

  <tr><td></td>
  <td><input type=radio name=NO value="2">Modèle de couleur <b>Windows</b></td>
  <td><img src="img/skin2/preview.gif"></td></tr>

  <tr><td></td>
  <td><input type=radio name=NO value="3">Modèle de couleur <b>Rouge</b></td>
  <td><img src="img/skin3/preview.gif"></td></tr>

  <tr><td></td>
  <td><input type=radio name=NO value="4">Modèle de couleur <b>Vert</b></td>
  <td><img src="img/skin4/preview.gif"></td></tr>

  <tr><td></td>
  <td><input type=radio name=NO value="5">Modèle de couleur <b>Jaune</b></td>
  <td><img src="img/skin5/preview.gif"></td></tr>


  <input type=HIDDEN name=MODE value=1>
 
</table>
<input type=submit value="Appliquer la personalisation" class=sbttn>
</form>
</tr></tr>
</table>
</body>
</html>