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


public class tracking$jsp extends HttpJspBase {


    static {
    }
    public tracking$jsp( ) {
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

            // HTML // begin [file="/tracking.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<HTML>\r\n");

            // end
            // HTML // begin [file="/tracking.jsp";from=(1,112);to=(3,0)]
                out.write("\r\n<HEAD><TITLE>Search Cases</TITLE>\r\n");

            // end
            // begin [file="/tracking.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/tracking.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/tracking.jsp";from=(4,26);to=(5,0)]
                out.write("\r\n");

            // end
            // begin [file="/tracking.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/tracking.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/tracking.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/tracking.jsp";from=(8,29);to=(13,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n\r\n\r\n");

            // end
            // begin [file="/tracking.jsp";from=(13,2);to=(23,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 if (username==null) return;
                 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                
                 int caseid=		Integer.valueOf(request.getParameter("CASEID")).intValue();
                 int transid=		Integer.valueOf(request.getParameter("TRANSID")).intValue();
            // end
            // HTML // begin [file="/tracking.jsp";from=(23,2);to=(28,35)]
                out.write("\r\n\r\n<!-- ------------------------------------ //-->\r\n<script language=JavaScript>\r\n//Display tab on top.jsp\r\nvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/tracking.jsp";from=(28,38);to=(28,78)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/tracking.jsp";from=(28,80);to=(28,86)]
                out.write("</b>, ");

            // end
            // begin [file="/tracking.jsp";from=(28,89);to=(28,132)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/tracking.jsp";from=(28,134);to=(28,136)]
                out.write(" (");

            // end
            // begin [file="/tracking.jsp";from=(28,139);to=(28,187)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/tracking.jsp";from=(28,189);to=(29,38)]
                out.write(")\";\r\nvar info2=\"Historique du cas:</td><td>");

            // end
            // begin [file="/tracking.jsp";from=(29,41);to=(29,47)]
                out.print(caseid);
            // end
            // HTML // begin [file="/tracking.jsp";from=(29,49);to=(29,50)]
                out.write(".");

            // end
            // begin [file="/tracking.jsp";from=(29,53);to=(29,60)]
                out.print(transid);
            // end
            // HTML // begin [file="/tracking.jsp";from=(29,62);to=(44,69)]
                out.write("\";\r\nvar tabno=3;\r\ntop.showTabText(tabno,info1,info2);\r\n</script>\r\n<!-- ------------------------------------ //-->\r\n\r\n</head>\r\n\r\n<BODY>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\" nobr>\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n        <TR class=Bg>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/tracking.jsp";from=(44,72);to=(44,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/tracking.jsp";from=(44,82);to=(52,0)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>Statut&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"17%\"><NOBR><FONT class=menu>ProcÃ©dure&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"40%\"><NOBR><FONT class=menu>Livrables dÃ©marrÃ©s&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>Date d'envoi du livrable&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>Utilisateur&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>Date d'arrivÃ©e&nbsp;</FONT></NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/tracking.jsp";from=(52,2);to=(108,0)]
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	PsDbConn conn2=PsDbMgr.newConnection();
                	ResultSet rs;
                	ResultSet rs2;
                
                	String statut;
                	String proc;
                	String delivs;
                	String delivsdate;
                	String dated;
                	String users;
                	String whichmenu;
                	String whichimg;
                
                	rs=conn.sqlQueryR("SELECT * FROM pemployee,ppdattr,pstatus,pproc,pproctrans WHERE pproctrans.caseid="+caseid+" AND pproctrans.transid="+transid+" AND pproc.procid=pproctrans.procid AND pstatus.statusid=pproctrans.statusid AND ppdattr.pdattribid=pproc.procid AND ppdattr.attribdefid= 1310721 AND pemployee.emplid=pproctrans.emplid");
                	while (rs.next())
                	{
                	 //display different color for 'in progress procedures'
                	 whichmenu="menu";
                	 whichimg="img/arr.gif";
                	 if (rs.getInt("statusid")<90)
                	 {
                		whichmenu="menu2";
                		whichimg="img/arrok.gif";
                         }
                
                	 //get vars
                	 statut=rs.getString("statusname");
                	 proc=rs.getString("mvalue");	 
                	 users="<a class=menu title=\""+rs.getString("fname")+" "+rs.getString("lname")+"\">"+rs.getString("login")+"</a>";
                	 dated=rs.getString("indate");
                	
                	 //create the list of deliverables
                	 delivs=null;
                	 delivsdate=null;
                	 rs2=conn.sqlQueryR("SELECT * FROM pdeliv,ppdattr,pdelivstatus WHERE pdelivstatus.caseid="+caseid+" AND pdelivstatus.transid="+transid+" AND pdelivstatus.procid="+rs.getString("procid")+" AND pdeliv.delivid=pdelivstatus.delivid AND ppdattr.pdattribid=pdeliv.delivid AND ppdattr.attribdefid=1310721");
                	 while (rs2.next())
                	 {
                		if (delivs==null)
                		{
                			delivs=rs2.getString("mvalue");
                			delivsdate=rs2.getString("mdated");
                		}
                		else
                		{
                			delivs=delivs+"<br>"+rs2.getString("mvalue");
                			delivsdate=delivsdate+"<br>"+rs2.getString("mdated");
                		}
                	 }
                
                	 if (delivs==null) //no deliv started yet
                		delivs="";		
                	 if (delivsdate==null)
                		delivsdate="";
            // end
            // HTML // begin [file="/tracking.jsp";from=(108,2);to=(110,65)]
                out.write("\r\n\t <TR>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"");

            // end
            // begin [file="/tracking.jsp";from=(110,68);to=(110,76)]
                out.print(whichimg);
            // end
            // HTML // begin [file="/tracking.jsp";from=(110,78);to=(111,55)]
                out.write("\"></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>&nbsp;");

            // end
            // begin [file="/tracking.jsp";from=(111,58);to=(111,64)]
                out.print(statut);
            // end
            // HTML // begin [file="/tracking.jsp";from=(111,66);to=(112,44)]
                out.write("</FONT></NOBR></TD>\r\n          <TD width=\"17%\"><NOBR><FONT class=");

            // end
            // begin [file="/tracking.jsp";from=(112,47);to=(112,56)]
                out.print(whichmenu);
            // end
            // HTML // begin [file="/tracking.jsp";from=(112,58);to=(112,60)]
                out.write(" >");

            // end
            // begin [file="/tracking.jsp";from=(112,63);to=(112,67)]
                out.print(proc);
            // end
            // HTML // begin [file="/tracking.jsp";from=(112,69);to=(113,49)]
                out.write("</FONT></NOBR></TD>\r\n          <TD width=\"40%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/tracking.jsp";from=(113,52);to=(113,58)]
                out.print(delivs);
            // end
            // HTML // begin [file="/tracking.jsp";from=(113,60);to=(114,49)]
                out.write("&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/tracking.jsp";from=(114,52);to=(114,62)]
                out.print(delivsdate);
            // end
            // HTML // begin [file="/tracking.jsp";from=(114,64);to=(115,49)]
                out.write("&nbsp;</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/tracking.jsp";from=(115,52);to=(115,57)]
                out.print(users);
            // end
            // HTML // begin [file="/tracking.jsp";from=(115,59);to=(116,49)]
                out.write("</FONT></NOBR></TD>\r\n          <TD width=\"10%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/tracking.jsp";from=(116,52);to=(116,57)]
                out.print(dated);
            // end
            // HTML // begin [file="/tracking.jsp";from=(116,59);to=(118,0)]
                out.write("</FONT></NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/tracking.jsp";from=(118,2);to=(125,0)]
                
                	}//while
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/tracking.jsp";from=(125,2);to=(133,0)]
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
