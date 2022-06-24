<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>

<html>
<head>
<link href="css/doc.css" rel="styleSheet" type="text/css"> 
<script language=JavaScript src="js/pss.js"></script>
<script language=JavaScript>
<!--
<%
//session check
 String xusername=(String)session.getAttribute( "USERNAME");
 int    userrole;
 if (xusername==null) 
   out.println("alert('Not logged');");
 else
   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
%>
//-->
</script>
</head>

<body>
<form name=FRM onsubmit="doSubmit();">
<input type=hidden name=QTY value=0>
<input type=submit>
<table name=TBL>
<tr>
<td>
Procédure:
</td>
<td>
<select name="CASE">
<%
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
%>
</select>
</td>
<td></td>
</tr>

<tr>
<td>
Case name:
</td>
<td>
<input type=text name=CASENAME>
</td>
<td></td>
</tr>


<tr>
<td>
Trans id:
</td>
<td>
<input type=text name=TRANSID value=<%=PsDbMgr.newConnection().nextVal("PTRANS")%>>
</td>
<td></td>
</tr>
<tr>
<td>
Trans name:
</td>
<td>
<input type=text name=TRANSNAME value="">
</td>
<td></td>
</tr>
<tr>
<td>
Employé:
</td>
<hr>
<td>
<input type=text name=EMPID value="<%=(String)session.getAttribute( "USERID")%>">
</td>
<td></td>
</tr>
<tr bgcolor=#808080>
<td>Ajout:</td>
<td><input type=text name=ADDATTR size=35 onchange="ADDATTRSEL.value='';"> <select name=ADDATTRSEL onchange="ADDATTR.value='';">
<option value="">Choose an attribute...</option>
<%
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
%>

</select>
</td>
<td><input type=button value="Add" onclick="javascript:newRow()"></td>
</tr>
</form>
<script language=JavaScript>

rowid=1;

function newRow()
{
  vsel=document.FRM.ADDATTRSEL.selectedIndex;
  if (vsel>0)
  {
	  keytext=document.FRM.ADDATTRSEL[vsel].name;
	  attribid=document.FRM.ADDATTRSEL[vsel].value;
  }
  else
  {
	  keytext=document.FRM.ADDATTR.value;
	  attribid=-1;
  }
  addRow(keytext,"",null,attribid);
}

function addRow(keytext,keyval,lentext,attribid) {
if (attribid==null)
	var attribid=-1;
if (lentext==null) 
	lentext=60;
var row=document.createElement("tr");
    row.name="ROW"+rowid;
var cel1=row.appendChild(document.createElement("td"));
var mkey=document.createElement("input");
    mkey.name=attribid;
    mkey.id="PSSKEY"+rowid;
    mkey.value=keytext;
    cel1.appendChild(mkey);
var cel2=row.appendChild(document.createElement("td"));
var cel3=row.appendChild(document.createElement("td"));
var b=cel3.appendChild(document.createElement("button"));
    cel3.name="DEL"+rowid;
    b.appendChild(document.createTextNode("Del"));
var txt=cel2.appendChild(document.createElement("input"));
    txt.value=keyval;
    txt.name="PSSVAL"+rowid;
    txt.id="PSSVAL"+rowid;
    txt.size=lentext;
document.FRM.appendChild(row);
rowid=rowid+1;
}

//put required fields
addRow("NOM","");
addRow("ID","");

function doSubmit() {
	var fromproc=-1; //no previous procedure
	var frm=document.FRM;
	var transid=<%=PsDbMgr.newConnection().nextVal("PTRANS")%>;
	var dta=new PssData(frm.CASENAME.value,frm.CASE.value,frm.EMPID.value,frm.TRANSNAME.value,transid,0,0,0,fromproc);
	var cnt=0;
	for (i=0;i<rowid;i++)
	{
		var mkey=document.FRM.all["PSSKEY"+i];
		var mval=document.FRM.all["PSSVAL"+i];

		if (mkey!=null)
		{
			dta.addAttrib(new PssDataAttrib(i,mkey.name,mkey.value,mval.value));
		}
	}

	dta.post("/pss/newcasesend.jsp");

	
}


//-->
</script>
</body>
</html>