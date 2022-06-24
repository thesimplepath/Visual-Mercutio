<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<html>
<body>
<%
  PsApp.init();

  int procid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

 try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs=conn.sqlQueryR("SELECT * FROM pattrib WHERE caseid="+procid+" AND transid="+transid+" ORDER BY segid,attribid");
	while (rs.next())
	{
		out.println(rs.getInt("segid")+" | "+rs.getString("mkey")+" = "+rs.getString("mvalue")+"<br>");
	}
    }
 catch (SQLException e)
    {
	PsDebug.fail("statustrans.jsp: SQLException: "+e.getMessage());
    }
%>
</body></html>