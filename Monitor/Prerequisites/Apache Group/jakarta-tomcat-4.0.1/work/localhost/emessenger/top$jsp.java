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

            // HTML // begin [file="/top.jsp";from=(0,0);to=(2,0)]
                out.write("ï»¿<html>\r\n<head>\r\n");

            // end
            // HTML // begin [file="/top.jsp";from=(2,37);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/top.jsp";from=(3,26);to=(5,0)]
                out.write("\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n");

            // end
            // begin [file="/top.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/top.jsp";from=(5,53);to=(7,0)]
                out.write("\r\n<link href=\"css/main.css\" rel=\"styleSheet\" type=\"text/css\">\r\n");

            // end
            // begin [file="/top.jsp";from=(7,2);to=(9,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/top.jsp";from=(9,2);to=(10,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/top.jsp";from=(10,19);to=(10,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/top.jsp";from=(10,29);to=(11,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n");

            // end
            // begin [file="/top.jsp";from=(11,2);to=(33,0)]
                
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
            // HTML // begin [file="/top.jsp";from=(33,2);to=(45,24)]
                out.write("\r\n<script language=JavaScript>\r\n//lock\r\ntop._top_loaded=false;\r\n</script>\r\n</head>\r\n<BODY>\r\n<TABLE class=Bg width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD noWrap width=\"15%\" height=51>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\" height=51><A class=menu><FONT \r\n      class=TitleLineBg>");

            // end
            // begin [file="/top.jsp";from=(45,26);to=(45,63)]
                out.println(PsConfig.get("COMPANY"));
            // end
            // HTML // begin [file="/top.jsp";from=(45,65);to=(52,0)]
                out.write("</FONT></TD></TR>\r\n  <TR>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD noWrap width=\"85%\">&nbsp;</TD></TR></TBODY></TABLE>\r\n<TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR> \r\n");

            // end
            // begin [file="/top.jsp";from=(52,2);to=(52,92)]
                ZZ=0;if (tab==ZZ) {AA=p0S;BB=p0;CC=p01;} else {AA=p1S;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(52,94);to=(53,49)]
                out.write("\r\n    <TD vAlign=top width=129><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(53,52);to=(53,54)]
                out.print(AA);
            // end
            // HTML // begin [file="/top.jsp";from=(53,56);to=(54,26)]
                out.write("\" width=129 align=top></TD>\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(54,29);to=(54,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(54,33);to=(56,28)]
                out.write(">\r\n\t<A class=menu tabIndex=120 href=\"acceuil.jsp\" target=doc><FONT class=menu>Accueil</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(56,31);to=(56,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(56,35);to=(57,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(57,2);to=(57,78)]
                ZZ=1;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(57,80);to=(58,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(58,29);to=(58,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(58,33);to=(60,28)]
                out.write(">\r\n\t<A class=menu tabIndex=121 href=\"listcase.jsp?MODE=0\" target=doc><FONT class=menu>BoÃ®te de<BR>travail</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(60,31);to=(60,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(60,35);to=(61,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(61,2);to=(61,78)]
                ZZ=2;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(61,80);to=(62,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(62,29);to=(62,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(62,33);to=(64,28)]
                out.write(">\r\n\t<A class=menu tabIndex=122 href=\"listcase.jsp?MODE=1\" target=doc><FONT class=menu>Processus<BR>en cours</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(64,31);to=(64,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(64,35);to=(65,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(65,2);to=(65,75)]
                ZZ=3;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (tab==9) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(65,77);to=(66,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(66,29);to=(66,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(66,33);to=(68,28)]
                out.write(">\r\n\t<A class=menu tabIndex=123 href=\"listcase.jsp?MODE=2\" target=doc><FONT class=menu>Recherche<br> Cas</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(68,31);to=(68,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(68,35);to=(69,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(69,2);to=(74,0)]
                
                //Test if Administration role is in use. If so display the "Server Config" tab
                String userrole= (String)session.getAttribute( "USERROLE");
                if (userrole!=null && (userrole.equals("0")==true || userrole.equals("1")==true || userrole.equals("2")==true))
                {
            // end
            // HTML // begin [file="/top.jsp";from=(74,2);to=(75,4)]
                out.write("\r\n    ");

            // end
            // begin [file="/top.jsp";from=(75,6);to=(75,79)]
                ZZ=9;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (tab==4) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(75,81);to=(76,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(76,29);to=(76,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(76,33);to=(78,28)]
                out.write(">\r\n\t<A class=menu tabIndex=123 href=\"stats.jsp\" target=doc><FONT class=menu>Statistiques</FONT></A>&nbsp;</TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(78,31);to=(78,33)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(78,35);to=(79,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(79,2);to=(84,0)]
                
                }
                
                if (userrole!=null && userrole.equals("0")==true)
                {
            // end
            // HTML // begin [file="/top.jsp";from=(84,2);to=(85,0)]
                out.write("\r\n");

            // end
            // begin [file="/top.jsp";from=(85,2);to=(85,78)]
                ZZ=4;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(85,80);to=(86,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(86,29);to=(86,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(86,33);to=(88,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"newproc.jsp\" target=doc><FONT class=menu>Nouveau <BR>processus</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(88,30);to=(88,32)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(88,34);to=(89,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(89,2);to=(89,78)]
                ZZ=5;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(89,80);to=(90,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(90,29);to=(90,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(90,33);to=(92,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"usermgt.jsp\" target=doc><FONT class=menu>Gestion<BR>Utilisateurs</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(92,30);to=(92,32)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(92,34);to=(93,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(93,2);to=(93,78)]
                ZZ=6;if (tab==ZZ) {BB=p0;CC=p01;} else {BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(93,80);to=(94,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(94,29);to=(94,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(94,33);to=(96,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"syslogic.jsp\" target=doc><FONT class=menu>SystÃ¨mes <BR>Logiques</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(96,30);to=(96,32)]
                out.print(CC);
            // end
            // HTML // begin [file="/top.jsp";from=(96,34);to=(97,0)]
                out.write("\" width=28></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(97,2);to=(97,92)]
                ZZ=7;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(97,94);to=(98,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(98,29);to=(98,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(98,33);to=(100,27)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"config.jsp?MODE=0\" target=doc><FONT class=menu>Configuration<BR>Server</FONT></A>&nbsp;</TD>\r\n   <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(100,30);to=(100,32)]
                out.print(AA);
            // end
            // HTML // begin [file="/top.jsp";from=(100,34);to=(101,0)]
                out.write("\" width=11></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(101,2);to=(105,0)]
                
                }
                else
                {
            // end
            // HTML // begin [file="/top.jsp";from=(105,2);to=(106,0)]
                out.write("\r\n");

            // end
            // begin [file="/top.jsp";from=(106,2);to=(106,92)]
                ZZ=4;if (tab==ZZ) {AA=p0E;BB=p0;CC=p01;} else {AA=p1E;BB=p1;CC=p11;if (ZZ+1==tab) CC=p10;}
            // end
            // HTML // begin [file="/top.jsp";from=(106,94);to=(107,26)]
                out.write("\r\n    <TD noWrap background=");

            // end
            // begin [file="/top.jsp";from=(107,29);to=(107,31)]
                out.print(BB);
            // end
            // HTML // begin [file="/top.jsp";from=(107,33);to=(111,28)]
                out.write(">\r\n\t<A class=swnub tabIndex=124 href=\"newproc.jsp\" target=doc>\r\n\t<FONT class=menu>Nouveau<BR>processus</FONT></A>\r\n    </TD>\r\n    <TD><IMG height=36 src=\"");

            // end
            // begin [file="/top.jsp";from=(111,31);to=(111,33)]
                out.print(AA);
            // end
            // HTML // begin [file="/top.jsp";from=(111,35);to=(112,0)]
                out.write("\" width=11></TD>\r\n");

            // end
            // begin [file="/top.jsp";from=(112,2);to=(114,0)]
                
                }
            // end
            // HTML // begin [file="/top.jsp";from=(114,2);to=(115,39)]
                out.write("\r\n    <TD noWrap align=middle background=");

            // end
            // begin [file="/top.jsp";from=(115,42);to=(115,44)]
                out.print(pE);
            // end
            // HTML // begin [file="/top.jsp";from=(115,46);to=(120,51)]
                out.write(" class=Bg>&nbsp;&nbsp;&nbsp;&nbsp;\r\n      <A class=swnub tabIndex=125 href=\"customize.jsp\" target=\"doc\"><FONT class=swnu>Personaliser</FONT></A> \r\n      |\r\n      <A class=swnub tabIndex=125 href=\"logout.jsp\" target=_top><FONT class=swnu>Logout</FONT></A>\r\n    </TD>\r\n    <TD noWrap align=right width=\"100%\" background=");

            // end
            // begin [file="/top.jsp";from=(120,54);to=(120,56)]
                out.print(pE);
            // end
            // HTML // begin [file="/top.jsp";from=(120,58);to=(128,25)]
                out.write(" class=Bg>&nbsp;</TD>\r\n</TR>\r\n</TBODY></TABLE>\r\n<TABLE class=BgL width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR valign=top >\r\n    <TD noWrap width=\"15%\" valign=top nobr><A class=menu><FONT class=menu>\r\n<script language=JavaScript>\r\ndocument.write(unescape(\"");

            // end
            // begin [file="/top.jsp";from=(128,28);to=(128,30)]
                out.print(L1);
            // end
            // HTML // begin [file="/top.jsp";from=(128,32);to=(135,25)]
                out.write("\"));\r\n</script>\r\n</FONT></A>&nbsp;</TD>\r\n  </TR>\r\n  <TR valign=top >\r\n    <TD noWrap width=\"15%\" nobr valign=top ><A class=menu><FONT class=menu>\r\n<script language=JavaScript>\r\ndocument.write(unescape(\"");

            // end
            // begin [file="/top.jsp";from=(135,28);to=(135,30)]
                out.print(L2);
            // end
            // HTML // begin [file="/top.jsp";from=(135,32);to=(145,15)]
                out.write("\"));\r\n</script>\r\n</FONT></A>&nbsp;</TD>\r\n  </TR></TBODY></TABLE>\r\n\r\n\r\n<DIV align=right id=TIMER name=TIMERDIV style=\"position:absolute;right:20px;top=10px;width:200px;height=50px;\" ></DIV>\r\n\r\n<Script language=JavaScript>\r\n<!--\r\ntop.currentTab=");

            // end
            // begin [file="/top.jsp";from=(145,18);to=(145,21)]
                out.print(tab);
            // end
            // HTML // begin [file="/top.jsp";from=(145,23);to=(200,7)]
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
