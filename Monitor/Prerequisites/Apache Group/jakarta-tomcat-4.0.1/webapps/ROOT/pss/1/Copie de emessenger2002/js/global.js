
var oLastBtn=0;
var imgPlus = new Image();
imgPlus.src = "/images/plus.gif";
var imgMinus = new Image();
imgMinus.src = "/images/minus.gif";


function RaiseButton()
{
		window.event.cancelBubble=true;
		oBtn = window.event.srcElement;
		var bChosen = false;
		if(oLastBtn && oLastBtn != oBtn){
			HideButton();
		}
		if(oBtn.buttonType){
			oBtn.className = oBtn.buttonType + "Up";
			oLastBtn=oBtn;
			}
		else {
		oLastBtn = 0;
		}
}
function DepressButton()
{
		window.event.cancelBubble=true;
		oBtn = window.event.srcElement;
		if(oBtn.buttonType){
			oBtn.className = oBtn.buttonType + "Down";
		}
}
function HideButton()
{
		if ((oLastBtn.buttonType == "TopMenuNavChosen") || (oLastBtn.buttonType == "TopMenuNavSubChosen")) 
		{
			oLastBtn.className = oLastBtn.buttonType;
		}
		else 
		{
		oLastBtn.className = oLastBtn.buttonType + "Off";
		}
}


function bgRoll(strTextColor)
{
		window.event.srcElement.style.backgroundColor = strTextColor;
		window.event.cancelBubble = true;
}
function fntRoll(strTextColor)
{
  		window.event.srcElement.style.color = strTextColor;
		window.event.cancelBubble = true;
}		


function doOutline() 
{
  var srcId, srcElement, targetElement;
  srcElement = window.event.srcElement;
  if (srcElement.className.toUpperCase() == "LEVEL1") 
  {
	srcID = srcElement.id.substr(0, srcElement.id.length-1);
	targetElement = document.all(srcID + "s");
	srcElement = document.all(srcID + "i");
  	
	if (targetElement.style.display == "none") 
	{			
		targetElement.style.display = "";
		if (srcElement.className == "LEVEL1") 
		   srcElement.src = imgMinus.src;
     	} 
	else 
	{
		targetElement.style.display = "none";
		if (srcElement.className == "LEVEL1") 
		   srcElement.src = imgPlus.src;
     	}
  }
}





{