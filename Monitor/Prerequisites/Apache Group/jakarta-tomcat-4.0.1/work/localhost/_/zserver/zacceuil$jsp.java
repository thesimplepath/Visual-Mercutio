package org.apache.jsp;

import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class zacceuil$jsp extends HttpJspBase {


    static {
    }
    public zacceuil$jsp( ) {
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

            // HTML // begin [file="/zserver/zacceuil.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(1,63);to=(3,0)]
                out.write("\r\n<head>\r\n");

            // end
            // begin [file="/zserver/zacceuil.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // begin [file="/zserver/zacceuil.jsp";from=(4,2);to=(6,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(6,2);to=(7,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/zserver/zacceuil.jsp";from=(7,19);to=(7,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(7,29);to=(16,36)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n\r\n<!-- ------------------------------------ //-->\r\n<script language=JavaScript>\r\n//Display tab on ztop.jsp\r\nfunction delayedDisplay()\r\n{\r\n\tvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/zserver/zacceuil.jsp";from=(16,39);to=(16,79)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(16,81);to=(26,0)]
                out.write("</b>\";\r\n\tvar info2=\"\";\r\n\tvar tabno=0;\r\n\ttop.showTabText(tabno,info1,info2);\r\n}\r\n//document.onload=delayedDisplay();\r\n</script>\r\n<!-- ------------------------------------ //-->\r\n\r\n<body onload=\"delayedDisplay();\">\r\n");

            // end
            // begin [file="/zserver/zacceuil.jsp";from=(26,3);to=(26,33)]
                out.print(PsConfig.get("WELCOME_SCREEN"));
            // end
            // HTML // begin [file="/zserver/zacceuil.jsp";from=(26,35);to=(28,7)]
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
