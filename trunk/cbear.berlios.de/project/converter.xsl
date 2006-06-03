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
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns="http://cbear.berlios.de/project"
	xmlns:prj="http://cbear.berlios.de/project"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear.exslt.common="http://cbear.berlios.de/exslt/common"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="prj xi cbear.exslt.common">

<xsl:import href="../url/main.xsl"/>

<xsl:param name="prj:converter.xsl" select="'project/html.xsl'"/>

<xsl:template match="comment()" mode="prj:converter">
	<xsl:comment><xsl:value-of select="."/></xsl:comment>
</xsl:template>

<xsl:template match="@*" mode="prj:converter">
	<xsl:attribute name="{name()}"><xsl:value-of select="."/></xsl:attribute>
</xsl:template>

<xsl:template match="*" mode="prj:converter">
	<xsl:element 
		name="{local-name()}" namespace="http://cbear.berlios.de/project">
		<xsl:apply-templates select="@*" mode="prj:converter"/>
		<xsl:apply-templates mode="prj:converter"/>
	</xsl:element>
</xsl:template>

<xsl:template match="imagedata" mode="prj:converter">
	<img src="{@fileref}"/>
</xsl:template>

<xsl:template match="programlisting" mode="prj:converter">
	<pre><xsl:apply-templates mode="prj:converter"/></pre>
</xsl:template>

<xsl:template match="emphasis" mode="prj:converter">
	<em><xsl:value-of select="."/></em>
</xsl:template>

<xsl:template match="xi:include" mode="prj:converter">
	<xsl:param name="filename"/>
	<section href="{@href}"/>
	<xsl:variable name="path">
		<xsl:call-template name="url.path">
			<xsl:with-param name="path" select="$filename"/>
		</xsl:call-template>
	</xsl:variable>
	<xsl:apply-templates select="document(@href)/*" mode="prj:converter">
		<xsl:with-param name="filename" select="concat($path, @href)"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="listitem" mode="prj:converter">
	<li><xsl:apply-templates mode="prj:converter"/></li>
</xsl:template>

<xsl:template match="orderedlist" mode="prj:converter">
	<ol><xsl:apply-templates mode="prj:converter"/></ol>
</xsl:template>

<xsl:template match="itemizedlist" mode="prj:converter">
	<ul><xsl:apply-templates mode="prj:converter"/></ul>
</xsl:template>

<xsl:template match="filename" mode="prj:converter">
	<a href="{.}"/>
</xsl:template>

<xsl:template match="ulink" mode="prj:converter">
	<a href="{@url}"><xsl:apply-templates mode="prj:converter"/></a>
</xsl:template>

<xsl:template match="para" mode="prj:converter">
	<p><xsl:apply-templates mode="prj:converter"/></p>
</xsl:template>

<xsl:template match="title" mode="prj:converter"/>

<xsl:template match="comment()" mode="prj:converter.section">
	<xsl:apply-templates select="." mode="prj:converter"/>
</xsl:template>

<xsl:template match="section" mode="prj:converter.section">
	<xsl:param name="filename"/>
	<section name="{title}">
		<xsl:apply-templates mode="prj:converter">
			<xsl:with-param name="filename" select="$filename"/>
		</xsl:apply-templates>
	</section>
</xsl:template>

<xsl:template match="section" mode="prj:converter">
	<xsl:param name="filename"/>
	<xsl:apply-templates select="." mode="prj:converter.section">
		<xsl:with-param name="filename" select="$filename"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="/section" mode="prj:converter">
	<xsl:param name="filename" select="'index.xml'"/>
	<exsl:document
		href="{$filename}"
		encoding="utf-8"
		method="xml">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:text>type="text/xsl" href="</xsl:text>
			<xsl:call-template name="url.backpath">
				<xsl:with-param name="path" select="$filename"/>
			</xsl:call-template>
			<xsl:value-of select="concat($prj:converter.xsl, '&#x22;')"/>
		</xsl:processing-instruction>
		<xsl:for-each select="/">
			<xsl:apply-templates mode="prj:converter.section">
				<xsl:with-param name="filename" select="$filename"/>
			</xsl:apply-templates>
		</xsl:for-each>
	</exsl:document>
</xsl:template>

<xsl:template match="*">
	<xsl:apply-templates select="." mode="prj:converter"/>
</xsl:template>

</xsl:stylesheet>
