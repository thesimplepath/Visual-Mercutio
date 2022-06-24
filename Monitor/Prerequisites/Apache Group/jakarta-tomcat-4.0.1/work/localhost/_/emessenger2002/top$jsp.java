package org.apache.jsp;

import PsDebug;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class top$jsp extends HttpJspBase {


    static {
    }
    public top$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/top.jsp";from=(0,28);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(1,29);to=(6,0)]
                out.write("\r\n<html>\r\n<head>\r\n<link href=\"css/main.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<link href=\"css/global.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(6,2);to=(29,0)]
                
                PsDebug.log("Document= top.jsp");
                
                String p10="img/menu.off.on.separator.gif";
                String p0="img/menu.on.bg.gif";
                String p01="img/menu.on.off.separator.gif";
                String p1="img/menu.off.bg.gif";
                String p11="img/menu.off.off.separator.gif";
                
                String p1E="img/menu.off.end.gif";
                String p0E="img/menu.on.end.gif";
                String pE="img/menu.end.bg.gif";
                
                String p1S="img/lgo_hm_129x36.off.gif";
                String p0S="img/lgo_hm_129x36.on.gif";
                
                int tab= 	Integer.valueOf(request.getParameter( "TAB" )).intValue();
                PsDebug.log("top.jsp tab selection="+tab);
                String AA,BB,CC;
                int ZZ;
                
                String L1=(String)request.getParameter( "L1" );
                String L2=(String)request.getParameter( "L2" );
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(29,2);to=(37,22)]
                out.write("\r\n</head>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=\"0\" MARGINWIDTH=\"0\">\r\n<TABLE width=\"100%\" bgColor=#336699 border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD noWrap width=\"15%\" height=51>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\" height=51><A class=menu><FONT \r\n      class=TitleLine>");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(37,24);to=(37,61)]
                out.println(PsConfig.get("COMPANY"));
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(37,63);to=(44,0)]
                out.write("<a href=\"aide.jsp\">X</a> <a href=\"setdebug.jsp?DEBUG=0\">0</a> <a href=\"setdebug.jsp?DEBUG=1\">1</a> <a href=\"http://127.0.0.1:8080/emessenger2002/config.jsp?MODE=0\" target=doc>C</a></FONT></A></TD></TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD noWrap width=\"85%\">&nbsp;</TD></TR></TBODY></TABLE>\r\n<TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR> \r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(44,2);to=(44,92)]
                ZZ=0;if (tab==ZZ) {AA=p0S;BB=p0;CC=p01;} else {AA=p1S;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(44,94);to=(45,49)]
                out.write("\r\n    <TD vAlign=top width=129><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(45,52);to=(45,54)]
                out.print(AA);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(45,56);to=(46,26)]
                out.write("\" width=129 align=top></TD>\r\n    <TD noWrap background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(46,29);to=(46,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(46,33);to=(48,28)]
                out.write(">\r\n\t<A class=menu tabIndex=120 href=\"acceuil.html\" target=doc><FONT class=menu>Accueil</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(48,31);to=(48,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(48,35);to=(49,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(49,2);to=(49,78)]
                ZZ=1;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(49,80);to=(50,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(50,29);to=(50,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(50,33);to=(52,28)]
                out.write(">\r\n\t<A class=menu tabIndex=121 href=\"listcase.jsp?MODE=0\" target=doc><FONT class=menu>Boîte de<BR>travail</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(52,31);to=(52,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(52,35);to=(53,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(53,2);to=(53,78)]
                ZZ=2;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(53,80);to=(54,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(54,29);to=(54,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(54,33);to=(56,28)]
                out.write(">\r\n\t<A class=menu tabIndex=122 href=\"listcase.jsp?MODE=1\" target=doc><FONT class=menu>Processus<BR>en cours</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(56,31);to=(56,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(56,35);to=(57,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(57,2);to=(57,78)]
                ZZ=3;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(57,80);to=(58,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(58,29);to=(58,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(58,33);to=(60,28)]
                out.write(">\r\n\t<A class=menu tabIndex=123 href=\"statproc.html\" target=doc><FONT class=menu>Statistiques</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(60,31);to=(60,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(60,35);to=(61,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(61,2);to=(61,92)]
                ZZ=4;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(61,94);to=(62,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(62,29);to=(62,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(62,33);to=(64,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"newproc.jsp\" target=doc><FONT class=menu>Nouveau <BR>processus</FONT></A></TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(64,30);to=(64,32)]
                out.print(AA);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(64,34);to=(65,39)]
                out.write("\" width=11></TD>\r\n    <TD noWrap align=middle background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(65,42);to=(65,44)]
                out.print(pE);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(65,46);to=(67,51)]
                out.write(" bgColor=#336699>&nbsp;&nbsp;&nbsp;&nbsp;\r\n\t<A class=swnub tabIndex=125 href=\"logout.jsp\" target=_top><FONT class=swnu>Logout</FONT></A></TD>\r\n    <TD noWrap align=right width=\"100%\" background=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(67,54);to=(67,56)]
                out.print(pE);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(67,58);to=(72,58)]
                out.write(" bgColor=#336699>&nbsp;</TD>\r\n</TR></TBODY></TABLE>\r\n<TABLE width=\"100%\" bgColor=#93bee2 border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD noWrap width=\"15%\"><A class=menu><FONT class=menu>");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(72,61);to=(72,63)]
                out.print(L1);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(72,65);to=(75,58)]
                out.write("</FONT></A>&nbsp;</TD>\r\n  </TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\"><A class=menu><FONT class=menu>");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(75,61);to=(75,63)]
                out.print(L2);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(75,65);to=(81,13)]
                out.write("</FONT></A>&nbsp;</TD>\r\n  </TR></TBODY></TABLE>\r\n<Script language=JavaScript>\r\n<!--\r\nfunction showTab(no)\r\n{\r\n  l1=escape(\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(81,16);to=(81,18)]
                out.print(L1);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(81,20);to=(82,13)]
                out.write("\");\r\n  l2=escape(\"");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(82,16);to=(82,18)]
                out.print(L2);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(82,20);to=(97,33)]
                out.write("\");\r\n  document.location=\"top.jsp?TAB=\"+no+\"&L1=\"+l1+\"&L2=\"+l2;\r\n}\r\n\r\nfunction showTabText(no,l1,l2)\r\n{\r\n  l1=escape(l1);\r\n  l2=escape(l2);\r\n  document.location=\"top.jsp?TAB=\"+no+\"&L1=\"+l1+\"&L2=\"+l2;\r\n}\r\n\r\nfunction showText(l1,l2)\r\n{\r\n  l1=escape(l1);\r\n  l2=escape(l2);\r\n  document.location=\"top.jsp?TAB=");

            // end
            // begin [file="/emessenger2002/top.jsp";from=(97,36);to=(97,39)]
                out.print(tab);
            // end
            // HTML // begin [file="/emessenger2002/top.jsp";from=(97,41);to=(102,7)]
                out.write("&L1=\"+l1+\"&L2=\"+l2;\r\n}\r\n//-->\r\n</script>\r\n</body>\r\n</html>");

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
