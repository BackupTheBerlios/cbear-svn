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
	xmlns:odl="http://cbear.sourceforge.net/com"
	exclude-result-prefixes="xi odl">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	indent="no"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>
	
<!-- * -->

<xsl:template match="*" mode="odl:html.a">
	<a href="{concat('#', @id)}">
		<xsl:apply-templates select="." mode="odl:html.title"/>
		<xsl:value-of select="@id"/>
	</a>
</xsl:template>

<xsl:template match="*" mode="odl:html.content.table">
	<li>
		<a href="{concat('#', @id)}">
			<xsl:apply-templates select="." mode="odl:html.title"/>
			<xsl:apply-templates select="." mode="odl:html.id"/>
		</a>
	</li>
</xsl:template>

<xsl:template match="*" mode="odl:html.id">
	<xsl:value-of select="concat(local-name(), ' ', @id)"/>
</xsl:template>

<xsl:template match="*" mode="odl:html.name">
	<span class="keyword"><xsl:value-of select="local-name()"/></span>
	<xsl:text> </xsl:text>
	<span class="id"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="*" mode="odl:html.title">
	<xsl:for-each select="odl:attribute[@id='helpstring']">
		<xsl:attribute name="title">
			<xsl:value-of select="substring(@value, 2, string-length(@value) - 2)"/>
		</xsl:attribute>
	</xsl:for-each>
</xsl:template>

<xsl:template match="*" mode="odl:html.intro"/>

<xsl:template match="*" mode="odl:html.header">
	<xsl:for-each select="odl:comment">
		<div class="comment"><xsl:copy-of select="*|text()"/></div>
	</xsl:for-each>
</xsl:template>

<xsl:template match="*" mode="odl:html.content">
	<div id="{concat(../@id, '.', @id)}" class="h3">
		<h3><xsl:apply-templates select="." mode="odl:html.name"/></h3>
		<xsl:apply-templates select="." mode="odl:html.header"/>
	</div>
</xsl:template>

<xsl:template match="*" mode="odl:html">
	<div id="{@id}" class="h2">
		<h2><xsl:apply-templates select="." mode="odl:html.name"/></h2>
		<xsl:apply-templates select="." mode="odl:html.header"/>
		<xsl:apply-templates select="*" mode="odl:html.content"/>
	</div>
</xsl:template>

<!-- comment -->

<xsl:template match="odl:comment" mode="odl:html.content.table"/>

<xsl:template match="odl:comment" mode="odl:html.content"/>

<xsl:template match="odl:comment" mode="odl:html"/>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:html.content.table"/>

<!--
<xsl:template match="odl:attribute" mode="odl:html.intro">
	<tr>
		<td class="id"><xsl:value-of select="@id"/></td>
		<td class="const"><xsl:value-of select="@value"/></td>
	</tr> 
</xsl:template>
-->

<xsl:template match="odl:attribute" mode="odl:html.content"/>

<xsl:template match="odl:attribute" mode="odl:html"/>

<xsl:template match="odl:attribute" mode="odl:html.parameter.base">
	<span class="keyword"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:html.parameter">
	<xsl:apply-templates select="." mode="odl:html.parameter.base"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template 
	match="odl:attribute[position()=last()]" mode="odl:html.parameter">
	<xsl:apply-templates select="." mode="odl:html.parameter.base"/>
</xsl:template>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:html.content.table"/>

<xsl:template match="odl:importlib" mode="odl:html"/>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:html.a">
	<xsl:variable name="id" select="@id"/>
	<xsl:choose>
		<xsl:when test="/odl:library/odl:interface[@id=$id]">
			<xsl:apply-templates 
				select="/odl:library/odl:interface[@id=$id]" mode="odl:html.a"/>
		</xsl:when>
		<xsl:otherwise>
			<span class="id"><xsl:value-of select="@id"/></span>
		</xsl:otherwise>
	</xsl:choose>
	<xsl:if test="odl:type.ref">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
		<xsl:text>)</xsl:text>
	</xsl:if>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:html.a">
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<xsl:template match="odl:type.ref" mode="odl:html.content"/>

<!-- item -->

<xsl:template match="odl:item" mode="odl:html.name">
	<span class="id"><xsl:value-of select="@id"/></span>
	<xsl:text> = </xsl:text>
	<span class="const"><xsl:value-of select="odl:const/@value"/></span>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:html.id">
	<xsl:apply-templates select="*" mode="odl:html.id"/>
</xsl:template>

<xsl:template match="odl:typedef" mode="odl:html.title">
	<xsl:apply-templates select="*" mode="odl:html.title"/>
</xsl:template>

<xsl:template match="odl:typedef" mode="odl:html">
	<xsl:apply-templates select="*" mode="odl:html"/>
</xsl:template>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:html.name.base">
	<xsl:text>[</xsl:text>
	<xsl:apply-templates select="odl:attribute" mode="odl:html.parameter"/>
	<xsl:text>]</xsl:text>
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:html.name">
	<xsl:param name="number"/>
	<xsl:apply-templates select="." mode="odl:html.name.base"/>
	<xsl:if test="position() &lt; $number">
		<xsl:text>, </xsl:text>
	</xsl:if>
</xsl:template>

<!-- method -->

<xsl:template match="odl:method" mode="odl:html.name.header">
	<xsl:for-each select="odl:parameter[odl:attribute/@id='retval']">
		<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
		<xsl:text> </xsl:text>
	</xsl:for-each>
	<span class="id"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:method" mode="odl:html.name">
	<xsl:apply-templates select="." mode="odl:html.name.header"/>
	<xsl:variable 
		name="number" 
		select="
			count(odl:parameter) - count(odl:parameter/odl:attribute[@id='retval'])"/>
	<xsl:text>(</xsl:text>
	<xsl:apply-templates 
		select="odl:parameter[position()&lt;=$number]" mode="odl:html.name">
		<xsl:with-param name="number" select="$number"/>
	</xsl:apply-templates>
	<xsl:text>)</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:html.name">
	<xsl:text>[</xsl:text>
	<span class="keyword">propget</span>
	<xsl:text>] </xsl:text>
	<xsl:apply-templates select="." mode="odl:html.name.header"/>
	
	<xsl:variable name="number" select="count(odl:parameter) - 1"/>
	<xsl:if test="$number &gt;= 1">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates 
			select="odl:parameter[position()&lt;=$number]" mode="odl:html.name">
			<xsl:with-param name="number" select="$number"/>
		</xsl:apply-templates>		
		<xsl:text>)</xsl:text>
	</xsl:if>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:html.name">
	<xsl:text>[</xsl:text>
	<span class="keyword">propput</span>
	<xsl:text>] </xsl:text>
	<xsl:apply-templates 
		select="odl:parameter[position()=last()]/odl:type.ref" mode="odl:html.a"/>
	<xsl:text> </xsl:text>
	<span class="id"><xsl:value-of select="@id"/></span>
	
	<xsl:variable name="number" select="count(odl:parameter) - 1"/>
	<xsl:if test="$number &gt;= 1">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates 
			select="odl:parameter[position()&lt;=$number]" mode="odl:html.name">
			<xsl:with-param name="number" select="$number"/>
		</xsl:apply-templates>		
		<xsl:text>)</xsl:text>
	</xsl:if>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:html.name">
	<span class="keyword">interface</span>
	<xsl:text> </xsl:text>
	<span class="id"><xsl:value-of select="@id"/></span>
	<xsl:text>: </xsl:text>
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<!-- library -->

<xsl:template match="odl:library" mode="odl:html">
	<html>
		<head>
			<title>
				<xsl:apply-templates select="." mode="odl:html.id"/>
			</title>
			<style type="text/css">
body { font-family: monospace; }
div 
{ 
	padding: 3px 20px 3px 3px;
	margin: 3px 3px 3px 3px; 
}
.comment { font-family: sans-serif; font-style: italic; }
.h2 { border-top: solid 1px silver; }
a { text-decoration: none; color: blue; }
a:hover { text-decoration: underline; }
.error { color: red; }
table { border-collapse: collapse; }
th, td { padding: 3px 3px 3px 3px; border: solid 1px black; }
.keyword { color: black; }
.id { color: navy; }
.const { color: green; }
			</style>
		</head>
		<body>
			<h1><xsl:apply-templates select="." mode="odl:html.name"/></h1>
			<div class="h2">
				<h2>Table Of Contents</h2>
				<ul>
					<li><a href="#Introduction">Introduction</a></li>
					<xsl:apply-templates select="*" mode="odl:html.content.table"/>
				</ul>
			</div>
			<div id="Introduction" class="h2">
				<h2>Introduction</h2>
				<xsl:apply-templates select="." mode="odl:html.header"/>
			</div>
			<xsl:apply-templates select="*" mode="odl:html"/>
		</body>
	</html>
</xsl:template>
	
<!-- Entry Point -->
	
<xsl:template match="*">
	<xsl:apply-templates select="." mode="odl:html"/>
</xsl:template>

</xsl:stylesheet>
