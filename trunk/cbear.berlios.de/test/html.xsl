<?xml version="1.0" encoding="utf-8"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-->
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
		<xsl:value-of select="T:error/@level"/>
		<pre>
			<xsl:value-of select="T:text"/>
		</pre>
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
			</style>
		</head>
		<body>
			<table>
				<tr>
					<td>File</td>
					<td>GCC</td>
					<td>VC</td>
				</tr>
				<xsl:apply-templates select="T:*"/>
			</table>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
