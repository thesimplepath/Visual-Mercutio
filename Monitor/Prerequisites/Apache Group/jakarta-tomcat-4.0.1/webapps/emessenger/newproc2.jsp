<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsAuthentication" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
<script language=JavaScript src="js/pss.js"></script>
</head>
<BODY>
<TABLE width="100%" border=0>
<%
  PsApp.init();

  int caseattachid = 	Integer.valueOf(request.getParameter( "CASEATTACHID" )).intValue();
  String casename =     request.getParameter("CASENAME" );
  int procid = 			Integer.valueOf(request.getParameter( "PROCID" )).intValue();
  int transid = 		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
  String transname = 	request.getParameter( "TRANSNAME" );
  int parenttransid= 	Integer.valueOf(request.getParameter( "PARENTTRANSID" )).intValue();
  int empid= 			Integer.valueOf(request.getParameter( "EMPID" )).intValue();
  int statusid = 		Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
  int globalyn = 		Integer.valueOf(request.getParameter( "GLOBALYN" )).intValue();
  int qty = 			Integer.valueOf(request.getParameter( "QTY" )).intValue();

  int fromproc = 		Integer.valueOf(request.getParameter( "FROMPROC" )).intValue();

  %>
  <TBODY>
  <TR>
  	<TD width="11%">&nbsp;</TD>
  	<TD class=NormalBlack vAlign=top width="89%">Nouveau cas créé: <%=casename%>, <%=transname%></TD>
  </TR>
  <TR>
  	<TD width="11%">&nbsp;</TD>
  	<TD class=NormalBlack vAlign=top width="89%"><P>&nbsp;</P><P>Le message a été envoyé dans la boîte de travail de la procédure:</P>
<%
 try {
	PsDbConn conn=PsDbMgr.newConnection();

	ResultSet rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid);
	rs.next();
	%>
		<P><B><%=rs.getString("delivname")%></B></P></TD></TR>
	<%
	int caseid;
	if (caseattachid<0)
		caseid=conn.nextVal("PCASE");
	else
		caseid=caseattachid;

	int attribid=conn.nextVal("PATTRIB");
	String txindate=conn.now();

	if (caseattachid==-1)
		conn.sqlExecR("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+PsDbConn.cnv_sql(casename)+"')");
	conn.sqlExecR("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+PsDbConn.cnv_sql(transname)+"',"+globalyn+","+attribid+",0)");
	conn.sqlExecR("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+","+conn.now()+")");

  	for (int i=0;i<qty;i++)
	{
	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
	    int attribdefid=Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
	    String mkey=	request.getParameter( "KEY"+i );
	    String mval=	request.getParameter( "VAL"+i );
		conn.sqlExecR("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
	}	
%>
</TR>
  <TR>
  	<TD width="11%">&nbsp;</TD>
  	<TD class=NormalBlack vAlign=top width="89%"><P>&nbsp;</P><P>Veuillez valider le(s) livrable(s) en sortie du point de démarrage en cliquant sur le bouton ci-dessous.</p>
<INPUT TYPE=button class=sbttn value="Validation Livrable(s)" onclick="javascript:goDetail();">
</TD>
  </TR>
</tbody></table>
<script language=JavaScript>
function goDetail()
{
	var url="detailcase.jsp?CASEID=<%=caseid%>&PROCID=<%=procid%>&TRANSID=<%=transid%>";
	document.location=url;
	return false;
}
</script>
<%
   }
 catch (SQLException e)
    {
		PsDebug.fail("newproc2.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>