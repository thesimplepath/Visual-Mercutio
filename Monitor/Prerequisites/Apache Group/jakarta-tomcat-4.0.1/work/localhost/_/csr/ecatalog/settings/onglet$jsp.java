package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class onglet$jsp extends HttpJspBase {


    static {
    }
    public onglet$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(1,26);to=(23,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/menu.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"JavaScript\">\r\nfunction ChangeImg(destination)\r\n{\r\n\tif(!document.all)\r\n\t{\r\n    \treturn\r\n\t}\r\n\t\tfor (i=1; i <= 8; i++)\r\n\t\t{\r\n\t\t\tdocument.all[\"b\"+ i].background = \"../../img/ecatalog/onglet_hide.gif\";\r\n\t\t}\r\n\t\tdocument.all[\"b\"+ destination].background = \"../../img/ecatalog/onglet_show.gif\";\r\n}\r\n</script>\r\n\r\n</head>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(23,2);to=(25,0)]
                
                 String tablename=	request.getParameter( "TABLENAME" );
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(25,2);to=(31,37)]
                out.write("\r\n\r\n<body background=\"../../img/ecatalog/onglet_bkg.gif\" leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\" background=\"../../img/ong_bkg.gif\">\r\n\t<tr>\r\n\t\t<td id=\"b7\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(31,39);to=(31,189)]
                if (tablename.equals("gcatalogue")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(31,191);to=(32,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit.jsp?TABLE=gcatalogue\" onclick=\"ChangeImg(7);\" target=\"content\">Catalogue</a></td>\r\n\t\t<td id=\"b1\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(32,39);to=(32,183)]
                if (tablename.equals("gccy")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(32,185);to=(33,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit_combo_ccy.jsp?TABLE=gccy\" onclick=\"ChangeImg(1);\" target=\"content\">Currency</a></td>\r\n\t\t<td id=\"b2\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(33,39);to=(33,187)]
                if (tablename.equals("gcountry")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(33,189);to=(34,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit.jsp?TABLE=gcountry\" onclick=\"ChangeImg(2);\" target=\"content\">Country</a></td>\r\n\t\t<td id=\"b3\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(34,39);to=(34,185)]
                if (tablename.equals("gstate")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(34,187);to=(35,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit_combo_state.jsp?TABLE=gstate\" onclick=\"ChangeImg(3);\" target=\"content\">State</a></td>\r\n\t\t<td id=\"b4\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(35,39);to=(35,184)]
                if (tablename.equals("gship")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(35,186);to=(36,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit_combo_ship.jsp?TABLE=gship\" onclick=\"ChangeImg(4);\" target=\"content\">Shipping</a></td>\r\n\t\t<td id=\"b5\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(36,39);to=(36,183)]
                if (tablename.equals("gvat")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(36,185);to=(37,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit_combo_gvat.jsp?TABLE=gvat\" onclick=\"ChangeImg(5);\" target=\"content\">Taxes</a></td>\r\n\t\t<td id=\"b6\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(37,39);to=(37,187)]
                if (tablename.equals("gvattype")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(37,189);to=(38,37)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit.jsp?TABLE=gvattype\" onclick=\"ChangeImg(6);\" target=\"content\">Vat Type</a></td>\r\n\t\t<td id=\"b8\" width=\"96\" background=\"");

            // end
            // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(38,39);to=(38,189)]
                if (tablename.equals("gwarehouse")==true) {out.println("../../img/ecatalog/onglet_show.gif");}else{out.println("../../img/ecatalog/onglet_hide.gif");}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/onglet.jsp";from=(38,191);to=(43,7)]
                out.write("\" valign=\"middle\" align=\"center\" nowrap><a class=\"monglet\" href=\"../../ecatalog/settings/table_edit.jsp?TABLE=gwarehouse\" onclick=\"ChangeImg(8);\" target=\"content\">Warehouse</a></td>\r\n\t\t<td width=\"100%\">&nbsp;</td>\r\n\t</tr>\r\n</table>\r\n</body>\r\n</html>");

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
