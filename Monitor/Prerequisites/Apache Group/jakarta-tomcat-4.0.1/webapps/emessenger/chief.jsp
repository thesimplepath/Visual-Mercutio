<html>
<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsWf" %>
<%@ page import="PsDebug" %>

<head>
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<META http-equiv=Content-Type content="text/html; charset=utf-8">
</head>

<body>
<%
 String username=(String)session.getAttribute("USERNAME");
 int modelid=1;//TODO
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 String msg=	(String)request.getParameter( "MSG" );
 String redirect=	(String)request.getParameter( "REDIRECT" );

 //remise au chef
 PsWf.doChiefReturn(caseid,procid,transid,userid);

 try
   {
	 //text
	 if (msg!=null)
	 {
		PsApp.init();
		PsDbConn conn=PsDbMgr.newConnection();
		ResultSet rs=conn.sqlQueryR("SELECT * FROM pproctranstxt WHERE modelid="+modelid+" AND procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		if (rs.next()==true)
			conn.sqlExec("UPDATE pproctranstxt SET msg='"+PsDbConn.cnv_sql(msg)+"' WHERE modelid="+modelid+" AND procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
		else
			conn.sqlExec("INSERT INTO pproctranstxt VALUES ("+modelid+","+procid+","+caseid+","+transid+",'"+PsDbConn.cnv_sql(msg)+"')");
	 }
   }
catch (SQLException e)
    {
	PsDebug.fail("return.jsp: SQLException: "+e.getMessage());
    }

%>

<script language=JavaScript>
<!--
document.location="<%=redirect%>";
//-->
</script>

</body>
</html>