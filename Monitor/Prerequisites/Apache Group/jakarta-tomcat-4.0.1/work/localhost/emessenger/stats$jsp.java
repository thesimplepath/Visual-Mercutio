package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class stats$jsp extends HttpJspBase {


    static {
    }
    public stats$jsp( ) {
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

            // HTML // begin [file="/stats.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/stats.jsp";from=(1,26);to=(3,0)]
                out.write("\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/stats.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/stats.jsp";from=(3,53);to=(5,40)]
                out.write("\r\n<script language=Javascript>\r\ntop.showTabText(9,\"Utilisateur:</td><td>");

            // end
            // begin [file="/stats.jsp";from=(5,43);to=(5,83)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/stats.jsp";from=(5,85);to=(17,0)]
                out.write("\",\"Statistiques de processus...\");\r\n\r\nfunction show(url)\r\n{\r\n\tusr.document.location=url;\r\n}\r\n</script>\r\n <frameset cols=\"15%,*\" framespacing=\"2\" frameborder=\"0\" bordercolor=\"#FFFFFF\">\r\n  <frame src=\"stats0.jsp\" name=\"wkg\" id=\"wkg\" scrolling=\"Auto\">\r\n  <frame src=\"blank.htm\" name=\"usr\" id=\"usr\" scrolling=\"Auto\">\r\n </frameset>\r\n</html>\r\n");

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
