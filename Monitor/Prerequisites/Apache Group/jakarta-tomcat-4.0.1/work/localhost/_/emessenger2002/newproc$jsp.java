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
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class newproc$jsp extends HttpJspBase {


    static {
    }
    public newproc$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(8,32);to=(14,45)]
                out.write("\r\n<html>\r\n<head>\r\n<LINK href=\"css/global.css\" rel=STYLESHEET type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<SCRIPT language=javascript>\r\ntop.menu.showTabText(4,\"Utilisateur:</td><td>");

            // end
            // begin [file="/emessenger2002/newproc.jsp";from=(14,48);to=(14,88)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(14,90);to=(37,0)]
                out.write("\",\"\");\r\n</SCRIPT>\r\n</head>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>\r\n<TABLE width=\"100%\" bgColor=#93bee2 border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD noWrap width=\"15%\"><A class=menu><FONT class=menu></FONT></A>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\"><A class=menu><FONT class=menu>Sélection d'un point \r\n      de démarrage</FONT></A>&nbsp;</TD></TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD class=menu noWrap width=\"85%\">\r\n      <DIV align=right>Nouveau processus</DIV></TD></TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD class=NormalBlack width=\"85%\">Pour démarrer un nouveau processus, \r\n      veuillez sélectionner un point de démarrage du processus affiché \r\n      ci-dessous. Vous pouvez naviguer au sein du modèle en sélectionnant les \r\n      symboles de processus, de page et de porte. </TD></TR></TBODY></TABLE>\r\n<br>\r\n<br>\r\nChoisir un processus start :<select name=\"CASE\">\r\n");

            // end
            // begin [file="/emessenger2002/newproc.jsp";from=(37,2);to=(61,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	PsWorkGroup w=new PsWorkGroup();
                 	Vector r=w.listProcStartGranted(username);
                 	int l=r.size();
                 	for (int i=0;i<l;i++)
                 	{
                		int proc=((Integer)r.elementAt(i)).intValue();
                		rs=conn.sqlQueryR("select * from pproc,pmodel where pproc.proctype=0 and pproc.procid="+proc+" and pproc.modelid=pmodel.modelid order by modelname");
                		rs.next();
                		out.println("<option value=\""+proc+"\">"+rs.getString("modelname")+". #proc:"+proc+"</option>");
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger2002/newproc.jsp";from=(61,2);to=(66,7)]
                out.write("\r\n</select>\r\n\r\n<input type=button onclick=\"javascript:document.location='newproc1.jsp?PROCID='+CASE.value;\" value=\"Aller à...\">\r\n</body>\r\n</html>");

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
