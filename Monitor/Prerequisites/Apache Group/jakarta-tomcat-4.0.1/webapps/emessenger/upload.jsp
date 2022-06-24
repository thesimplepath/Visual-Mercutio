<HTML>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf,HttpUpload,HttpFile,HttpFiles,HttpRequest,HttpUploadException" %>
<HEAD><TITLE>ProcessSoft Mercutio Messenger - Upload</TITLE>
<jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<META http-equiv=Content-Type content="text/html; charset=utf-8">

<jsp:useBean id="doupld" scope="page" class="HttpUpload" />
</jsp:useBean>

<%
 PsApp.init();

 PsDbConn conn=PsDbMgr.newConnection();
 ResultSet rs;

 String username=(String)session.getAttribute("USERNAME");
 if (username==null) return;
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 int caseid=-1;
 if (request.getParameter( "CASEID" )!=null)		
	caseid=Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=-1;
 if (request.getParameter( "TRANSID" )!=null)
	transid=Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 int mode=2;
 
 if (request.getParameter( "MODE" )!=null)
	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();

 if (mode==2)
 {
	PsDebug.log("upload.jsp starting upload");
	doupld.initialize(pageContext);
	//doupld.setTotalMaxFileSize(2000000);
	//doupld.setAllowedFilesList("htm,html,txt,doc,xls,ppt,xml,tif,jpg,gif,png,bmp,,");
	doupld.upload();

	caseid=Integer.valueOf((String)doupld.getRequest().getParameter("CASEID")).intValue();
	transid=Integer.valueOf((String)doupld.getRequest().getParameter("TRANSID")).intValue();
	PsDebug.log("upload.jsp processing");

	try {
			HttpFile myFile = doupld.getFiles().getFile(0);
			PsDebug.log("upload.jsp "+myFile.getFileName());
			if (!myFile.isMissing()) 
			{
				String fname		= ""+caseid+"-"+transid+"-"+myFile.getFileName();
				PsDebug.log("upload.jsp saving file docs/"+fname);
				myFile.saveAs("docs/"+fname);
	
				conn.sqlExec("INSERT INTO pattach VALUES("+caseid+","+transid+",'"+PsDbConn.cnv_sql(fname)+"',"+conn.now()+",'"+username+"')");
			}					
			
	} catch (Exception e) { 
		PsDebug.fail(e.toString());
	} 
	 

	PsDebug.log("upload.jsp done");
	%>
	<script language="JavaScript">
	window.close();
	</script>
	<%
 }
%>

</head>

<BODY>
<TABLE width="100%">
<TR>
<TD width="2%">
&nbsp;
</TD>
<TD width="98%">

<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="96%"><NOBR><FONT class=menu>Téléchargement</FONT></NOBR></TD>
        </TR>
</TBODY>
</TABLE>
<br>

<%
if (mode!=2)
	{
%>
Téléchargement de fichiers vers le cas:<br>
<%
	PsDebug.log("upload.jsp caseid="+caseid+" transid="+transid);
	rs=conn.sqlQueryR("SELECT * FROM pcase,ptrans WHERE pcase.caseid="+caseid+" AND pcase.caseid=ptrans.caseid AND ptrans.transid="+transid);
	rs.next();
%>
<b><%=rs.getString("casename")%><br><%=rs.getString("transname")%></b>
<br> 
<FORM action="upload.jsp" method="POST" ENCTYPE="multipart/form-data">
<INPUT TYPE="FILE" style="width:100%" NAME=FILE1>
<INPUT TYPE="HIDDEN" NAME=MODE VALUE="2">
<INPUT TYPE="HIDDEN" NAME=CASEID VALUE=<%=caseid%> >
<INPUT TYPE="HIDDEN" NAME=TRANSID VALUE=<%=transid%> >
<br><br>
<p align=center>
<INPUT TYPE=SUBMIT VALUE="Envoi du fichier">
</p>
</FORM>
<%
	}
%>
</TABLE>
</BODY>
</HTML>
