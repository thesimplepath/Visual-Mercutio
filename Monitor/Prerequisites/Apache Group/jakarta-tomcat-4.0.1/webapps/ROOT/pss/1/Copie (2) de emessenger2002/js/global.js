
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




function CA(isOnload)
{var trk=0;for (var i=0;i<frm.elements.length;i++){var e = frm.elements[i];if ((e.name != 'allbox') && (e.type=='checkbox')){if (isOnload != 1){trk++;e.checked = frm.allbox.checked;if (frm.allbox.checked){hL(e);if ((folderID == "F000000005") && (ie) && (trk > 1))document.all.notbulkmail.disabled = true;}else{dL(e);if ((folderID == "F000000005") && (ie))document.all.notbulkmail.disabled = false;}if (document.all.nullbulkmail)document.all.nullbulkmail.disabled = document.all.notbulkmail.disabled;}else{e.tabIndex = i;if (folderID != "")e.parentElement.parentElement.children[2].children[0].tabIndex = i;if (e.checked){hL(e);}else{dL(e);}}}}}function CCA(CB){if (CB.checked)hL(CB);elsedL(CB);var TB=TO=0;for (var i=0;i<frm.elements.length;i++){var e = frm.elements[i];if ((e.name != 'allbox') && (e.type=='checkbox')){TB++;if (e.checked)TO++;}}if ((folderID == "F000000005") && (ie)){if (TO > 1)document.all.notbulkmail.disabled = true;elsedocument.all.notbulkmail.disabled = false;if (document.all.nullbulkmail)document.all.nullbulkmail.disabled = document.all.notbulkmail.disabled;}if (TO==TB)frm.allbox.checked=true;elsefrm.allbox.checked=false;}function hL(E){if (ie){while (E.tagName!="TR"){E=E.parentElement;}}else{while (E.tagName!="TR"){E=E.parentNode;}}E.className = "H";}function dL(E){if (ie){while (E.tagName!="TR"){E=E.parentElement;}}else{while (E.tagName!="TR"){E=E.parentNode;}}E.className = "";}
