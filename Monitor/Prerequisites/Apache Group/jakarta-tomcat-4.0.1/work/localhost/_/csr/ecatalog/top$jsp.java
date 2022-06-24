package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class top$jsp extends HttpJspBase {


    static {
    }
    public top$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/top.jsp";from=(0,0);to=(20,0)]
                out.write("<html>\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n</head>\r\n\r\n<body bgcolor=\"#FFFFFF\" leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\" rightmargin=\"0\">\r\n\r\n<div align=\"left\">\r\n<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">\r\n\t<tr>\r\n\t\t<td width=\"348\"><img src=\"../img/ecatalog/top_left.gif\"></td>\r\n\t\t<td width=\"100%\" background=\"../img/ecatalog/top_bkg.gif\">&nbsp;</td>\r\n\t\t<td width=\"562\"><img src=\"../img/ecatalog/top_right.gif\"></td>\r\n\t</tr>\r\n</table>\r\n</div>\r\n\r\n</body>\r\n</html>\r\n\r\n");

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
