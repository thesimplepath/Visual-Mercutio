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

            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(8,32);to=(9,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(9,25);to=(20,23)]
                out.write("\r\n<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n<HTML><HEAD><TITLE>List Cases</TITLE>\r\n<LINK href=\"css/global.css\" rel=STYLESHEET>\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<META http-equiv=Content-Type content=\"text/html; charset=iso-8859-1\">\r\n<!--********** Start: Global function **************-->\r\n<SCRIPT language=JavaScript src=\"js/global.js\">\r\n</SCRIPT>\r\n\r\n<SCRIPT language=javascript>\r\ntop.menu.showTabText(1+");

            // end
            // begin [file="/emessenger2002/listcase.jsp";from=(20,26);to=(20,84)]
                out.print(Integer.valueOf(request.getParameter( "MODE" )).intValue());
            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(20,86);to=(20,109)]
                out.write(",\"Utilisateur:</td><td>");

            // end
            // begin [file="/emessenger2002/listcase.jsp";from=(20,112);to=(20,152)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(20,154);to=(29,0)]
                out.write("\",\"\");\r\nfunction CA()\r\n{\r\n//update all status to on/off and refresh display\r\nalert(\"TODO\");\r\ndocument.location=document.location;\r\n}\r\n</SCRIPT>\r\n<!--\r\n");

            // end
            // begin [file="/emessenger2002/listcase.jsp";from=(29,2);to=(31,0)]
                
                 PsDebug.log("Document= listcase.jsp");
            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(31,2);to=(100,0)]
                out.write("\r\n//-->\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n//  alert(\"Send to chief \"+procid+\" / \"+transid);\r\n  document.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n//  alert(\"Start Deliv :\"+delivid);\r\n  document.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n//  alert(\"Retour a l'envoyeur\");\r\n  document.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\n//-->\r\n</script>\r\n\r\n</head>\r\n\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=\"0\" MARGINWIDTH=\"0\">\r\n<TABLE width=\"100%\" border=0>\r\n\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" >\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 \r\n        width=\"100%\"><INPUT type=hidden value=F000000001 name=curmbox> <INPUT \r\n        type=hidden name=js> <INPUT type=hidden name=_HMaction> <INPUT \r\n        type=hidden value=inbox name=foo> <INPUT type=hidden name=page> \r\n        <TR bgColor=#336699>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/ard.gif\"></TD>\r\n          <TD width=\"17%\"><NOBR><A title=\"Trier par statut\" \r\n            href=\"\"><FONT \r\n            class=swb \r\n            color=#ffffff>Statut</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"36%\" bgColor=#93bee2><NOBR><A title=\"Trier par expéditeur\" \r\n            href=\"\"><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0><FONT \r\n            class=sbbd\r\n            color=#003366>Livrable de la combinaison</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"23%\"><NOBR><A title=\"Trier par procedure\" \r\n            href=\"\"><FONT \r\n            class=swb \r\n            color=#ffffff>Procedure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><FONT \r\n            class=swb color=#ffffff>Date creation</FONT></A>&nbsp;</NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><A title=\"Trier par date\" \r\n            href=\"\">\r\n            <FONT class=swb color=#ffffff>Date d'arrivée</FONT></A>&nbsp;</NOBR></TD>\r\n          <TD align=right width=\"17%\"><NOBR>&nbsp;<A title=\"Trier par cas\" \r\n            href=\"\"><FONT \r\n            class=swb color=#ffffff>Cas</FONT></A>&nbsp;</NOBR></TD></TR>\r\n");

            // end
            // begin [file="/emessenger2002/listcase.jsp";from=(100,2);to=(227,0)]
                
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
                		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=0 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
                	else	     //open deliv
                		rs=conn.sqlQueryR("SELECT distinct pcase.caseid,pstatus.statusid as stid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2,5,6) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=0 AND pproctrans.statusid=1 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
                
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
                
                	rs2=conn2.sqlQueryR("SELECT mvalue FROM pproc,ppdattr WHERE pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=59 AND pproc.procid="+procid);
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
                	rs2=conn2.sqlQueryR("SELECT distinct mvalue FROM pdeliv,ppdattr,pproctransfrom WHERE pproctransfrom.procid="+procid+" AND pproctransfrom.refprocid=pdeliv.procidsrc AND pdeliv.procidtrg="+procid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=0 ORDER BY pdeliv.delivname");
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
            // end
            // HTML // begin [file="/emessenger2002/listcase.jsp";from=(227,2);to=(231,0)]
                out.write("\r\n</TABLE>\r\n\r\n</BODY></HTML>\r\n");

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
