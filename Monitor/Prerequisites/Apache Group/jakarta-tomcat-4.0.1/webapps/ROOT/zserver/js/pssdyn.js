//Dynamic Attributes Handler
//ProcessSoft 2002

//Default settings
var defstyle="";

//Global Validator
function Adynvalidator(mkey,mtype,mval,mmask)
{  
  mval=unescape(mval);
  mmask=unescape(mmask);
//  alert(mkey+" mval="+mval);
}

//Calendar Control
var dialogWindow=null;
var dialogReturn=null;
function Adyncalendar(ctl)
{
	dialogReturn=ctl;
	if (dialogWindow!=null)
	{
		dialogWindow.close();
		dialogWindow=null;
	}
	dialogWindow = window.open("calendar.htm","","height=270,width=240,modal=yes");
}

//Show default text
function Adyn_show()
{
   var tg="<input type=text style=\"width:100%;"+defstyle+"\" name=\"CTL_"+this.mid+"\" value=\""+this.mval+"\" onchange=\"Adynvalidator('"+this.mkey+"',"+this.mtype+",escape(CTL_"+this.mid+".value),'"+escape(this.mmask)+"');\">"
   document.writeln(tg);
}

//Show text area
function Adyn_show_textarea()
{
   var tg="<textarea style=\"width:100%;"+defstyle+"\" name=\"CTL_"+this.mid+"\" onchange=\"Adynvalidator('"+this.mkey+"',"+this.mtype+",escape(CTL_"+this.mid+".value),'"+escape(this.mmask)+"');\">"+this.mval+"</textarea>"
   document.writeln(tg);
}

//show checkbox
function Adyn_show_checkbox()
{
   var c="";
   if (this.mval == '1')
   	c="checked";
   var tg="<input type=checkbox "+c+" style=\""+defstyle+"\" name=\"CTL_"+this.mid+"\" onchange=\"Adynvalidator('"+this.mkey+"',"+this.mtype+",escape(CTL_"+this.mid+".value),'"+escape(this.mmask)+"');\">"
   document.writeln(tg);
}

//show calendar
function Adyn_show_calendar()
{
   var tg="<table cellSpacing=0 cellPadding=0 border=0><tr valign=middle><td>";
   tg=tg+"<input type=text readonly size=11 style=\""+defstyle+"\" name=\"CTL_"+this.mid+"\" value=\""+this.mval+"\">"
   tg=tg+"</td><td>";
   tg=tg+"&nbsp;<img src=\"img/calendaropen.gif\" alt=\"Open Calendar\" onclick=\"Adyncalendar(CTL_"+this.mid+")\"";
   tg=tg+"</td></tr></table>";
   document.writeln(tg);
}

//Adyn object constructor
function Adyn(mid,mkey,mval,mtype,mmask,minlen,maxlen,mandatorychars,forbiddenchars)
{
  //defaults settings
  if (minlen==null) minlen=0;
  if (maxlen==null) maxlen=255;
  if (mandatorychars==null) mandatorychars="";
  if (forbiddenchars==null) forbiddenchars="";
  
  //properties assignement
  this.mid=mid;
  this.mkey=mkey;
  this.mval=mval;
  this.mtype=mtype;
  this.mmask=mmask;
  this.minlen=minlen;
  this.maxlen=maxlen;
  this.mandatorychars=mandatorychars;
  this.forbiddenchars=forbiddenchars;

  //show method depending on mtype
  this.show=Adyn_show;
  
  if (mtype==3)
      this.show=Adyn_show_calendar;
  if (mtype==4)
      this.show=Adyn_show_textarea;
  if (mtype==5)
      this.show=Adyn_show_checkbox;

}