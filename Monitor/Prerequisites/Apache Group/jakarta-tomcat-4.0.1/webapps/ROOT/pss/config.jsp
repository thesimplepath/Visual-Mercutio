<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<html>
<head>
<script language=JavaScript>
<!--
function doSubmit()
{
	alert("TODO");
}
//-->
</script>
</head>
<body>
<form name=FRM>
<table>
<% 
  PsApp.init(); 
  Hashtable v; 
  v=PsConfig.getHashTable(); 
  Enumeration f=v.elements();
  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
         out.println("<tr><td>"+(String)e.nextElement()+"</td>");
	 out.println("<td><input type=text size=80 value=\""+(String)f.nextElement()+"\"></td></tr>");
     }
 
%>
</table>
<input type=button value=Save onclick="doSubmit();">
</form>
</body>
</html>