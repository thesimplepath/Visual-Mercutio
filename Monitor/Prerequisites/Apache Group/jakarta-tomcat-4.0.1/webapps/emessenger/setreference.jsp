<html>
<%@ page import="java.util.*,java.lang.*,PsWf" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>
</head>

<body>
<%
 //String username=(String)session.getAttribute("USERNAME");
 //int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 int delivid=   Integer.valueOf(request.getParameter( "DELIVID" )).intValue();
 int refid=    Integer.valueOf(request.getParameter( "REFID" )).intValue(); 
 String redir=			request.getParameter( "REDIRECT" );

 PsWf.setReferenceStatus(caseid,procid,transid,delivid,refid);	
%>	

<script language=JavaScript>
<!--
//document.location="<%=redir%>";
//-->
</script>

</body>
</html>