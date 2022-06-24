<?xml version="1.0" encoding="UTF-8"?>
<!--
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsBpml" %>
<%@ page contentType="text/plain" %>
ProcessSoft Mercutio BPML Export
<%
	String prm=request.getParameter( "MODELID" );
	if (prm==null)
		prm="0";
	int modelid=Integer.valueOf(prm).intValue();
%>
-->
<%=PsBpml.genBpml(modelid)%>