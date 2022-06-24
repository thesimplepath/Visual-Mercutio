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


public class usermgt2$jsp extends HttpJspBase {


    static {
    }
    public usermgt2$jsp( ) {
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

            // HTML // begin [file="/usermgt2.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/usermgt2.jsp";from=(1,71);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/usermgt2.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/usermgt2.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(9,29);to=(12,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(12,2);to=(43,0)]
                
                 PsApp.init();
                 
                 try {
                  PsDbConn co;
                  ResultSet rs;
                  co=PsDbMgr.newConnection();	
                
                  String wkgid=request.getParameter( "WKGID" );
                  String mode=request.getParameter( "MODE" );
                  String login=request.getParameter("LOGIN");
                  if (mode!=null)
                  {
                   	if (mode.equals("1")==true)
                	{
                		//add
                		co.sqlExec("INSERT INTO pempmap VALUES ("+wkgid+",'"+login+"')");
                	} 
                   	if (mode.equals("2")==true)
                	{
                		//del
                		co.sqlExec("DELETE FROM pempmap WHERE wkgid="+wkgid+" AND login='"+login+"'");	
                	} 
                  }
                  
                  String wkgname="";
                  rs=co.sqlQueryR("SELECT wkgname FROM pworkgroup WHERE wkgid="+wkgid);
                  if (rs.next()==true)
                  {
                  	wkgname=rs.getString("wkgname");
                  }
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(43,2);to=(47,14)]
                out.write("\r\n<body>\r\n<TABLE width=\"100%\" border=0>\r\n<tr class=Bg><td>\r\n<a class=menu>");

            // end
            // begin [file="/usermgt2.jsp";from=(47,17);to=(47,24)]
                out.print(wkgname);
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(47,26);to=(58,0)]
                out.write("</a>\r\n</td></tr></table>\r\n\r\n<table width=\"100%\" border=0>\r\n<tr>\r\n<td>Utilisateurs:</td>\r\n<td></td>\r\n<td>Membres:</td>\r\n</tr>\r\n<tr>\r\n<td width=\"45%\" valign=top><select name=EMP size=18 style=\"width:100%;\">\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(58,2);to=(62,0)]
                
                	rs=co.sqlQueryR("SELECT count(*) as cnt,login,fname,lname FROM pemployee GROUP BY login ORDER BY lname,fname,login");
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(62,2);to=(63,16)]
                out.write("\r\n\t<option value=\"");

            // end
            // begin [file="/usermgt2.jsp";from=(63,19);to=(63,40)]
                out.print(rs.getString("login"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(63,42);to=(63,44)]
                out.write("\">");

            // end
            // begin [file="/usermgt2.jsp";from=(63,47);to=(63,68)]
                out.print(rs.getString("login"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(63,70);to=(63,73)]
                out.write(" : ");

            // end
            // begin [file="/usermgt2.jsp";from=(63,76);to=(63,97)]
                out.print(rs.getString("fname"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(63,99);to=(63,100)]
                out.write(" ");

            // end
            // begin [file="/usermgt2.jsp";from=(63,103);to=(63,124)]
                out.print(rs.getString("lname"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(63,126);to=(64,0)]
                out.write("</option>\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(64,2);to=(66,0)]
                
                	}
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(66,2);to=(70,131)]
                out.write("\r\n</select> \r\n</td>\r\n<td width=\"10%\" valign=middle align=center>\r\n<input type=button value=\"&nbsp;&nbsp;&gt;&nbsp;&gt;&nbsp;&nbsp;\" onclick=\"javascript:document.location='usermgt2.jsp?MODE=1&WKGID=");

            // end
            // begin [file="/usermgt2.jsp";from=(70,134);to=(70,139)]
                out.print(wkgid);
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(70,141);to=(72,131)]
                out.write("&LOGIN='+escape(EMP.value);\">\r\n<br><br>\r\n<input type=button value=\"&nbsp;&nbsp;&lt;&nbsp;&lt;&nbsp;&nbsp;\" onclick=\"javascript:document.location='usermgt2.jsp?MODE=2&WKGID=");

            // end
            // begin [file="/usermgt2.jsp";from=(72,134);to=(72,139)]
                out.print(wkgid);
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(72,141);to=(77,0)]
                out.write("&LOGIN='+escape(MAP.value);\">\r\n</td>\r\n\r\n<td width=\"45%\" valign=top>\r\n<select name=MAP size=18 style=\"width:100%;\">\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(77,2);to=(83,0)]
                
                if (wkgid!=null) 
                 {
                	rs=co.sqlQueryR("SELECT * FROM pempmap WHERE wkgid="+wkgid+" ORDER BY login");
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(83,2);to=(85,15)]
                out.write("\r\n\r\n<option value=\"");

            // end
            // begin [file="/usermgt2.jsp";from=(85,18);to=(85,39)]
                out.print(rs.getString("login"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(85,41);to=(85,43)]
                out.write("\">");

            // end
            // begin [file="/usermgt2.jsp";from=(85,46);to=(85,67)]
                out.print(rs.getString("login"));
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(85,69);to=(87,0)]
                out.write("</option>\r\n\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(87,2);to=(90,0)]
                
                	}	
                 }//if
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(90,2);to=(95,0)]
                out.write("\r\n</select>\r\n</td>\r\n</table>\r\n</body>\r\n");

            // end
            // begin [file="/usermgt2.jsp";from=(95,2);to=(102,0)]
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/usermgt2.jsp";from=(102,2);to=(103,7)]
                out.write("\r\n</html>");

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
