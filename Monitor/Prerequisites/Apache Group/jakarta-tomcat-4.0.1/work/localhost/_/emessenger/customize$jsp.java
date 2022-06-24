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


public class customize$jsp extends HttpJspBase {


    static {
    }
    public customize$jsp( ) {
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

            // HTML // begin [file="/emessenger/customize.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(1,106);to=(4,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/customize.jsp";from=(4,2);to=(6,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(6,2);to=(7,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/customize.jsp";from=(7,19);to=(7,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(7,29);to=(9,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n");

            // end
            // begin [file="/emessenger/customize.jsp";from=(9,0);to=(9,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(9,53);to=(14,35)]
                out.write("\r\n\r\n<!-- ------------------------------------ //-->\r\n<script language=JavaScript>\r\n//Display tab on top.jsp\r\nvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/emessenger/customize.jsp";from=(14,38);to=(14,78)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(14,80);to=(14,86)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/customize.jsp";from=(14,89);to=(14,132)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(14,134);to=(14,136)]
                out.write(" (");

            // end
            // begin [file="/emessenger/customize.jsp";from=(14,139);to=(14,187)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(14,189);to=(31,34)]
                out.write(")\";\r\nvar info2=\"\";\r\nvar tabno=7;\r\ntop.showTabText(tabno,info1,info2);\r\n</script>\r\n<!-- ------------------------------------ //-->\r\n\r\n</head>\r\n<body>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" >\r\n\r\n<form name=FRM action=\"customize.jsp\" method=GET>\r\n<table cellSpacing=0 cellPadding=0 width=\"100%\">\r\n <tr class=Bg height=23 >\r\n <td width=23>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/customize.jsp";from=(31,37);to=(31,45)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(31,47);to=(36,0)]
                out.write("/ard.gif\">&nbsp;</td>\r\n <td><font class=swb>ParamÃ¨tre</font></td>\r\n <td><font class=swf>Valeur</font></td>\r\n </tr>\r\n\r\n");

            // end
            // begin [file="/emessenger/customize.jsp";from=(36,2);to=(53,1)]
                 
                  int mode=0;
                  if (request.getParameter("MODE")!=null)
                	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
                  PsApp.init(); 
                
                  //mode 1
                  if (mode==1)
                  {
                	PsDebug.log("CUSTOMIZE.JSP customization updated...");
                	PsDbConn conn=PsDbMgr.newConnection();
                	String skin=request.getParameter("NO");
                	ResultSet rs=conn.sqlQueryR("SELECT * FROM ppersonalize WHERE login='"+(String)session.getAttribute("USERNAME")+"'");
                	if (rs.next()==false)
                		conn.sqlExec("INSERT INTO ppersonalize VALUES ('"+(String)session.getAttribute("USERNAME")+"','"+skin+"',0)");
                	else
                		conn.sqlExec("UPDATE ppersonalize SET userskin='"+skin+"' WHERE login='"+(String)session.getAttribute("USERNAME")+"'");
                	
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(53,3);to=(55,1)]
                out.write("\r\n\r\n\t");

            // end
            // begin [file="/emessenger/customize.jsp";from=(55,3);to=(59,8)]
                
                  	//Set cookie
                	 Cookie c = new Cookie("userskin", skin); 
                	 response.addCookie(c); 
                        
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(59,10);to=(64,1)]
                out.write("\r\n\r\n\t<script language=JavaScript>\r\n\ttop.document.location=\"logout.jsp\";\r\n\t</script>\r\n\t");

            // end
            // begin [file="/emessenger/customize.jsp";from=(64,3);to=(66,0)]
                
                  }
            // end
            // HTML // begin [file="/emessenger/customize.jsp";from=(66,2);to=(96,7)]
                out.write("\r\n  <tr><td></td>\r\n  <td><input type=radio name=NO value=\"1\">ModÃ¨le de couleur <b>Messenger</b></td>\r\n  <td><img src=\"img/skin1/preview.gif\"></td></tr>\r\n\r\n  <tr><td></td>\r\n  <td><input type=radio name=NO value=\"2\">ModÃ¨le de couleur <b>Windows</b></td>\r\n  <td><img src=\"img/skin2/preview.gif\"></td></tr>\r\n\r\n  <tr><td></td>\r\n  <td><input type=radio name=NO value=\"3\">ModÃ¨le de couleur <b>Rouge</b></td>\r\n  <td><img src=\"img/skin3/preview.gif\"></td></tr>\r\n\r\n  <tr><td></td>\r\n  <td><input type=radio name=NO value=\"4\">ModÃ¨le de couleur <b>Vert</b></td>\r\n  <td><img src=\"img/skin4/preview.gif\"></td></tr>\r\n\r\n  <tr><td></td>\r\n  <td><input type=radio name=NO value=\"5\">ModÃ¨le de couleur <b>Jaune</b></td>\r\n  <td><img src=\"img/skin5/preview.gif\"></td></tr>\r\n\r\n\r\n  <input type=HIDDEN name=MODE value=1>\r\n \r\n</table>\r\n<input type=submit value=\"Appliquer la personalisation\" class=sbttn>\r\n</form>\r\n</tr></tr>\r\n</table>\r\n</body>\r\n</html>");

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
