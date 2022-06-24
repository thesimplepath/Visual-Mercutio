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


public class acceuil$jsp extends HttpJspBase {


    static {
    }
    public acceuil$jsp( ) {
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

            // HTML // begin [file="/emessenger/acceuil.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(1,63);to=(3,0)]
                out.write("\r\n<head>\r\n");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(4,2);to=(6,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(6,2);to=(7,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(7,19);to=(7,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(7,29);to=(16,36)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n\r\n<!-- ------------------------------------ //-->\r\n<script language=JavaScript>\r\n//Display tab on top.jsp\r\nfunction delayedDisplay()\r\n{\r\n\tvar info1=\"Utilisateur:</td><td><b>");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(16,39);to=(16,79)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(16,81);to=(16,87)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(16,90);to=(16,133)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(16,135);to=(16,137)]
                out.write(" (");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(16,140);to=(16,188)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(16,190);to=(25,0)]
                out.write(")\";\r\n\tvar info2=\"Welcome...\";\r\n\tvar tabno=0;\r\n\ttop.showTabText(tabno,info1,info2);\r\n}\r\n//document.onload=delayedDisplay();\r\n</script>\r\n<!-- ------------------------------------ //-->\r\n\r\n");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(25,2);to=(52,0)]
                
                 String username=(String)session.getAttribute("USERNAME");
                 if (username==null) return;
                 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                
                 PsApp.init();
                
                 System.out.println("JDBCDRIVER="+PsConfig.get("JDBCDRIVER")+"*");
                 System.out.println("JDBCDNS="+PsConfig.get("JDBCDNS")+"*");
                 System.out.println("JDBCLOGIN="+PsConfig.get("JDBCLOGIN")+"*");
                 System.out.println("JDBCPASSWD="+PsConfig.get("JDBCPASSWD")+"*");
                
                 PsDbConn conn=PsDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid<90");
                 rs.next();
                 int nbrCaseAll=rs.getInt("cnt");
                
                 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid<=6 AND statusid>=3");
                 rs.next();
                 int nbrCaseWait=rs.getInt("cnt");
                
                 rs=conn.sqlQueryR("SELECT count(*) as cnt FROM pproctrans WHERE emplid="+userid+" AND statusid=1");
                 rs.next();
                 int nbrCaseLock=rs.getInt("cnt");
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(52,2);to=(55,0)]
                out.write("\r\n\r\n<body onload=\"delayedDisplay();\">\r\n");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(55,3);to=(55,33)]
                out.print(PsConfig.get("WELCOME_SCREEN"));
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(55,35);to=(63,69)]
                out.write("\r\n<br>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" >\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n        <TR class=BgL>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(63,72);to=(63,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(63,82);to=(70,20)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"87%\"><FONT class=menu>Statistiques</FONT></TD>\r\n          <TD width=\"10%\" class=BgL><FONT class=menu>&nbsp;</FONT></TD>\r\n\t</TR>\r\n\t<TR>\r\n \t  <TD>&nbsp;</TD>\r\n \t  <TD>Nombre de cas:</TD>\r\n \t  <TD align=right>");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(70,23);to=(70,33)]
                out.print(nbrCaseAll);
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(70,35);to=(75,20)]
                out.write("</TD>\r\n\t</TR>\r\n\t<TR>\r\n \t  <TD>&nbsp;</TD>\r\n \t  <TD>Nombre de cas en attente:</TD>\r\n \t  <TD align=right>");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(75,23);to=(75,34)]
                out.print(nbrCaseWait);
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(75,36);to=(80,20)]
                out.write("</TD>\r\n\t</TR>\r\n\t<TR>\r\n \t  <TD>&nbsp;</TD>\r\n \t  <TD>Nombre de cas en cours de travail:</TD>\r\n \t  <TD align=right>");

            // end
            // begin [file="/emessenger/acceuil.jsp";from=(80,23);to=(80,34)]
                out.print(nbrCaseLock);
            // end
            // HTML // begin [file="/emessenger/acceuil.jsp";from=(80,36);to=(87,7)]
                out.write("</TD>\r\n\t</TR>\t\r\n      </TABLE>\r\n  </TR>\r\n</TABLE>\r\n\r\n</body>\r\n</html>");

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
