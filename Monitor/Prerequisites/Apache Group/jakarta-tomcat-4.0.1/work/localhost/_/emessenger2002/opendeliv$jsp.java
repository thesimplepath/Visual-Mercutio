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


public class opendeliv$jsp extends HttpJspBase {


    static {
    }
    public opendeliv$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(8,32);to=(9,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(9,25);to=(52,0)]
                out.write("\r\n<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n<HTML><HEAD><TITLE>List Cases</TITLE>\r\n<LINK href=\"css/global.css\" rel=STYLESHEET>\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<META http-equiv=Content-Type content=\"text/html; charset=iso-8859-1\">\r\n<!--********** Start: Global function **************-->\r\n<SCRIPT language=JavaScript src=\"js/global.js\">\r\n</SCRIPT>\r\n\r\n<script language=JavaScript>\r\n<!--\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=document.location;\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n//  alert(\"Send to chief \"+procid+\" / \"+transid);\r\n  document.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n//  alert(\"Start Deliv :\"+delivid);\r\n  document.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n//  alert(\"Retour a l'envoyeur\");\r\n  document.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\n//-->\r\n</script>\r\n\r\n</head>\r\n\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=\"0\" MARGINWIDTH=\"0\">\r\n");

            // end
            // begin [file="/emessenger2002/opendeliv.jsp";from=(52,2);to=(121,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/opendeliv.jsp";from=(121,2);to=(123,0)]
                out.write("\r\n</BODY></HTML>\r\n");

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
