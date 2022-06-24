<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>

<html>
<head>
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript>
<!--
//-->
</script>
</head>

<body>
<%
 PsApp.init();
 
// try {
	int wkgid=2;
	String lst=String.valueOf(wkgid);
	PsWorkGroup w=new PsWorkGroup();
	Vector r=w.listSubWorkGroup(wkgid);
	int l=r.size();
	if (l>0)
	  lst+=",";
	for (int i=0;i<l;i++)
	{
		lst+=String.valueOf((Integer)r.elementAt(i));
		if (i<l-1)
			lst+=",";
	}
    out.println(lst);
// }
// catch (SQLException e)
 {
	PsDebug.fail("grp_suivants.jsp: "+e.getMessage());
 }

%>

</body>
</html>