<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,java.io.File,java.text.DateFormat" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
</head>
<body>

<table cellSpacing=0 cellPadding=0 width="100%">
<tr class=Bg height=23>
<td><font class=swb>Version</font></td>
<td><font class=swb>Fichier</font></td>
<td><font class=swb>Création</font></td>
<td><font class=swb>Modification</font></td>
<td><font class=swb>Accès</font></td>
</tr>
<%
 PsApp.init();

 PsDbConn conn=PsDbMgr.newConnection();
 ResultSet rs;

 String dir=request.getParameter( "DIR" ); 
 String fulldir=PsConfig.get("ZSERVER_ROOT")+File.separator+dir;
 try
 {
	File f;
	f=new File(fulldir);
	String r[];
	r=f.list();
	for (int i=0;i<r.length;i++)
	{
		File t;
		t=new File(f,r[i]);
		if (t.isDirectory()==false)
		{
			Date filedate=new Date(f.lastModified());
			Time filetime=new Time(f.lastModified());
			String ftime=filetime.toString()+" "+filedate.toString();
		
			int filever=0;
			Date creationDate=new Date(0);
			Date lastChange=new Date(0);
			int countaccess=0;
	
			rs=conn.sqlQueryR("SELECT * FROM pzsrvfiles WHERE dirname='"+dir+"' AND filename='"+r[i]+"' ORDER BY filename");
			if (rs.next()==true)
			{
				filever=rs.getInt("filever");
				creationDate=rs.getDate("creationdate");
				lastChange=rs.getDate("lastChange");
				countaccess=rs.getInt("countaccess");
			}

	  %>
		<tr>
		<td><%=filever%></td>
		<td><%=r[i]%></td>
		<td><%=creationDate.toString()%></td>
		<td><%=ftime%></td>
		<td><%=countaccess%></td>
		</tr>
	  <%
		}
	}

 }
 catch (SecurityException e)
 {
	PsDebug.fail("Security Exception: "+e.getMessage());
 }


%>
</table>
</body>
</html>