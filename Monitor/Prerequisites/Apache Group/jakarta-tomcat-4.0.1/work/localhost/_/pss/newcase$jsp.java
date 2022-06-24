package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsWorkGroup;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class newcase$jsp extends HttpJspBase {


    static {
    }
    public newcase$jsp( ) {
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

            // HTML // begin [file="/pss/newcase.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(8,32);to=(16,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/pss/newcase.jsp";from=(16,2);to=(24,0)]
                
                //session check
                 String xusername=(String)session.getAttribute( "USERNAME");
                 int    userrole;
                 if (xusername==null) 
                   out.println("alert('Not logged');");
                 else
                   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(24,2);to=(40,0)]
                out.write("\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n<form name=FRM onsubmit=\"doSubmit();\">\r\n<input type=hidden name=QTY value=0>\r\n<input type=submit>\r\n<table name=TBL>\r\n<tr>\r\n<td>\r\nProcédure:\r\n</td>\r\n<td>\r\n<select name=\"CASE\">\r\n");

            // end
            // begin [file="/pss/newcase.jsp";from=(40,2);to=(64,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	PsWorkGroup w=new PsWorkGroup();
                 	Vector r=w.listProcStartGranted(username);
                 	int l=r.size();
                 	for (int i=0;i<l;i++)
                 	{
                		int proc=((Integer)r.elementAt(i)).intValue();
                		rs=conn.sqlQueryR("select * from pproc,pmodel where pproc.proctype=0 and pproc.procid="+proc+" and pproc.modelid=pmodel.modelid order by modelname");
                		rs.next();
                		out.println("<option value=\""+proc+"\">"+rs.getString("modelname")+". #proc:"+proc+"</option>");
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(64,2);to=(86,36)]
                out.write("\r\n</select>\r\n</td>\r\n<td></td>\r\n</tr>\r\n\r\n<tr>\r\n<td>\r\nCase name:\r\n</td>\r\n<td>\r\n<input type=text name=CASENAME>\r\n</td>\r\n<td></td>\r\n</tr>\r\n\r\n\r\n<tr>\r\n<td>\r\nTrans id:\r\n</td>\r\n<td>\r\n<input type=text name=TRANSID value=");

            // end
            // begin [file="/pss/newcase.jsp";from=(86,39);to=(86,80)]
                out.print(PsDbMgr.newConnection().nextVal("PTRANS"));
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(86,82);to=(105,35)]
                out.write(">\r\n</td>\r\n<td></td>\r\n</tr>\r\n<tr>\r\n<td>\r\nTrans name:\r\n</td>\r\n<td>\r\n<input type=text name=TRANSNAME value=\"\">\r\n</td>\r\n<td></td>\r\n</tr>\r\n<tr>\r\n<td>\r\nEmployé:\r\n</td>\r\n<hr>\r\n<td>\r\n<input type=text name=EMPID value=\"");

            // end
            // begin [file="/pss/newcase.jsp";from=(105,38);to=(105,77)]
                out.print((String)session.getAttribute( "USERID"));
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(105,79);to=(113,0)]
                out.write("\">\r\n</td>\r\n<td></td>\r\n</tr>\r\n<tr bgcolor=#808080>\r\n<td>Ajout:</td>\r\n<td><input type=text name=ADDATTR size=35 onchange=\"ADDATTRSEL.value='';\"> <select name=ADDATTRSEL onchange=\"ADDATTR.value='';\">\r\n<option value=\"\">Choose an attribute...</option>\r\n");

            // end
            // begin [file="/pss/newcase.jsp";from=(113,2);to=(127,0)]
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                	rs=conn.sqlQueryR("select * from pattribdef");
                	while (rs.next())
                	{
                	out.println("<option name=\""+rs.getString("attribdefname")+"\" value=\""+rs.getInt("attribdefid")+"\">"+rs.getString("attribdefname")+"</option>");
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(127,2);to=(188,13)]
                out.write("\r\n\r\n</select>\r\n</td>\r\n<td><input type=button value=\"Add\" onclick=\"javascript:newRow()\"></td>\r\n</tr>\r\n</form>\r\n<script language=JavaScript>\r\n\r\nrowid=1;\r\n\r\nfunction newRow()\r\n{\r\n  vsel=document.FRM.ADDATTRSEL.selectedIndex;\r\n  if (vsel>0)\r\n  {\r\n\t  keytext=document.FRM.ADDATTRSEL[vsel].name;\r\n\t  attribid=document.FRM.ADDATTRSEL[vsel].value;\r\n  }\r\n  else\r\n  {\r\n\t  keytext=document.FRM.ADDATTR.value;\r\n\t  attribid=-1;\r\n  }\r\n  addRow(keytext,\"\",null,attribid);\r\n}\r\n\r\nfunction addRow(keytext,keyval,lentext,attribid) {\r\nif (attribid==null)\r\n\tvar attribid=-1;\r\nif (lentext==null) \r\n\tlentext=60;\r\nvar row=document.createElement(\"tr\");\r\n    row.name=\"ROW\"+rowid;\r\nvar cel1=row.appendChild(document.createElement(\"td\"));\r\nvar mkey=document.createElement(\"input\");\r\n    mkey.name=attribid;\r\n    mkey.id=\"PSSKEY\"+rowid;\r\n    mkey.value=keytext;\r\n    cel1.appendChild(mkey);\r\nvar cel2=row.appendChild(document.createElement(\"td\"));\r\nvar cel3=row.appendChild(document.createElement(\"td\"));\r\nvar b=cel3.appendChild(document.createElement(\"button\"));\r\n    cel3.name=\"DEL\"+rowid;\r\n    b.appendChild(document.createTextNode(\"Del\"));\r\nvar txt=cel2.appendChild(document.createElement(\"input\"));\r\n    txt.value=keyval;\r\n    txt.name=\"PSSVAL\"+rowid;\r\n    txt.id=\"PSSVAL\"+rowid;\r\n    txt.size=lentext;\r\ndocument.FRM.appendChild(row);\r\nrowid=rowid+1;\r\n}\r\n\r\n//put required fields\r\naddRow(\"NOM\",\"\");\r\naddRow(\"ID\",\"\");\r\n\r\nfunction doSubmit() {\r\n\tvar fromproc=-1; //no previous procedure\r\n\tvar frm=document.FRM;\r\n\tvar transid=");

            // end
            // begin [file="/pss/newcase.jsp";from=(188,16);to=(188,57)]
                out.print(PsDbMgr.newConnection().nextVal("PTRANS"));
            // end
            // HTML // begin [file="/pss/newcase.jsp";from=(188,59);to=(211,7)]
                out.write(";\r\n\tvar dta=new PssData(frm.CASENAME.value,frm.CASE.value,frm.EMPID.value,frm.TRANSNAME.value,transid,0,0,0,fromproc);\r\n\tvar cnt=0;\r\n\tfor (i=0;i<rowid;i++)\r\n\t{\r\n\t\tvar mkey=document.FRM.all[\"PSSKEY\"+i];\r\n\t\tvar mval=document.FRM.all[\"PSSVAL\"+i];\r\n\r\n\t\tif (mkey!=null)\r\n\t\t{\r\n\t\t\tdta.addAttrib(new PssDataAttrib(i,mkey.name,mkey.value,mval.value));\r\n\t\t}\r\n\t}\r\n\r\n\tdta.post(\"/pss/newcasesend.jsp\");\r\n\r\n\t\r\n}\r\n\r\n\r\n//-->\r\n</script>\r\n</body>\r\n</html>");

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
