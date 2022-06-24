<%@ page import="PsApp" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsAuthentication" %>
<html>
<head>
<LINK href="css/global.css" rel=STYLESHEET type="text/css">
<script language=JavaScript src="js/pss.js"></script>
</head>
<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>
<TABLE width="100%" border=0>
<%
  PsApp.init();

  int caseattachid = 	Integer.valueOf(request.getParameter( "CASEATTACHID" )).intValue();
  String casename =     request.getParameter("CASENAME" );
  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
  String transname = 	request.getParameter( "TRANSNAME" );
  int parenttransid= 	Integer.valueOf(request.getParameter( "PARENTTRANSID" )).intValue();
  int empid= 		Integer.valueOf(request.getParameter( "EMPID" )).intValue();
  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
  int globalyn = 	Integer.valueOf(request.getParameter( "GLOBALYN" )).intValue();
  int qty = 		Integer.valueOf(request.getParameter( "QTY" )).intValue();

  int fromproc = 	Integer.valueOf(request.getParameter( "FROMPROC" )).intValue();

  out.println("<TBODY>");
  out.println("<TR>");
  out.println(" <TD width=\"11%\">&nbsp;</TD>");
  out.println(" <TD class=NormalBlack vAlign=top width=\"89%\">Nouveau cas créé: "+casename+"</TD>");
  out.println(" <TR>");
  out.println(" <TD width=\"11%\" height=454>&nbsp;</TD>");
  out.println(" <TD class=NormalBlack vAlign=top width=\"89%\" height=454>");
  out.println("   <P>&nbsp;</P>");
  out.println("   <P>Le message a été envoyé dans la boîte de travail de la procédure:</P>");

 try {
	PsDbConn conn=PsDbMgr.newConnection();

	ResultSet rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid);
	rs.next();
	out.println("   <P><B>"+rs.getString("delivname")+"</B></P></TD></TR>");

	int caseid;
	if (caseattachid<0)
		caseid=conn.nextVal("PCASE");
	else
		caseid=caseattachid;

	int attribid=conn.nextVal("PATTRIB");
	String txindate=conn.now();

	if (caseattachid==-1)
		conn.sqlExecR("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+casename+"')");
	conn.sqlExecR("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+transname+"',"+globalyn+","+attribid+",0)");
	conn.sqlExecR("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+")");

  	for (int i=0;i<qty;i++)
	{
	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
	    int attribdefid=	Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
	    String mkey=	request.getParameter( "KEY"+i );
	    String mval=	request.getParameter( "VAL"+i );
	conn.sqlExecR("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
	}	
    }
 catch (SQLException e)
    {
	PsDebug.fail("newproc2.jsp: SQLException: "+e.getMessage());
    }
%>
</tbody></table>

<SCRIPT language=javascript>
//top.menu.showTab(4);
</script>
</body>
</html>