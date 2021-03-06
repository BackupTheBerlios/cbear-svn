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
	xmlns:B="http://cbear.berlios.de/bat"
	xmlns="http://www.w3.org/1999/xhtml">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	encoding="utf-8"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:template match="*" mode="B:id">
	<xsl:value-of select="concat('n', count(preceding::*|ancestor::*))"/>
</xsl:template>

<xsl:template match="B:command">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<xsl:variable name="class">
		<xsl:if test="B:errorlevel/@value!=0">
			<xsl:text>error</xsl:text>
		</xsl:if>
	</xsl:variable>
	<div id="{$id}" class="{$class}">
		<h2><xsl:value-of select="@name"/></h2>
		<div>
			<h4>Command</h4>
			<pre><xsl:value-of select="@text"/></pre>
		</div>
		<div>
			<h4>Output</h4>
			<pre><xsl:value-of select="B:output"/></pre>
		</div>
		<div>
			<h4>Errorlevel</h4>
			<pre><xsl:value-of select="B:errorlevel/@value"/></pre>
		</div>
	</div>
</xsl:template>

<xsl:template match="B:bat">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<div id="{$id}">
		<h2><xsl:value-of select="@name"/></h2>
		<xsl:apply-templates select="*"/>
	</div>
</xsl:template>

<xsl:template match="B:command" mode="B:content.table">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<xsl:variable name="class">
		<xsl:if test="B:errorlevel/@value!=0">
			<xsl:text>error</xsl:text>
		</xsl:if>
	</xsl:variable>
	<li>
		<a href="{concat('#', $id)}" class="{$class}"><xsl:value-of select="@name"/></a>
	</li>
</xsl:template>

<xsl:template match="B:bat" mode="B:content.table">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<li>
		<a href="{concat('#', $id)}"><xsl:value-of select="@name"/></a>
		<xsl:if test="*">
			<ul>
				<xsl:apply-templates select="*" mode="B:content.table"/>
			</ul>
		</xsl:if>
	</li>
</xsl:template>

<xsl:template match="/B:bat">
	<html>
		<head>
			<style type="text/css">
div
{
	border-style: solid;
	border-width: 1px; 
	border-color: gray;	

	margin: 5px 5px 5px 5px;
}
.error
{
	color: red;
}
a { color: blue; }
			</style>
			<title><xsl:value-of select="@name"/></title>
		</head>
		<body>
			<ul>
				<xsl:apply-templates select="*" mode="B:content.table"/>
			</ul>
			<xsl:apply-templates select="*"/>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
