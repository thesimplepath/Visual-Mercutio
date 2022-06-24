<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsConv" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<link href="css/tree.css" rel="styleSheet" type="text/css"> 

<script language=javaScript src="js/tree.js"></script>
<script language=JavaScript>
<!--
 function doAdd(parent)
 {
	name=window.prompt("Veuillez saisir le nom du nouveau groupe","");
	if (name=="null")
		name="";

	document.writeln("<form name=frm action=\"zusermgt1.jsp\" method=POST>");
	document.writeln("<input type=hidden name=MODE value=1>");
	document.writeln("<input type=hidden name=GRPPARENT value="+parent+">");
	document.writeln("<input type=hidden name=GRPNAME value=\""+name+"\">");
	document.writeln("</form>");
	document.writeln("<script language=JavaScript>");
	document.writeln("frm.submit();");
	document.writeln("</script>");
	//document.location="zusermgt1.jsp?MODE=1&GRPPARENT="+parent+"&GRPNAME="+escape(name);
 }

 function doDel(grpid)
 {
	document.location="zusermgt1.jsp?MODE=2&GRPID="+grpid;
 }

 var m=new oMenu;
<%
 PsApp.init();
 
 try {
	String mode=request.getParameter( "MODE" );
	String grpid=request.getParameter( "GRPID" );
	String grpparent=request.getParameter( "GRPPARENT" );
	String grpname=request.getParameter( "GRPNAME" );

	PsDbConn co=PsDbMgr.newConnection();

	if (mode!=null)
	  {
	   	if (mode.equals("1")==true)
		{
			//add
			ResultSet nxt=co.sqlQueryR("SELECT max(grpid)+1 as nxt FROM pzsrvgroup");
			nxt.next();
			grpid=nxt.getString("nxt");
			co.sqlExec("INSERT INTO pzsrvgroup VALUES ("+grpid+","+grpparent+",'"+co.cnv_sql(grpname)+"')");
		} 
	   	if (mode.equals("2")==true)
		{
			//del
			co.sqlExec("DELETE FROM pzsrvempmap WHERE grpid="+grpid);
			co.sqlExec("DELETE FROM pzsrvgroup WHERE grpid="+grpid);		
		} 
       }
	boolean firstPass=true;
	int maxWkgId=-1;
	ResultSet rs=co.sqlQueryR("SELECT * FROM pzsrvgroup ORDER BY grpid");
	while (rs.next())
	{
		String lnk="zusermgt2.jsp?WKGID="+rs.getInt("grpid");
		if (maxWkgId<rs.getInt("grpid")) 
			maxWkgId=rs.getInt("grpid")+1;		
		String txt=rs.getString("grpname");

		txt+=" <img src='img/add.gif' border=0 onclick=doAdd("+rs.getInt("grpid")+");>";

		if (firstPass==false)
		{
			txt+="<img src='img/remove.gif' border=0 onclick=doDel("+rs.getInt("grpid")+");>";
		}
		else
		{
			firstPass=false;
		}
		out.println("m.add("+rs.getInt("grpid")+","+rs.getInt("grpparent")+",\""+txt+"\",\""+lnk+"\");");
	}	

 }
 catch (SQLException e)
 {
   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
 }

%>
//-->
</script>
</head>

<body>
<script language=JavaScript>
<!--
 m.setTarget("usr");
 m.setIconDocument("img/doc.gif");
 m.setIconCollapse("img/close.gif");
 m.setIconExpand("img/open.gif");

 m.gen(true);
//-->
</script>
</body>
</html>