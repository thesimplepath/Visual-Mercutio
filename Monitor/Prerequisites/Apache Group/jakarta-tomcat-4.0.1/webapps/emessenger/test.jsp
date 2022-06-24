<html>
<%@ page import="PsApp,PsWf" %>
<%@ page session="true" %>
<head>
</head>
<body>
Hello,<br>

<%
 PsApp.init();
 
 int procid=3;
 int delivid=13;
 
 int ret=PsWf.getLateralReturn(procid,delivid);
 
 out.println("Proc de retour: "+ret);

%>
</html>