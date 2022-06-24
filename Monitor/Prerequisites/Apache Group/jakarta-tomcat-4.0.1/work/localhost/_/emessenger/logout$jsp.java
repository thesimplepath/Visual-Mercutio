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


public class logout$jsp extends HttpJspBase {


    static {
    }
    public logout$jsp( ) {
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

            // HTML // begin [file="/emessenger/logout.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/logout.jsp";from=(1,107);to=(2,1)]
                out.write("\r\n ");

            // end
            // begin [file="/emessenger/logout.jsp";from=(2,1);to=(2,54)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/logout.jsp";from=(2,54);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/logout.jsp";from=(3,26);to=(5,0)]
                out.write("\r\n<body>\r\n");

            // end
            // begin [file="/emessenger/logout.jsp";from=(5,2);to=(26,0)]
                
                 PsApp.init();
                 String redirect="index.htm";
                 String username=(String)session.getAttribute("USERNAME");
                 if (username!=null)
                 {
                	 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                	try {
                			PsDbConn conn=PsDbMgr.newConnection();	
                			//unlock every locked cases
                			conn.sqlExecR("UPDATE pproctrans SET statusid=2 WHERE statusid=1 AND emplid="+userid);
                	    }
                	catch (SQLException e)
                	    {
                			PsDebug.fail("setdecision.jsp: SQLException: "+e.getMessage());
                	    }
                 }
                //logout
                session.setAttribute("USERNAME",null);
                session.setAttribute("USERID",null);
                session.invalidate();
            // end
            // HTML // begin [file="/emessenger/logout.jsp";from=(26,2);to=(30,19)]
                out.write("\r\n\r\n<script language=JavaScript>\r\n<!--\r\ndocument.location=\"");

            // end
            // begin [file="/emessenger/logout.jsp";from=(30,22);to=(30,30)]
                out.print(redirect);
            // end
            // HTML // begin [file="/emessenger/logout.jsp";from=(30,32);to=(35,7)]
                out.write("\";\r\n//-->\r\n</script>\r\n\r\n</body>\r\n</html>");

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
