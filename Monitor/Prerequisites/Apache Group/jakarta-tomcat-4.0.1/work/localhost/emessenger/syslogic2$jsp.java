package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsConv;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class syslogic2$jsp extends HttpJspBase {


    static {
    }
    public syslogic2$jsp( ) {
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

            // HTML // begin [file="/syslogic2.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/syslogic2.jsp";from=(1,78);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/syslogic2.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/syslogic2.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(9,29);to=(12,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(12,2);to=(41,0)]
                
                 PsApp.init();
                 
                 try {
                  PsDbConn co;
                  ResultSet rs;
                  co=PsDbMgr.newConnection();	
                
                  String systemid=request.getParameter( "SYSTEMID" );
                  String mode=request.getParameter( "MODE" );
                  String cmd=request.getParameter("CMD");
                  String par=request.getParameter("PAR");
                  String dir=request.getParameter("DIR");
                  String sysname="";
                  if (mode!=null)
                  {
                   	if (mode.equals("1")==true)
                	{
                		//update		
                		co.sqlExec("UPDATE psystem set command='"+PsConv.c4JS(cmd)+"',parameters='"+PsConv.c4JS(par)+"',directory='"+PsConv.c4JS(dir)+"' WHERE systemid="+systemid);
                	} 
                
                  }
                
                  rs=co.sqlQueryR("SELECT systemtitle FROM psystem WHERE systemid="+systemid);
                  if (rs.next()==true)
                  sysname=rs.getString("systemtitle");	
                
                
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(41,2);to=(45,13)]
                out.write("\r\n<body>\r\n<TABLE width=\"100%\" border=0>\r\n<tr class=Bg><td>\r\n<a class=swb>");

            // end
            // begin [file="/syslogic2.jsp";from=(45,16);to=(45,23)]
                out.print(sysname);
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(45,25);to=(48,0)]
                out.write("</a>\r\n</td></tr></table>\r\n\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(48,2);to=(53,0)]
                
                	rs=co.sqlQueryR("SELECT * FROM psystem WHERE systemid="+systemid);
                
                	if (rs.next()==true)
                	{
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(53,2);to=(57,82)]
                out.write("\r\n<table class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n<tr>\r\n<td width=16> </td>\r\n<td>Identificateur :</td><td><input readonly type=text style=\"width:100%;\" value=\"");

            // end
            // begin [file="/syslogic2.jsp";from=(57,85);to=(57,106)]
                out.print(rs.getString("clsid"));
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(57,108);to=(61,82)]
                out.write("\"></td>\r\n</tr>\r\n<tr>\r\n<td width=16> </td>\r\n<td>Titre SystÃ¨me :</td><td><input readonly type=text style=\"width:100%;\" value=\"");

            // end
            // begin [file="/syslogic2.jsp";from=(61,85);to=(61,112)]
                out.print(rs.getString("systemtitle"));
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(61,114);to=(65,76)]
                out.write("\"></td>\r\n</tr>\r\n<tr>\r\n<td width=16> </td>\r\n<td>Commande :</td><td><input name=CMD type=text style=\"width:100%;\" value=\"");

            // end
            // begin [file="/syslogic2.jsp";from=(65,79);to=(65,102)]
                out.print(rs.getString("command"));
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(65,104);to=(69,77)]
                out.write("\"></td>\r\n</tr>\r\n<tr>\r\n<td width=16> </td>\r\n<td>Parametre :</td><td><input name=PAR type=text style=\"width:100%;\" value=\"");

            // end
            // begin [file="/syslogic2.jsp";from=(69,80);to=(69,106)]
                out.print(rs.getString("parameters"));
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(69,108);to=(73,79)]
                out.write("\"></td>\r\n</tr>\r\n<tr>\r\n<td width=16> </td>\r\n<td>RÃ©pertoire :</td><td><input name=DIR type=text style=\"width:100%;\" value=\"");

            // end
            // begin [file="/syslogic2.jsp";from=(73,82);to=(73,107)]
                out.print(rs.getString("directory"));
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(73,109);to=(78,150)]
                out.write("\"></td>\r\n</tr>\r\n<tr>\r\n<tr>\r\n<td width=16> </td>\r\n<td>&nbsp;</td><td><input type=button class=sbttn value=Sauver les modifications onclick=\"javascript:document.location='syslogic2.jsp?MODE=1&SYSTEMID=");

            // end
            // begin [file="/syslogic2.jsp";from=(78,153);to=(78,161)]
                out.print(systemid);
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(78,163);to=(82,0)]
                out.write("&CMD='+escape(CMD.value)+'&PAR='+escape(PAR.value)+'&DIR='+escape(DIR.value);\"></td>\r\n</tr>\r\n</table>\r\n\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(82,2);to=(84,0)]
                
                	}
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(84,2);to=(86,0)]
                out.write("\r\n</body>\r\n");

            // end
            // begin [file="/syslogic2.jsp";from=(86,2);to=(93,0)]
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("syslogic2.jsp: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/syslogic2.jsp";from=(93,2);to=(94,7)]
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
