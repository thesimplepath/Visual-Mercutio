package org.apache.jsp;

import ApimApp;
import ApimDbMgr;
import ApimDbConn;
import ApimDebug;
import ApimConfig;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class menu$jsp extends HttpJspBase {


    static {
    }
    public menu$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(2,80);to=(6,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../css/menu.css\" rel=\"styleSheet\" type=\"text/css\">\r\n");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(6,2);to=(8,0)]
                
                int idacc=1;//TODO get it from Session login
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(8,2);to=(38,0)]
                out.write("\r\n<script language=\"JavaScript\">\r\n\t\tvar oldChild = \"\";\r\n\t\tfunction outliner(doc,child)\r\n\t\t{\r\n\t\t\tif (oldChild != \"\")\r\n\t\t\t{\r\n\t\t\t\tif (document.all[oldChild].className != \"\")\r\n\t\t\t\t{\r\n\t\t\t\t\tdocument.all[oldChild].className = document.all[oldChild].className == \"collapsed\" ? \"expanded\" : \"collapsed\";\r\n\t\t\t\t}\r\n\t\t\t}\r\n\t\t\t\r\n\t\t\tif (child == null)\r\n\t\t\t{\r\n\t\t\t\tvar child = doc.srcElement.getAttribute(\"child\",false);\r\n\t\t\t}\r\n\t\t\t\r\n\t\t\tif (document.all[child].className != \"\")\r\n\t\t\t{\r\n\t\t\t\tdocument.all[child].className = document.all[child].className == \"collapsed\" ? \"expanded\" : \"collapsed\";\r\n\t\t\t\toldChild = child;\r\n\t\t\t}\r\n\t\t}\r\n</script>\r\n<script language=\"JavaScript\" src=\"../js/toolkit/tree.js\"></script>\r\n<script language=\"JavaScript\">\r\n\t\t\tvar tree = new Tree();\r\n\t\t\ttree.initTree();\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(38,2);to=(47,0)]
                
                	ApimApp.init();
                
                	ApimDbConn conn=ApimDbMgr.newConnection();
                	ResultSet rs;
                	rs=conn.sqlQueryR("SELECT a.idmenu, a.idparent, a.idchild, a.mname, a.mimage, a.mstyle, a.page, a.target, a.param FROM gsmenu a, catmenuconf b, catsecurity c, catuser d, catroles e, catperm f	WHERE d.idaccount = "+idacc+" and a.idmenu = b.idmenu	and a.idapplic = 5 and b.idcatperm = c.idcatperm and d.idcatroles = c.idcatroles and e.idcatroles = c.idcatroles and f.idcatperm = c.idcatperm	and c.status = 1 ORDER BY a.idmenu");
                
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(47,2);to=(48,27)]
                out.write("\r\n\t\t\ttree.addItem(tree.pRoot,");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,30);to=(48,49)]
                out.print(rs.getInt("idmenu"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,51);to=(48,52)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,55);to=(48,76)]
                out.print(rs.getInt("idparent"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,78);to=(48,79)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,82);to=(48,102)]
                out.print(rs.getInt("idchild"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,104);to=(48,107)]
                out.write(", \"");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,110);to=(48,131)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,133);to=(48,140)]
                out.write("\", \"../");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,143);to=(48,163)]
                out.print(rs.getString("page"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,165);to=(48,166)]
                out.write("?");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,169);to=(48,190)]
                out.print(rs.getString("param"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,192);to=(48,196)]
                out.write("\", \"");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(48,199);to=(48,221)]
                out.print(rs.getString("target"));
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(48,223);to=(49,0)]
                out.write("\");\r\n");

            // end
            // begin [file="/csr/ecatalog/menu.jsp";from=(49,2);to=(51,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/menu.jsp";from=(51,2);to=(313,0)]
                out.write("\r\n\r\nif (navigator.appName == \"Microsoft Internet Explorer\") \r\n\t{\t\t\r\n\tTree.prototype.viewTree = function viewTreeMenu(doc, pNode, level)\r\n\t{\r\n\t\tvar i = 0;\r\n\t\tvar strLevel = \"\";\r\n\t\t\r\n\t\tfor (i = 0;i < level;i++)\r\n\t\t{\r\n\t\t\tstrLevel += \"&nbsp;\";\r\n\t\t}\r\n\t\r\n\t\tif (pNode.pFirst != null)\r\n\t\t{\r\n\t\t\tif (level == 0)\r\n\t\t\t{\r\n\t\t\t\tdoc.writeln(\"<div style=\\\"background: #D6D6D6; cursor:hand; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/open.gif\\\" child=\\\"C\"+ pNode.idchild +\"\\\" onclick=\\\"top.menu.outliner(event)\\\"><b>&nbsp;<a href=\\\"javascript:top.menu.outliner(event,'C\"+ pNode.idchild +\"')\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t}\r\n\t\t\telse if (level == 4)\r\n\t\t\t{\r\n\t\t\t\tdoc.writeln(\"<div style=\\\"background: #E7E7E7; cursor:hand; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/open.gif\\\" child=\\\"C\"+ pNode.idchild +\"\\\" onclick=\\\"top.menu.outliner(event,null)\\\"><b>&nbsp;\"+ pNode.cname +\"</b></div>\\n\");\t\t\r\n\t\t\t}\r\n\t\t\telse\r\n\t\t\t{\r\n\t\t\t\tdoc.writeln(\"<div style=\\\"background: #F6F6F6; cursor:hand; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/open.gif\\\" child=\\\"C\"+ pNode.idchild +\"\\\" onclick=\\\"top.menu.outliner(event,null)\\\"><b>&nbsp;\"+ pNode.cname +\"</b></div>\\n\");\t\t\r\n\t\t\t}\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tif (pNode.pPrec == null && pNode.pNext == null)\r\n\t\t\t{\r\n\t\t\t\tif (level == 4)\r\n\t\t\t\t{\r\n\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #E7E7E7; width : 190px;\\\" id=\\\"C\"+ pNode.idcat +\"\\\" class=\\\"collapsed\\\" valign=\\\"top\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t{\r\n\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #F6F6F6; width : 190px;\\\" id=\\\"C\"+ pNode.idcat +\"\\\" class=\\\"collapsed\\\" valign=\\\"top\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t}\r\n\t\t\t}\r\n\t\t\telse\r\n\t\t\t{\r\n\t\t\t\tif (pNode.pNext != null && pNode.pPrec == null)\r\n\t\t\t\t{\r\n\t\t\t\t\tif (level == 4)\r\n\t\t\t\t\t{\r\n\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #E7E7E7; width : 190px;\\\" id=\\\"C\"+ pNode.idcat +\"\\\" class=\\\"collapsed\\\" valign=\\\"top\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b>\\n\");\r\n\t\t\t\t\t}\r\n\t\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #F6F6F6; width : 190px;\\\" id=\\\"C\"+ pNode.idcat +\"\\\" class=\\\"collapsed\\\" valign=\\\"top\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b>\\n\");\r\n\t\t\t\t\t}\r\n\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t{\r\n\t\t\t\t\tif (pNode.pNext != null)\r\n\t\t\t\t\t{\r\n\t\t\t\t\t\tif (level == 4)\r\n\t\t\t\t\t\t{\r\n\t\t\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #E7E7E7; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\" class=\\\"expanded\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t\t\t}\r\n\t\t\t\t\t\telse\r\n\t\t\t\t\t\t{\r\n\t\t\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #F6F6F6; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\" class=\\\"expanded\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t\t\t}\r\n\t\t\t\t\t}\r\n\t\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\t\tif (level == 4)\r\n\t\t\t\t\t\t{\r\n\t\t\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #E7E7E7; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\" class=\\\"expanded\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t\t\t}\r\n\t\t\t\t\t\telse\r\n\t\t\t\t\t\t{\r\n\t\t\t\t\t\t\tdoc.writeln(\"<div style=\\\"background: #F6F6F6; width : 190px;\\\" id=\\\"B\"+ pNode.idcat +\"\\\" class=\\\"expanded\\\">\"+ strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b>&nbsp;<a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\">\"+ pNode.cname +\"</a></b></div>\\n\");\r\n\t\t\t\t\t\t}\r\n\t\t\t\t\t}\r\n\t\t\t\t}\r\n\t\t\t}\r\n\t\t}\r\n\t\t\r\n\t\tif (pNode.pFirst != null)\r\n\t\t{\r\n\t\t\tthis.viewTree(doc, pNode.pFirst, level + 4);\r\n\t\t\tdoc.writeln(\"</div>\");\r\n\t\t}\r\n\t\r\n\t\tif (pNode.pNext != null)\r\n\t\t{\r\n\t\t\tthis.viewTree(doc, pNode.pNext, level);\r\n\t\t}\r\n\t}\r\n}\r\n\r\nif (navigator.appName == \"Netscape\") \r\n\t{\r\n\tTree.prototype.viewTree = function viewTreeEdit(doc, pNode, level) \r\n\t{ \r\n\t\tvar i = 0; \r\n\t\tvar strLevel = \"\"; \r\n\t\tfor (i = 0;i < level;i++) \r\n\t\t{ \r\n\t\t\tstrLevel += \"&nbsp;\"; \r\n\t\t} \r\n\t \r\n\t\tif (pNode.pFirst != null) \r\n\t\t{ \r\n\t\t\tdoc.writeln(strLevel +\"<img src=\\\"../img/ecatalog/button/open.gif\\\"><b><a href=\\\"#\\\" class=\\\"datas\\\">\"+ pNode.cname +\"</a></b><br>\");\r\n\t\t} \r\n\t\telse \r\n\t\t{ \r\n\t\t\tif (pNode.pPrec == null && pNode.pNext == null) \r\n\t\t\t{ \r\n\t\t\t\tdoc.writeln(strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b><a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\" class=\\\"datas\\\">\"+ pNode.cname +\"</a></b><br>\");\r\n\t\t\t} \r\n\t\t\telse \r\n\t\t\t{ \r\n\t\t\t\tif (pNode.pNext != null && pNode.pPrec == null) \r\n\t\t\t\t{ \r\n\t\t\t\t\tdoc.writeln(strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b><a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\" class=\\\"datas\\\">\"+ pNode.cname +\"</a></b><br>\");\r\n\t\t\t\t} \r\n\t\t\t\telse \r\n\t\t\t\t{ \r\n\t\t\t\t\tif (pNode.pNext != null) \r\n\t\t\t\t\t{ \r\n\t\t\t\t\t\tdoc.writeln(strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b><a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\" class=\\\"datas\\\">\"+ pNode.cname +\"</a></b><br>\");\r\n\t\t\t\t\t} \r\n\t\t\t\t\telse \r\n\t\t\t\t\t{ \r\n\t\t\t\t\t\t// end element \r\n\t\t\t\t\t\tdoc.writeln(strLevel +\"<img src=\\\"../img/ecatalog/button/closed.gif\\\"><b><a href=\\\"\"+ pNode.curl +\"\\\" target=\\\"\"+ pNode.target +\"\\\" class=\\\"datas\\\">\"+ pNode.cname +\"</a></b><br>\");\r\n\t\t\t\t\t} \r\n\t\t\t\t} \r\n\t\t\t} \r\n\t\t} \r\n\t\t \r\n\t\tif (pNode.pFirst != null) \r\n\t\t{ \r\n\t\t\tthis.viewTree(doc, pNode.pFirst, level + 2); \r\n\t\t} \r\n\t \r\n\t\tif (pNode.pNext != null) \r\n\t\t{ \r\n\t\t\tthis.viewTree(doc, pNode.pNext, level); \r\n\t\t} \r\n\t} \r\n}\r\n\r\n\tfunction searchArt()\r\n\t{\r\n\t\tvar sUrl = \"ecatalog/catalog/list.jsp&SKUIN=\"+ document.search.SKUIN.value;\r\n\t\tsUrl += \"&IDCATALOGUE=0\";\r\n\t\t\r\n\t\twindow.top.content.document.location\t= sUrl;\r\n\t}\r\n\t\r\n\tfunction changeStyle(event,mode)\r\n\t{\r\n\t\tif (mode == 1)\r\n\t\t{\r\n\t\t\tevent.srcElement.className = \"selectedInput\";\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tevent.srcElement.className = \"stdInput\";\r\n\t\t}\r\n\t}\r\n\t</script>\r\n\r\n<style>\r\n\t.datas { font-family: Arial; font-size: 9pt; color: black; text-decoration: none; font-weight: normal;}\r\n\t.datas:Hover { font-family: Arial; font-size: 9pt; color: black; text-decoration: underline; font-weight: normal; }\r\n\r\n\tA { font-family: Arial; font-size: 9pt; color: #205D91; text-decoration: none; }\r\n\t.:Hover { font-family: Arial; font-size: 9pt; color: red; text-decoration: none; font-weight: bold; }\r\n\t\r\n\t.expandable {color:blue; cursor:hand}\r\n\t.expanded {color:black;}\r\n\t.collapsed {display:none}\r\n\t\r\n\t.formview{display: yes;}\r\n\t.formhide{display: none;}\r\n\r\n\t.stdInput\r\n\t{ \r\n\t\tpadding-left:0px;\r\n\t\tpadding-right:0px;\r\n\t\tfont-size: 8pt; font-family: arial,helvetica,sans-serif;\r\n\t\tbackground-color: #F6F6F6; \r\n\t\tborder:1 solid #82807A; \r\n\t\theight: 15px;\r\n\t\tcolor: black;\r\n\t\tcursor: hand;\r\n\t\ttext-align: right;\r\n\t}\r\n\t\r\n\t.selectedInput\r\n\t{ \r\n\t\tpadding-left:0px;\r\n\t\tpadding-right:0px;\r\n\t\tfont-size: 8pt; font-family: arial,helvetica,sans-serif;\r\n\t\tbackground-color: #FFCC33; \r\n\t\tborder:1 solid #82807A; \r\n\t\theight: 15px;\r\n\t\tcolor: black;\r\n\t\tcursor: hand;\r\n\t\ttext-align: right;\r\n\t}\r\n</style>\r\n\r\n</head>\r\n\r\n<body bgcolor=\"#4D5C6D\" background=\"../img/ecatalog/menu_bkg.gif\" leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\" bottommargin=\"0\" rightmargin=\"0\">\r\n\r\n\r\n<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\r\n\t<tr>\r\n\t\t<td width=\"100%\" background=\"../img/ecatalog/top_mnu_bkg.gif\"></td>\r\n\t\t<td width=\"15\" align=\"right\">\r\n\t\t<div id=\"frm1\" class=\"formview\">\r\n\t\t\t<a href=\"Javascript:top.ViewForm(2);top.HideFrameNav();\" name=\"srcImg\"><img src=\"../img/ecatalog/bmnu_hide.gif\" border=\"0\"></a>\r\n\t\t</div>\r\n\t\t<div id=\"frm2\" class=\"formhide\">\r\n\t\t\t<a href=\"Javascript:top.ViewForm(1);top.GrowFrameNav();\" name=\"srcImg\"><img src=\"../img/ecatalog/bmnu_show.gif\" border=\"0\"></a>\r\n\t\t</div>\r\n\t\t</td>\r\n\t\t<td width=\"15\" align=\"left\">\r\n\t\t<div id=\"home\">\r\n\t\t\t<a href=\"../ecatalog/default.jsp\" target=\"_top\"><img src=\"../img/ecatalog/bmnu_home.gif\" border=\"0\"></a>\r\n\t\t</div>\r\n\t\t</td>\r\n\t\t<td width=\"40\">&nbsp;&nbsp;</td>\r\n\t</tr>\r\n</table>\r\n\r\n<table width=\"165\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\r\n<tr>\r\n\t<td width=\"15\"></td>\r\n\t<td>\r\n\t\t<script language=\"JavaScript\">\r\n\t\t\ttree.viewTree(top.menu.document, tree.pRoot.pFirst, 0);\t\r\n\t\t</script>\r\n\t</td>\r\n</tr>\r\n</table>\r\n<table width=\"190\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\r\n<tr><form name=\"search\">\r\n\t<td width=\"15\" class=\"corpslittle\" align=\"right\" height=\"15\">&nbsp;</td>\r\n\t<td class=\"corpslittle\" align=\"right\" valign=\"top\">\r\n\t\tSKU <input type=\"text\" name=\"SKUIN\" size=\"5\" maxlength=\"50\" value=\"\" title=\"Search Article by SKU\" class=\"stdInput\" onclick=\"changeStyle(event,1);\" onblur=\"changeStyle(event,2);\">\r\n\t</td>\r\n\t<td class=\"corpslittle\" align=\"right\" valign=\"bottom\" width=\"15\">\r\n\t\t<a href=\"javascript:searchArt()\"><img src=\"../img/ecatalog/button/s_go.gif\" border=\"0\"></a>\r\n\t</td>\r\n\t</form>\r\n</tr>\r\n</table>\r\n\r\n</body>\r\n</html>\r\n");

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
