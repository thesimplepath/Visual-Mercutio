package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import java.io.File;
import java.text.DateFormat;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class zbrowse2$jsp extends HttpJspBase {


    static {
    }
    public zbrowse2$jsp( ) {
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

            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(1,105);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(9,29);to=(21,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n</head>\r\n<body>\r\n\r\n<table cellSpacing=0 cellPadding=0 width=\"100%\">\r\n<tr class=Bg height=23>\r\n<td><font class=swb>Version</font></td>\r\n<td><font class=swb>Fichier</font></td>\r\n<td><font class=swb>CrÃ©ation</font></td>\r\n<td><font class=swb>Modification</font></td>\r\n<td><font class=swb>AccÃ¨s</font></td>\r\n</tr>\r\n");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(21,2);to=(59,3)]
                
                 PsApp.init();
                
                 PsDbConn conn=PsDbMgr.newConnection();
                 ResultSet rs;
                
                 String dir=request.getParameter( "DIR" ); 
                 String fulldir=PsConfig.get("ZSERVER_ROOT")+File.separator+dir;
                 try
                 {
                	File f;
                	f=new File(fulldir);
                	String r[];
                	r=f.list();
                	for (int i=0;i<r.length;i++)
                	{
                		File t;
                		t=new File(f,r[i]);
                		if (t.isDirectory()==false)
                		{
                			Date filedate=new Date(f.lastModified());
                			Time filetime=new Time(f.lastModified());
                			String ftime=filetime.toString()+" "+filedate.toString();
                		
                			int filever=0;
                			Date creationDate=new Date(0);
                			Date lastChange=new Date(0);
                			int countaccess=0;
                	
                			rs=conn.sqlQueryR("SELECT * FROM pzsrvfiles WHERE dirname='"+dir+"' AND filename='"+r[i]+"' ORDER BY filename");
                			if (rs.next()==true)
                			{
                				filever=rs.getInt("filever");
                				creationDate=rs.getDate("creationdate");
                				lastChange=rs.getDate("lastChange");
                				countaccess=rs.getInt("countaccess");
                			}
                
                	  
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(59,5);to=(61,6)]
                out.write("\r\n\t\t<tr>\r\n\t\t<td>");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(61,9);to=(61,16)]
                out.print(filever);
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(61,18);to=(62,6)]
                out.write("</td>\r\n\t\t<td>");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(62,9);to=(62,13)]
                out.print(r[i]);
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(62,15);to=(63,6)]
                out.write("</td>\r\n\t\t<td>");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(63,9);to=(63,32)]
                out.print(creationDate.toString());
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(63,34);to=(64,6)]
                out.write("</td>\r\n\t\t<td>");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(64,9);to=(64,14)]
                out.print(ftime);
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(64,16);to=(65,6)]
                out.write("</td>\r\n\t\t<td>");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(65,9);to=(65,20)]
                out.print(countaccess);
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(65,22);to=(67,3)]
                out.write("</td>\r\n\t\t</tr>\r\n\t  ");

            // end
            // begin [file="/zserver/zbrowse2.jsp";from=(67,5);to=(78,0)]
                
                		}
                	}
                
                 }
                 catch (SecurityException e)
                 {
                	PsDebug.fail("Security Exception: "+e.getMessage());
                 }
                
                
            // end
            // HTML // begin [file="/zserver/zbrowse2.jsp";from=(78,2);to=(81,7)]
                out.write("\r\n</table>\r\n</body>\r\n</html>");

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
