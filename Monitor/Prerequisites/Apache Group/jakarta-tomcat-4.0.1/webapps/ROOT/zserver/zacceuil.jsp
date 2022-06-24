<html>
<%@ page import="java.sql.*,PsApp,PsDbMgr,PsDbConn,PsConfig" %>
<head>
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

</head>

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on ztop.jsp
function delayedDisplay()
{
	var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>";
	var info2="";
	var tabno=0;
	top.showTabText(tabno,info1,info2);
}
//document.onload=delayedDisplay();
</script>
<!-- ------------------------------------ //-->

<body onload="delayedDisplay();">
<%=PsConfig.get("WELCOME_SCREEN")%>
</body>
</html>