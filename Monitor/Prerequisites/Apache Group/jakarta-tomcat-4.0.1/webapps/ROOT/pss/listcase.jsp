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

<html>
<head>
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>
<script language=JavaScript>
<!--
<%
//session check
 String xusername=(String)session.getAttribute( "USERNAME");
 int    userrole;
 if (xusername==null) 
   out.println("alert('Not logged');");
 else
   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
%>
//-->
</script>

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
<body>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

out.println("Liste des procedures libres pour <i>"+username+"</i>");
if (userrole==2)
 out.println("&nbsp;&nbsp;(Chef)");
out.println("<hr>");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	ResultSet rs;
	ResultSet rs2;

	PsWorkGroup w=new PsWorkGroup();
 	Vector r=w.listProcAllGranted(username);
 	int l=r.size();
	String procin;
	procin="";
 	for (int i=0;i<l;i++)
 	{
		int proc=((Integer)r.elementAt(i)).intValue();
		procin+=proc;
		if (i<l-1)
			procin+=",";
	}

	String chefflag;
	chefflag="";
	if (userrole==3) //hide "remise au chef" for simple employees
		chefflag=" AND chiefflag=0";

	rs=conn.sqlQueryR("SELECT distinct pcase.caseid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.* FROM pstatus,pproctrans,pproc,pmodel,pcase WHERE pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" GROUP BY pcase.caseid,pproctrans.caseid");
	while (rs.next())
	{
	String xx;
	xx="";
	
	out.println(rs.getString("modelname")+": #"+rs.getInt("procid")+" => "+rs.getString("casename")+" ("+rs.getString("statusname")+"/"+rs.getInt("emplid")+") "+xx+"<br>");

	int procid=rs.getInt("procid");
	rs2=conn2.sqlQueryR("SELECT pprocattr.attribdefid as attribdefid,pprocattr.mvalue as mvalue FROM pproc,pprocattr WHERE pproc.procid="+procid+" AND pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid>=13 AND pprocattr.attribdefid<=32");
	//tasks
	while (rs2.next())
	{
		if (rs2.getString("mvalue").length()>0)
			out.println("&nbsp;&nbsp;Task ("+rs2.getInt("attribdefid")+") = "+rs2.getString("mvalue")+"<br>");
	}
	//decisions
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,pprocattr WHERE pproc.procid="+procid+" AND pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid>=33 AND pprocattr.attribdefid<=52");
	while (rs2.next())
	{
		if (rs2.getString("mvalue").length()>0)
			out.println("&nbsp;&nbsp;Decision ("+rs2.getInt("attribdefid")+") = "+rs2.getString("mvalue")+"<br>");
	}

int transid=0;
int caseid=rs.getInt("caseid");
	rs2=conn2.sqlQueryR("SELECT pproctrans.statusid as sid,pstatus.statusname as sname,pstatus.*,pcase.*,pproctrans.*,ptrans.* FROM pstatus,pcase,pproctrans,ptrans WHERE ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid="+rs.getInt("caseid")+" AND pcase.caseid=pproctrans.caseid AND (pproctrans.statusid in (0,2) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) AND pproctrans.procid in ("+procin+")");
	//open cases
	while (rs2.next())
	 {
	transid=rs.getInt("transid");
		if (rs2.getInt("sid")==0 || rs2.getInt("sid")==2)		
		xx="<input type=button value=\"bloquer\" onclick=\"doChangeStatus(1,"+rs.getInt("procid")+","+rs.getInt("transid")+",1);\">";
		if (rs2.getInt("sid")==1)
			xx="<input type=button value=\"liberer\" onclick=\"doChangeStatus(1,"+rs.getInt("procid")+","+rs.getInt("transid")+",2);\">";
		if (rs2.getInt("sid")==1)
		{
			xx+="<br>&nbsp;&nbsp;Livrable lateraux:";
			PsDbConn c1=PsDbMgr.newConnection();
			ResultSet rx2=c1.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+rs.getInt("procid")+" AND lateral=1");
			while (rx2.next())
			{
				xx+="<input type=button value=\""+rx2.getString("delivname")+"\" onclick=\"doStartDeliv("+procid+","+caseid+","+transid+","+rx2.getString("delivid")+",1);\">";

				PsDbConn kc=PsDbMgr.newConnection();
				int retdelivid=PsWf.getLateralReturn(procid,rx2.getInt("delivid"));
				ResultSet ks=kc.sqlQueryR("SELECT openclose FROM pdelivlateralstate WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+retdelivid);
				if (ks.next()==true)
				{
					if (ks.getInt("openclose")==1)
						xx+="(done) ";
					else
						xx+="(wait) ";
				}

				//mendatory deliv
				double pct=PsWf.percentageDeliv(rx2.getInt("delivid"));
				if (pct>=99.999)
					xx+="(mandatory) ";
				
			}

			xx+="<br>&nbsp;&nbsp;Livrable:";
			PsDbConn c=PsDbMgr.newConnection();
			ResultSet rx=c.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+rs.getInt("procid")+" AND lateral=0");
			while (rx.next())
			{
				xx+="<input type=button value=\""+rx.getString("delivname")+"\" onclick=\"doStartDeliv("+procid+","+caseid+","+transid+","+rx.getInt("delivid")+",0);\">";

				//mendatory deliv
				double pct=PsWf.percentageDeliv(rx.getInt("delivid"));
				if (pct>=99.999)
					xx+="(mandatory) ";

			}
		}
		out.println("&nbsp;&nbsp;&nbsp;<a href=\"showattrib.jsp?CASEID="+rs2.getInt("caseid")+"&TRANSID="+rs2.getInt("transid")+"\">"+rs2.getInt("transid")+"</a> : "+rs2.getString("transname")+" ("+rs2.getString("statusname")+"/"+rs2.getInt("emplid")+")"+xx+"<br>");
	 }
	out.println("<input type=button value=\"Retour à l'envoyeur\" onclick=\"retSender("+procid+","+caseid+","+transid+");\">");
if (userrole==3)
        out.println("<input type=button value=\"Remise au chef\" onclick=\"sendChief("+procid+","+caseid+","+transid+");\">");
out.println("<hr><hr>");
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
    }
%>
</body>
</html>