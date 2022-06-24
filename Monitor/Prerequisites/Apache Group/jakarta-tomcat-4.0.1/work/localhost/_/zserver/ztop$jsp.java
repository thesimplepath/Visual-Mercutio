package org.apache.jsp;

import PsDebug;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class ztop$jsp extends HttpJspBase {


    static {
    }
    public ztop$jsp( ) {
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

            // HTML // begin [file="/zserver/ztop.jsp";from=(0,0);to=(2,0)]
                out.write("ï»¿<html>\r\n<head>\r\n");

            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(2,37);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(3,26);to=(5,0)]
                out.write("\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(5,53);to=(7,0)]
                out.write("\r\n<link href=\"css/main.css\" rel=\"styleSheet\" type=\"text/css\">\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(7,2);to=(9,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(9,2);to=(10,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/zserver/ztop.jsp";from=(10,19);to=(10,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(10,29);to=(11,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(11,2);to=(33,0)]
                
                String p10="img/"+userskin+"/menu.off.on.separator.gif";
                String p0="img/"+userskin+"/menu.on.bg.gif";
                String p01="img/"+userskin+"/menu.on.off.separator.gif";
                String p1="img/"+userskin+"/menu.off.bg.gif";
                String p11="img/"+userskin+"/menu.off.off.separator.gif";
                
                String p1E="img/"+userskin+"/menu.off.end.gif";
                String p0E="img/"+userskin+"/menu.on.end.gif";
                String pE="img/"+userskin+"/menu.end.bg.gif";
                
                String p1S="img/"+userskin+"/lgo_hm_129x36.off.gif";
                String p0S="img/"+userskin+"/lgo_hm_129x36.on.gif";
                
                int tab= 	Integer.valueOf(request.getParameter( "TAB" )).intValue();
                //PsDebug.log("top.jsp tab selection="+tab);
                String AA,BB,CC;
                int ZZ;
                
                String L1=(String)request.getParameter( "L1" );
                String L2=(String)request.getParameter( "L2" );
                
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(33,2);to=(52,0)]
                out.write("\r\n<script language=JavaScript>\r\n//lock\r\ntop._top_loaded=false;\r\n</script>\r\n</head>\r\n<BODY>\r\n<TABLE class=Bg width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD noWrap width=\"15%\" height=51>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\" height=51><A class=menu><FONT \r\n      class=TitleLineBg>ProcessSoft's ZServer</FONT></TD></TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD noWrap width=\"85%\">&nbsp;</TD></TR></TBODY></TABLE>\r\n<TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR> \r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(52,2);to=(52,92)]
                ZZ=0;if (tab==ZZ) {AA=p0S;BB=p0;CC=p01;} else {AA=p1S;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(52,94);to=(53,49)]
                out.write("\r\n    <TD vAlign=top width=129><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(53,52);to=(53,54)]
                out.print(AA);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(53,56);to=(54,26)]
                out.write("\" width=129 align=top></TD>\r\n    <TD noWrap background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(54,29);to=(54,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(54,33);to=(56,28)]
                out.write(">\r\n\t<A class=menu tabIndex=120 href=\"zacceuil.jsp\" target=doc><FONT class=menu>Acceuil</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(56,31);to=(56,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(56,35);to=(57,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(57,2);to=(57,78)]
                ZZ=1;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(57,80);to=(58,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(58,29);to=(58,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(58,33);to=(60,28)]
                out.write(">\r\n\t<A class=menu tabIndex=121 href=\"zbrowse.jsp?PATH=\" target=doc><FONT class=menu>Explorateur<br>de fichiers</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(60,31);to=(60,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(60,35);to=(61,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(61,2);to=(61,78)]
                ZZ=2;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(61,80);to=(62,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(62,29);to=(62,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(62,33);to=(64,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"zdirmap.jsp\" target=doc><FONT class=menu>Authorisation<BR>d'accÃ¨s</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(64,30);to=(64,32)]
                out.print(CC);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(64,34);to=(65,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(65,2);to=(65,78)]
                ZZ=3;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(65,80);to=(66,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(66,29);to=(66,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(66,33);to=(68,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"zusermgt.jsp\" target=doc><FONT class=menu>Gestion<BR>Utilisateurs</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(68,30);to=(68,32)]
                out.print(CC);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(68,34);to=(69,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/zserver/ztop.jsp";from=(69,2);to=(69,92)]
                ZZ=4;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(69,94);to=(70,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(70,29);to=(70,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(70,33);to=(72,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"zconfig.jsp?MODE=0\" target=doc><FONT class=menu>Configuration<BR>Server</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(72,30);to=(72,32)]
                out.print(AA);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(72,34);to=(74,39)]
                out.write("\" width=11></TD>\r\n\r\n    <TD noWrap align=middle background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(74,42);to=(74,44)]
                out.print(pE);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(74,46);to=(79,51)]
                out.write(" class=Bg>&nbsp;&nbsp;&nbsp;&nbsp;\r\n      <A class=swnub tabIndex=125 href=\"customize.jsp\" target=\"doc\"><FONT class=swnu>Personaliser</FONT></A> \r\n      |\r\n      <A class=swnub tabIndex=125 href=\"logout.jsp\" target=_top><FONT class=swnu>Logout</FONT></A>\r\n    </TD>\r\n    <TD noWrap align=right width=\"100%\" background=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(79,54);to=(79,56)]
                out.print(pE);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(79,58);to=(87,25)]
                out.write(" class=Bg>&nbsp;</TD>\r\n</TR>\r\n</TBODY></TABLE>\r\n<TABLE class=BgL width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR valign=top >\r\n    <TD noWrap width=\"15%\" valign=top nobr><A class=menu><FONT class=menu>\r\n<script language=JavaScript>\r\ndocument.write(unescape(\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(87,28);to=(87,30)]
                out.print(L1);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(87,32);to=(94,25)]
                out.write("\"));\r\n</script>\r\n</FONT></A>&nbsp;</TD>\r\n  </TR>\r\n  <TR valign=top >\r\n    <TD noWrap width=\"15%\" nobr valign=top ><A class=menu><FONT class=menu>\r\n<script language=JavaScript>\r\ndocument.write(unescape(\"");

            // end
            // begin [file="/zserver/ztop.jsp";from=(94,28);to=(94,30)]
                out.print(L2);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(94,32);to=(104,15)]
                out.write("\"));\r\n</script>\r\n</FONT></A>&nbsp;</TD>\r\n  </TR></TBODY></TABLE>\r\n\r\n\r\n<DIV align=right id=TIMER name=TIMERDIV style=\"position:absolute;right:20px;top=10px;width:200px;height=50px;\" ></DIV>\r\n\r\n<Script language=JavaScript>\r\n<!--\r\ntop.currentTab=");

            // end
            // begin [file="/zserver/ztop.jsp";from=(104,18);to=(104,21)]
                out.print(tab);
            // end
            // HTML // begin [file="/zserver/ztop.jsp";from=(104,23);to=(159,7)]
                out.write(";\r\n\r\n// manage clock display\r\nfunction writeObj(id,text)\r\n{\r\n  if (document.getElementById)\r\n\t{\r\n\t\tx = document.getElementById(id);\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.all)\r\n\t{\r\n\t\tx = document.all[id];\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.layers)\r\n\t{\r\n\t\tx = document.layers[id];\r\n\t\tx.document.open();\r\n\t\tx.document.write(text);\r\n\t\tx.document.close();\r\n\t}\r\n\r\n}\r\nfunction format2(num)\r\n{\r\n\tvar ret=\"\";\r\n\tif (num<=9)\r\n\t\tret=\"0\";\r\n\tret=ret+num;\r\n\treturn ret;\t\t\r\n\r\n}\r\nfunction displayTimer()\r\n{\r\n\tvar monthList=new Array(\"Jan\",\"Fev\",\"Mar\",\"Avr\",\"Mai\",\"Jui\",\"Juil\",\"Aou\",\"Sep\",\"Oct\",\"Nov\",\"Dec\");\r\n\tvar today = new Date();  \r\n\tdis=format2(today.getHours())+\":\"+format2(today.getMinutes())+\":\"+format2(today.getSeconds());\r\n\tdis=dis+\"<br>\";\r\n\tdis=dis+today.getDate()+\" \"+monthList[today.getMonth()]+\" \"+today.getYear();\r\n\twriteObj(\"TIMER\",\"<FONT class=menu>\"+dis+\"</font>\");\r\n\r\n\tsetTimeout(\"displayTimer()\",  1000);\r\n}\r\n\r\nsetTimeout(\"displayTimer()\",  1000);\r\n//-->\r\n</script>\r\n\r\n<script language=JavaScript>\r\n//unlock\r\ntop._top_loaded=true;\r\n</script>\r\n\r\n</body>\r\n</html>");

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
