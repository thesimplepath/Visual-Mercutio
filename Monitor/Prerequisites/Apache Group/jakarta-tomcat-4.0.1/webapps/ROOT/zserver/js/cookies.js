function GetCookieValue(offset)
{
	cook=top.document.cookie;
	var endstr = cook.indexOf(";", offset);
	
	if (endstr == -1)
		endstr = cook.length;
	return (cook.substring(offset, endstr));
}

function GetCookie(name)
{
	cook=top.document.cookie;
	var arg = name + "=";
	var alen = arg.length;
	var clen = cook.length;
	var i = 0;

	while (i < clen)
	{
		var j = i + alen;
		if (cook.substring(i, j) == arg)
			return unescape(GetCookieValue(j));
		i = cook.indexOf(" ", i) + 1;
		if (i == 0) break;
	}
	
	return "";
}

function SetCookie(name,value,expire,extra)
{
	top.document.cookie=name + "=" + escape(value) +((expire == null) ? "" : ("; expires=" + expire.toGMTString())) +"; path=/; "+extra;
}			