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

</head>
<%
 PsApp.init();
 
 try {
  PsDbConn co;
  ResultSet rs;
  co=PsDbMgr.newConnection();	

  String wkgid=request.getParameter( "WKGID" );
  String mode=request.getParameter( "MODE" );
  String login=request.getParameter("LOGIN");
  if (mode!=null)
  {
   	if (mode.equals("1")==true)
	{
		//add
		co.sqlExec("INSERT INTO pempmap VALUES ("+wkgid+",'"+login+"')");
	} 
   	if (mode.equals("2")==true)
	{
		//del
		co.sqlExec("DELETE FROM pempmap WHERE wkgid="+wkgid+" AND login='"+login+"'");	
	} 
  }
  
  String wkgname="";
  rs=co.sqlQueryR("SELECT wkgname FROM pworkgroup WHERE wkgid="+wkgid);
  if (rs.next()==true)
  {
  	wkgname=rs.getString("wkgname");
  }
%>
<body>
<TABLE width="100%" border=0>
<tr class=Bg><td>
<a class=menu><%=wkgname%></a>
</td></tr></table>

<table width="100%" border=0>
<tr>
<td>Utilisateurs:</td>
<td></td>
<td>Membres:</td>
</tr>
<tr>
<td width="45%" valign=top><select name=EMP size=18 style="width:100%;">
<%
	rs=co.sqlQueryR("SELECT count(*) as cnt,login,fname,lname FROM pemployee GROUP BY login ORDER BY lname,fname,login");
	while (rs.next())
	{
%>
	<option value="<%=rs.getString("login")%>"><%=rs.getString("login")%> : <%=rs.getString("fname")%> <%=rs.getString("lname")%></option>
<%
	}
%>
</select> 
</td>
<td width="10%" valign=middle align=center>
<input type=button value="&nbsp;&nbsp;&gt;&nbsp;&gt;&nbsp;&nbsp;" onclick="javascript:document.location='usermgt2.jsp?MODE=1&WKGID=<%=wkgid%>&LOGIN='+escape(EMP.value);">
<br><br>
<input type=button value="&nbsp;&nbsp;&lt;&nbsp;&lt;&nbsp;&nbsp;" onclick="javascript:document.location='usermgt2.jsp?MODE=2&WKGID=<%=wkgid%>&LOGIN='+escape(MAP.value);">
</td>

<td width="45%" valign=top>
<select name=MAP size=18 style="width:100%;">
<%
if (wkgid!=null) 
 {
	rs=co.sqlQueryR("SELECT * FROM pempmap WHERE wkgid="+wkgid+" ORDER BY login");
	while (rs.next())
	{
%>

<option value="<%=rs.getString("login")%>"><%=rs.getString("login")%></option>

<%
	}	
 }//if
%>
</select>
</td>
</table>
</body>
<%
 }
 catch (SQLException e)
 {
   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
 }

%>
</html>