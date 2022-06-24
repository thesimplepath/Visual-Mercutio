<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsWf" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
</head>

<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 int delivid=0;
 String redirect=(String)request.getParameter( "REDIRECT" );

 PsWf.doSign(caseid,procid,transid,userid,delivid);

//manage dynamic attributes
 PsDebug.log("Save dynamic attributs");
 int nbr=	Integer.valueOf(request.getParameter( "NBR_INPUT" )).intValue(); 
	
 for (int i=1;i<=nbr;i++)
 {
	int modelid=1;
	String attribdefid=request.getParameter( "CTL2_"+i );
	String mval=request.getParameter( "CTL_"+i );
	conn.sqlExec("INSERT INTO pinputdata VALUES("+modelid+","+procid+","+attribdefid+","+caseid+","+transid+",'"+mval+"',"+conn.now()+")");
 }

%>

<script language=JavaScript>
<!--
document.location="<%=redirect%>";
//-->
</script>

</body>
</html>