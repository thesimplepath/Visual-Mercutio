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
//-->
</script>
</head>
<body>
<form name=FRM action="config.jsp" method=POST>
<table>
<% 
  int mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
  PsApp.init(); 

  //mode 1
  if (mode==1)
  {
	PsDebug.log("CONFIG.JSP update configuration...");
	Enumeration pn=request.getParameterNames();
	for (; pn.hasMoreElements();) 
	{
		String key=(String)pn.nextElement();
		if (key.startsWith("CFG_")==true)
		{
			String val=(String)request.getParameter(key);
			key=key.substring(4) ;
			PsDebug.log("Set config "+key+"=("+val+")");
			PsConfig.set(key,val);
		}	
	}
	PsConfig.save("config.ini");
	PsDebug.log("Configuration Saved!");	
	System.out.println("Configuration updated successfully!");
	PsConfig.reset();
	PsConfig.load("config.ini");
  }

  Hashtable v; 
  v=PsConfig.getHashTable(); 
  Enumeration f=v.elements();
  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
	 String kn=(String)e.nextElement();
         out.println("<tr><td>"+kn+"</td>");
	 out.println("<td><input type=text size=80 name=\"CFG_"+kn+"\" value=\""+(String)f.nextElement()+"\"></td></tr>");
     }
  out.println("<input type=HIDDEN name=MODE value=1>");
 
%>
</table>
<input type=submit value=Save>
</form>
</body>
</html>