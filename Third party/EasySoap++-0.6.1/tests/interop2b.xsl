<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="html"/>
<xsl:template match="/">
<html>
<head>
<title>EasySoap++ Round 2B Interop Matrix</title>
<body>

<h3>Round 2B</h3>
Table updated: <xsl:value-of select="InteropTests/Date"/>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoStructAsSimpleTypes</th>
	<th bgcolor="teal">echoSimpleTypesAsStruct</th>
	<th bgcolor="teal">echo2DStringArray</th>
	<th bgcolor="teal">echoNestedStruct</th>
	<th bgcolor="teal">echoNestedArray</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoStructAsSimpleTypes']" />
<xsl:apply-templates select="Test[@name='echoSimpleTypesAsStruct']" />
<xsl:apply-templates select="Test[@name='echo2DStringArray']" />
<xsl:apply-templates select="Test[@name='echoNestedStruct']" />
<xsl:apply-templates select="Test[@name='echoNestedArray']" />
</tr>
</xsl:for-each>
</table>
</body>
</head>
</html>
</xsl:template>

<xsl:template match='Server'>
<td bgcolor="gray">
<a><xsl:attribute name="href"><xsl:value-of select="@name" />/</xsl:attribute><xsl:value-of select="@name" /></a></td>
</xsl:template>

<xsl:template match='Test'>
<td align="CENTER">
<xsl:if test="Result[. = 'PASS']">
<xsl:attribute name="bgcolor">silver</xsl:attribute>
</xsl:if>
<xsl:if test="Result[. = 'FAIL']">
<xsl:attribute name="bgcolor">red</xsl:attribute>
</xsl:if>
<xsl:if test="Result[. = 'NETWORK ERROR']">
<xsl:attribute name="bgcolor">yellow</xsl:attribute>
</xsl:if>
<xsl:if test="Result[. = 'FP LOSS']">
<xsl:attribute name="bgcolor">cyan</xsl:attribute>
</xsl:if>
<xsl:if test="Result[. = 'FAULT']">
<xsl:attribute name="bgcolor">fuchsia</xsl:attribute>
</xsl:if>
<a><xsl:attribute name="href"><xsl:value-of select="../@name" />/<xsl:value-of select="@name" />.txt</xsl:attribute>
   <xsl:attribute name="title"><xsl:value-of select="Message" /></xsl:attribute>
   <xsl:value-of select="Result" />
</a>
</td>
</xsl:template>

</xsl:stylesheet>
