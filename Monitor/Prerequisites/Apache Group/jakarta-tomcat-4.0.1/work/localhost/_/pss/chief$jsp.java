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


public class chief$jsp extends HttpJspBase {


    static {
    }
    public chief$jsp( ) {
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

            // HTML // begin [file="/pss/chief.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/chief.jsp";from=(8,32);to=(16,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/pss/chief.jsp";from=(16,2);to=(24,0)]
                
                //session check
                 String xusername=(String)session.getAttribute( "USERNAME");
                 int    userrole;
                 if (xusername==null) 
                   out.println("alert('Not logged');");
                 else
                   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
            // end
            // HTML // begin [file="/pss/chief.jsp";from=(24,2);to=(35,0)]
                out.write("\r\n//-->\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/pss/chief.jsp";from=(35,2);to=(55,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                
                out.println("Remise au chef...<br>");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                	conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=0,chiefflag=1 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("chiefflag.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/chief.jsp";from=(55,2);to=(57,7)]
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
