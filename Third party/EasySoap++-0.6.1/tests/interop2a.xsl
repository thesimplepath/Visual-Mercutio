<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="html"/>
<xsl:template match="/">
<html>
<head>
<title>EasySoap++ Round 2 base Interop Matrix</title>
<body>

<h3>Basic Tests</h3>
Just some basic types.  Integer, float, String, struct, etc.<p/>
Table updated: <xsl:value-of select="InteropTests/Date"/>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoInteger</th>
	<th bgcolor="teal">echoFloat</th>
	<th bgcolor="teal">echoString</th>
	<th bgcolor="teal">echoString<br/>(check CR escape)</th>
	<th bgcolor="teal">echoStruct</th>
	<th bgcolor="teal">echoBase64</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoInteger']" />
<xsl:apply-templates select="Test[@name='echoFloat']" />
<xsl:apply-templates select="Test[@name='echoString']" />
<xsl:apply-templates select="Test[@name='echoString_newlines']" />
<xsl:apply-templates select="Test[@name='echoStruct']" />
<xsl:apply-templates select="Test[@name='echoBase64']" />
</tr>
</xsl:for-each>
</table>
<h3>Array Tests</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoIntegerArray</th>
	<th bgcolor="teal">echoFloatArray</th>
	<th bgcolor="teal">echoStringArray</th>
	<th bgcolor="teal">echoStructArray</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoIntegerArray']" />
<xsl:apply-templates select="Test[@name='echoFloatArray']" />
<xsl:apply-templates select="Test[@name='echoStringArray']" />
<xsl:apply-templates select="Test[@name='echoStructArray']" />
</tr>
</xsl:for-each>
</table>
<P/>
<h3>Zero Length Array Tests</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoIntegerArray</th>
	<th bgcolor="teal">echoFloatArray</th>
	<th bgcolor="teal">echoStringArray</th>
	<th bgcolor="teal">echoStructArray</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoIntegerArray_ZeroLen']" />
<xsl:apply-templates select="Test[@name='echoFloatArray_ZeroLen']" />
<xsl:apply-templates select="Test[@name='echoStringArray_ZeroLen']" />
<xsl:apply-templates select="Test[@name='echoStructArray_ZeroLen']" />
</tr>
</xsl:for-each>
</table>
<h3>echoVoid and echoBoolean</h3>
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoVoid</th>
	<th bgcolor="teal">echoBoolean<br/>(true)</th>
	<th bgcolor="teal">echoBoolean<br/>(false)</th>
	<th bgcolor="teal">echoBoolean<br/>(junk)</th>
	<th bgcolor="teal">echoFloat<br/>(NaN)</th>
	<th bgcolor="teal">echoFloat<br/>(INF)</th>
	<th bgcolor="teal">echoFloat<br/>(-INF)</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoVoid']" />
<xsl:apply-templates select="Test[@name='echoBoolean_true']" />
<xsl:apply-templates select="Test[@name='echoBoolean_false']" />
<xsl:apply-templates select="Test[@name='echoBoolean_junk']" />
<xsl:apply-templates select="Test[@name='echoFloat_NaN']" />
<xsl:apply-templates select="Test[@name='echoFloat_INF']" />
<xsl:apply-templates select="Test[@name='echoFloat_negINF']" />
</tr>
</xsl:for-each>
</table>
<P/>
<h3>More Floating Point Tests</h3>
Try to break floats a bit more by trying 3.5e38 (single overflow),
1.8e308 (double overflow), 6.9e-46 (single underflow), and 2.4e-324
(double underflow).  Several servers handle double overflow but few
handle underflow.  And even fewer handler single precision
overflow/underflow.  Click <a href="http://babbage.cs.qc.edu/courses/cs341/IEEE-754references.html">here</a> for IEEE-754 references.
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoFloat<br/>(single overflow, 3.5e38)</th>
	<th bgcolor="teal">echoFloat<br/>(single underflow, 6.9e-46)</th>
	<th bgcolor="teal">echoFloat<br/>(double overflow, 1.8e308)</th>
	<th bgcolor="teal">echoFloat<br/>(double underflow, 2.4e-324)</th>
	<th bgcolor="teal">echoFloat<br/>(1234junk)</th>
	<th bgcolor="teal">echoFloat<br/>(1234 with whitespace)</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoFloat_SingleOverflow']" />
<xsl:apply-templates select="Test[@name='echoFloat_SingleUnderflow']" />
<xsl:apply-templates select="Test[@name='echoFloat_DoubleOverflow']" />
<xsl:apply-templates select="Test[@name='echoFloat_DoubleUnderflow']" />
<xsl:apply-templates select="Test[@name='echoFloat_Junk1']" />
<xsl:apply-templates select="Test[@name='echoFloat_Junk2']" />
</tr>
</xsl:for-each>
</table>
<h3>More Integer Tests</h3>
Again, trying to break things.  Here we send the most positive 32-bit
integer, most negative 32-bit integer, and two integers that should
cause overflow and underflow.
<table>
<tr>
	<th></th>
	<th bgcolor="teal">echoInteger<br/>(2147483647)</th>
	<th bgcolor="teal">echoInteger<br/>(-2147483648)</th>
	<th bgcolor="teal">echoInteger<br/>(2147483648, overflow)</th>
	<th bgcolor="teal">echoInteger<br/>(-2147483649, underflow)</th>
	<th bgcolor="teal">echoInteger<br/>(1234junk)</th>
	<th bgcolor="teal">echoInteger<br/>(1234 with whitespace)</th>
</tr>
<xsl:for-each select="InteropTests/Server">
<tr>
<xsl:apply-templates select="." />
<xsl:apply-templates select="Test[@name='echoInteger_MostPositive']" />
<xsl:apply-templates select="Test[@name='echoInteger_MostNegative']" />
<xsl:apply-templates select="Test[@name='echoInteger_Overflow']" />
<xsl:apply-templates select="Test[@name='echoInteger_Underflow']" />
<xsl:apply-templates select="Test[@name='echoInteger_Junk1']" />
<xsl:apply-templates select="Test[@name='echoInteger_Junk2']" />
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
