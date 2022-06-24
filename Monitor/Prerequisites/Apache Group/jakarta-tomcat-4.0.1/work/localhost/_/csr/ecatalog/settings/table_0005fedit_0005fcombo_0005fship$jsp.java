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


public class table_0005fedit_0005fcombo_0005fship$jsp extends HttpJspBase {


    static {
    }
    public table_0005fedit_0005fcombo_0005fship$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(2,80);to=(9,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/style.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"javascript\" src=\"../../js/dbadmin.js\"></script>\r\n<script language=\"JavaScript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(9,2);to=(20,0)]
                
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
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(20,2);to=(23,0)]
                out.write("\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(23,2);to=(38,0)]
                
                 ApimApp.init();
                
                 int dbtype=9;//TODO read it from configuration
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as nbline from "+tablename);
                 rs.next();
                 int nbline=rs.getInt("nbline");
                
                 int nbresult=10;
                
                 rs=conn.sqlQueryR("SELECT b.idaccount,a.lname,a.fname,a.company from gaddress a, gaccount b, gmember c where a.idaccount = b.idaccount and b.idmember = c.idmember and c.idmember = 3 order by a.lname ");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(38,2);to=(46,2)]
                out.write("\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction ship(idaccount)\r\n\t\t{\r\n\t\t\tvar comboship = \"\";\r\n\t\t\tcomboship = \"<select name=\\\"IDPROVIDER\\\">\";\r\n\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(46,4);to=(49,3)]
                
                			while (rs.next())
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(49,5);to=(50,21)]
                out.write("\r\n\t\t\t\tif (idaccount == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(50,24);to=(50,49)]
                out.print(rs.getString("IDACCOUNT"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(50,51);to=(52,35)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcomboship += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,38);to=(52,63)]
                out.print(rs.getString("IDACCOUNT"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,65);to=(52,77)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,80);to=(52,101)]
                out.print(rs.getString("lname"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,103);to=(52,104)]
                out.write(" ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,107);to=(52,128)]
                out.print(rs.getString("fname"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,130);to=(52,132)]
                out.write(" (");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,135);to=(52,158)]
                out.print(rs.getString("company"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(52,160);to=(56,35)]
                out.write(")</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcomboship += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,38);to=(56,63)]
                out.print(rs.getString("IDACCOUNT"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,65);to=(56,68)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,71);to=(56,92)]
                out.print(rs.getString("lname"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,94);to=(56,95)]
                out.write(" ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,98);to=(56,119)]
                out.print(rs.getString("fname"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,121);to=(56,123)]
                out.write(" (");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,126);to=(56,149)]
                out.print(rs.getString("company"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(56,151);to=(58,3)]
                out.write(")</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(58,5);to=(60,3)]
                
                			}
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(60,5);to=(78,15)]
                out.write("\r\n\t\t\tcomboship += \"</select>\";\r\n\t\t\treturn comboship;\r\n\t\t}\r\n//-->\r\n</script>\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\nfunction savefrm()\r\n{\t\t\t\r\n\tdocument.addressfrm.submit();\r\n}\t\r\n\t\r\nvar oArray \t\t\t= new oFieldsArray();\r\n\t\t\r\nfunction genPages()\r\n{\r\n\tvar nbLine\t\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(78,18);to=(78,24)]
                out.print(nbline);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(78,26);to=(79,16)]
                out.write(";\r\n\tvar nbResult\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(79,19);to=(79,27)]
                out.print(nbresult);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(79,29);to=(82,69)]
                out.write(";\r\n\tvar nbPages\t\t= parseInt(nbLine / nbResult) + 1;\r\n\t\r\n\tvar sUrl = \"../../ecatalog/settings/table_edit_combo_ship.jsp?TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(82,72);to=(82,81)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(82,83);to=(146,0)]
                out.write("\";\r\n\t\r\n\tvar nbStart = -9;\r\n\tvar nbEnd\t= nbResult;\r\n\t\t\r\n\tfor(i=1; i <= nbPages; i++)\r\n\t{\r\n\t\tif (i == 1)\r\n\t\t{\r\n\t\t\tnbStart = 1;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnbStart = nbEnd;\r\n\t\t}\r\n\t\tnbEnd\t= i * nbResult;\r\n\t\tdocument.writeln(\"<a href=\\\"\"+ sUrl +\"&NBSTART=\"+ nbStart +\"&NBEND=\"+ nbEnd +\"\\\" class\\\"mmenu\\\">\"+ i +\"</a>\");\r\n\t}\r\n}\r\n\r\nfunction ReplaceQuote(theForm) \r\n\t{ \r\n\t\tvar ElemVal = \"\"; \r\n\t\tvar posn = 0; \r\n\t\tvar nstring = \"\"; \r\n\t\tvar c = \"\"; \r\n\t\tvar newval = \"\";\r\n\r\n\t\tfor (i = 0; i < document[theForm].length; i++) \r\n\t\t{ \r\n\r\n\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t{\r\n\t\t\tElemVal = document[theForm].elements[i].value; \r\n\t\t\tposn = document[theForm].elements[i].value.length; \r\n\t\t\t \r\n\t\t\tfor (var j=0; j < posn; j++) \r\n\t\t\t{ \r\n\t\t\t\tc = ElemVal.substring(j,j+1);\r\n\t\t\t\t\r\n\t\t\t\tif (c == \"'\") \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += \"`\"; \r\n\t\t\t\t} \r\n\t\t\t\telse \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += c; \r\n\t\t\t\t} \r\n\t\t\t}\r\n\t\t\t\r\n\t\t\tnewval = nstring;\r\n\t\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t\t{\r\n\t\t\t\tdocument[theForm].elements[i].value = newval; \r\n\t\t\t}\r\n\t\t\tnstring = \"\";\r\n\t\t}\r\n\t  }\r\n\t  return;  \r\n\t}\r\n\t\t\r\n//-->\r\n</script>\r\n<script language=\"javascript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(146,2);to=(150,1)]
                
                	rs=conn.sqlQueryR("SELECT a.fkey as fkey,a.idfield as idfield,c.fieldtype as fieldtype,b.typename as typename,a.name as name,a.minlength as minlength,a.maxlength as maxlength,a.publics as publics,a.acols as acols,a.arows as arows,a.required as required,a.allowed as allowed,a.freadonly as freadonly,a.fvisible as fvisible,a.fprecint as fprecint,a.fprecdec as fprecdec FROM gfields a, gviewtype b, gfieldtype c, gtables d WHERE a.idviewtype = b.idviewtype and a.idfieldtype = c.idfieldtype and a.idtable = d.idtable and d.name = '"+tablename+"' ORDER BY a.idfield");
                	while (rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(150,3);to=(151,19)]
                out.write("\r\n\t\toArray.AddFields(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,22);to=(151,42)]
                out.print(rs.getInt("idfield"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,44);to=(151,46)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,49);to=(151,58)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,60);to=(151,63)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,66);to=(151,91)]
                out.print(rs.getString("fieldtype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,93);to=(151,96)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,99);to=(151,123)]
                out.print(rs.getString("typename"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,125);to=(151,128)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,131);to=(151,151)]
                out.print(rs.getString("name"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,153);to=(151,155)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,158);to=(151,178)]
                out.print(rs.getString("fkey"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,180);to=(151,181)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,184);to=(151,190)]
                out.print(dbtype);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,192);to=(151,193)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,196);to=(151,221)]
                out.print(rs.getString("minlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,223);to=(151,224)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,227);to=(151,252)]
                out.print(rs.getString("maxlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,254);to=(151,255)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,258);to=(151,281)]
                out.print(rs.getString("publics"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,283);to=(151,284)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,287);to=(151,308)]
                out.print(rs.getString("acols"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,310);to=(151,311)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,314);to=(151,335)]
                out.print(rs.getString("arows"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,337);to=(151,339)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,342);to=(151,366)]
                out.print(rs.getString("required"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,368);to=(151,371)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,374);to=(151,397)]
                out.print(rs.getString("allowed"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,399);to=(151,401)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,404);to=(151,429)]
                out.print(rs.getString("freadonly"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,431);to=(151,432)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,435);to=(151,459)]
                out.print(rs.getString("fvisible"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,461);to=(151,462)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,465);to=(151,489)]
                out.print(rs.getString("fprecint"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,491);to=(151,492)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,495);to=(151,519)]
                out.print(rs.getString("fprecdec"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(151,521);to=(152,1)]
                out.write(");\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(152,3);to=(154,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(154,2);to=(169,18)]
                out.write("\r\n\t\r\n\tfunction sendUpdate(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=42\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&IDPROVIDER=\"+ document[frmName].IDPROVIDER.value;\r\n\t\tsUrl += \"&SERVICE=\"+ document[frmName].SERVICE.value;\r\n\t\tsUrl += \"&COSTWEIGHT=\"+ document[frmName].COSTWEIGHT.value;\r\n\t\tsUrl += \"&COSTVOL=\"+ document[frmName].COSTVOL.value;\r\n\t\tsUrl += \"&COSTITEM=\"+ document[frmName].COSTITEM.value;\r\n\t\tsUrl += \"&COSTBASE=\"+ document[frmName].COSTBASE.value;\r\n\t\tsUrl += \"&SHIPID=\"+ document[frmName].IDSHIP.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(169,21);to=(169,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(169,32);to=(181,19)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction sendDelete(frmName,id)\r\n\t{\r\n\t\tvar Hnd = confirm(\"Are you sure to delete this Element ?\");\r\n\t\tif (Hnd == true)\r\n\t\t{\r\n\t\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=43\";\r\n\t\t\tsUrl += \"&SHIPID=\"+ id;\r\n\t\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(181,22);to=(181,31)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(181,33);to=(200,18)]
                out.write("\";\r\n\t\t\r\n\t\t\tdocument.location = sUrl;\r\n\t\t}\r\n\t\treturn;\r\n\t}\r\n\t\r\n\tfunction sendInsert(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=41\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&IDPROVIDER=\"+ document[frmName].IDPROVIDER.value;\r\n\t\tsUrl += \"&SERVICE=\"+ document[frmName].SERVICE.value;\r\n\t\tsUrl += \"&COSTWEIGHT=\"+ document[frmName].COSTWEIGHT.value;\r\n\t\tsUrl += \"&COSTVOL=\"+ document[frmName].COSTVOL.value;\r\n\t\tsUrl += \"&COSTITEM=\"+ document[frmName].COSTITEM.value;\r\n\t\tsUrl += \"&COSTBASE=\"+ document[frmName].COSTBASE.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(200,21);to=(200,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(200,32);to=(229,0)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction formatNbr(nbre)\r\n\t{\r\n\t\tvar posn = nbre.indexOf(\".\",0);\r\n\t\tvar nstring = \"\";\r\n\t\r\n\t\tif (posn==0)\r\n\t\t{\r\n\t\t\tnstring = \"0\"+ nbre.substring(0,posn+3)\r\n\t\t}\r\n\t\telse if (posn>=0)\r\n\t\t{\r\n\t\t\tnstring = nbre.substring(0,posn+3)\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnstring = nbre + \"00\";\r\n\t\t}\r\n\t\treturn nstring;\r\n\t}\r\n</script>\r\n</head>\r\n\r\n<body bgcolor=\"#F6F6F6\" leftmargin=\"0\" rightmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(229,2);to=(232,1)]
                
                	if (msg!=null)
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(232,3);to=(233,46)]
                out.write("\r\n\t<b><font color=\"Red\" size=\"3\" class=\"notice\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(233,49);to=(233,52)]
                out.print(msg);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(233,54);to=(234,1)]
                out.write("</font></b>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(234,3);to=(236,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(236,2);to=(260,0)]
                out.write("\r\n\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>PROVIDER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>SERVICE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTWEIGHT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTVOL</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTITEM</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTBASE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUSER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCINDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUPDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"left\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(260,2);to=(269,3)]
                
                	rs=conn.sqlQueryR("SELECT idship,idprovider,service,costweight,costvol,costitem,costbase,syncuser,syncindate,syncupdate FROM gship ORDER BY service");
                	try 
                	{
                		int incr=1;
                		while (rs.next())
                		{
                			if ((nbstart!=null && incr>=Integer.valueOf(nbstart).intValue() && incr<Integer.valueOf(nbend).intValue())||(nbstart==null && incr<10))
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(269,5);to=(272,18)]
                out.write("\r\n\r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(272,21);to=(272,25)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(272,27);to=(273,32)]
                out.write("\" action=\"\" method=\"post\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(273,35);to=(273,44)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(273,46);to=(274,32)]
                out.write("\" name=\"TABLE\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(274,35);to=(274,57)]
                out.print(rs.getString("idship"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(274,59);to=(279,26)]
                out.write("\" name=\"IDSHIP\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(ship(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(279,29);to=(279,55)]
                out.print(rs.getString("idprovider"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(279,57);to=(283,107)]
                out.write("));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t  \t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SERVICE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(283,110);to=(283,133)]
                out.print(rs.getString("service"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(283,135);to=(285,154)]
                out.write("\" size=\"20\" maxlength=\"100\"></td>\r\n\t\t  <script language=\"JavaScript\">\r\n\t\t  \tdocument.writeln(\"<td bgcolor=\\\"#E2E8ED\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"COSTWEIGHT\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(285,157);to=(285,183)]
                out.print(rs.getString("costweight"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(285,185);to=(286,150)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"10\\\"></td>\");\r\n\t\t \tdocument.writeln(\"<td bgcolor=\\\"#E2E8ED\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"COSTVOL\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(286,153);to=(286,176)]
                out.print(rs.getString("costvol"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(286,178);to=(287,152)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"10\\\"></td>\");\r\n\t\t  \tdocument.writeln(\"<td bgcolor=\\\"#E2E8ED\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"COSTITEM\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(287,155);to=(287,179)]
                out.print(rs.getString("costitem"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(287,181);to=(288,152)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"10\\\"></td>\");\r\n\t\t  \tdocument.writeln(\"<td bgcolor=\\\"#E2E8ED\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"COSTBASE\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(288,155);to=(288,179)]
                out.print(rs.getString("costbase"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(288,181);to=(290,106)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"10\\\"></td>\");\r\n\t\t  </script>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUSER\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(290,109);to=(290,133)]
                out.print(rs.getString("syncuser"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(290,135);to=(291,108)]
                out.write("\" size=\"5\" maxlength=\"5\" style=\"background-color:#E2E8ED; align:center; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCINDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(291,111);to=(291,137)]
                out.print(rs.getString("syncindate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(291,139);to=(292,108)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUPDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(292,111);to=(292,137)]
                out.print(rs.getString("syncupdate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(292,139);to=(293,107)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td class=\"corps\" align=\"left\" width=\"20\"><input type=\"button\" value=\"Update\" onclick=\"sendUpdate('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(293,110);to=(293,114)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(293,116);to=(294,96)]
                out.write("');\"></td>\r\n\t\t  <td class=\"corps\" align=\"left\"><input type=\"button\" value=\"Delete\" onclick=\"sendDelete('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(294,99);to=(294,103)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(294,105);to=(294,107)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(294,110);to=(294,132)]
                out.print(rs.getString("idship"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(294,134);to=(297,1)]
                out.write(");\"></td>\r\n\t\t</form>\r\n\t  </tr>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(297,3);to=(306,0)]
                
                			}
                		incr++;
                		}
                	}
                	catch(SQLException e)
                	{
                		ApimDebug.fail("Exception:"+e.getMessage());
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ship.jsp";from=(306,2);to=(365,7)]
                out.write("\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n<br>\r\n<font size=\"3\" class=\"corps\">\r\nPages :&nbsp;\r\n<script language=\"JavaScript\">\r\n\tgenPages();\r\n</script>\r\n</font>\r\n\r\n<br>\r\n<br>\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>PROVIDER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>SERVICE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTWEIGHT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTVOL</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTITEM</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COSTBASE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\t\t<tr bgcolor=\"#CFD9E2\"> \r\n\t\t<form name=\"frmInsert\" action=\"\" method=\"post\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(ship(0));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\"><input type=\"text\" name=\"SERVICE\" value=\"\" size=\"25\" maxlength=\"100\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"COSTWEIGHT\" value=\"\" size=\"5\" maxlength=\"10\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"COSTVOL\" value=\"\" size=\"5\" maxlength=\"10\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"COSTITEM\" value=\"\" size=\"5\" maxlength=\"10\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"COSTBASE\" value=\"\" size=\"5\" maxlength=\"10\"></td>\r\n\t\t  <td class=\"corps\" width=\"20\" bgcolor=\"#E2E8ED\"><input type=\"button\" value=\"Insert\" onclick=\"sendInsert('frmInsert');\"></td> \r\n\t\t</form>\r\n\t  </tr>\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n\r\n</body>\r\n</html>");

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
