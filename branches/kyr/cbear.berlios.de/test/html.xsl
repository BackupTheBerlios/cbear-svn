<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:T="http://cbear.berlios.de/test"
	xmlns="http://www.w3.org/1999/xhtml">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	encoding="utf-8"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:template match="T:compiler">
	<td>
		<xsl:for-each select="T:command">
			<p>
				<xsl:if test="T:error/@level!=0">
					<xsl:attribute name="class">error</xsl:attribute>
				</xsl:if>
				<xsl:value-of select="T:error/@level"/>
				<pre>
					<xsl:value-of select="T:output"/>
				</pre>
			</p>
		</xsl:for-each>
	</td>
</xsl:template>

<xsl:template match="T:file">
	<tr>
		<td><xsl:value-of select="concat($dir, @name)"/></td>
		<xsl:apply-templates select="T:compiler"/>
	</tr>
</xsl:template>

<xsl:template match="T:dir">
	<xsl:apply-templates select="T:*"/>
</xsl:template>

<xsl:template match="/T:report">
	<html>
		<head>
			<style type="text/css">
td
{
	border-style: solid;
	border-width: 1px; 
	border-color: black;
}
.error
{
	color: red;
}
			</style>
		</head>
		<body>
			<table>
				<tr>
					<td>File</td>
					<td>GCC</td>
					<td>VC</td>
					<td>DMC</td>
				</tr>
				<xsl:apply-templates select="T:*"/>
			</table>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
