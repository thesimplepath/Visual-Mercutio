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


public class termin$jsp extends HttpJspBase {


    static {
    }
    public termin$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/termin.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(8,32);to=(9,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(9,25);to=(18,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/emessenger2002/termin.jsp";from=(18,2);to=(49,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                
                 String redirect=(String)request.getParameter( "REDIRECT" );
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                
                	//check approval (all mandatory delivs must have been completed)	
                	//TODO
                
                	//terminate the current procedure	
                	conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("deliv.jsp: SQLException: "+e.getMessage());
                    }
                
                out.println("<script language=JavaScript>");
                out.println("<!--");
                out.println("document.location=\""+redirect+"\";");
                out.println("//-->");
                out.println("</script>");
                
            // end
            // HTML // begin [file="/emessenger2002/termin.jsp";from=(49,2);to=(51,7)]
                out.write("\r\n</body>\r\n</html>");

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