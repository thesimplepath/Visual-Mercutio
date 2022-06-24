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


public class table_0005fedit_0005fcombo_0005fgvat$jsp extends HttpJspBase {


    static {
    }
    public table_0005fedit_0005fcombo_0005fgvat$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(2,80);to=(9,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/style.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"javascript\" src=\"../../js/dbadmin.js\"></script>\r\n<script language=\"JavaScript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(9,2);to=(20,0)]
                
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
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(20,2);to=(23,0)]
                out.write("\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(23,2);to=(38,0)]
                
                 ApimApp.init();
                
                 int dbtype=9;//TODO read it from configuration
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as nbline from "+tablename);
                 rs.next();
                 int nbline=rs.getInt("nbline");
                
                 int nbresult=10;
                
                 rs=conn.sqlQueryR("SELECT country,idcountry from gcountry order by country");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(38,2);to=(46,0)]
                out.write("\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction country(idcountry)\r\n\t\t{\r\n\t\t\tvar combocountry = \"\";\r\n\t\t\tcombocountry = \"<select name=\\\"IDCOUNTRY\\\">\";\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(46,2);to=(49,1)]
                
                	while(rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(49,3);to=(50,21)]
                out.write("\r\n\t\t\t\tif (idcountry == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(50,24);to=(50,46)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(50,48);to=(52,38)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(52,41);to=(52,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(52,65);to=(52,77)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(52,80);to=(52,103)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(52,105);to=(56,38)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(56,41);to=(56,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(56,65);to=(56,68)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(56,71);to=(56,94)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(56,96);to=(58,1)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(58,3);to=(60,1)]
                
                	}
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(60,3);to=(67,0)]
                out.write("\r\n\t\t\tcombocountry += \"</select>\";\r\n\t\t\treturn combocountry;\r\n\t\t}\r\n//-->\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(67,2);to=(69,0)]
                
                 rs=conn.sqlQueryR("SELECT distinct text, idstate FROM Gstate order by idstate");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(69,2);to=(76,3)]
                out.write("\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction state(idstate)\r\n\t\t{\r\n\t\t\tvar combostate = \"\";\r\n\t\t\tcombostate = \"<select name=\\\"IDSTATE\\\">\";\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(76,5);to=(79,3)]
                
                			while (rs.next())
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(79,5);to=(80,19)]
                out.write("\r\n\t\t\t\tif (idstate == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(80,22);to=(80,45)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(80,47);to=(82,36)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombostate += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(82,39);to=(82,62)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(82,64);to=(82,76)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(82,79);to=(82,99)]
                out.print(rs.getString("text"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(82,101);to=(86,36)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombostate += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(86,39);to=(86,62)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(86,64);to=(86,67)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(86,70);to=(86,90)]
                out.print(rs.getString("text"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(86,92);to=(88,3)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(88,5);to=(90,3)]
                
                			}
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(90,5);to=(97,0)]
                out.write("\r\n\t\t\tcombostate += \"</select>\";\r\n\t\t\treturn combostate;\r\n\t\t}\r\n//-->\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(97,2);to=(99,0)]
                
                 rs=conn.sqlQueryR("SELECT idvattype, descr FROM Gvattype ORDER BY descr");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(99,2);to=(107,3)]
                out.write("\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction vattype(idvattype)\r\n\t\t{\r\n\t\t\tvar combovattype = \"\";\r\n\t\t\tcombovattype = \"<select name=\\\"IDVATTYPE\\\">\";\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(107,5);to=(110,3)]
                
                			while (rs.next())
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(110,5);to=(111,21)]
                out.write("\r\n\t\t\t\tif (idvattype == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(111,24);to=(111,49)]
                out.print(rs.getString("idvattype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(111,51);to=(113,38)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombovattype += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(113,41);to=(113,66)]
                out.print(rs.getString("idvattype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(113,68);to=(113,80)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(113,83);to=(113,104)]
                out.print(rs.getString("descr"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(113,106);to=(117,38)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombovattype += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(117,41);to=(117,66)]
                out.print(rs.getString("idvattype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(117,68);to=(117,71)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(117,74);to=(117,95)]
                out.print(rs.getString("descr"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(117,97);to=(119,3)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(119,5);to=(121,3)]
                
                			}
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(121,5);to=(201,15)]
                out.write("\r\n\t\t\tcombovattype += \"</select>\";\r\n\t\t\treturn combovattype;\r\n\t\t}\r\n\r\nfunction formatNbr(nbre)\r\n{\r\n\tvar posn = nbre.indexOf(\".\",0);\r\n\tvar nstring = \"\";\r\n\r\n\tif (posn==0)\r\n\t{\r\n\t\tnstring = \"0\"+ nbre.substring(0,posn+3)\r\n\t}\r\n\telse if (posn>=0)\r\n\t{\r\n\t\tnstring = nbre.substring(0,posn+3)\r\n\t}\r\n\telse\r\n\t{\r\n\t\tnstring = nbre + \"00\";\r\n\t}\r\n\treturn nstring;\r\n}\r\n\r\nfunction ReplaceQuote(theForm) \r\n\t{ \r\n\t\tvar ElemVal = \"\"; \r\n\t\tvar posn = 0; \r\n\t\tvar nstring = \"\"; \r\n\t\tvar c = \"\"; \r\n\t\tvar newval = \"\";\r\n\r\n\t\tfor (i = 0; i < document[theForm].length; i++) \r\n\t\t{ \r\n\r\n\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t{\r\n\t\t\tElemVal = document[theForm].elements[i].value; \r\n\t\t\tposn = document[theForm].elements[i].value.length; \r\n\t\t\t \r\n\t\t\tfor (var j=0; j < posn; j++) \r\n\t\t\t{ \r\n\t\t\t\tc = ElemVal.substring(j,j+1);\r\n\t\t\t\t\r\n\t\t\t\tif (c == \"'\") \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += \"`\"; \r\n\t\t\t\t} \r\n\t\t\t\telse \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += c; \r\n\t\t\t\t} \r\n\t\t\t}\r\n\t\t\t\r\n\t\t\tnewval = nstring;\r\n\t\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t\t{\r\n\t\t\t\tdocument[theForm].elements[i].value = newval; \r\n\t\t\t}\r\n\t\t\tnstring = \"\";\r\n\t\t}\r\n\t  }\r\n\t  return;  \r\n\t}\r\n//-->\r\n</script>\r\n\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\nfunction savefrm()\r\n{\t\t\t\r\n\tdocument.addressfrm.submit();\r\n}\t\r\n\t\r\nvar oArray \t\t\t= new oFieldsArray();\r\n\t\t\r\nfunction genPages()\r\n{\r\n\tvar nbLine\t\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(201,18);to=(201,24)]
                out.print(nbline);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(201,26);to=(202,16)]
                out.write(";\r\n\tvar nbResult\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(202,19);to=(202,27)]
                out.print(nbresult);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(202,29);to=(205,69)]
                out.write(";\r\n\tvar nbPages\t\t= parseInt(nbLine / nbResult) + 1;\r\n\t\r\n\tvar sUrl = \"../../ecatalog/settings/table_edit_combo_gvat.jsp?TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(205,72);to=(205,81)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(205,83);to=(228,0)]
                out.write("\";\r\n\t\r\n\tvar nbStart = -9;\r\n\tvar nbEnd\t= nbResult;\r\n\t\t\r\n\tfor(i=1; i <= nbPages; i++)\r\n\t{\r\n\t\tif (i == 1)\r\n\t\t{\r\n\t\t\tnbStart = 1;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnbStart = nbEnd;\r\n\t\t}\r\n\t\tnbEnd\t= i * nbResult;\r\n\t\tdocument.writeln(\"<a href=\\\"\"+ sUrl +\"&NBSTART=\"+ nbStart +\"&NBEND=\"+ nbEnd +\"\\\" class\\\"mmenu\\\">\"+ i +\"</a>\");\r\n\t}\r\n}\r\n\t\t\r\n//-->\r\n</script>\r\n<script language=\"javascript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(228,2);to=(232,1)]
                
                	rs=conn.sqlQueryR("SELECT a.fkey as fkey,a.idfield as idfield,c.fieldtype as fieldtype,b.typename as typename,a.name as name,a.minlength as minlength,a.maxlength as maxlength,a.publics as publics,a.acols as acols,a.arows as arows,a.required as required,a.allowed as allowed,a.freadonly as freadonly,a.fvisible as fvisible,a.fprecint as fprecint,a.fprecdec as fprecdec FROM gfields a, gviewtype b, gfieldtype c, gtables d WHERE a.idviewtype = b.idviewtype and a.idfieldtype = c.idfieldtype and a.idtable = d.idtable and d.name = '"+tablename+"' ORDER BY a.idfield");
                	while (rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(232,3);to=(233,19)]
                out.write("\r\n\t\toArray.AddFields(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,22);to=(233,42)]
                out.print(rs.getInt("idfield"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,44);to=(233,46)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,49);to=(233,58)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,60);to=(233,63)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,66);to=(233,91)]
                out.print(rs.getString("fieldtype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,93);to=(233,96)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,99);to=(233,123)]
                out.print(rs.getString("typename"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,125);to=(233,128)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,131);to=(233,151)]
                out.print(rs.getString("name"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,153);to=(233,155)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,158);to=(233,178)]
                out.print(rs.getString("fkey"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,180);to=(233,181)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,184);to=(233,190)]
                out.print(dbtype);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,192);to=(233,193)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,196);to=(233,221)]
                out.print(rs.getString("minlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,223);to=(233,224)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,227);to=(233,252)]
                out.print(rs.getString("maxlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,254);to=(233,255)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,258);to=(233,281)]
                out.print(rs.getString("publics"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,283);to=(233,284)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,287);to=(233,308)]
                out.print(rs.getString("acols"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,310);to=(233,311)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,314);to=(233,335)]
                out.print(rs.getString("arows"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,337);to=(233,339)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,342);to=(233,366)]
                out.print(rs.getString("required"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,368);to=(233,371)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,374);to=(233,397)]
                out.print(rs.getString("allowed"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,399);to=(233,401)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,404);to=(233,429)]
                out.print(rs.getString("freadonly"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,431);to=(233,432)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,435);to=(233,459)]
                out.print(rs.getString("fvisible"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,461);to=(233,462)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,465);to=(233,489)]
                out.print(rs.getString("fprecint"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,491);to=(233,492)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,495);to=(233,519)]
                out.print(rs.getString("fprecdec"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(233,521);to=(234,1)]
                out.write(");\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(234,3);to=(236,1)]
                
                	}
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(236,3);to=(249,18)]
                out.write("\r\n\t\r\n\tfunction sendUpdate(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=22\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&VATID=\"+ document[frmName].IDVAT.value;\r\n\t\tsUrl += \"&COUNTRYID=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&STATEID=\"+ document[frmName].IDSTATE.value;\r\n\t\tsUrl += \"&VATTYPEID=\"+ document[frmName].IDVATTYPE.value;\r\n\t\tsUrl += \"&VAT=\"+ document[frmName].VAT.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(249,21);to=(249,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(249,32);to=(261,19)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction sendDelete(frmName,id)\r\n\t{\r\n\t\tvar Hnd = confirm(\"Are you sure to delete this Element ?\");\r\n\t\tif (Hnd == true)\r\n\t\t{\r\n\t\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=23\";\r\n\t\t\tsUrl += \"&VATID=\"+ document[frmName].IDVAT.value;\r\n\t\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(261,22);to=(261,31)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(261,33);to=(278,18)]
                out.write("\";\r\n\t\t\r\n\t\t\tdocument.location = sUrl;\r\n\t\t}\r\n\t\treturn;\r\n\t}\r\n\t\r\n\tfunction sendInsert(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=21\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&COUNTRYID=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&STATEID=\"+ document[frmName].IDSTATE.value;\r\n\t\tsUrl += \"&VATTYPEID=\"+ document[frmName].IDVATTYPE.value;\r\n\t\tsUrl += \"&VAT=\"+ document[frmName].VAT.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(278,21);to=(278,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(278,32);to=(288,0)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n</script>\r\n</head>\r\n\r\n<body bgcolor=\"#F6F6F6\" leftmargin=\"0\" rightmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(288,2);to=(291,1)]
                
                	if (msg!=null)
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(291,3);to=(292,46)]
                out.write("\r\n\t<b><font color=\"Red\" size=\"3\" class=\"notice\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(292,49);to=(292,52)]
                out.print(msg);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(292,54);to=(293,1)]
                out.write("</font></b>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(293,3);to=(295,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(295,2);to=(316,0)]
                out.write("\r\n\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>STATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>TYPE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>VAT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUSER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCINDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUPDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"left\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(316,2);to=(325,3)]
                
                	rs=conn.sqlQueryR("SELECT idvat,idcountry,idstate,vat,syncuser,syncindate,syncupdate FROM gvat ORDER BY vat");
                	try 
                	{
                		int incr=1;
                		while (rs.next())
                		{
                			if ((nbstart!=null && incr>=Integer.valueOf(nbstart).intValue() && incr<Integer.valueOf(nbend).intValue())||(nbstart==null && incr<10))
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(325,5);to=(327,18)]
                out.write("\r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(327,21);to=(327,25)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(327,27);to=(328,32)]
                out.write("\" action=\"\" method=\"post\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(328,35);to=(328,44)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(328,46);to=(329,32)]
                out.write("\" name=\"TABLE\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(329,35);to=(329,56)]
                out.print(rs.getString("idvat"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(329,58);to=(334,29)]
                out.write("\" name=\"IDVAT\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(country(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(334,32);to=(334,57)]
                out.print(rs.getString("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(334,59);to=(341,27)]
                out.write("));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(state(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(341,30);to=(341,53)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(341,55);to=(348,29)]
                out.write("));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(vattype(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(348,32);to=(348,57)]
                out.print(rs.getString("idvattype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(348,59);to=(353,145)]
                out.write("));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <script language=\"JavaScript\">\r\n\t\t\tdocument.writeln(\"<td bgcolor=\\\"#E2E8ED\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"VAT\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(353,148);to=(353,167)]
                out.print(rs.getString("vat"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(353,169);to=(356,106)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"5\\\"></td>\");  \r\n\t\t  </script>\r\n\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUSER\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(356,109);to=(356,133)]
                out.print(rs.getString("syncuser"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(356,135);to=(357,108)]
                out.write("\" size=\"5\" maxlength=\"5\" style=\"background-color:#E2E8ED; align:center; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCINDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(357,111);to=(357,137)]
                out.print(rs.getString("syncindate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(357,139);to=(358,108)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUPDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(358,111);to=(358,137)]
                out.print(rs.getString("syncupdate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(358,139);to=(359,125)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\"><input type=\"button\" value=\"Update\" onclick=\"sendUpdate('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(359,128);to=(359,132)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(359,134);to=(360,114)]
                out.write("');\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\"><input type=\"button\" value=\"Delete\" onclick=\"sendDelete('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(360,117);to=(360,121)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(360,123);to=(360,125)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(360,128);to=(360,149)]
                out.print(rs.getString("idvat"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(360,151);to=(363,3)]
                out.write(");\"></td>\r\n\t\t</form>\r\n\t  </tr>\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(363,5);to=(374,1)]
                
                			}
                		incr++;
                		}
                	}
                	catch(SQLException e)
                	{
                		ApimDebug.fail("Exception:"+e.getMessage());
                	}
                
                
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_gvat.jsp";from=(374,3);to=(441,7)]
                out.write("\t\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n<br>\r\n<font size=\"3\" class=\"corps\">\r\nPages :&nbsp;\r\n<script language=\"JavaScript\">\r\n\tgenPages();\r\n</script>\r\n</font>\r\n\r\n<br>\r\n<br>\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>STATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>TYPE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>VAT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"frmInsert\" action=\"\" method=\"post\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(country(-1));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(state(-1));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(vattype(-1));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t  \t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"VAT\" value=\"\" size=\"5\" maxlength=\"5\"></td>\r\n\t\t  <td class=\"corps\" width=\"20\"><input type=\"button\" value=\"Insert\" onclick=\"sendInsert('frmInsert');\"></td> \r\n\t\t</form>\r\n\t  </tr>\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n\r\n</body>\r\n</html>");

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
