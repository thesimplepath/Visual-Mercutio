<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>
<%@ page import="PsWf" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML><HEAD><TITLE>List Cases</TITLE>
<LINK href="css/global.css" rel=STYLESHEET>
<script language=JavaScript src="js/pss.js"></script>
<META http-equiv=Content-Type content="text/html; charset=iso-8859-1">
<!--********** Start: Global function **************-->
<SCRIPT language=JavaScript src="js/global.js">
</SCRIPT>

<script language=JavaScript>
<!--
function doChangeStatus(mode,caseid,transid,statusid)
{
	var url;
	url=document.location;
	document.location="statustrans.jsp?MODE="+mode+"&CASEID="+caseid+"&TRANSID="+transid+"&STATUSID="+statusid+"&REDIRECT="+url;
}

function sendChief(procid,caseid,transid)
{
//  alert("Send to chief "+procid+" / "+transid);
  document.location="chief.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid;
}

function doStartDeliv(procid,caseid,transid,delivid,lateral)
{
//  alert("Start Deliv :"+delivid);
  document.location="deliv.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&LATERAL="+lateral;
}

function retSender(procid,caseid,transid)
{
//  alert("Retour a l'envoyeur");
  document.location="return.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid;
}

//-->
</script>

</head>

<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT="0" MARGINWIDTH="0">
<%
  PsApp.init();

  PsDebug.log("Document= opendeliv.jsp");

  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();

  int caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

 try {
	PsDbConn conn=PsDbMgr.newConnection();

	//check if already locked (concurrency check)
	ResultSet rs;
	rs=conn.sqlQueryR("SELECT statusid,emplid FROM pproctrans WHERE procid="+procid+" AND transid="+transid);
	rs.next();
	if (rs.getInt("statusid")==1 && rs.getInt("emplid")!=userid)
	{
		out.println("alert(\"Travail déjà encours par le user "+rs.getInt("emplid")+"\");");
		return;
	}

	//automatic locking
	conn.sqlExecR("UPDATE pproctrans SET statusid=1,emplid="+userid+" WHERE procid="+procid+" AND transid="+transid);	

	rs=conn.sqlQueryR("SELECT * FROM pcase,ptrans,pproctrans WHERE pcase.caseid=ptrans.caseid AND ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND pproctrans.caseid="+caseid+" AND pproctrans.transid="+transid+" AND pproctrans.procid="+procid);
	rs.next();

	out.println("Case name: "+rs.getString("casename")+"<br>");
	out.println("Trans name: "+rs.getString("transname")+"<br>");
	out.println("Deliv:<br>");

	//Display from delivs
	boolean readyOrNot=false;

	rs=conn.sqlQueryR("SELECT mvalue FROM pproc,pprocattr WHERE pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid=59 AND pproc.procid="+procid);
	rs.next();
	String delivMaster;
	delivMaster=rs.getString("mvalue");

	rs=conn.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+caseid+" AND pdelivstatus.transid="+transid+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
	while (rs.next())
	{
		//lister les execs et forms
		if (rs.getInt("mstate")==1)
		{
			out.println("* <font color=red>"+rs.getString("delivname")+"</font> : OK<br>");
			if (rs.getString("delivname").equalsIgnoreCase(delivMaster))
			{
				readyOrNot=true;
			}
		}
		else
		{
			out.println("* "+rs.getString("delivname")+" : WAIT<br>");
			if (rs.getString("delivname").equalsIgnoreCase(delivMaster))
				out.println("--"+rs.getString("delivname")+" is the Master deliv from this combinaison, waiting on this to proceed<br>");
		}
	}

	out.println("<input type=button value=\"Procedure\" onclick=\"document.location='detailcase.jsp?CASEID="+caseid+"&PROCID="+procid+"&TRANSID="+transid+"';\">");	

    }
 catch (SQLException e)
    {
	PsDebug.fail("opendeliv.jsp: SQLException: "+e.getMessage());
    }
%>
</BODY></HTML>
