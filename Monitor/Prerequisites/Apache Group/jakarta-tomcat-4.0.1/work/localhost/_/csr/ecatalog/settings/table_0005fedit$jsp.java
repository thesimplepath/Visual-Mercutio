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


public class table_0005fedit$jsp extends HttpJspBase {


    static {
    }
    public table_0005fedit$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(2,80);to=(9,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/style.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"javascript\" src=\"../../js/dbadmin.js\"></script>\r\n<script language=\"JavaScript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(9,2);to=(20,0)]
                
                 String msg=	request.getParameter( "MSG" );
                 String tablename=	request.getParameter( "TABLE" );
                 String refresh=	request.getParameter( "REFRESH" );
                 String nbstart=        request.getParameter( "NBSTART" );
                 String nbend=        request.getParameter( "NBEND" );
                 if (refresh!=null && refresh.toUpperCase().equals("YES")==true)
                 {
                	String sUrl="../../ecatalog/settings/onglet.jsp?TABLENAME="+tablename;
                	out.println("top.onglet.document.location=\""+sUrl+"\";");
                 } 
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(20,2);to=(34,0)]
                out.write("\r\n\t\r\nfunction showCalendar(field)\r\n{\r\n\tvar\thwnd = null;\r\n\tsUrl = \"../../ecatalog/calendar.jsp?FIELD=\"+ field;\r\n\t\r\n\tif (hwnd != null) {\r\n\thwnd.close();\r\n\t}\r\n\thwnd = window.open(sUrl,\"\",\"resizable=yes,width=260,height=250\");\r\n}\t\t\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(34,2);to=(47,0)]
                
                 ApimApp.init();
                
                 int dbtype=9;//TODO read it from configuration
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as nbline from "+tablename);
                 rs.next();
                 int nbline=rs.getInt("nbline");
                
                 int nbresult=10;
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(47,2);to=(60,15)]
                out.write("\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\nfunction savefrm()\r\n{\t\t\t\r\n\tdocument.addressfrm.submit();\r\n}\t\r\n\t\r\nvar oArray \t\t\t= new oFieldsArray();\r\n\t\t\r\nfunction genPages()\r\n{\r\n\tvar nbLine\t\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(60,18);to=(60,24)]
                out.print(nbline);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(60,26);to=(61,16)]
                out.write(";\r\n\tvar nbResult\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(61,19);to=(61,27)]
                out.print(nbresult);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(61,29);to=(64,58)]
                out.write(";\r\n\tvar nbPages\t\t= parseInt(nbLine / nbResult) + 1;\r\n\t\r\n\tvar sUrl = \"../../ecatalog/settings/table_edit.jsp?TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(64,61);to=(64,70)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(64,72);to=(87,0)]
                out.write("\";\r\n\t\r\n\tvar nbStart = -9;\r\n\tvar nbEnd\t= nbResult;\r\n\t\t\r\n\tfor(i=1; i <= nbPages; i++)\r\n\t{\r\n\t\tif (i == 1)\r\n\t\t{\r\n\t\t\tnbStart = 1;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnbStart = nbEnd;\r\n\t\t}\r\n\t\tnbEnd\t= i * nbResult;\r\n\t\tdocument.writeln(\"<a href=\\\"\"+ sUrl +\"&NBSTART=\"+ nbStart +\"&NBEND=\"+ nbEnd +\"\\\" class\\\"mmenu\\\">\"+ i +\"</a>\");\r\n\t}\r\n}\r\n\t\t\r\n//-->\r\n</script>\r\n<script language=\"javascript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(87,2);to=(92,1)]
                	
                	rs=conn.sqlQueryR("SELECT a.fkey as fkey,a.idfield as idfield,c.fieldtype as fieldtype,b.typename as typename,a.name as name,a.minlength as minlength,a.maxlength as maxlength,a.publics as publics,a.acols as acols,a.arows as arows,a.required as required,a.allowed as allowed,a.freadonly as freadonly,a.fvisible as fvisible,a.fprecint as fprecint,a.fprecdec as fprecdec FROM gfields a, gviewtype b, gfieldtype c, gtables d WHERE a.idviewtype = b.idviewtype and a.idfieldtype = c.idfieldtype and a.idtable = d.idtable and d.name = '"+tablename+"' ORDER BY a.idfield");
                	while (rs.next())
                	{
                
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(92,3);to=(94,19)]
                out.write("\r\n\r\n\t\toArray.AddFields(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,22);to=(94,42)]
                out.print(rs.getInt("idfield"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,44);to=(94,46)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,49);to=(94,58)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,60);to=(94,63)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,66);to=(94,91)]
                out.print(rs.getString("fieldtype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,93);to=(94,96)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,99);to=(94,123)]
                out.print(rs.getString("typename"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,125);to=(94,128)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,131);to=(94,151)]
                out.print(rs.getString("name"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,153);to=(94,155)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,158);to=(94,178)]
                out.print(rs.getString("fkey"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,180);to=(94,181)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,184);to=(94,190)]
                out.print(dbtype);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,192);to=(94,193)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,196);to=(94,221)]
                out.print(rs.getString("minlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,223);to=(94,224)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,227);to=(94,252)]
                out.print(rs.getString("maxlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,254);to=(94,255)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,258);to=(94,281)]
                out.print(rs.getString("publics"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,283);to=(94,284)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,287);to=(94,308)]
                out.print(rs.getString("acols"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,310);to=(94,311)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,314);to=(94,335)]
                out.print(rs.getString("arows"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,337);to=(94,339)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,342);to=(94,366)]
                out.print(rs.getString("required"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,368);to=(94,371)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,374);to=(94,397)]
                out.print(rs.getString("allowed"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,399);to=(94,401)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,404);to=(94,429)]
                out.print(rs.getString("freadonly"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,431);to=(94,432)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,435);to=(94,459)]
                out.print(rs.getString("fvisible"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,461);to=(94,462)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,465);to=(94,489)]
                out.print(rs.getString("fprecint"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,491);to=(94,492)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,495);to=(94,519)]
                out.print(rs.getString("fprecdec"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(94,521);to=(95,1)]
                out.write(");\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(95,3);to=(97,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(97,2);to=(103,0)]
                out.write("\r\n</script>\r\n</head>\r\n\r\n<body bgcolor=\"#F6F6F6\" leftmargin=\"0\" rightmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(103,2);to=(106,1)]
                
                	if (msg!=null)
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(106,3);to=(107,46)]
                out.write("\r\n\t<b><font color=\"Red\" size=\"3\" class=\"notice\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(107,49);to=(107,52)]
                out.print(msg);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(107,54);to=(108,1)]
                out.write("</font></b>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(108,3);to=(110,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(110,2);to=(127,0)]
                out.write("\r\n\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 cellspacing=1 cellpadding=2> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <script language=\"javascript\">\r\n\t\t  \tdocument.writeln(oArray.GenTop());\r\n\t\t  </script>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"left\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n\r\n<!-- start content row --> \r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(127,2);to=(137,3)]
                
                	rs=conn.sqlQueryR("SELECT * FROM "+tablename);
                	try 
                	{
                		int incr=1;
                
                		while (rs.next())
                		{
                			if ((nbstart!=null && incr>=Integer.valueOf(nbstart).intValue() && incr<Integer.valueOf(nbend).intValue())||(nbstart==null && incr<10))
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(137,5);to=(139,18)]
                out.write("\r\n\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(139,21);to=(139,25)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(139,27);to=(140,32)]
                out.write("\" action=\"../../ecatalog/settings/action.jsp&ACTION=2\" method=\"post\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(140,35);to=(140,44)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(140,46);to=(141,32)]
                out.write("\" name=\"TABLE\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(141,35);to=(141,50)]
                out.print(rs.getString(1));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(141,52);to=(145,2)]
                out.write("\" name=\"ID\">\r\n\t\t  <input type=\"Hidden\" value=\"\" name=\"QUERY\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <script language=\"javascript\">\r\n\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(145,4);to=(153,2)]
                		
                			ResultSetMetaData md=rs.getMetaData();
                
                			int cols=md.getColumnCount();
                			for (int i=1;i<=cols;i++)
                			{
                			String colname=md.getColumnName(i);
                
                		
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(153,4);to=(154,37)]
                out.write("\r\n\t\t\tdocument.writeln(oArray.GenField('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(154,40);to=(154,47)]
                out.print(colname);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(154,49);to=(154,52)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(154,55);to=(154,70)]
                out.print(rs.getString(i));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(154,72);to=(155,2)]
                out.write("'));\t\r\n\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(155,4);to=(157,2)]
                	
                			}
                		
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(157,4);to=(165,3)]
                out.write("\r\n\t  \t </script>\r\n\t\t  <td class=\"corps\" align=\"left\" width=\"20\"><input type=\"button\" value=\"Update\" onclick=\"oArray.GenQuery(document.FORM[[[INCR]]],'[[[TABLE]]]',0,'null');\"></td>\r\n\t\t</form>\r\n\t\t<form>\r\n\t\t  <td class=\"corps\" align=\"left\"><input type=\"button\" value=\"Delete\" onclick=\"oArray.GenQueryDel(document.FORM[[[INCR]]],'[[[TABLE]]]');\"></td>\r\n\t\t</form>\r\n\t  </tr>\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(165,5);to=(175,0)]
                
                			}
                			incr++;
                		}
                	}
                	catch(SQLException e)
                	{
                		ApimDebug.fail("Exception:"+e.getMessage());
                	}
                
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(175,2);to=(208,30)]
                out.write("\r\n\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n<br>\r\n<font size=\"3\" class=\"corps\">\r\nPages :&nbsp;\r\n<script language=\"JavaScript\">\r\n\tgenPages();\r\n</script>\r\n</font>\r\n<br>\r\n<br>\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr>\r\n <td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t<td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t<script language=\"javascript\">\r\n\t\tdocument.writeln(oArray.GenInsertTop());\r\n\t\t</script>\r\n\t\t<td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t </tr> \r\n         <!-- start content row --> \r\n\t <tr bgcolor=\"#E2E8ED\"> \r\n\t <form name=\"frm\" action=\"../../ecatalog/settings/action.jsp&ACTION=10\" method=\"post\">\r\n\t <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(208,33);to=(208,42)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(208,44);to=(215,113)]
                out.write("\" name=\"TABLE\">\r\n\t <input type=\"Hidden\" value=\"\" name=\"QUERY\">\r\n\t <input type=\"Hidden\" value=\"\" name=\"QUERYEND\">\r\n\t\t <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t <script language=\"javascript\">\r\n\t\t document.writeln(oArray.GenInsertField());\r\n\t\t </script>\r\n\t\t <td class=\"corps\" width=\"20\"><input type=\"button\" value=\"Insert\" onclick=\"oArray.GenQueryInsert(document.frm,'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(215,116);to=(215,125)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit.jsp";from=(215,127);to=(226,7)]
                out.write("',0,'null');\"></td> \r\n\t  </form>\r\n\t  </tr>\r\n   </table>\r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n\r\n</body>\r\n</html>");

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
