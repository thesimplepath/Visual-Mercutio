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
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class config$jsp extends HttpJspBase {


    static {
    }
    public config$jsp( ) {
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

            // HTML // begin [file="/pss/config.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(4,31);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(5,28);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(6,29);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(7,28);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/config.jsp";from=(8,29);to=(23,0)]
                out.write("\r\n<html>\r\n<head>\r\n<script language=JavaScript>\r\n<!--\r\nfunction doSubmit()\r\n{\r\n\talert(\"TODO\");\r\n}\r\n//-->\r\n</script>\r\n</head>\r\n<body>\r\n<form name=FRM>\r\n<table>\r\n");

            // end
            // begin [file="/pss/config.jsp";from=(23,2);to=(33,0)]
                 
                  PsApp.init(); 
                  Hashtable v; 
                  v=PsConfig.getHashTable(); 
                  Enumeration f=v.elements();
                  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
                         out.println("<tr><td>"+(String)e.nextElement()+"</td>");
                	 out.println("<td><input type=text size=80 value=\""+(String)f.nextElement()+"\"></td></tr>");
                     }
                 
            // end
            // HTML // begin [file="/pss/config.jsp";from=(33,2);to=(38,7)]
                out.write("\r\n</table>\r\n<input type=button value=Save onclick=\"doSubmit();\">\r\n</form>\r\n</body>\r\n</html>");

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
