<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsMD5" %>
<%@ page session="true" %>
<head>
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

  String mode=request.getParameter( "MODE" );
  String login=request.getParameter("LOGIN");
  String passwd=request.getParameter("PASSWD");
  String roleid=request.getParameter("ROLEID");
  String fname=request.getParameter("FNAME");
  String lname=request.getParameter("LNAME");
  String email=request.getParameter("EMAIL");

  if (mode!=null)
  {
   	if (mode.equals("1")==true)
	{
		//add
		rs=co.sqlQueryR("SELECT max(emplid)+1 as id FROM pemployee");
		rs.next();
		int id=rs.getInt("id");			

		co.sqlExecR("INSERT INTO pemployee VALUES ("+id+",'"+login+"',"+roleid+",'"+fname+"','"+lname+"','"+email+"')");
		co.sqlExecR("INSERT INTO pemppasswd VALUES("+id+",'"+PsMD5.encode(passwd)+"')");
	} 
   	if (mode.equals("2")==true)
	{
		//del
		rs=co.sqlQueryR("SELECT emplid as id FROM pemployee WHERE login='"+login+"'");
		if (rs.next()==true)
		{
			int id=rs.getInt("id");
	
			co.sqlExecR("DELETE FROM pemployee WHERE emplid="+id);
			co.sqlExecR("DELETE FROM pemppasswd WHERE emplid="+id);
			co.sqlExecR("DELETE FROM pempmap WHERE login='"+login+"'");
		}
	} 
  }
%>
<body>

<table width="100%" border=0>
<form action="usermgt3.jsp" method=POST>
<input type=hidden name=MODE value=1>
<tr>
<td><a class=menu>Login</a></td>
<td><a class=menu>Passwd</a></td>
<td><a class=menu>First Name</a></td>
<td><a class=menu>Last Name</a></td>
<td><a class=menu>Email</a></td>
<td><a class=menu>Role</a></td>
<td>&nbsp</td>
</tr>

<tr>
<td><input type=text name=LOGIN style="width:100%"></td>
<td><input type=text name=PASSWD style="width:100%"></td>
<td><input type=text name=FNAME style="width:100%"></td>
<td><input type=text name=LNAME style="width:100%"></td>
<td><input type=text name=EMAIL style="width:100%"></td>
<td><SELECT name=ROLEID style="width:100%">
<%	String rolelist="";
	rs=co.sqlQueryR("SELECT * FROM pemproles");
	while (rs.next())
	{
	rolelist+="<option value=\""+rs.getInt("roleid")+"\">"+rs.getString("rolename")+"</option>\n";
	}
	out.println(rolelist);
%>
</SELECT></td>
<td>&nbsp;<input type=submit value=Add></td>
</tr>
</form>

<tr class=Bg height=2>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
<td> </td>
</tr>

<%
	rs=co.sqlQueryR("SELECT * FROM pemployee,pemppasswd WHERE pemployee.emplid=pemppasswd.emplid ORDER BY login");
	int frmcnt=0;
	while (rs.next())
	{
	frmcnt++;
%>
<form action=usermgt3.jsp method=POST name=FRM<%=frmcnt%>>
<input type=hidden name=MODE value=2>
<tr>
<td><input readonly type=text name=LOGIN  style="background-color:lightgrey;width:100%" value="<%=rs.getString("login")%>"></td>
<td><input type=text name=PASSWD style="width:100%" value="<%=rs.getString("passwd")%>"></td>
<td><input type=text name=FNAME style="width:100%"  value="<%=rs.getString("fname")%>"></td>
<td><input type=text name=LNAME style="width:100%"  value="<%=rs.getString("lname")%>"></td>
<td><input type=text name=EMAIL style="width:100%"  value="<%=rs.getString("email")%>"></td>
<td><SELECT name=ROLEID style="width:100%"><%=rolelist%></SELECT>
<script language=javascript>
 document.FRM<%=frmcnt%>.ROLEID.value=<%=rs.getString("roleid")%>;
</script>
</td>
<td>&nbsp;<input type=submit value=Del></td>
</tr>
</form>
<%
	}
%>
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