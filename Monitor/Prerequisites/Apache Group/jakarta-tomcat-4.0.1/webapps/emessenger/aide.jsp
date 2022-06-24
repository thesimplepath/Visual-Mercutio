<html>
<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<body>
<%
try {
	PsDebug.log("Delete all cases from database");
	PsDbConn conn=PsDbMgr.newConnection();
	conn.sqlExecR("delete from pcase");
	conn.sqlExecR("delete from ptrans");
	conn.sqlExecR("delete from pproctrans");
	conn.sqlExecR("delete from pattrib");
	conn.sqlExecR("delete from pproctransfrom");
	conn.sqlExecR("delete from pdelivlateralstate");
	conn.sqlExecR("delete from pdelivstatus");
	conn.sqlExecR("delete from ptaskstatus");
	conn.sqlExecR("delete from pdecisionstatus");
	conn.sqlExecR("delete from pinfostatus");
    }
 catch (SQLException e)
    {
	PsDebug.fail("aide.jsp: SQLException: "+e.getMessage());
    }
%>
Database cleaned !
</body></html>