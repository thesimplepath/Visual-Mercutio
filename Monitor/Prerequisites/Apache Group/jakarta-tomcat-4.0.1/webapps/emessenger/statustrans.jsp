<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWf" %>
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<SCRIPT LANGUAGE="JavaScript">
<!--	
<%
  PsApp.init();

  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();

  int mode=             Integer.valueOf(request.getParameter( "MODE" )).intValue();
  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
  int caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();

  String redir= 	request.getParameter("REDIRECT");
  
  PsWf.doChangeStatusTrans(mode,caseid,procid,transid,userid,statusid);
%>

document.location = "<%=redir%>";
// --> 
</SCRIPT>

<body></body></html>