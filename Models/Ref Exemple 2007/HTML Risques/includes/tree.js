function menu_Entry(idmenu,refid,txtmenu,urlmenu)
{	
  this.idmenu=idmenu;
  this.refid=refid;
  this.txtmenu=txtmenu;
  this.urlmenu=urlmenu; 
}

function menu_add(idmenu, refid, txtmenu, urlmenu)
{
  this.dta[this.dtanbr++]=new menu_Entry(idmenu,refid,txtmenu,urlmenu);
}

function menu_set_icon_doc(iconimg)
{
  this.icondoc=iconimg;
}

function menu_set_icon_open(iconimg)
{
  this.iconopen=iconimg;
}

function menu_set_icon_close(iconimg)
{
  this.iconclose=iconimg;
}

function menu_set_target(target)
{
  this.target=target;
}

var menu_level;
function menu_genrec(no,expyn)
{
	var st="collapsed";
	if (expyn==true)
		st="expanded";

	var i;
	menu_level++;
	for (i=0;i<this.dtanbr;i++)
	{
		var dta=this.dta[i];
		if (dta.refid==no)
		{		
var spc="";
for (j=0;j<menu_level;j++) spc=spc+="&nbsp;&nbsp;&nbsp;";
			if (dta.urlmenu==null)
				document.writeln("<div id=B"+ dta.idmenu+" style=\"cursor:hand; width:160px;\" nowrap>"+spc+"<img src=\""+this.iconclose+"\" onclick=\"menu_outliner('Z"+ dta.idmenu +"')\">&nbsp;<a href=\"javascript:menu_outliner('Z"+ dta.idmenu +"')\">"+dta.txtmenu +"</a></div><div class=\""+st+"\" id=\"Z"+dta.idmenu+"\">");

			if (dta.urlmenu!=null)
				document.writeln("<div id=Q"+ dta.refid +" style=\"cursor:hand; width:160px;\" nowrap class=\""+st+"\" valign=\"top\">"+spc+"<img src=\""+this.icondoc+"\">&nbsp;<a href=\""+ dta.urlmenu +"\" target="+this.target+" title=\"Go to "+dta.txtmenu+"\">"+dta.txtmenu +"</a></div>");

			this.gen2(dta.idmenu,expyn);
			if (dta.urlmenu==null)
				document.writeln("</div>");
		}
	}
	
	menu_level--;
}

var mexpyn=false;
function menu_gen(expyn)
{
	mexpyn=expyn;
	this.expyn=expyn;
	menu_level=-1;
	this.gen2(0,expyn);//start from root
}

var oldchild=null;
function menu_outliner(child)
{
 if (oldchild!=null && mexpyn!=true)
 {
  document.all[oldchild].className = "collapsed";
 }
 document.all[child].className = document.all[child].className == "collapsed" ? "expanded" : "collapsed";
 oldchild=child;
}

//Class definition oMenu
function oMenu()
{
//private:
  this.gen2 = menu_genrec;
  this.target="doc";
  this.icondoc="";
  this.iconopen="";
  this.iconclose="";

  this.expyn=false;

  this.dtanbr=0;
  this.dta = new Array;
//public:
  this.add = menu_add;
  this.setIconDocument = menu_set_icon_doc;
  this.setIconCollapse = menu_set_icon_close;
  this.setIconExpand = menu_set_icon_open;
  this.gen = menu_gen;
  this.setTarget = menu_set_target;
}
