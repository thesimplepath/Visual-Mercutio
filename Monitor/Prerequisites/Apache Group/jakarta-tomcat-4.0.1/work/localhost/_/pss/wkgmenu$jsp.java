package org.apache.jsp;

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


public class wkgmenu$jsp extends HttpJspBase {


    static {
    }
    public wkgmenu$jsp( ) {
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

            // HTML // begin [file="/pss/wkgmenu.jsp";from=(0,26);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(1,31);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(2,28);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(3,29);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(5,29);to=(16,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"/>\r\n<link href=\"css/main.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<link href=\"css/tree.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=javaScript src=\"js/tree.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n var m=new oMenu;\r\n");

            // end
            // begin [file="/pss/wkgmenu.jsp";from=(16,2);to=(48,0)]
                
                
                //session check
                 String username=(String)session.getAttribute( "USERNAME");
                 int    userrole;
                 if (username==null) 
                   out.println("alert('Not logged');");
                 else
                   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                
                
                 PsApp.init();
                 
                 try {
                	String lnk;
                	PsDbConn co=PsDbMgr.newConnection();
                	ResultSet rs=co.sqlQueryR("select * from pmenuitem where menuid=1 order by itemid");
                	while (rs.next())
                	{
                		lnk="\""+rs.getString("ilink")+"\"";
                		if (rs.getInt("linkorgroup")==0)
                			lnk="null";
                				
                		out.println("m.add("+rs.getInt("itemid")+","+rs.getInt("parentid")+",\""+rs.getString("iname")+"\","+lnk+");");
                	}	
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("wkgmenu: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/pss/wkgmenu.jsp";from=(48,2);to=(65,7)]
                out.write("\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body topmargin=0>\r\n<h2>eMessenger<hr></h2>\r\n<script language=JavaScript>\r\n<!--\r\n m.setIconDocument(\"img/doc.gif\");\r\n m.setIconCollapse(\"img/open.gif\");\r\n m.setIconExpand(\"img/close.gif\");\r\n\r\n m.gen(true);\r\n//-->\r\n</script>\r\n</body>\r\n</html>");

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
