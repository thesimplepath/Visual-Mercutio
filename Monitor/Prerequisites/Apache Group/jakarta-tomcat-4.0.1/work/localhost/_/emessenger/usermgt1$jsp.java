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


public class usermgt1$jsp extends HttpJspBase {


    static {
    }
    public usermgt1$jsp( ) {
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

            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(1,71);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/usermgt1.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/usermgt1.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/usermgt1.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(9,29);to=(17,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<link href=\"css/tree.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\r\n<script language=javaScript src=\"js/tree.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n var m=new oMenu;\r\n");

            // end
            // begin [file="/emessenger/usermgt1.jsp";from=(17,2);to=(38,0)]
                
                 PsApp.init();
                 
                 try {
                	int maxWkgId=-1;
                	PsDbConn co=PsDbMgr.newConnection();
                	ResultSet rs=co.sqlQueryR("SELECT * FROM pworkgroup ORDER BY wkgid");
                	while (rs.next())
                	{
                		String lnk="usermgt2.jsp?WKGID="+rs.getInt("wkgid");
                		if (maxWkgId<rs.getInt("wkgid")) 
                			maxWkgId=rs.getInt("wkgid")+1;		
                		out.println("m.add("+rs.getInt("wkgid")+","+rs.getInt("wkgparent")+",\""+rs.getString("wkgname")+"\",\""+lnk+"\");");
                	}	
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/emessenger/usermgt1.jsp";from=(38,2);to=(55,7)]
                out.write("\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n<script language=JavaScript>\r\n<!--\r\n m.setTarget(\"usr\");\r\n m.setIconDocument(\"img/doc.gif\");\r\n m.setIconCollapse(\"img/close.gif\");\r\n m.setIconExpand(\"img/open.gif\");\r\n\r\n m.gen(true);\r\n//-->\r\n</script>\r\n</body>\r\n</html>");

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