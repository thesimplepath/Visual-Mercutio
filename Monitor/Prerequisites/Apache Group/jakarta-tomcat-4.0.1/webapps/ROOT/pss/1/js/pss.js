//Dynamic Attribute Manager
function PssDataAttrib_dump()
{
  var out=document;
  out.writeln(" Seg: "+this.segid+" AttribId:"+this.attribid+" Mvalue:"+this.mvalue); 
}

function PssDataAttrib(segid,attribid,mkey,mvalue)
{
  if (segid==null) segid=-1;
  if (attribid==null) attribid=-1;
  if (mvalue==null) mvalue="";

  this.segid=segid;
  this.attribid=attribid;
  this.mkey=mkey;
  this.mvalue=mvalue;

  this.dump=PssDataAttrib_dump;
}

//Data Object Manager
function PssData_reset()
{
  this.attrib=new Array();
}

function PssData_add(dta)
{
  this.attrib[this.attrib.length]=dta;
}

function PssData_dump()
{
  var out=document;
  out.writeln("<pre>");
  out.writeln("Proc #"+this.procid);
  out.writeln("#"+this.transid+" ("+this.transname+")");
  out.writeln("Parent transaction: "+this.parenttransid);
  out.writeln("Employee: "+this.empid);
  out.writeln("Status: "+this.statusid+" GlobalYN: "+this.globalyn);

  l=this.attrib.length;
  for (i=0;i<l;i++) {
	var n=this.attrib[i];
	out.writeln(" Seg: "+n.segid+" AttribId:"+n.attribid+" Mvalue:"+n.mvalue);
  }  

  out.writeln("</pre>");
}

function PssData_post(url)
{
  var out=document;
  out.writeln("<form name=\"PSSDATA_FORM\" method=GET action=\""+url+"\" onsubmit=\"alert('yo');\">");
  out.writeln("<input type=hidden name=CASENAME value=\""+this.casename+"\">");
  out.writeln("<input type=hidden name=PROCID value="+this.procid+">");
  out.writeln("<input type=hidden name=TRANSID value="+this.transid+">");
  out.writeln("<input type=hidden name=TRANSNAME value=\""+this.transname+"\">");
  out.writeln("<input type=hidden name=PARENTTRANSID value="+this.parenttransid+">");
  out.writeln("<input type=hidden name=EMPID value="+this.empid+">");
  out.writeln("<input type=hidden name=STATUSID value="+this.statusid+">");
  out.writeln("<input type=hidden name=GLOBALYN value="+this.globalyn+">");
  out.writeln("<input type=hidden name=CASEATTACHID value="+this.caseattachid+">");

  out.writeln("<input type=hidden name=FROMPROC value="+this.fromproc+">");

  l=this.attrib.length;
  out.writeln("<input type=hidden name=QTY value="+l+">");

  for (i=0;i<l;i++) {
	var n=this.attrib[i];
	out.writeln("<input type=hidden name=SEG"+i+" value="+n.segid+">");
	out.writeln("<input type=hidden name=ATTRIBID"+i+" value="+n.attribid+">");
	out.writeln("<input type=hidden name=VAL"+i+" value=\""+n.mvalue+"\">");
	out.writeln("<input type=hidden name=KEY"+i+" value=\""+n.mkey+"\">");
  }  
  
  out.writeln("</form>");

  //submit form to URL
  out.writeln("<script language=JavaScript>");
  out.writeln("document.PSSDATA_FORM.submit();");
  out.writeln("</script>");
}

function PssData(caseattachid,casename,procid,empid,transname,transid,parenttransid,statusid,globalyn,fromproc)
{
  if (casename==null) casename="";
  if (procid==null) procid=-1;
  if (parenttransid==null) parenttransid=0;
  if (transname==null) transname="";
  if (transid==null) transid=-1;
  if (empid==null) empid=-1;
  if (statusid==null) statusid=-1;
  if (globalyn==null) globalyn=0;
  if (caseattachid==null) caseattachid=-1;

  this.caseattachid=caseattachid;
  this.casename=casename;
  this.procid=procid;
  this.empid=empid;
  this.transname=transname;
  this.transid=transid;
  this.parenttransid=parenttransid;
  this.attrib=new Array();
  this.statusid=statusid;
  this.globalyn=globalyn;
  this.fromproc=fromproc;

  this.addAttrib= PssData_add;
  this.reset=PssData_reset;
  this.dump=PssData_dump;
  this.post=PssData_post;
}

//Procedure Validator Object Definition
function PssProcedureValidator()
{
	this.lstToCheck=new Array;
	this.lstChecked=new Array;
	this.reset=PssProcedureValidator_reset;
	this.set=PssProcedureValidator_set;
	this.validator=PssProcedureValidator_validator;	
}

function PssProcedureValidator_set(livname,statusid)
{
	this.lstToCheck[this.lstToCheck.length]=livname;
	this.lstChecked[this.lstChecked.length]=statusid;
}

function PssProcedureValidator_reset(livname,statusid)
{
	this.lstToCheck=new Array;
	this.lstChecked=new Array;
}

function PssProcedureValidator_validator()
{
	var i=this.lstToCheck.length;
	for (j=0;j<i;j++)
	{
		if (this.lstChecked[j]!=1)
		{
			alert("Vous devez activer le livrable \""+this.lstToCheck[j]+"\" avant de clore cette procedure");
			return false;
		}
	}
	return true;
}