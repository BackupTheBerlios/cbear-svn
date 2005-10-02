<?xml version="1.0"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
	xmlns:cbear.docbook="http://cbear.sourceforge.net/docbook"
	exclude-result-prefixes="xi cbear.docbook">

<xsl:param name="docbook.html.top"/>
<xsl:param name="docbook.html.up"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<!-- Error, element -->
<xsl:template match="*" mode="docbook.html">
	<span class="error">
		<xsl:value-of select="concat('&lt;', name(), '&gt;')"/>
		<xsl:apply-templates select="*|text()" mode="docbook.html"/>
		<xsl:value-of select="concat('&lt;/', name(), '&gt;')"/>
	</span>
</xsl:template>

<!-- Section Id -->
<xsl:template match="*" mode="docbook.html.id">
	<xsl:value-of select="concat('section-', count(preceding::*))"/>
</xsl:template>

<!-- Lists -->

<xsl:template match="listitem" mode="docbook.html">
	<li><xsl:apply-templates mode="docbook.html"/></li>
</xsl:template>

<xsl:template match="orderedlist" mode="docbook.html">
	<ol><xsl:apply-templates mode="docbook.html"/></ol>
</xsl:template>

<xsl:template match="itemizedlist" mode="docbook.html">
	<ul><xsl:apply-templates mode="docbook.html"/></ul>
</xsl:template>

<!-- File -->
<xsl:template match="filename" mode="docbook.html">
	<a href="{.}" class="filename"><xsl:value-of select="."/></a>
</xsl:template>

<!-- Link -->
<xsl:template match="ulink" mode="docbook.html">
	<a href="{@url}" class="ulink">
		<xsl:apply-templates select="text()|*" mode="docbook.html"/>
	</a>
</xsl:template>

<!-- Emphasis -->
<xsl:template match="emphasis" mode="docbook.html">
	<em class="emphasis"><xsl:apply-templates mode="docbook.html"/></em>
</xsl:template>

<!-- Literal Layout -->
<xsl:template match="literallayout" mode="docbook.html">
	<table class="literallayout">
		<tbody class="literallayout">
			<tr class="literallayout">
				<td class="literallayout">
					<pre class="literallayout">
						<xsl:apply-templates mode="docbook.html"/>
					</pre>
				</td>
			</tr>
		</tbody>
	</table>
</xsl:template>

<!-- Attribution -->
<xsl:template match="attribution" mode="docbook.html">
	<div class="attribution">
		<xsl:apply-templates mode="docbook.html"/>
	</div>
</xsl:template>

<!-- Epigraph -->
<xsl:template match="epigraph" mode="docbook.html">
	<div class="epigraph">
		<xsl:apply-templates select="literallayout" mode="docbook.html"/>
		<xsl:apply-templates select="attribution" mode="docbook.html"/>
	</div>
</xsl:template>

<!-- Block Quote -->
<xsl:template match="blockquote" mode="docbook.html">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="docbook.html.id"/>
	</xsl:variable>
	<div class="blockquote" id="{$id}">
		<xsl:apply-templates select="." mode="docbook.html.title"/>
		<xsl:apply-templates select="epigraph" mode="docbook.html"/>
		<div class="literallayout">
			<xsl:apply-templates select="literallayout" mode="docbook.html"/>
		</div>
		<xsl:apply-templates select="attribution" mode="docbook.html"/>
	</div>
</xsl:template>

<!-- Image -->
<xsl:template match="imagedata" mode="docbook.html">
	<img src="{@fileref}" height="{@height}" width="{@width}"/>
</xsl:template>

<!-- Paragraph -->
<xsl:template match="para" mode="docbook.html">
	<p class="para"><xsl:apply-templates mode="docbook.html"/></p>
</xsl:template>

<!-- Title -->
<xsl:template match="*" mode="docbook.html.title">
	<xsl:param name="title" select="string(title)"/>
	<xsl:if test="$title=''">
		<span class="error">No Title</span>
	</xsl:if>
	<xsl:element name="{concat('h', count(ancestor::*) + 1)}">
		<xsl:attribute name="class">title</xsl:attribute>
		<xsl:copy-of select="$title"/>
	</xsl:element>
</xsl:template>

<!-- Include, Name -->
<xsl:template match="xi:include" mode="docbook.html.name">
	<xsl:value-of select="substring(@href, 1, string-length(@href) - 4)"/>
</xsl:template>

<!-- Include, Reference -->
<xsl:template match="xi:include" mode="docbook.html.href">
	<xsl:value-of select="@href"/>
</xsl:template>

<!-- Title Stub -->
<xsl:template match="title" mode="docbook.html"/>

<!-- Section Info Stub -->
<xsl:template match="sectioninfo" mode="docbook.html"/>

<!-- Table Of Contents, Item, * -->
<xsl:template match="*" mode="docbook.html.contents.item"/>

<!-- Table Of Contents, Item, Section -->
<xsl:template match="section|blockquote" mode="docbook.html.contents.item">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="docbook.html.id"/>
	</xsl:variable>
	<li class="section-contents-table">
		<a href="{concat('#', $id)}"><xsl:value-of select="title"/></a>
		<xsl:if test="section or blockquote or xi:include">
			<ul class="section-contents-table">
				<xsl:apply-templates select="*" mode="docbook.html.contents.item"/>				
			</ul>
		</xsl:if>
	</li>
</xsl:template>

<!-- Table Of Contents, Item, Include -->
<xsl:template match="xi:include" mode="docbook.html.contents.item">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="docbook.html.id"/>
	</xsl:variable>
	<xsl:variable name="href">
		<xsl:apply-templates select="." mode="docbook.html.href"/>
	</xsl:variable>
	<li class="section-contents-table">
		<a href="{$href}"><xsl:value-of select="document(@href)/section/title"/></a>
	</li>
</xsl:template>

<!-- Program Listing -->
<xsl:template match="programlisting" mode="docbook.html">
	<pre class="programlisting"><xsl:apply-templates select="text()|*"/></pre>
</xsl:template>

<!-- Section -->
<xsl:template match="section" mode="docbook.html">
	<xsl:param name="table-of-contents"/>
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="docbook.html.id"/>
	</xsl:variable>
	<div class="section" id="{$id}">
		<xsl:apply-templates select="." mode="docbook.html.title"/>
		<xsl:for-each select="sectioninfo">
			<div class="sectioninfo">
				<xsl:apply-templates select="*" mode="docbook.html"/>
			</div>
		</xsl:for-each>
		<div class="section-contents">
			<xsl:if test="(.=/) and (section or blockquote or xi:include)">
				<div class="section-contents-table">
					<xsl:if test="$table-of-contents">
						<div class="title"><xsl:value-of select="$table-of-contents"/></div>
					</xsl:if>
					<ul class="section-contents-table">
						<xsl:apply-templates select="*" mode="docbook.html.contents.item"/>
					</ul>
				</div>
			</xsl:if>
			<xsl:apply-templates mode="docbook.html"/>
		</div>
	</div>
</xsl:template>

<!-- Include -->
<!-- <xsl:template match="xi:include" mode="docbook.html"/> -->
<xsl:template match="xi:include" mode="docbook.html">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="docbook.html.id"/>
	</xsl:variable>
	<div class="xi-include" id="{$id}">
		<xsl:apply-templates select="." mode="docbook.html.title">
			<xsl:with-param name="title">
				<xsl:variable name="href">
					<xsl:apply-templates select="." mode="docbook.html.href"/>
				</xsl:variable>
				<a href="{$href}">
					<xsl:value-of select="document(@href)/section/title"/>
				</a>
			</xsl:with-param>
		</xsl:apply-templates>
	</div>
</xsl:template>

<!-- Navigation -->
<xsl:template match="section" mode="docbook.html.navigation">
	<xsl:param name="top" select="$docbook.html.top"/>
	<xsl:param name="up" select="$docbook.html.up"/>
	<xsl:if test="$top or $up">
		<table class="navigation">
			<tbody>
				<tr>
					<xsl:if test="$top">
						<td><a href="{$top}">Top</a></td>
					</xsl:if>
					<xsl:if test="$up">
						<td><a href="{$up}">Up</a></td>
					</xsl:if>
				</tr>	
			</tbody>
		</table>
	</xsl:if>
</xsl:template>

<xsl:template name="cbear.docbook:footer">
	<div class="footer">
		<a href="http://cbear.sourceforge.net/">
			<img
				src="http://cbear.sourceforge.net/logo.png"
				alt="C Bear Framework"
				height="31"
				width="88"/>
		</a>
		<xsl:text> </xsl:text>
		<a href="http://validator.w3.org/check?uri=referer">
			<img
 	     	src="http://www.w3.org/Icons/valid-xhtml11"
        alt="Valid XHTML 1.1" 
				height="31" 
				width="88" />
		</a>
		<xsl:text> </xsl:text>
		<a href="http://jigsaw.w3.org/css-validator/check/referer">
		  <img 
				style="border:0;width:88px;height:31px"
				src="http://jigsaw.w3.org/css-validator/images/vcss" 
				alt="Valid CSS!" />
		</a>
	</div>
</xsl:template>

<xsl:template name="cbear.docbook:style"/>

<xsl:template name="cbear.docbook:additional"/>

<xsl:template name="cbear.docbook:body">
	<xsl:param name="content"/>
	<xsl:copy-of select="$content"/>
</xsl:template>

<!-- Root Section -->
<xsl:template match="/section" mode="docbook.html.root">
	<xsl:param name="top" select="$docbook.html.top"/>
	<xsl:param name="up" select="$docbook.html.up"/>
	<xsl:param name="header"/>
	<xsl:param name="style"/>
	<xsl:param name="table-of-contents" select="'Table Of Contents'"/>
<xsl:comment>
The file is generated by http://cbear.sourceforge.net/docbook/html.xsl
</xsl:comment>
	<html>
		<head>
			<title><xsl:value-of select="title"/></title>
			<style type="text/css">
body { background-color: white; font-family: sans-serif; font-size: 10pt; }
span.error { background-color: yellow; color: red; }
em.emphasis { font-style: normal; font-weight: bold; }
.title
{ 
	font-weight: bold; 
	color: #404080; 
	background-color: #F0F0FF; 
	padding: 5px 5px 5px 5px;
	margin: 0px 0px 0px 0px;
}
.blockquote .title { text-align: center; background-color: white; }
h1 { font-size: 18pt; }
h2 { font-size: 17pt; }
h3 { font-size: 16pt; }
h4 { font-size: 15pt; }
h5 { font-size: 14pt; }
h6 { font-size: 13pt; }
h7 { font-size: 12pt; }
h8 { font-size: 11pt; }
h9 { font-size: 10pt; }
a { color: blue; text-decoration: none; font-weight: bold; }
a:hover { text-decoration: underline; }
div, pre
{
	background-color: white; /* Because Of Internet Explorer */

	border-width: 1px; 
	border-color: #C0C0FF;

	padding: 0px 0px 0px 0px;
	margin: 5px 1px 1px 5px;
}
div.section, div.xi-include
{ 
	border-style: solid; 
}
div.blockquote
{
	border-top-style: solid; 
}
div.section-contents
{
	padding: 5px 1px 1px 5px;
}
div.sectioninfo
{
	padding: 0px 20px 0px 20px;
}
div.section-contents-table
{
	background-color: #F0F0FF;

	border-style: solid; 

	padding: 5px 5px 5px 5px;
}
ul.section-contents-table
{
	padding: 0 0 0 10px;
	margin: 0 0 0 10px;

	list-style: disc;
}
div.literallayout
{
	text-align: center;
}
table.literallayout
{
	margin: 0 auto 0 auto;
}
td.literallayout
{
	text-align: left;
}
pre.literallayout
{
	font-family: sans-serif;
}
div.attribution
{
	text-align: right;
}
img { border-style: none; }
pre.programlisting { border-style: solid; 	background-color: #F0F0FF; }
div.epigraph { 	text-align: right; font-style: italic; }
div.epigraph table.literallayout
{
	margin: 0 0 0 auto;
}
div.main { margin: 0 0 0 0; padding: 0 0 0 0; }
<xsl:call-template name="cbear.docbook:style"/>
			</style>
		</head>
		<body>
			<xsl:call-template name="cbear.docbook:body">
				<xsl:with-param name="content">
				<div class="main">
						<xsl:if test="$header">
							<div class="header"><xsl:copy-of select="$header"/></div>
						</xsl:if>
						<xsl:apply-templates select="." mode="docbook.html.navigation">
							<xsl:with-param name="top" select="$top"/>
							<xsl:with-param name="up" select="$up"/>
						</xsl:apply-templates>
						<xsl:apply-templates select="." mode="docbook.html">
							<xsl:with-param name="table-of-contents" select="$table-of-contents"/>
						</xsl:apply-templates>
						<xsl:call-template name="cbear.docbook:footer"/>	
					</div>
				</xsl:with-param>
			</xsl:call-template>
		</body>
	</html>
</xsl:template>

<!-- Default Root Template -->
<xsl:template match="/section">
	<xsl:apply-templates select="." mode="docbook.html.root"/>	
</xsl:template>

</xsl:stylesheet>
