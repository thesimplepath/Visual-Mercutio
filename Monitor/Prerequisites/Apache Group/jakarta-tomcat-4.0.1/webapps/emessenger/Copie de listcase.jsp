<HTML>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf" %>
<HEAD><TITLE>Search Cases</TITLE>
<jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<META http-equiv=Content-Type content="text/html; charset=utf-8">


<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 if (username==null) return;
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 int mode=0;
 
 if (request.getParameter( "MODE" )!=null)
	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();

 String searchKey="";
 if    (mode==2)
 {
	searchKey=request.getParameter("KEYSEARCH");
	if (searchKey==null) searchKey="";
 }

%>

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on top.jsp
var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)";
var info2="";
var tabno=1+<%=mode%>;
top.showTabText(tabno,info1,info2);
</script>
<!-- ------------------------------------ //-->

</head>

<BODY>
<FORM action="listcase.jsp" method=POST>
<INPUT TYPE=HIDDEN NAME=MODE VALUE=2>
<TABLE width="100%" border=0>
  <TR>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%" nobr>
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
<%
if (mode==2) {
%>
	<TR class=Bg>
	<TD width="3%">&nbsp;</TD>
	<TD width="17%">Recherche:</TD>
	<TD width="70%" colspan=5><input type=text NAME=KEYSEARCH  value="<%=searchKey%>" style="width:100%;"></td>
	<TD width="10%" align=center><input type=submit class=sbttn value="Recherche"></TD>
	</TR>

	<TR height=5><td colspan=8>&nbsp;</td></tr>
<%
 }
%>
        <TR class=Bg>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="17%"><NOBR><A title="Trier par statut" 
            href=""><FONT 
            class=menu>Statut</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
<%
if (mode==2) {
%>			
          <TD width="31%" class=BgL><NOBR><A title="Trier par expéditeur" 
            href=""><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0><FONT 
            class=swnub>Livrables de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="18%"><NOBR><A title="Trier par procedure" 
            href=""><FONT 
            class=menu>Procédure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="10%"><NOBR><A title="Trier par date" 
            href=""><FONT 
            class=menu>Utilisateur</FONT></A>&nbsp;</NOBR></TD>			
<%
 } else {
%>
          <TD width="36%" class=BgL><NOBR><A title="Trier par expéditeur" 
            href=""><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0><FONT 
            class=swnub>Livrables de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="23%"><NOBR><A title="Trier par procedure" 
            href=""><FONT 
            class=menu>Procédure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
<%
 }
 %>			
          <TD width="10%"><NOBR><A title="Trier par date" 
            href=""><FONT 
            class=menu>Date creation</FONT></A>&nbsp;</NOBR></TD>
          <TD width="10%"><NOBR><A title="Trier par date" 
            href="">
            <FONT class=menu>Date d'arrivée</FONT></A>&nbsp;</NOBR></TD>
          <TD align=right width="17%"><NOBR>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<A title="Trier par cas" 
            href=""><FONT 
            class=menu>Cas</FONT></A>&nbsp;</NOBR></TD></TR>
<%
try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	PsDbConn conn3=PsDbMgr.newConnection();
	ResultSet rs;
	ResultSet rs2;
	ResultSet rs3;

	PsWorkGroup w=new PsWorkGroup();
 	Vector r=w.listProcAllGranted(username);

 	int l=r.size();
	String procin;
	procin="";
	//build the proc granted list
	if (mode!=2)
	{
	 	for (int i=0;i<l;i++)
	 	{
			int proc=((Integer)r.elementAt(i)).intValue();
			procin+=proc;
			if (i<l-1)
				procin+=",";
		}	
	}	
	
	//generate the full procin for search
	if (mode==2)
	{
		procin="";
		rs=conn.sqlQueryR("SELECT procid FROM pproc");
		boolean outa=rs.next();	
		while (outa)
		{
			procin=procin+rs.getString("procid");
			outa=rs.next();
			if (outa==true)
				procin=procin+",";
		}
	}

	//nothing to see...abort
	if (procin.length()<=0)
		return;
		
	
	String chefflag;
	chefflag="";
	if (userrole==3) //hide "remise au chef" for simple employees
		chefflag=" AND chiefflag=0";

	if (mode==0) //workbasket
		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
	else if (mode==1)     //open deliv
		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND pproctrans.statusid=1 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
	else     //search
		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pcase.casename like '%"+searchKey+"%' OR ptrans.transname like '%"+searchKey+"%') "+chefflag+" AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");

 //display each rows
 if ((mode==2 && searchKey!=null) || (mode!=2))
 {
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
	String indate=rs.getString("indate"); // depuis la table pprocttrans
	String procname=rs.getString("mvalue");
	String livrables="";


//TODO: manage AND/OR logical operators
	//check Distrib rules
	boolean skipIt=false;
	rs2=conn2.sqlQueryR("SELECT * FROM pdistribmap WHERE modelid="+rs.getInt("modelid")+" AND pdattribid="+procid);

	if (rs2.next()==true)
	{
		int caseid=rs.getInt("caseid");
		int transid=rs.getInt("transid");

		int wkgid=rs.getInt("wkgid");

		PsDebug.log("Test Distribution rules for wkgid="+wkgid);

 	        PsWorkGroup pw=new PsWorkGroup();
		rs2=conn2.sqlQueryR("SELECT * FROM pworkgroup,pempmap WHERE pworkgroup.wkgid=pempmap.wkgid AND pworkgroup.wkgparent="+wkgid+" AND pempmap.login='"+username+"'");
		while (rs2.next())
		{
		   String wkgtree=rs2.getString("wkgid");
		   PsDebug.log("==>test wkgid "+wkgtree+"?");
		   rs3=conn3.sqlQueryR("SELECT * FROM pattribdef,pdistribmap,pdistrib,pinputdata WHERE pattribdef.attribdefid=pinputdata.attribdefid AND pdistrib.modelid=pdistribmap.modelid AND pdistrib.modelid=pinputdata.modelid AND pdistrib.attribdefid=pinputdata.attribdefid AND pdistrib.attribdefid=pdistribmap.attribdefid AND pdistrib.wkgid = "+wkgtree+" AND pdistribmap.pdattribid="+procid+" AND pinputdata.caseid="+caseid+" AND pinputdata.transid="+transid);//pdistribmap.pdattribid=pinputdata.pdattribid AND 


		   boolean t=true;
		   skipIt=true;//by default, skip
		   int nbrlinesinrule=0;
		   while (rs3.next())
		   {
			nbrlinesinrule++;
			String s1=rs3.getString("mdata").trim();
			String s2=rs3.getString("mval").trim();			
			double v1=0.0;
			double v2=0.0;
			try {
			v1=Double.valueOf(s1).doubleValue();
			v2=Double.valueOf(s2).doubleValue();
			} catch (NumberFormatException e) {
				//nothing...forget about this exception...the purpose there is juste for forcing conversion to double...but it's not a number
			}

			int mop=rs3.getInt("mop");//1 is ==, < <= >= > !=
			int lop=rs3.getInt("mlop");//0 AND 1=OR

			int mtype=rs3.getInt("attribdeftype");//0=unknown 1=string, others should be numeric

			if (mtype==0 || mtype==1) 
			{//string
				if (mop==1) {if (!(s1.equals(s2)==true)) t=false;}
					else
				if (mop==2) {if (!(s1.compareTo(s2)<0)) t=false;}
					else
				if (mop==3) {if (!(s1.compareTo(s2)<=0)) t=false;}
					else
				if (mop==4) {if (!(s1.compareTo(s2)>=0)) t=false;}
					else
				if (mop==5) {if (!(s1.compareTo(s2)>0)) t=false;}
					else
					  {if (!(s1.equals(s2)!=true)) t=false;}
			}
			else
			{//numeric
				if (mop==1) {if (!(v1==v2)) t=false;}
					else
				if (mop==2) {if (!(v1<v2)) t=false;}
					else
				if (mop==3) {if (!(v1<=v2)) t=false;}
					else
				if (mop==4) {if (!(v1>=v2)) t=false;}
					else
				if (mop==5) {if (!(v1>v2)) t=false;}
					else
					  {if (!(v1!=v2)) t=false;}
			}

		   }//while rs3

		   if (t==true && nbrlinesinrule>0)
		   {
			skipIt=false;//ok, distribution rule was found
			PsDebug.log("Distribution rule found on proc "+procid+". Workgroup "+rs2.getInt("wkgid")+" was choosed");
			break;
		   }
			
		}//while rs2
	}//if

	
   if (skipIt==false)
   {
	//status information (checkbox display)
	int statusid=rs.getInt("stid");
	String checked="";
	if (statusid==1)
		checked="checked";

	//Display from delivs
	boolean readyOrNot=false;

	rs2=conn2.sqlQueryR("SELECT mvalue FROM pproc,ppdattr WHERE pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=31457284 AND pproc.procid="+procid);//master
	String delivMaster;
	boolean hasDelivMaster=true;
	if (rs2.next()==true)
	{
		delivMaster=rs2.getString("mvalue");
		if (delivMaster.length()==0)
			hasDelivMaster=false;
	}
	else
	{
		delivMaster="";
		hasDelivMaster=false;
	}

	String dummy="";

	livrables="Start";
	rs2=conn2.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
//System.out.println("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
	while (rs2.next())
	{		
		String dname=rs2.getString("delivname");
//System.out.println(dname+"=="+delivMaster);
		if (dname.equals(delivMaster))
		{
			readyOrNot=true;
		}
		else
		{
			dummy=dummy+" "+dname;
		}
		
	}

	//No deliv, so it means it's a new case
	if (dummy.length()==0 && hasDelivMaster==false) 
	{
		dummy="Nouveau Cas";
		//bug just in case, search for a lateral loop
		//todo: this is not checked... what happens when having more than one lateral deliv ?
		rs3=conn3.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc  AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND procidtrg="+procid);
		if (rs3.next()==true)
		{
			dummy=rs3.getString("delivname");
		}
	}
	
	//deliv display
	livrables=delivMaster + " "+ dummy;

	//if master of the combination has not been received, then hide the combination
	boolean skipRow=false;
	if (hasDelivMaster==true && readyOrNot==false)		
		skipRow=true;		
System.out.println("############=> skipRow="+skipRow+" hasDelivMaster:"+hasDelivMaster+" readyOrNot:"+readyOrNot+" liv:"+livrables+"("+delivMaster+")");
	//links
	String plink="detailcase.jsp?CASEID="+rs.getInt("caseid")+"&PROCID="+procid+"&TRANSID="+rs.getString("transid");
	//String llink="opendeliv.jsp?CASEID="+rs.getInt("caseid")+"&PROCID="+procid+"&TRANSID="+rs.getString("transid");

	//switch
	int statuschangeid=2; //free
	if (statusid==0 || statusid==2)
		statuschangeid=1;//locked

	//enhance status
	if (rs.getInt("chiefflag")!=0)
		statusname= "Chef : "+statusname;

	String userlock="&nbsp;";
	if (mode==2)
	{
		rs2=conn2.sqlQueryR("SELECT * FROM pproctrans,pemployee WHERE pproctrans.procid="+procid+" AND pproctrans.caseid="+rs.getString("caseid")+" AND pproctrans.transid="+rs.getString("transid")+" AND pproctrans.emplid=pemployee.emplid");
		if (rs2.next()==true)
			userlock=rs2.getString("login");
	}	

	//display row
	if (skipRow==false)
	{
	out.println("<TR>");
	out.println("<TD width=\"3%\"><img src=\"img/st"+rs.getInt("stid")+".gif\" border=0 alt=\""+statusname+"\">&nbsp;</TD>");
	
      	out.println("<TD width=\"15%\">"+statusname+"</TD>");

	if (mode!=2)
		{//links in mode 0 and 1
      	out.println("<TD width=\"23%\"><A href=\""+plink+"\">"+livrables);
	//TODO: modelid
	int modelid=1;
	rs3=conn3.sqlQueryR("SELECT * FROM pproctranstxt WHERE modelid="+modelid+" AND procid="+procid+" AND caseid="+rs.getInt("caseid")+" AND transid="+rs.getInt("transid"));
	if (rs3.next()==true)
	{
		String msg=rs3.getString("msg");
		if (msg.length()>0)
			out.println("<br>Message: "+msg);
	}
	out.println("</A></TD>");
      	out.println("<TD width=\"21%\">"+procname+"</TD>");
		}
		else
		{//tracking link in mode=2
	plink="tracking.jsp?CASEID="+rs.getInt("caseid")+"&TRANSID="+rs.getString("transid");
      	out.println("<TD width=\"18%\"><A href=\""+plink+"\">"+livrables+"</A></TD>");
      	out.println("<TD width=\"16%\">"+procname+"</TD>");
      	out.println("<TD width=\"10%\">"+userlock+"</TD>");		
		}
		
      	out.println("<TD width=\"10%\">"+txindate+"</TD>");
      	out.println("<TD width=\"10%\">"+indate+"</TD>");
      	out.println("<TD align=right width=\"17%\">"+casename+","+transname+"</TD></TR>");
	}//if
	}//while
   }//skipIt
 }//if
    }
catch (SQLException e)
    {
	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
    }
%>
</TABLE>
</TD>
</TR>
</TABLE>
</FORM>
</BODY>
</HTML>
