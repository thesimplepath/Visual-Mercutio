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


public class c$jsp extends HttpJspBase {


    static {
    }
    public c$jsp( ) {
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

            // HTML // begin [file="/emessenger/c.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/c.jsp";from=(1,106);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n\r\n");

            // end
            // begin [file="/emessenger/c.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/c.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/c.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/c.jsp";from=(8,29);to=(20,25)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n<body>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" >\r\n\r\n<form name=FRM action=\"c.jsp\" method=POST>\r\n<table cellSpacing=0 cellPadding=0 width=\"100%\">\r\n <tr class=Bg height=23 >\r\n <td>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/c.jsp";from=(20,28);to=(20,36)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/c.jsp";from=(20,38);to=(25,0)]
                out.write("/ard.gif\">&nbsp;</td>\r\n <td><font class=swb>ParamÃ¨tre</font></td>\r\n <td><font class=swf>Valeur</font></td>\r\n </tr>\r\n\r\n");

            // end
            // begin [file="/emessenger/c.jsp";from=(25,2);to=(62,0)]
                 
                  int mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
                  PsApp.init(); 
                
                  //mode 1
                  if (mode==1)
                  {
                	PsDebug.log("CONFIG.JSP update configuration...");
                	Enumeration pn=request.getParameterNames();
                	for (; pn.hasMoreElements();) 
                	{
                		String key=(String)pn.nextElement();
                		if (key.startsWith("CFG_")==true)
                		{
                			String val=(String)request.getParameter(key);
                			key=key.substring(4) ;
                			PsDebug.log("Set config "+key+"=("+val+")");
                			PsConfig.set(key,val);			
                		}	
                	}
                	PsConfig.save("config.ini");
                	PsDebug.log("Configuration Saved!");	
                	System.out.println("Configuration updated successfully!");
                	PsConfig.reset();
                	PsConfig.load("config.ini");
                  }
                
                  Hashtable v; 
                  v=PsConfig.getHashTable(); 
                  Enumeration f=v.elements();
                  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
                	 String kn=(String)e.nextElement();
                         out.println("<tr><td></td><td>"+kn+" :</td>");
                	 out.println("<td><input  style=\"width:100%;\" type=text size=80 name=\"CFG_"+kn+"\" value=\""+(String)f.nextElement()+"\"></td></tr>");
                     }
                  out.println("<input type=HIDDEN name=MODE value=1>");
                 
            // end
            // HTML // begin [file="/emessenger/c.jsp";from=(62,2);to=(70,7)]
                out.write("\r\n</table>\r\n<input type=submit value=\"Save Configuration\" class=sbttn>\r\n</form>\r\n<br><a href=\"aide.jsp\" target=\"_main\">Clean database !</a>\r\n</tr></tr>\r\n</table>\r\n</body>\r\n</html>");

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
