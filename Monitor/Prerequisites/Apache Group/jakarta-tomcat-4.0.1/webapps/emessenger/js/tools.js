function Iso2UtfConv(strIn)
{
	var strOut="";
 	len=strIn.length;
	for (i=0;i<len;i++)
	{
		c=strIn.substring(i,i+1);
		if (c.indexOf("é")==0)
		{
			c="é";
		}
		else
		if (c.indexOf("è")==0)
		{
			c="é";
		}
		strOut+=c;
	}
	return strOut;
}
