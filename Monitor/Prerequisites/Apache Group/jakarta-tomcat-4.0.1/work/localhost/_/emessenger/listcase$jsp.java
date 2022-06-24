package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsWorkGroup;
import PsWf;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class listcase$jsp extends HttpJspBase {


    static {
    }
    public listcase$jsp( ) {
    }

    private static boolean _jspx_inited = false;

    public final void _jspx_init() throws org.apache.jasper.runtime.JspException {
    }

    public void _jspService(HttpServletRequest request, HttpServletResponse  response)
        throws java.io.IOException, ServletException {

        JspFactory _jspxFactory = null;
        PageContext pageContext = null;
        HttpSession session = null;
        ServletContext application = null;
        ServletConfig config = null;
        JspWriter out = null;
        Object page = this;
        String  _value = null;
        try {

            if (_jspx_inited == false) {
                synchronized (this) {
                    if (_jspx_inited == false) {
                        _jspx_init();
                        _jspx_inited = true;
                    }
                }
            }
            _jspxFactory = JspFactory.getDefaultFactory();
            response.setContentType("text/html;charset=ISO-8859-1");
            pageContext = _jspxFactory.getPageContext(this, request, response,
			"", true, 8192, true);

            application = pageContext.getServletContext();
            config = pageContext.getServletConfig();
            session = pageContext.getSession();
            out = pageContext.getOut();

            // HTML // begin [file="/emessenger/listcase.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<HTML>\r\n");

            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(1,112);to=(3,0)]
                out.write("\r\n<HEAD><TITLE>Search Cases</TITLE>\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(4,26);to=(5,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(8,29);to=(13,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n\r\n\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(13,2);to=(33,0)]
                
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
                
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(33,2);to=(38,35)]
                out.write("\r\n\r\n<!-- ------------------------------------ //-->\r\n<script language=JavaScript>\r\n//Display tab on top.jsp\r\nvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(38,38);to=(38,78)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(38,80);to=(38,86)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(38,89);to=(38,132)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(38,134);to=(38,136)]
                out.write(" (");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(38,139);to=(38,187)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(38,189);to=(40,12)]
                out.write(")\";\r\nvar info2=\"\";\r\nvar tabno=1+");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(40,15);to=(40,19)]
                out.print(mode);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(40,21);to=(55,0)]
                out.write(";\r\ntop.showTabText(tabno,info1,info2);\r\n</script>\r\n<!-- ------------------------------------ //-->\r\n\r\n</head>\r\n\r\n<BODY>\r\n<FORM action=\"listcase.jsp\" method=POST>\r\n<INPUT TYPE=HIDDEN NAME=MODE VALUE=2>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\" nobr>\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(55,2);to=(57,0)]
                
                if (mode==2) {
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(57,2);to=(61,67)]
                out.write("\r\n\t<TR class=Bg>\r\n\t<TD width=\"3%\">&nbsp;</TD>\r\n\t<TD width=\"17%\">Recherche:</TD>\r\n\t<TD width=\"70%\" colspan=5><input type=text NAME=KEYSEARCH  value=\"");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(61,70);to=(61,79)]
                out.print(searchKey);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(61,81);to=(66,0)]
                out.write("\" style=\"width:100%;\"></td>\r\n\t<TD width=\"10%\" align=center><input type=submit class=sbttn value=\"Recherche\"></TD>\r\n\t</TR>\r\n\r\n\t<TR height=5><td colspan=8>&nbsp;</td></tr>\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(66,2);to=(68,0)]
                
                 }
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(68,2);to=(70,69)]
                out.write("\r\n        <TR class=Bg>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(70,72);to=(70,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(70,82);to=(74,0)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"17%\"><NOBR><A title=\"Trier par statut\" \r\n            href=\"\"><FONT \r\n            class=menu>Statut</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(74,2);to=(76,0)]
                
                if (mode==2) {
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(76,2);to=(78,87)]
                out.write("\t\t\t\r\n          <TD width=\"31%\" class=BgL><NOBR><A title=\"Trier par expÃ©diteur\" \r\n            href=\"\"><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(78,90);to=(78,98)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(78,100);to=(86,0)]
                out.write("/desc.gif\" width=7 border=0><FONT \r\n            class=swnub>Livrables de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"18%\"><NOBR><A title=\"Trier par procedure\" \r\n            href=\"\"><FONT \r\n            class=menu>ProcÃ©dure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><FONT \r\n            class=menu>Utilisateur</FONT></A>&nbsp;</NOBR></TD>\t\t\t\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(86,2);to=(88,0)]
                
                 } else {
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(88,2);to=(90,87)]
                out.write("\r\n          <TD width=\"36%\" class=BgL><NOBR><A title=\"Trier par expÃ©diteur\" \r\n            href=\"\"><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(90,90);to=(90,98)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(90,100);to=(95,0)]
                out.write("/desc.gif\" width=7 border=0><FONT \r\n            class=swnub>Livrables de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"23%\"><NOBR><A title=\"Trier par procedure\" \r\n            href=\"\"><FONT \r\n            class=menu>ProcÃ©dure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(95,2);to=(97,1)]
                
                 }
                 
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(97,3);to=(107,0)]
                out.write("\t\t\t\r\n          <TD width=\"10%\"><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><FONT \r\n            class=menu>Date creation</FONT></A>&nbsp;</NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><A title=\"Trier par date\" \r\n            href=\"\">\r\n            <FONT class=menu>Date d'arrivÃ©e</FONT></A>&nbsp;</NOBR></TD>\r\n          <TD align=right width=\"17%\"><NOBR>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<A title=\"Trier par cas\" \r\n            href=\"\"><FONT \r\n            class=menu>Cas</FONT></A>&nbsp;</NOBR></TD></TR>\r\n");

            // end
            // begin [file="/emessenger/listcase.jsp";from=(107,2);to=(432,0)]
                
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
                
                
                	boolean readyOrNot=false;
                	boolean hasDelivMaster=false;
                	boolean skipRow=false;		
                	String delivmastername;
                	String delivready="";
                	boolean hasNoCombinationAtAll=true;//start and stop have this
                	rs3=conn3.sqlQueryR("SELECT prow,mvalue FROM ppdattr WHERE pdattribid="+procid+" AND attribdefid in (31457281,31457282,31457284)");// titre,livrables,,maitre
                	while (rs3.next())
                	{
                		hasNoCombinationAtAll=false;
                
                		delivmastername="";
                		hasDelivMaster=false;
                		delivready="";
                		String combname=rs3.getString("mvalue").trim();
                		rs3.next();
                		String combdeliv=rs3.getString("mvalue").trim();
                		rs3.next();
                		String combmaster=rs3.getString("mvalue").trim();		
                
                		//list of all linked deliv ready for this proc
                		rs2=conn2.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
                		while (rs2.next())
                		{		
                			String dname=rs2.getString("delivname").trim();
                			if (dname.equals(combmaster)==false)	
                			{
                				delivready+=dname+" ";
                			}
                			else
                			{
                				hasDelivMaster=true;
                				delivmastername=dname;
                			}
                		}
                	
                		//No deliv arrived, so it means it's a new case
                		if (delivready.trim().length()==0) 
                		{
                			//deliv
                			delivready=delivmastername;
                		}
                		else
                		{
                			//deliv display
                			int pos=combdeliv.indexOf(combmaster);
                			if (pos>=0)
                			{
                				combdeliv+=" ";
                				String p0=combdeliv.substring(0,pos);
                				String p1=combdeliv.substring(pos+combmaster.length()+1);
                				combdeliv=p0+p1;
                				combdeliv.trim();
                			}
                			if (combdeliv.length()==0)
                				delivready=combmaster;
                			else
                				delivready=combmaster + ": "+ combdeliv;
                		}
                
                		//if master of the combination has not been received, then hide the combination
                		skipRow=false;
                		if (hasDelivMaster==false)		
                			skipRow=true;		
                
                		PsDebug.log("Test combination '"+combname+"' liv:'"+combdeliv+"' mas:'"+combmaster+"' sR="+skipRow);
                
                		if (skipRow==false)
                			break;//exit while
                	}//while combination
                
                	if (delivready.trim().length()==0)
                	{
                		delivready="";
                		if (hasNoCombinationAtAll==true)
                		{
                			rs2=conn2.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getString("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
                			while (rs2.next())
                			{
                				//stop
                				delivready+=rs2.getString("delivname")+" ";
                			}
                		}
                		if (delivready.length()==0)
                			delivready="Nouveau Cas";//no delivs to this current procedure ('start')
                	}
                
                	PsDebug.log("Combination selected: sR:"+skipRow+" hM:"+hasDelivMaster+" Liv:'"+delivready+"'");
                	
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
                      	out.println("<TD width=\"23%\"><A href=\""+plink+"\">"+delivready);
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
                      	out.println("<TD width=\"18%\"><A href=\""+plink+"\">"+delivready+"</A></TD>");
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
            // end
            // HTML // begin [file="/emessenger/listcase.jsp";from=(432,2);to=(440,0)]
                out.write("\r\n</TABLE>\r\n</TD>\r\n</TR>\r\n</TABLE>\r\n</FORM>\r\n</BODY>\r\n</HTML>\r\n");

            // end

        } catch (Throwable t) {
            if (out != null && out.getBufferSize() != 0)
                out.clearBuffer();
            if (pageContext != null) pageContext.handlePageException(t);
        } finally {
            if (_jspxFactory != null) _jspxFactory.releasePageContext(pageContext);
        }
    }
}
