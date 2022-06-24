package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class showtab$jsp extends HttpJspBase {


    static {
    }
    public showtab$jsp( ) {
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

            // begin [file="/emessenger/showtab.jsp";from=(0,2);to=(3,0)]
                
                if ((String)session.getAttribute( "USERNAME")==null) 
                 {	
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(3,2);to=(6,7)]
                out.write("\r\n   <script language=JavaScript>\r\n   <!--\r\n\tinfo1=");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(6,10);to=(6,15)]
                out.print(info1);
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(6,17);to=(7,7)]
                out.write(";\r\n\tinfo2=");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(7,10);to=(7,15)]
                out.print(info2);
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(7,17);to=(8,7)]
                out.write(";\r\n\ttabno=");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(8,10);to=(8,15)]
                out.print(tabno);
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(8,17);to=(10,37)]
                out.write(";\r\n\tif (info1==null)\r\n\t\tvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(10,40);to=(10,80)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(10,82);to=(10,88)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(10,91);to=(10,134)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(10,136);to=(10,138)]
                out.write(" (");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(10,141);to=(10,189)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(10,191);to=(18,0)]
                out.write(")\";\r\n\tif (info2==null)\r\n\t\tvar info2=\"\";\r\n\tif (tabno==null)\r\n\t\tvar tabno=-1;\r\n\ttop.showTabText(tabno,info1,info2);\r\n   //-->\r\n   </script>\r\n");

            // end
            // begin [file="/emessenger/showtab.jsp";from=(18,2);to=(20,0)]
                
                 }
            // end
            // HTML // begin [file="/emessenger/showtab.jsp";from=(20,2);to=(21,0)]
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
