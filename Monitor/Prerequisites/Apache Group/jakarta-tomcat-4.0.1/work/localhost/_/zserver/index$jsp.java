package org.apache.jsp;

import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class index$jsp extends HttpJspBase {


    static {
    }
    public index$jsp( ) {
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

            // HTML // begin [file="/zserver/index.jsp";from=(0,0);to=(2,0)]
                out.write("ï»¿<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n<HTML>\r\n");

            // end
            // HTML // begin [file="/zserver/index.jsp";from=(2,26);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/index.jsp";from=(3,29);to=(6,0)]
                out.write("\r\n<HEAD><TITLE>Sign In</TITLE>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n");

            // end
            // begin [file="/zserver/index.jsp";from=(6,2);to=(26,0)]
                 
                	//String userskin = ServletUtils.getCookie(request, "userskin"); 
                	Cookie cookies[]= request.getCookies();
                	String userskin=null;
                	if (cookies!=null)
                	{
                		int l=cookies.length;
                		for (int i=0;i<l;i++)
                		{
                		System.out.println(cookies[i].getName()+"="+cookies[i].getValue());
                			if (cookies[i].getName().equals("userskin")==true)
                			{
                				userskin=cookies[i].getValue();
                				break;
                			}
                		}
                	}
                	if (userskin==null)
                		userskin="1";
                	userskin="skin"+userskin;
            // end
            // HTML // begin [file="/zserver/index.jsp";from=(26,2);to=(27,16)]
                out.write("\r\n<LINK href=\"css/");

            // end
            // begin [file="/zserver/index.jsp";from=(27,19);to=(27,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/index.jsp";from=(27,29);to=(56,24)]
                out.write("/global.css\" rel=STYLESHEET>\r\n\r\n<SCRIPT language=JavaScript>\r\nfunction checkForm()\r\n{\r\n\tif (document.InputInfo.LOGIN.value == \"\")\r\n\t{\r\n\t\talert(\"Merci d'indiquer votre identifiant.\");\r\n\t\tdocument.InputInfo.ID.focus();\r\n\t\treturn false;\r\n\t}\r\n\treturn true;\r\n}\r\n\r\nfunction resetForm()\r\n{\r\n\tdocument.InputInfo.reset();\r\n\treturn false;\r\n}\r\n</SCRIPT>\r\n\r\n</HEAD>\r\n\r\n<BODY>\r\n<TABLE width=\"72%\" border=0>\r\n  <TBODY>\r\n  <TR class=Bg>\r\n    <TD noWrap width=\"15%\" height=51>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\" height=51><A class=menu><FONT \r\n      class=TitleLineBg>");

            // end
            // begin [file="/zserver/index.jsp";from=(56,27);to=(56,50)]
                out.print(PsConfig.get("COMPANY"));
            // end
            // HTML // begin [file="/zserver/index.jsp";from=(56,52);to=(88,0)]
                out.write("</FONT></A></TD></TR>\r\n  <TR>\r\n    <TD width=\"16%\" height=477>&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"84%\" height=477>\r\n      <P>Bienvenue sur la page d'Identification de Mercutio â Messenger 2002 Beta 1.</P>\r\n      <P>Veuillez saisir votre Identifiant et votre mot de passe.</P>\r\n      <P>&nbsp;</P>\r\n      <FORM name=InputInfo action=\"logon.jsp\" method=post>\r\n      <TABLE class=MTable cellSpacing=0 cellPadding=0 width=\"100%\" border=0>\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD height=25><FONT class=swb>Identification</FONT></TD></TR>\r\n        <TR>\r\n          <TD>\r\n            <TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0>\r\n              <TBODY>\r\n              <TR>\r\n                <TD class=TableInfoBackground width=225 height=25>Identifiant \r\n                <TD class=TableFieldBackground width=434 height=25><INPUT maxLength=30 size=30 name=LOGIN> </TD>\r\n              <TR>\r\n                <TD class=TableInfoBackground width=225 height=25>Mot de passe \r\n\r\n                <TD class=TableFieldBackground width=434 height=25><INPUT type=password maxLength=256 size=30 name=PASSWD> \r\n              </TD></TR></TBODY></TABLE></TD></TR></TBODY></TABLE>\r\n      <TABLE height=26 width=181>\r\n        <TBODY>\r\n        <TR>\r\n          <TD width=80><INPUT class=sbttn title=\"Clicker sur ce bouton pour vous signer\" tabIndex=1 type=submit value=Signer name=sign> \r\n          </TD>\r\n          <TD width=80><INPUT class=sbttn title=\"Clicker sur ce bouton pour effacer le contenu de la forme\" onclick=\"return resetForm();\" tabIndex=2 type=reset value=Effacer name=clear> \r\n          </TD></TR></TBODY></TABLE></FORM>\r\n      <P>&nbsp;</P></TD></TR></TBODY></TABLE></BODY></HTML>\r\n");

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
