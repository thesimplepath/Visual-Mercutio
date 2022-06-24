<html>
<%@ page import="java.util.*,java.lang.*,PsWf,PsDbMgr,PsDbConn,PsDebug,PsApp" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
</head>

<body>
<%
 String username=(String)session.getAttribute("USERNAME");
 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 int delivid=	Integer.valueOf(request.getParameter( "DELIVID" )).intValue();

 int lat=	Integer.valueOf(request.getParameter( "LATERAL" )).intValue(); //0=no,1=yes
 String redirect=(String)request.getParameter( "REDIRECT" );

 PsWf.doSendDeliv(caseid,procid,transid,userid,delivid,lat);

 PsApp.init();

 //manage dynamic attributes
 PsDebug.log("Save dynamic attributs");
 int nbr=	Integer.valueOf(request.getParameter( "NBR_INPUT" )).intValue(); 
 PsDbConn conn=PsDbMgr.newConnection();
 for (int i=1;i<=nbr;i++)
 {
	int modelid=1;
	String attribdefid=request.getParameter( "CTL2_"+i );
	String mval=request.getParameter( "CTL_"+i );
	conn.sqlExec("INSERT INTO pinputdata VALUES("+modelid+","+delivid+","+attribdefid+","+caseid+","+transid+",'"+mval+"',"+conn.now()+")");
 }
%>

<script language=JavaScript>
<!--
//alert(document.location);
document.location="<%=redirect%>&SESSION=<%=session.getId()%>";
//-->
</script>

</body>
</html>