package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsBpml;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class bpml$jsp extends HttpJspBase {


    static {
    }
    public bpml$jsp( ) {
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
            response.setContentType("text/plain");
            pageContext = _jspxFactory.getPageContext(this, request, response,
			"", true, 8192, true);

            application = pageContext.getServletContext();
            config = pageContext.getServletConfig();
            session = pageContext.getSession();
            out = pageContext.getOut();

            // HTML // begin [file="/emessenger/bpml.jsp";from=(0,0);to=(2,0)]
                out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<!--\r\n");

            // end
            // HTML // begin [file="/emessenger/bpml.jsp";from=(2,113);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/bpml.jsp";from=(3,36);to=(5,0)]
                out.write("\r\nProcessSoft Mercutio BPML Export\r\n");

            // end
            // begin [file="/emessenger/bpml.jsp";from=(5,2);to=(10,0)]
                
                	String prm=request.getParameter( "MODELID" );
                	if (prm==null)
                		prm="0";
                	int modelid=Integer.valueOf(prm).intValue();
            // end
            // HTML // begin [file="/emessenger/bpml.jsp";from=(10,2);to=(12,0)]
                out.write("\r\n-->\r\n");

            // end
            // begin [file="/emessenger/bpml.jsp";from=(12,3);to=(12,26)]
                out.print(PsBpml.genBpml(modelid));
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
