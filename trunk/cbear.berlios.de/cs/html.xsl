<?xml version="1.0"?>
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
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:cs="http://cbear.berlios.de/cs"
	xmlns:txt="http://cbear.berlios.de/text"
	exclude-result-prefixes="cs txt xi">

<xsl:import href="../text/main.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<!-- Styles -->

<xsl:variable name="cs:html">
	border-style: solid;
	border-width: 1px;
	margin: 5px 5px 5px 5px;
</xsl:variable>

<xsl:variable name="cs:html.preprocessor">
	color: navy;
</xsl:variable>

<xsl:variable name="cs:html.keyword">
	color: green;
</xsl:variable>

<xsl:variable name="cs:html.id">
	color: blue;
</xsl:variable>

<xsl:variable name="cs:html.const">
	color: magenta;
</xsl:variable>

<!-- block -->

<xsl:template match="*" mode="cs:html.block">
	<xsl:param name="begin" select="'{'"/>
	<xsl:param name="end" select="'}'"/>
	<xsl:call-template name="txt:main.block">
		<xsl:with-param name="begin" select="$begin"/>
		<xsl:with-param name="end" select="$end"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="cs:html"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- * -->

<xsl:template match="*" mode="cs:html">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- attribute -->

<xsl:template match="cs:attribute" mode="cs:html"/>

<xsl:template match="cs:attribute" mode="cs:html.attribute">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:value-of select="'['"/>
			<xsl:if test="@id">
				<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
				<xsl:value-of select="': '"/>
			</xsl:if>
			<xsl:apply-templates select="*" mode="cs:html"/>
			<xsl:value-of select="']'"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- id.ref -->

<xsl:template match="cs:id.ref[@id]" mode="cs:html">
	<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="cs:id.ref[@value]" mode="cs:html">
	<span style="{$cs:html.const}"><xsl:value-of select="@value"/></span>
</xsl:template>

<xsl:template match="cs:id.ref" mode="cs:html.dot">
	<xsl:apply-templates select="." mode="cs:html"/>
	<xsl:value-of select="'.'"/>
</xsl:template>

<xsl:template match="cs:id.ref[last()]" mode="cs:html.dot">
	<xsl:apply-templates select="." mode="cs:html"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='.']" mode="cs:html">
	<xsl:apply-templates select="*" mode="cs:html.dot"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='()']" mode="cs:html">
	<xsl:apply-templates select="*[1]" mode="cs:html"/>
	<xsl:value-of select="'('"/>
	<xsl:apply-templates select="*[position()>1]" mode="cs:html"/>
	<xsl:value-of select="')'"/>
</xsl:template>

<!-- interface -->

<xsl:template match="cs:interface" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">interface</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- namespace -->

<xsl:template match="cs:namespace" mode="cs:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">namespace</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- unit -->

<xsl:template match="cs:unit" mode="txt:main.indent"/>

<xsl:template match="cs:unit" mode="cs:html.unit">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:apply-templates select="*" mode="cs:html"/>
</xsl:template>

<xsl:template match="cs:unit" mode="cs:html">
	<xsl:apply-templates select="." mode="cs:html.unit"/>	
</xsl:template>

<xsl:template match="/cs:unit" mode="cs:html">
	<html>
		<body><pre><xsl:apply-templates select="." mode="cs:html.unit"/></pre></body>
	</html>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="cs:*">
	<xsl:apply-templates select="." mode="cs:html"/>
</xsl:template>

</xsl:stylesheet>
