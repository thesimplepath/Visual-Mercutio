<%@page import="java.io.*, java.net.*,java.sql.*, PsDbMgr,PsDbConn, PsWf" %>
<%@page import="java.net.*, java.util.zip.*, java.util.*" %>

<html>
<body>
<%
//get the parameters
String sProcid ;
String sCaseid ;
String sTransid ;
String sToExport ;

if (request.getParameter("procid") != null)
	sProcid = request.getParameter("procid").trim() ;
else
	sProcid = "" ;

if (request.getParameter("caseid") != null)
	sCaseid = request.getParameter("caseid").trim() ;
else
	sCaseid = "" ;

if (request.getParameter("transid") != null)
	sTransid = request.getParameter("transid").trim() ;
else
	sTransid = "" ;

if (request.getParameter("toExport") != null)
	sToExport = request.getParameter("toExport").trim() ;
else
	sToExport = "" ;

/****check if we need to treat 1 or many files*****/
//store a triplet (array of 3 id) for each file to generate
ArrayList aCapsulesToGenerate = new ArrayList() ;

if (sToExport.equals(""))
	{
	String[] temp = {sProcid, sCaseid, sTransid} ;
	aCapsulesToGenerate.add(temp) ;
	}
else
	{
	//extract all informations. Because the version of java is too old(1.3.2) the function split doesn't exist.
	//We do the split by hand :-(
	int pos = 0 ;
	int oldPos = 0 ;
	String tempProc, tempCase, tempTrans ;

	while(pos < sToExport.length())
		{
		pos = sToExport.indexOf('-', oldPos) ;

		if (pos != -1)
			{
			tempProc = sToExport.substring(oldPos, pos) ;
			oldPos = pos+1 ;
			pos = sToExport.indexOf('-', oldPos) ;		
			if (pos != -1)
				{
				tempCase = sToExport.substring(oldPos, pos) ;
				oldPos = pos+1 ;
				pos = sToExport.indexOf('-', oldPos) ;	
				if (pos != -1)
					{
					tempTrans = sToExport.substring(oldPos, pos) ;
					oldPos = pos+1 ;
					String[] temp = {tempProc, tempCase, tempTrans} ;
					aCapsulesToGenerate.add(temp) ;
					}
				else
					{
					pos = sToExport.length() ;
					}
				}
			else
				{
				pos = sToExport.length() ;
				}
			}
		else
			{
			pos = sToExport.length() ;
			}

		}
	
	}


/******** Create the xml file ***********/
PsDbConn conn;
PsDbConn conn2;
ResultSet rs ;
ResultSet rs2 ;
ResultSet rs3 ;
String mvalue, mdated ;
conn=PsDbMgr.newConnection();
conn2=PsDbMgr.newConnection();
//String path = "./ct_" + sProcid + sCaseid + sTransid + ".xm" ;
ServletContext app = getServletContext();
ArrayList aNameOfFilesToZip = new ArrayList();
String pathOfZip = "";

for(int i=0; i<aCapsulesToGenerate.size(); i++)
{
//extract the info of the current file
String[] temp = (String[])aCapsulesToGenerate.get(i) ;
sProcid = temp[0] ;
sCaseid = temp[1] ;
sTransid = temp[2] ;


String path = app.getRealPath("") + "/capsulesTravail/ct_" + sProcid + sCaseid + sTransid + ".xml" ;
aNameOfFilesToZip.add(path) ;
pathOfZip = app.getRealPath("") + "/capsulesTravail/ct_" + sProcid + sCaseid + sTransid + ".zip" ;


File myFile = new File(path);


//delete an old file, if it exists
myFile.delete();

//create a new empty file, and opend it
//BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(myFile));
FileOutputStream fos = new FileOutputStream(myFile) ;

//create the xml stream
StringBuffer sb = new StringBuffer(1024) ;
String lineReturn = "\r\n" ;
String lineTab = "\t" ;

sb.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") ;
sb.append(lineReturn) ;

//***add case info
rs=conn.sqlQueryR("SELECT casename,transname FROM pcase,ptrans WHERE pcase.caseid="+sCaseid+" AND ptrans.caseid=pcase.caseid AND ptrans.transid="+sTransid);
rs.next();

sb.append("<root>");
sb.append(lineReturn) ;
sb.append(lineTab) ;
sb.append("<case caseid=\"") ;
sb.append(sCaseid) ;
sb.append("\" procid=\"") ;
sb.append(sProcid) ;
sb.append("\" transid=\"") ;
sb.append(sTransid) ;
sb.append("\" name=\"") ;
sb.append(rs.getString("casename").trim().replace('"', '\'')) ;
sb.append("\" transname=\"") ;
sb.append(rs.getString("transname").trim().replace('"', '\''));
rs.close() ;

rs=conn.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND  pproc.procid="+sProcid); 
rs.next();
sb.append("\" procname=\"") ;
sb.append(rs.getString("mvalue").trim().replace('"', '\''));
sb.append("\">") ;
sb.append(lineReturn) ;


//***add the input livrables
boolean readyOrNot=false;

rs=conn.sqlQueryR("SELECT mvalue FROM pproc,ppdattr WHERE pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=31522830 AND pproc.procid="+sProcid);//master
String delivMaster;
if (rs.next()==true)
	delivMaster=rs.getString("mvalue");
else
	 delivMaster="Start";

rs.close() ;

rs=conn.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+sCaseid+" AND pdelivstatus.transid="+sTransid+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+sProcid);

while (rs.next())
{	
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<livrableInput name=\"") ;
	sb.append(rs.getString("delivname")) ;
	if (rs.getInt("mstate")==1)
		{
		sb.append("\" delivid=\"") ;
		sb.append(rs.getString("delivid")) ;
		sb.append("\" checked=\"1\" mdated=\"") ;
		sb.append(rs.getString("mdated")) ;
		sb.append("\" >") ;
		}
	else
		{
		sb.append("\" delivid=\"") ;
		sb.append(rs.getString("delivid")) ;
		sb.append("\" checked=\"0\" mdated=\"\">") ;
		}

	sb.append(lineReturn) ;


	//***add the attributs to input
	rs2=conn.sqlQueryR("SELECT distinct pattribdef.attribdefname as attribdefname,pinput.modelid as modelid,pattribdef.attribdeftype,ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue,pinput.pdattribid as pdattribid,pinput.mdefval as mdefval,pinput.mflag as mflag,pinput.constraintid as constraintid,pattribdef.attribdeftype as attribdeftype FROM pinput,ppdattr,pattribdef WHERE ppdattr.pdattribid="+ rs.getString("delivid") +" AND pinput.attribdefid=ppdattr.attribdefid AND pinput.pdattribid=ppdattr.pdattribid AND pattribdef.attribdefid=pinput.attribdefid AND ppdattr.attribdefid=pattribdef.attribdefid  ORDER BY ppdattr.pdattribid");


	while (rs2.next())
	{
		mvalue = rs2.getString("mdefval") ;
		mdated = "" ;

		//get value already edited if any
		rs3=conn.sqlQueryR("SELECT mval,mdate FROM pinputdata WHERE modelid="+rs2.getInt("modelid")+" AND pdattribid="+rs2.getInt("pdattribid")+" AND attribdefid="+rs2.getInt("attribdefid")+" AND caseid="+sCaseid+" AND transid="+sTransid+" ORDER BY mdate desc");
		if (rs3.next()==true)
		{
			mvalue=rs3.getString("mval");
			mdated=rs3.getString("mdate");
		}
		rs3.close() ;


		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append("<attribut name=\"") ;
		sb.append(rs2.getString("attribdefname")) ;
		sb.append("\" value=\"") ;
		sb.append(mvalue);
		sb.append("\" mdated=\"") ;
		sb.append(mdated) ;
		sb.append("\" />") ;
		sb.append(lineReturn) ;
	}
	rs2.close() ;


	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("</livrableInput>") ;
	sb.append(lineReturn) ;
}
rs.close() ;



//***add the lateral livrables
rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+sProcid+" AND lateral=1");

while (rs.next())
{
	int proctrg=rs.getInt("procidtrg");

	if (rs.getString("delivname").length()>0)
	{
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<livrableLateral name=\"") ;
	sb.append(rs.getString("delivname")) ;
	sb.append("\" delivid=\"") ;
	sb.append(rs.getString("delivid")) ;
	sb.append("\"") ;

	double pct=PsWf.percentageDeliv(rs.getInt("delivid"));
	int retdelivid=PsWf.getLateralReturn(Integer.parseInt(sProcid),rs.getInt("delivid"));

	rs2=conn2.sqlQueryR("SELECT openclose FROM pdelivlateralstate WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND delivid="+retdelivid);
	if (rs2.next())
		{
		if (rs2.getInt("openclose")==0)
			{
			sb.append(" inProgress=\"1\" isTerminate=\"0\" mdated=\"\"") ;
			}
		else
			{
			sb.append(" inProgress=\"0\" isTerminate=\"1\" mdated=\"") ;
			rs2.close() ;
			rs2=conn2.sqlQuery("SELECT * FROM pdelivstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND delivid="+retdelivid);
			if (rs2.next()==true)
				sb.append(rs2.getString("mdated")) ;
			sb.append("\" isMandatroy=\"0\"") ;
			}
		}
	else
		{
		sb.append(" inProgress=\"0\" isTerminate=\"0\" mdated=\"\"") ;
		if (pct>=99.999)
			sb.append(" isMandatory=\"1\"") ;
		else
			sb.append(" isMandatory=\"0\"") ;
		}

	rs2.close() ;
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.attribdefid=1310721");
	if (rs2.next())
		{
		sb.append(" procname=\"") ;
		sb.append(rs2.getString("mvalue")) ;
		sb.append("\"") ;
		}
	else
		{
		sb.append(" procname=\"\"") ;
		}
	rs2.close() ;
	sb.append(" >") ;

	sb.append(lineReturn) ;

	//***add the attributs to lateral
	rs2=conn.sqlQueryR("SELECT distinct pattribdef.attribdefname as attribdefname,pinput.modelid as modelid,pattribdef.attribdeftype,ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue,pinput.pdattribid as pdattribid,pinput.mdefval as mdefval,pinput.mflag as mflag,pinput.constraintid as constraintid,pattribdef.attribdeftype as attribdeftype FROM pinput,ppdattr,pattribdef WHERE ppdattr.pdattribid="+ rs.getString("delivid") +" AND pinput.attribdefid=ppdattr.attribdefid AND pinput.pdattribid=ppdattr.pdattribid AND pattribdef.attribdefid=pinput.attribdefid AND ppdattr.attribdefid=pattribdef.attribdefid  ORDER BY ppdattr.pdattribid");


	while (rs2.next())
	{
		mvalue = rs2.getString("mdefval") ;
		mdated = "" ;

		//get value already edited if any
		rs3=conn.sqlQueryR("SELECT mval,mdate FROM pinputdata WHERE modelid="+rs2.getInt("modelid")+" AND pdattribid="+rs2.getInt("pdattribid")+" AND attribdefid="+rs2.getInt("attribdefid")+" AND caseid="+sCaseid+" AND transid="+sTransid+" ORDER BY mdate desc");
		if (rs3.next()==true)
		{
			mvalue=rs3.getString("mval");
			mdated=rs3.getString("mdate");
		}
		rs3.close() ;


		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append("<attribut name=\"") ;
		sb.append(rs2.getString("attribdefname")) ;
		sb.append("\" value=\"") ;
		sb.append(mvalue);
		sb.append("\" mdated=\"") ;
		sb.append(mdated) ;
		sb.append("\" />") ;
		sb.append(lineReturn) ;
	}
	rs2.close() ;


	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("</livrableLateral>") ;

	sb.append(lineReturn) ;
	}
}
rs.close() ;


//***add the output livrables
rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+sProcid+" AND lateral=0");

while (rs.next())
{
	int proctrg=rs.getInt("procidtrg");

	if (rs.getString("delivname").length()>0)
	{
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<livrableOutput name=\"") ;
	sb.append(rs.getString("delivname")) ;
	sb.append("\" delivid=\"") ;
	sb.append(rs.getString("delivid")) ;
	sb.append("\"") ;

	rs2=conn2.sqlQueryR("SELECT * FROM pdelivstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND delivid="+rs.getString("delivid"));

	if (rs2.next())
	{
		if (rs2.getInt("mstate")==1)
			sb.append(" isCompleted=\"1\"") ;
		else
			sb.append(" isCompleted=\"0\"") ;
		sb.append(" mdated=\"") ;
		sb.append(rs2.getString("mdated"));
		sb.append("\"") ;
	}
	else
	{
		sb.append(" isCompleted=\"0\" mdated=\"\"") ;
	}
	rs2.close() ;

	double pct=PsWf.percentageDeliv(rs.getInt("delivid"));
	if (pct>=99.999) 
		sb.append(" isMandatory=\"1\"") ;
	else
		sb.append(" isMandatory=\"0\"") ;

	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.attribdefid=1310721;");
	if (rs2.next())
		{
		sb.append(" procname=\"") ;
		sb.append(rs2.getString("mvalue")) ;
		sb.append("\"") ;
		}
	else
		sb.append(" procname=\"\"") ;

	rs2.close() ;
	sb.append(" >") ;

	sb.append(lineReturn) ;

	//***add the attributs to output
	rs2=conn.sqlQueryR("SELECT distinct pattribdef.attribdefname as attribdefname,pinput.modelid as modelid,pattribdef.attribdeftype,ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue,pinput.pdattribid as pdattribid,pinput.mdefval as mdefval,pinput.mflag as mflag,pinput.constraintid as constraintid,pattribdef.attribdeftype as attribdeftype FROM pinput,ppdattr,pattribdef WHERE ppdattr.pdattribid="+ rs.getString("delivid") +" AND pinput.attribdefid=ppdattr.attribdefid AND pinput.pdattribid=ppdattr.pdattribid AND pattribdef.attribdefid=pinput.attribdefid AND ppdattr.attribdefid=pattribdef.attribdefid  ORDER BY ppdattr.pdattribid");


	while (rs2.next())
	{
		mvalue = rs2.getString("mdefval") ;
		mdated = "" ;

		//get value already edited if any
		rs3=conn.sqlQueryR("SELECT mval,mdate FROM pinputdata WHERE modelid="+rs2.getInt("modelid")+" AND pdattribid="+rs2.getInt("pdattribid")+" AND attribdefid="+rs2.getInt("attribdefid")+" AND caseid="+sCaseid+" AND transid="+sTransid+" ORDER BY mdate desc");
		if (rs3.next()==true)
		{
			mvalue=rs3.getString("mval");
			mdated=rs3.getString("mdate");
		}
		rs3.close() ;


		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append("<attribut name=\"") ;
		sb.append(rs2.getString("attribdefname")) ;
		sb.append("\" value=\"") ;
		sb.append(mvalue);
		sb.append("\" mdated=\"") ;
		sb.append(mdated) ;
		sb.append("\" />") ;
		sb.append(lineReturn) ;
	}
	rs2.close() ;

	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("</livrableOutput>") ;

	sb.append(lineReturn) ;
	}
}
rs.close() ;


//***add the task
rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+sProcid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=41943041 AND ppdattr.attribdefid<=41943421");

while (rs.next())
{	
	String checked="0";
	mdated="";
	rs2=conn2.sqlQueryR("SELECT * FROM ptaskstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND taskid="+rs.getString("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="1";
		else
			checked="0";
		mdated=rs2.getString("mdated");
	}
	if (rs.getString("mvalue").length()>0)
	{
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<task mvalue=\"") ;
	sb.append(rs.getString("mvalue").trim().replace('"', '\'')) ;
	sb.append("\" attribid=\"") ;
	sb.append(rs.getString("attribdefid")) ;
	sb.append("\" mdated=\"") ;
	sb.append(mdated) ;
	sb.append("\" mstate=\"") ;
	sb.append(checked) ;
	sb.append("\" />") ;
	sb.append(lineReturn) ;
	}
	
	rs2.close() ;
 }

rs.close() ;

//***add the decisions
rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+sProcid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=43253761 AND ppdattr.attribdefid<=43254141");

while (rs.next())
{
	String checked="0";
	mdated="";
	rs2=conn2.sqlQueryR("SELECT * FROM pdecisionstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND decisionid="+rs.getString("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="1";
		else
			checked="0" ;
		mdated=rs2.getString("mdated");
	}

	if (rs.getString("mvalue").length()>0)
	{
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<decision mvalue=\"") ;
	sb.append(rs.getString("mvalue").trim().replace('"', '\'')) ;
	sb.append("\" attribid=\"") ;
	sb.append(rs.getString("attribdefid")) ;
	sb.append("\" mdated=\"") ;
	sb.append(mdated) ;
	sb.append("\" mstate=\"") ;
	sb.append(checked) ;
	sb.append("\" />") ;
	sb.append(lineReturn) ;
	}
	rs2.close() ;
 }
rs.close() ;

//***add the rules
rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+sProcid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid >= 68157441 AND ppdattr.attribdefid <= 68157821 ORDER BY ppdattr.pdattribid");

while (rs.next())
{	
	String rule=rs.getString("mvalue");

	String checked="0";
	mdated="";

	rs2=conn2.sqlQueryR("SELECT * FROM prulesstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND delivid=-1 AND refid="+rs.getInt("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="1";
		else
			checked="0" ;
		mdated=rs2.getString("mdated");
	}

	if (rule.length()>0)
	{
	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<rule mvalue=\"") ;
	sb.append(rs.getString("mvalue").trim().replace('"', '\'')) ;
	sb.append("\" delivid=\"-1\" refid=\"") ;
	sb.append(rs.getString("attribdefid")) ;
	sb.append("\" mdated=\"") ;
	sb.append(mdated) ;
	sb.append("\" mstate=\"") ;
	sb.append(checked) ;
	sb.append("\" />") ;
	sb.append(lineReturn) ;
	}
	rs2.close() ;
}
rs.close() ;


//***add the files
rs=conn.sqlQueryR("SELECT * FROM pattach WHERE caseid="+sCaseid+" AND transid="+sTransid);
while (rs.next())
{	
	String filename=rs.getString("filename");
	String mlogin=rs.getString("mlogin");
	mdated=rs.getString("filedate");

	sb.append(lineTab) ;
	sb.append(lineTab) ;
	sb.append("<file name=\"") ;
	sb.append(filename) ;
	sb.append("\" login=\"") ;
	sb.append(mlogin) ;
	sb.append("\" mdated=\"") ;
	sb.append(mdated) ;
	sb.append("\" />") ;
	sb.append(lineReturn) ;

}
rs.close() ;


//***add the application
rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,psystem.* FROM pproc,ppdattr,psystem WHERE pproc.procid="+ sProcid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid = 47185921 AND psystem.systemtitle=ppdattr.mvalue ORDER BY ppdattr.pdattribid");//ref title,ref

while (rs.next())
{	
	String systemid=rs.getString("systemid");
	String titreSys=rs.getString("systemtitle");
	String command=rs.getString("command");
	String parameters=rs.getString("parameters");
	String directory=rs.getString("directory");
	String priority=rs.getString("priority");
	String windowst=rs.getString("windowst");

	String checked="";
	mdated="";


	rs2=conn2.sqlQueryR("SELECT * FROM psystemstatus WHERE procid="+sProcid+" AND caseid="+sCaseid+" AND transid="+sTransid+" AND delivid=-1 AND refid="+rs.getInt("prow"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}
	rs2.close() ;

	if (command.length()>0)
	{
		sb.append(lineTab) ;
		sb.append(lineTab) ;
		sb.append("<application checked=\"") ;
		sb.append(checked) ;
		sb.append("\" name=\"") ;
		sb.append(titreSys) ;
		sb.append("\" command=\"") ;
		//sb.append(PsConv.c4JS(command)) ;
		sb.append(command) ;
		sb.append("\" parameters=\"") ;
		//sb.append(PsConv.c4JS(parameters)) ;
		sb.append(parameters) ;
		sb.append("\" mdated=\"") ;
		sb.append(mdated) ;
		sb.append("\" />") ;
		sb.append(lineReturn) ;
	}
 }
rs.close() ;


//***close the file

sb.append(lineTab) ;
sb.append("</case>") ;
sb.append(lineReturn) ;
sb.append("</root>") ;

//write the xml stream to the file
fos.write(sb.toString().getBytes()) ;

fos.close() ;
}






//on zip le(s) fichier(s)
//files to include in the zip
String[] filenames = new String[aNameOfFilesToZip.size()] ;
for(int i=0; i<aNameOfFilesToZip.size(); i++)
	filenames[i] = (String)aNameOfFilesToZip.get(i) ;
    
// Create a buffer for reading the files
byte[] buf = new byte[1024];
    
try
	{
        // Create the ZIP file
        String outFilename = pathOfZip ;
        ZipOutputStream out2 = new ZipOutputStream(new FileOutputStream(outFilename));
    
        // Compress the files
        for (int i=0; i<filenames.length; i++) {
            FileInputStream in = new FileInputStream(filenames[i]);
    
            // Add ZIP entry to output stream.
            out2.putNextEntry(new ZipEntry(filenames[i]));
    
            // Transfer bytes from the file to the ZIP file
            int len;
            while ((len = in.read(buf)) > 0) {
                out2.write(buf, 0, len);
            }
    
            // Complete the entry
            out2.closeEntry();
            in.close();
        }
    
        // Complete the ZIP file
        out2.close();
    }
catch (IOException e)
    {
	out.print("Une erreur est survenue en créant le fichier compressé (.zip) : " + e.getMessage()) ;
	return ;
    }




//conn.close() ;
//conn2.close() ;
%>
La capsule de travail est pr&ecirc;te pour le t&eacute;l&eacute;chargement.<br>
<br><br>
Pour la r&eacute;cup&eacute;rer, faites bouton droit de la souris, puis "Enregister la cible sous...". Sauvez le fichier dans le r&eacute;pertoire ad&eacute;quate.
<br><br>
<a href="capsulesTravail/<%=pathOfZip%>">T&eacute;l&eacute;charger la capsule de travail en XML</a><br>




</body>
</html>