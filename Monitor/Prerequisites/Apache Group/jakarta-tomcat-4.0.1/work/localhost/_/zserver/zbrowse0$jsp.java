package org.apache.jsp;

import PsDebug;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class zbrowse0$jsp extends HttpJspBase {


    static {
    }
    public zbrowse0$jsp( ) {
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

            // HTML // begin [file="/zserver/zbrowse0.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/zserver/zbrowse0.jsp";from=(1,37);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/zbrowse0.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/zserver/zbrowse0.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/zserver/zbrowse0.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/zserver/zbrowse0.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/zbrowse0.jsp";from=(8,29);to=(23,7)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n\r\n<body>\r\n<TABLE width=\"100%\" border=0>\r\n<TR class=Bg>\r\n<TD width=\"15%\">&nbsp;</TD>\r\n<TD width=\"85%\">\r\n<FONT class=menu>\r\n<a href=\"usermgt2.jsp\" class=menu target=\"usr\"><FONT class=menu>Gestion des groupes de travail</font></a> | <a href=\"usermgt3.jsp\" class=menu target=\"usr\"><FONT class=menu>Gestion des utilisateurs</font></a> | <font color=#808080>Repertoire d'entreprise</font>\r\n</FONT>\r\n</TD>\r\n</TR>\r\n</TABLE>\r\n</body>\r\n</html>");

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
