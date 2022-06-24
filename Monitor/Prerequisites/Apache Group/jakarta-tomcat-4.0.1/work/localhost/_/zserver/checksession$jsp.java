package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class checksession$jsp extends HttpJspBase {


    static {
    }
    public checksession$jsp( ) {
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

            // begin [file="/zserver/checksession.jsp";from=(0,2);to=(3,0)]
                
                 if ((String)session.getAttribute( "USERNAME")==null) 
                 {
            // end
            // HTML // begin [file="/zserver/checksession.jsp";from=(3,2);to=(9,0)]
                out.write("\r\n   <script language=JavaScript>\r\n   <!--\r\n   top.document.location=\"index.htm\";\r\n   //-->\r\n   </script>\r\n");

            // end
            // begin [file="/zserver/checksession.jsp";from=(9,2);to=(11,0)]
                
                 }
            // end
            // HTML // begin [file="/zserver/checksession.jsp";from=(11,2);to=(12,0)]
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
