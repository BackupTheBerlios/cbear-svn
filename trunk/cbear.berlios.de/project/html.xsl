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
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:prj="http://cbear.berlios.de/project"
	xmlns:cbear.html="http://cbear.berlios.de/html"
	exclude-result-prefixes="prj xi">

<xsl:import href="../url/main.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	encoding="utf-8"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:param name="prj:html.style">
body
{
  background-color: #CCCCCC;

	font-family: sans-serif;
	font-size: 10pt;
	margin-left: 0px;
	margin-right: 0px;
	margin-top: 0px;
	margin-bottom: 0px;

	padding-left: 0px;
	padding-right: 0px;
	padding-top: 0px;
	padding-bottom: 0px;
}
h1 { font-size: 18pt; }
h2 { font-size: 17pt; }
h3 { font-size: 16pt; }
h4 { font-size: 15pt; }
h5 { font-size: 14pt; }
h6 { font-size: 13pt; }
h7 { font-size: 12pt; }
h8 { font-size: 11pt; }
h9 { font-size: 10pt; }
a 
{ 
	color: blue; 
	text-decoration: none; 
}
a:hover { text-decoration: underline; }
div
{
	background-color: white;

	border-color: #D0D0D0;
	border-width: 1px;
	border-style: solid;

	margin-left: 5px;
	margin-right: 5px;
	margin-top: 5px;
	margin-bottom: 5px;

	padding-left: 5px;
	padding-right: 5px;
	padding-top: 5px;
	padding-bottom: 5px;
}
h1, h2, h3, h4, h5, h6, h7, h8, h9
{ 
	color: navy; 

	margin-left: 2px;
	margin-right: 2px;
	margin-top: 2px;
	margin-bottom: 2px;

	padding-left: 2px;
	padding-right: 2px;
	padding-top: 2px;
	padding-bottom: 2px;
}
ul { list-style: disc; }
pre 
{ 
	background-color: #F0F0F0;
	border-left: solid 1px; 
	border-color: #D0D0D0;

	padding: 5px 5px 5px 5px;
}
.background
{
	margin: 0 0 0 0;
	border: 0;
	background-color: #CCCCCC;
}
</xsl:param>

<!-- * -->

<xsl:template match="prj:*" mode="prj:html.content.table.item"/>

<xsl:template match="prj:*" mode="prj:html">
	<xsl:element name="{local-name()}">
		<xsl:apply-templates mode="prj:html"/>
	</xsl:element>
</xsl:template>

<xsl:template match="prj:*" mode="prj:html.id">
	<xsl:value-of select="translate(@name, ' ,()+', '_____')"/>
</xsl:template>

<!-- a -->

<xsl:template match="prj:a[.='']" mode="prj:html.a">
	<xsl:value-of select="@href"/>
</xsl:template>

<xsl:template match="prj:a" mode="prj:html">
	<a href="{@href}"><xsl:apply-templates select="." mode="prj:html.a"/></a>
</xsl:template>

<!-- section -->

<xsl:template match="prj:section" mode="prj:html.link">
	<a href="{@href}">
		<xsl:value-of select="document(@href, .)/prj:section/
			@name"/>
	</a>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.content.table.item">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="prj:html.id"/>
	</xsl:variable>
	<li>
		<a href="{concat('#', $id)}"><xsl:value-of select="@name"/></a>
		<xsl:apply-templates select="." mode="prj:html.content.table"/>
	</li> 
</xsl:template>

<xsl:template match="prj:section[@href]" mode="prj:html.content.table.item">
	<li><xsl:apply-templates select="." mode="prj:html.link"/></li>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.content.table"/>

<xsl:template match="prj:section[prj:section]" mode="prj:html.content.table">
	<ul><xsl:apply-templates mode="prj:html.content.table.item"/></ul>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.history.search.start">
	<xsl:param name="name"/>
	<xsl:param name="filename"/>
	<xsl:apply-templates select="prj:section" mode="prj:html.history.search">
		<xsl:with-param name="name" select="$name"/>
		<xsl:with-param name="content">
			<a href="{$filename}"><xsl:value-of select="@name"/></a>
		</xsl:with-param>
		<xsl:with-param name="filename" select="$filename"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.history.search">
	<xsl:param name="name"/>
	<xsl:param name="filename"/>
	<xsl:apply-templates select="." mode="prj:html.history.search.start">
		<xsl:with-param name="name" select="$name"/>
		<xsl:with-param name="filename" select="$filename"/>
	</xsl:apply-templates>	
</xsl:template>

<xsl:template match="/prj:section" mode="prj:html.history.search">
	<xsl:param name="name"/>
	<xsl:param name="filename"/>
	<xsl:param name="content"/>
	<xsl:choose>
		<xsl:when test="@name=$name">
			<xsl:copy-of select="$content"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:apply-templates select="." mode="prj:html.history.search.start">
				<xsl:with-param name="name" select="$name"/>
				<xsl:with-param name="filename" select="$filename"/>
			</xsl:apply-templates>	
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="prj:section[@href]" mode="prj:html.history.search">
	<xsl:param name="name"/>
	<xsl:param name="filename"/>
	<xsl:param name="content"/>
	<xsl:apply-templates 
		select="document(@href, .)/prj:section"
		mode="prj:html.history.search">
		<xsl:with-param name="name" select="$name"/>
		<xsl:with-param name="filename">
			<xsl:call-template name="url.path">
				<xsl:with-param name="path" select="$filename"/>
			</xsl:call-template>
			<xsl:value-of select="@href"/>
		</xsl:with-param>
		<xsl:with-param name="content" select="$content"/>		
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.history.index">
	<xsl:param name="name"/>
	<xsl:param name="filename"/>
	<xsl:choose>
		<xsl:when test="$name=@name">
			<xsl:apply-templates 
				select="document('../index.xml', .)/prj:section" 
				mode="prj:html.history.index">
				<xsl:with-param name="name" select="$name"/>
				<xsl:with-param name="filename">
					<xsl:call-template name="url.path">
						<xsl:with-param name="filename"/>
					</xsl:call-template>
					<xsl:value-of select="'../index.xml.xml'"/>
				</xsl:with-param>
			</xsl:apply-templates>
		</xsl:when>
		<xsl:otherwise>
			<xsl:apply-templates select="." mode="prj:html.history.search.start">
				<xsl:with-param name="name" select="$name"/>
				<xsl:with-param name="filename" select="$filename"/>
			</xsl:apply-templates>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.history">
	<ul>
		<xsl:apply-templates 
			select="document('index.xml', .)/prj:section" 
			mode="prj:html.history.index">
			<xsl:with-param name="name" select="@name"/>
			<xsl:with-param name="filename" select="'index.xml'"/>
		</xsl:apply-templates>
	</ul>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="prj:html.id"/>
	</xsl:variable>
	<div id="{$id}">
		<h2><xsl:value-of select="@name"/></h2>
		<xsl:apply-templates mode="prj:html"/>
	</div>
</xsl:template>

<xsl:template match="prj:section[@href]" mode="prj:html">
	<div><h2><xsl:apply-templates select="." mode="prj:html.link"/></h2></div>
</xsl:template>

<xsl:template match="*" mode="prj:html.top"/>

<xsl:template match="*" mode="prj:html.bottom"/>

<xsl:template match="/prj:section" mode="prj:html">
	<html>
		<head>
			<title><xsl:value-of select="@name"/></title>
			<style type="text/css"><xsl:copy-of select="$prj:html.style"/></style>
		</head>
		<body>
			<xsl:variable name="id">
				<xsl:apply-templates select="." mode="prj:html.id"/>
			</xsl:variable>
			<div class="background">
				<xsl:apply-templates select="." mode="prj:html.top"/>
				<xsl:apply-templates select="." mode="prj:html.history"/>
				<div id="{$id}">
					<h1><xsl:value-of select="@name"/></h1>
					<xsl:apply-templates select="." mode="prj:html.content.table"/>
					<xsl:apply-templates mode="prj:html"/>
				</div>
				<xsl:apply-templates select="." mode="prj:html.bottom"/>
			</div>
		</body>
	</html>
</xsl:template>

<!-- Entry Point -->
<xsl:template match="prj:*">
	<xsl:apply-templates select="." mode="prj:html"/>
</xsl:template>

</xsl:stylesheet>
