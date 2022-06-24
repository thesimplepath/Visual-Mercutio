<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf,PsConv" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

</head>
<%
  PsApp.init();

  String username=(String)session.getAttribute("USERNAME");
  if (username==null) return;
  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
  int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
 
  int modelid=1;//TODO

  PsDbConn conn,conn2;
  ResultSet rs,rs2;
  conn=PsDbMgr.newConnection();	
  conn2=PsDbMgr.newConnection();	

  String searchKey=request.getParameter( "KEYSEARCH" );
  if (searchKey==null)
	searchKey="";

  PsWorkGroup w=new PsWorkGroup();
  Vector r=w.listProcAllGranted(username);
  int l=r.size();
  String procin;
  procin="";
  //build the proc granted list
  for (int i=0;i<l;i++)
  {
	int proc=((Integer)r.elementAt(i)).intValue();
	procin+=proc;
	if (i<l-1)
		procin+=",";
  }		

%>
<body>
<FORM action="stats100.jsp" method=POST>
<INPUT TYPE=HIDDEN NAME=MODE VALUE=2>
<TABLE width="100%" border=0>
  <TR>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%" nobr>
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
	<TR class=Bg>
	<TD width="3%">&nbsp;</TD>
	<TD width="6%">Recherche:</TD>
	<TD width="81%" colspan=6><input type="text" NAME="KEYSEARCH"  value="<%=searchKey%>" style="width:100%;"></td>
	<TD width="10%" align=center><input type=submit class=sbttn value="Recherche"></TD>
	</TR>

	<TR height=5><td colspan=9>&nbsp;</td></tr>
	
	<TR class=Bg>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="6%"><NOBR><FONT class=menu>Nombre</FONT>&nbsp;</NOBR></TD>
	  <TD width="6%"><NOBR><FONT class=menu>Charge j*h</FONT>&nbsp;</NOBR></TD>
	  <TD width="26%"><NOBR><FONT class=menu>Combinaisons</FONT>&nbsp;</NOBR></TD>
	  <TD width="20%"><NOBR><FONT class=menu>Procédure</FONT>&nbsp;</NOBR></TD>
	  <TD width="12%"><NOBR><FONT class=menu>Age moyen</FONT>&nbsp;</NOBR></TD>
	  <TD width="12%"><NOBR><FONT class=menu>Ligne verte</FONT>&nbsp;</NOBR></TD>
	  <TD width="6%"><NOBR><FONT class=menu>Ecart %</FONT>&nbsp;</NOBR></TD>
	  <TD align="right" width="3%"><NOBR><FONT class=menu>Statut</FONT>&nbsp;</NOBR></TD>
	</TR>
<%
	rs=conn.sqlQueryR("SELECT distinct pcase.caseid,ptrans.transid,pproc.procid as procid,ppdattr.mvalue as mvalue ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pcase.casename like '%"+searchKey+"%' OR ptrans.transname like '%"+searchKey+"%') AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
	String combinationname="";
	int number=0;
	int masterid=-1;
	Calendar now;
	long nowt;
	while (rs.next())
	{
	int caseid=rs.getInt("caseid");
	int transid=rs.getInt("transid");
	int procid=rs.getInt("procid");

	rs2=conn2.sqlQueryR("SELECT count(pdeliv.delivid) as number,pdeliv.delivname,pdelivstatus.mdated FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getInt("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid+" GROUP BY pdeliv.delivid");

	if (rs2.next()==true)
	{
	combinationname=rs2.getString("delivname");//find out the right master
	number=rs2.getInt("number");

	//get info about master deliv - greenLine
	masterid=PsWf.getMasterDelivFromCombination(modelid,procid,caseid,transid);
	}//if rs2.next	

	now=Calendar.getInstance();
	nowt=now.get(Calendar.DAY_OF_YEAR)*86400+now.get(Calendar.HOUR_OF_DAY)*3600+now.get(Calendar.MINUTE)*60+now.get(Calendar.SECOND);
	String tmp="";
	rs2=conn2.sqlQueryR("SELECT ppdattr.mvalue FROM pdeliv,ppdattr WHERE pdeliv.modelid="+modelid+" AND pdeliv.delivid="+masterid+" AND ppdattr.pdattribid=pdeliv.delivid AND ppdattr.attribdefid=15728647 ORDER BY ppdattr.attribdefid");		
	if (rs2.next()==true)
		tmp=rs2.getString("mvalue").trim();
	if (tmp.length()==0)
		tmp="0";


	tmp+="d 0:0:0"; //WARNING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!temporary fix


System.out.println("*************"+tmp);
	long greenLinet=0;
	if (tmp.length()>0)
	{
		try 
		{
		StringTokenizer st = new StringTokenizer(tmp,"d");
		greenLinet=Integer.valueOf((String)st.nextToken()).intValue()*24*3600;
		StringTokenizer st2 = new StringTokenizer(st.nextToken().trim(),":");
		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue()*3600;
		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue()*60;
		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue();
		}
		catch (NoSuchElementException e)
		{
			PsDebug.log("Green line has unexpected format: '"+tmp+"'");
			greenLinet=0; //default value
		}
	}

System.out.println("*************");
	//get charge/Activation of procedure
	double chargeActivation=0.0;
	rs2=conn2.sqlQueryR("SELECT mvalue FROM ppdattr,pattribdef WHERE ppdattr.attribdefid=pattribdef.attribdefid and ppdattr.attribdefid=36700165 and ppdattr.pdattribid="+procid);
	if (rs2.next()==true)
	{
		chargeActivation=Double.valueOf(rs2.getString("mvalue").trim()).doubleValue();;
	}

	//calculate median time
	long medianTime=0;
	long medianCount=0;	
	rs2=conn2.sqlQueryR("SELECT pdeliv.delivname,pdelivstatus.mdated FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getInt("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
	while (rs2.next())
	{
		Calendar dt=PsConv.parseSqlDate(rs2.getString("mdated"));

		long lt=dt.get(Calendar.DAY_OF_YEAR)*86400+dt.get(Calendar.HOUR_OF_DAY)*3600+dt.get(Calendar.MINUTE)*60+dt.get(Calendar.SECOND);
System.out.println("lt="+lt+" nowt="+nowt+"  "+dt.get(Calendar.DAY_OF_YEAR)+","+dt.get(Calendar.HOUR_OF_DAY)+","+dt.get(Calendar.MINUTE));
System.out.println("    "+now.get(Calendar.DAY_OF_YEAR)+","+now.get(Calendar.HOUR_OF_DAY)+","+now.get(Calendar.MINUTE));
		medianTime+=(nowt-lt);
		medianCount++;	
	}
	if (medianCount!=0)
		medianTime/=medianCount;
	else
		medianTime=0;

	double deltaPercent;//ecart
	deltaPercent=medianTime*100.0;
	if (greenLinet!=0.0)
		deltaPercent/=greenLinet;
	else
		deltaPercent=0.0;
	if (medianTime<greenLinet)
		deltaPercent*=-1;
	int vtmp=(int)(deltaPercent*100);
	deltaPercent=(double)(vtmp)/100.0;

	String color="green";
	if (deltaPercent<=100.0)
	{}
	else
	if (deltaPercent<=105.0)
	{color="orange";}
	else
	if (deltaPercent>105.0)
	{color="red";}

%>
	<TR>
          <TD width="3%" height=23 valign=bottom>&nbsp;</TD>
          <TD width="6%"><NOBR><FONT class=menu><%=number%></FONT>&nbsp;</NOBR></TD>
	  <TD width="6%"><NOBR><FONT class=menu><%=chargeActivation*number%></FONT>&nbsp;</NOBR></TD>
	  <TD width="26%"><FONT class=menu><%=combinationname%></FONT>&nbsp;</TD>
	  <TD width="20%"><FONT class=menu><%=rs.getString("mvalue")%></FONT>&nbsp;</TD>
	  <TD width="12%"><NOBR><FONT class=menu><%=PsConv.secondsFrom1970ToString(medianTime)%></FONT>&nbsp;</NOBR></TD>
	  <TD width="12%"><NOBR><FONT class=menu><%=PsConv.secondsFrom1970ToString(greenLinet)%></FONT>&nbsp;</NOBR></TD>
	  <TD width="6%"><NOBR><FONT class=menu><%=deltaPercent%></FONT>&nbsp;</NOBR></TD>
	  <TD align="right" width="3%"><NOBR><FONT class=menu><img src="img/<%=color%>.gif" border="0"></FONT>&nbsp;</NOBR></TD>
	</TR>
<%
	}
%>

      </TABLE>
     </TD>
   </TR>
</TABLE>
</body>
</html>