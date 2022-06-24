package org.apache.jsp;

import java.util.*;
import  org.apache.soap.server.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class list$jsp extends HttpJspBase {


    static {
    }
    public list$jsp( ) {
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

            // HTML // begin [file="/admin/list.jsp";from=(0,58);to=(4,0)]
                out.write("\r\n\r\n<h1>Service Listing</h1>\r\n\r\n");

            // end
            // begin [file="/admin/list.jsp";from=(4,2);to=(14,4)]
                 
                  ServiceManager serviceManager =
                    org.apache.soap.server.http.ServerHTTPUtils.getServiceManagerFromContext(application);
                
                  String[] serviceNames = serviceManager.list ();
                  if (serviceNames.length == 0) {
                    out.println ("<p>Sorry, there are no services currently deployed.</p>");
                  } else {
                    out.println ("<p>Here are the deployed services (select one to see");
                    out.println ("details)</p>");
                    
            // end
            // HTML // begin [file="/admin/list.jsp";from=(14,6);to=(16,4)]
                out.write("\r\n    <ul>\r\n    ");

            // end
            // begin [file="/admin/list.jsp";from=(16,6);to=(19,4)]
                
                    for (int i = 0; i < serviceNames.length; i++) {
                      String id = serviceNames[i];
                    
            // end
            // HTML // begin [file="/admin/list.jsp";from=(19,6);to=(20,38)]
                out.write("\r\n      <li><a href=\"showdetails.jsp?id=");

            // end
            // begin [file="/admin/list.jsp";from=(20,41);to=(20,43)]
                out.print(id);
            // end
            // HTML // begin [file="/admin/list.jsp";from=(20,45);to=(20,47)]
                out.write("\">");

            // end
            // begin [file="/admin/list.jsp";from=(20,50);to=(20,53)]
                out.print( id);
            // end
            // HTML // begin [file="/admin/list.jsp";from=(20,55);to=(21,4)]
                out.write("</li>\r\n    ");

            // end
            // begin [file="/admin/list.jsp";from=(21,6);to=(23,4)]
                
                    }
                    
            // end
            // HTML // begin [file="/admin/list.jsp";from=(23,6);to=(25,4)]
                out.write("\r\n    </ul>\r\n    ");

            // end
            // begin [file="/admin/list.jsp";from=(25,6);to=(27,0)]
                
                  }
            // end
            // HTML // begin [file="/admin/list.jsp";from=(27,2);to=(28,0)]
                out.write("\r\n");

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
