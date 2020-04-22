<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="html"/>
<xsl:template match="/">
<html>
<head>
<title>EasySoap++ Interop Matrix</title>
<body>

<h2>Round 2C</h2>
Table updated: <xsl:value-of select="InteropTests/Date"/>
<h3>Default Actor</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=1</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=0 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=1 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=0 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=1 actor=default']" />

<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=0 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=1 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=0 actor=default']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=1 actor=default']" />
</tr>
</xsl:for-each>
</table>

<h3>Next Actor</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=1</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=0 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=1 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=0 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=1 actor=next']" />

<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=0 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=1 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=0 actor=next']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=1 actor=next']" />
</tr>
</xsl:for-each>
</table>

<h3>Other Actor</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrString mu=1 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=0 understandable=1</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=0</th>
	<th bgcolor="teal">echoHdrStruct mu=1 understandable=1</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=0 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=0 understandable=1 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=0 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrString mu=1 understandable=1 actor=other']" />

<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=0 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=0 understandable=1 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=0 actor=other']" />
<xsl:apply-templates select="Test[@name='echoHdrStruct mu=1 understandable=1 actor=other']" />
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
