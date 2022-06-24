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

<SCRIPT language=javascript>
top.menu.showTabText(1+<%=Integer.valueOf(request.getParameter( "MODE" )).intValue()%>,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","");
function CA()
{
//update all status to on/off and refresh display
alert("TODO");
document.location=document.location;
}
</SCRIPT>
<!--
<%
 PsDebug.log("Document= listcase.jsp");
%>
//-->
</script>

<script language=JavaScript>
<!--
function doChangeStatus(mode,caseid,transid,statusid)
{
	var url;
	url=escape(document.location);
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
<TABLE width="100%" border=0>

  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 
        width="100%"><INPUT type=hidden value=F000000001 name=curmbox> <INPUT 
        type=hidden name=js> <INPUT type=hidden name=_HMaction> <INPUT 
        type=hidden value=inbox name=foo> <INPUT type=hidden name=page> 
        <TR bgColor=#336699>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/ard.gif"></TD>
          <TD width="17%"><NOBR><A title="Trier par statut" 
            href=""><FONT 
            class=swb 
            color=#ffffff>Statut</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="36%" bgColor=#93bee2><NOBR><A title="Trier par expéditeur" 
            href=""><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/desc.gif" width=7 border=0><FONT 
            class=sbbd
            color=#003366>Livrable de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="23%"><NOBR><A title="Trier par procedure" 
            href=""><FONT 
            class=swb 
            color=#ffffff>Procedure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="10%"><NOBR><A title="Trier par date" 
            href=""><FONT 
            class=swb color=#ffffff>Date creation</FONT></A>&nbsp;</NOBR></TD>
          <TD width="10%"><NOBR><A title="Trier par date" 
            href="">
            <FONT class=swb color=#ffffff>Date d'arrivée</FONT></A>&nbsp;</NOBR></TD>
          <TD align=right width="17%"><NOBR>&nbsp;<A title="Trier par cas" 
            href=""><FONT 
            class=swb color=#ffffff>Cas</FONT></A>&nbsp;</NOBR></TD></TR>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 int mode = 	Integer.valueOf(request.getParameter( "MODE" )).intValue();

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

	if (mode==0) //workbasket
		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,pprocattr.*,ptrans.* FROM ptrans,pprocattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND pprocattr.procattribid=pproc.procattribid AND pprocattr.attribdefid=0 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
	else	     //open deliv
		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,pprocattr.*,ptrans.* FROM ptrans,pprocattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND pprocattr.procattribid=pproc.procattribid AND pprocattr.attribdefid=0 AND pproctrans.statusid=1 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");

	//loop for each delivs
	while (rs.next())
	{
	String casename=rs.getString("casename");
	String transname=rs.getString("transname");
	String modelname=rs.getString("modelname");
	int    procid=rs.getInt("procid");
	String statusname=rs.getString("statusname");
	int    emplid=rs.getInt("emplid");
	String txindate=rs.getString("txindate");
	String indate=txindate;//TODO: rs.getString("indate"); depuis la table pprocttrans
	String procname=rs.getString("mvalue");
	String livrables="";

	//status information (checkbox display)
	int statusid=rs.getInt("stid");
	String checked="";
	if (statusid==1)
		checked="checked";

	//Display from delivs
	boolean readyOrNot=false;

	rs2=conn2.sqlQueryR("SELECT mvalue FROM pproc,pprocattr WHERE pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid=59 AND pproc.procid="+procid);
	String delivMaster;
	if (rs2.next()==true)
		delivMaster=rs2.getString("mvalue");
	else
		delivMaster="Start";

	String dummy="";

	livrables="Start";
	rs2=conn2.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
	while (rs2.next())
	{		
		dummy=rs2.getString("delivname");
		if (dummy.equalsIgnoreCase(delivMaster)==true) 
		{
			livrables=dummy; //livrable d'origine
			break;
		}
	}
	
	//TODO: ici je force le livrable maitre, mais il faut en parler avec Eric et Dom
	livrables=delivMaster + " ("+ dummy +")";


	//build deliv list (but must be done differently TODO)
/*
	rs2=conn2.sqlQueryR("SELECT distinct mvalue FROM pdeliv,pdelivattr,pproctransfrom WHERE pproctransfrom.procid="+procid+" AND pproctransfrom.refprocid=pdeliv.procidsrc AND pdeliv.procidtrg="+procid+" AND pdeliv.delivattribid=pdelivattr.delivattribid AND pdelivattr.attribdefid=0 ORDER BY pdeliv.delivname");
	if (rs2.next()==true)
	{
		livrables=rs2.getString("mvalue");
	}
	else
		livrables="Start";
	*/

	//links
	String plink="detailcase.jsp?CASEID="+rs.getInt("caseid")+"&PROCID="+procid+"&TRANSID="+rs.getString("transid");
	String llink="opendeliv.jsp?CASEID="+rs.getInt("caseid")+"&PROCID="+procid+"&TRANSID="+rs.getString("transid");

	//switch
	int statuschangeid=2; //free
	if (statusid==0 || statusid==2)
		statuschangeid=1;//locked

	//enhance status
	if (rs.getInt("stid")!=0)
		statusname= "Chef : "+statusname;

	

	//display row
	out.println("<TR>");
	out.println("<TD width=\"3%\"><INPUT onclick=doChangeStatus(1,"+rs.getInt("procid")+","+rs.getInt("transid")+","+statuschangeid+"); type=checkbox "+checked+"> </TD>");
      	out.println("<TD width=\"15%\">"+statusname+"</TD>");
      	out.println("<TD width=\"23%\"><A href=\""+plink+"\">"+livrables+"</A></TD>");
      	out.println("<TD width=\"21%\"><A href=\""+plink+"\">"+procname+"</A></TD>");
      	out.println("<TD width=\"10%\">"+txindate+"</TD>");
      	out.println("<TD width=\"10%\">"+indate+"</TD>");
      	out.println("<TD align=right width=\"17%\">"+casename+","+transname+"</TD></TR>");
	}	
    }
catch (SQLException e)
    {
	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
    }
%>
</TABLE>

</BODY></HTML>
