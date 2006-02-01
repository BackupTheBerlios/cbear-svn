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
	xmlns:api="http://cbear.berlios.de/api"
	exclude-result-prefixes="xi">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:template match="api:*" mode="api:html.id">
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>
</xsl:template>

<xsl:template match="api:*" mode="api:html.name">
	<xsl:value-of select="'The '"/>
	<xsl:apply-templates select="." mode="api:html.id"/>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="api:html.type"/>			
</xsl:template>
	
<xsl:template match="api:*" mode="api:html.body">
	<xsl:apply-templates select="api:*" mode="api:html"/>
</xsl:template>

<xsl:template match="api:*" mode="api:html.id">
	<xsl:value-of select="@id"/>
</xsl:template>
	
<xsl:template match="api:library/api:*/api:*" mode="api:html.id">
	<xsl:value-of select="concat(../@id, '.', @id)"/>
</xsl:template>	
	
<xsl:template match="api:*" mode="api:html">
	<xsl:variable name="class" select="concat('h', count(ancestor::*) + 1)"/>
	<div class="{$class}">
		<xsl:attribute name="id">
			<xsl:apply-templates select="." mode="api:html.id"/>
		</xsl:attribute>		
		<xsl:element name="{$class}">
			<xsl:apply-templates select="." mode="api:html.name"/>
		</xsl:element>
		<xsl:apply-templates select="." mode="api:html.body"/>
	</div>
</xsl:template>

<!-- * -->
	
<xsl:template match="api:*" mode="api:html.link.external">
	<a href="{concat(/api:library/@id,'.html#', @id)}">
		<xsl:value-of select="@id"/>
	</a>
</xsl:template>

<xsl:template match="api:*" mode="api:html.table">
	<xsl:attribute name="id">
		<xsl:apply-templates select="." mode="api:html.id"/>
	</xsl:attribute>
	<li>
		<a href="{concat('#', @id)}">
			<xsl:apply-templates select="." mode="api:html.name"/>
		</a>
	</li>
</xsl:template>
	
<xsl:template match="api:*" mode="api:html.link.id">
	<a href="{concat('#', @id)}">
		<xsl:value-of select="@id"/>
	</a>
</xsl:template>	

<!-- pragma -->

<xsl:template match="api:pragma" mode="api:html"/>	
	
<!-- comment -->

<xsl:template match="api:comment" mode="api:html.table"/>	

<xsl:template match="api:comment" mode="api:html">
	<div class="comment"><xsl:copy-of select="*|text()"/></div>
</xsl:template>

<!-- type.ref -->
	
<xsl:template match="api:type.ref" mode="api:html.link.id">
	<xsl:variable name="id" select="@id"/>
	<xsl:apply-templates 
		select="/api:library/api:*[@id=$id]" mode="api:html.link.id"/>
</xsl:template>

<xsl:template match="api:type.ref[@library]" mode="api:html.link.id">
	<xsl:variable name="library" select="@library"/>
	<xsl:variable name="id" select="@id"/>
	<xsl:apply-templates 
		select="document(/api:library/api:using[@id=$library]/@href)/api:library/api:*[@id=$id]"
		mode="api:html.link.external"/>
</xsl:template>

<xsl:template match="api:type.ref[@library='base']" mode="api:html.link.id">
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>	
</xsl:template>	
	
<xsl:template match="api:type.ref" mode="api:html.link">
	<xsl:apply-templates select="." mode="api:html.link.id"/>
	<xsl:if test="api:type.ref">
		<xsl:value-of select="'('"/>
		<xsl:for-each select="api:type.ref">
			<xsl:apply-templates select="." mode="api:html.link"/>
			<xsl:if test="position()!=last()">
				<xsl:value-of select="', '"/>
			</xsl:if>
		</xsl:for-each>
		<xsl:value-of select="')'"/>
	</xsl:if>
</xsl:template>
	
<xsl:template match="api:type.ref[@id='idispatch']" mode="api:html.link">
	<span class="id">
		<xsl:value-of select="'IDispatch'"/>
	</span>
</xsl:template>

<xsl:template match="api:type.ref[@id='vector']" mode="api:html.link">
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:value-of select="'[]'"/>
</xsl:template>		

<xsl:template match="api:type.ref[@id='array']" mode="api:html.link">
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:value-of select="'['"/>
	<span class="constant"><xsl:value-of select="api:const/@value"/></span>	
	<xsl:value-of select="']'"/>
</xsl:template>		
	
<xsl:template match="api:type.ref" mode="api:html.parent">
	<p>
		Parent is
		<xsl:apply-templates select="." mode="api:html.link"/>.
	</p>
</xsl:template>

<xsl:template match="api:type.ref" mode="api:html"/>	

<xsl:template match="api:interface/api:type.ref" mode="api:html">
	<xsl:apply-templates select="." mode="api:html.parent"/>
</xsl:template>
	
<xsl:template match="api:library/api:object/api:type.ref" mode="api:html">
	<xsl:apply-templates select="." mode="api:html.parent"/>
</xsl:template>

<!-- get, set -->
	
<xsl:template match="api:get|api:set" mode="api:html"/>

<xsl:template match="api:get|api:set" mode="api:html.name">
	<xsl:value-of select="' '"/>
	<span class="keyword">
		<xsl:value-of select="local-name()"/>
	</span>
</xsl:template>
	
<!-- in, out -->
	
<xsl:template match="api:in|api:out" mode="api:html.name">
	<span class="keyword">
		<xsl:value-of select="local-name()"/>
	</span>
	<xsl:value-of select="' '"/>	
</xsl:template>
	
<!-- parameter -->

<xsl:template match="api:parameter" mode="api:html.name">
	<xsl:apply-templates select="api:in|api:out" mode="api:html.name"/>
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:if test="position()!=last()">
		<xsl:value-of select="', '"/>
	</xsl:if>
</xsl:template>

<xsl:template match="api:parameter" mode="api:html"/>	

<!-- property -->
	
<xsl:template match="api:property" mode="api:html.name">
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:value-of select="' '"/>
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>
	<xsl:if test="api:parameter">
		<xsl:value-of select="'['"/>
		<xsl:apply-templates select="api:parameter" mode="api:html.name"/>
		<xsl:value-of select="']'"/>
	</xsl:if>
	<xsl:apply-templates select="api:get|api:set" mode="api:html.name"/>
</xsl:template>

<!-- method -->
	
<xsl:template match="api:method" mode="api:html.name">
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:value-of select="' '"/>
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>
	<xsl:value-of select="'('"/>
	<xsl:if test="api:parameter">
		<xsl:apply-templates select="api:parameter" mode="api:html.name"/>
	</xsl:if>
	<xsl:value-of select="')'"/>
</xsl:template>

<!-- const -->
	
<xsl:template match="api:const" mode="api:html"/>	
	
<!-- item -->

<xsl:template match="api:item" mode="api:html.name">
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>
	<xsl:value-of select="' = '"/>
	<span class="constant">
		<xsl:value-of select="api:const/@value"/>
	</span>
</xsl:template>

<!-- using -->
	
<xsl:template match="api:using" mode="api:html"/>

<xsl:template match="api:using" mode="api:html.table"/>

<!-- -->
	
<xsl:template match="api:enum" mode="api:html.type">
	<xsl:value-of select="'Enumeration'"/>
</xsl:template>

<xsl:template match="api:struct" mode="api:html.type">
	<xsl:value-of select="'Structure'"/>
</xsl:template>
	
<xsl:template match="api:interface" mode="api:html.type">
	<xsl:value-of select="'Interface'"/>
</xsl:template>

<!-- object -->
	
<xsl:template match="api:struct/api:object" mode="api:html.name">
	<xsl:apply-templates select="api:type.ref" mode="api:html.link"/>
	<xsl:value-of select="' '"/>
	<span class="id">
		<xsl:value-of select="@id"/>
	</span>
</xsl:template>	
	
<xsl:template match="api:object" mode="api:html.type">
	<xsl:value-of select="'Object'"/>
</xsl:template>

<!-- library -->
	
<xsl:template match="api:library" mode="api:html.type">
	<xsl:value-of select="'Library'"/>
</xsl:template>
	
<xsl:template match="api:library" mode="api:html.body">
	<div class="h2">
		<h2>Table Of Contents</h2>
		<ul>
			<xsl:apply-templates select="api:*" mode="api:html.table"/>
		</ul>
	</div>
	<xsl:apply-templates select="api:*" mode="api:html"/>
</xsl:template>	

<xsl:template match="api:library" mode="api:html.root">
	<html>
		<head>
			<style type="text/css">
body { font-family: monospace; font-size: 12pt; }

a:link, a:visited, a:active
{
	color: blue;
	text-decoration: none;
}

a:hover
{
	color: blue;
	text-decoration: underline;
}

/* 	'hr'
	For more information about styling 'hr' see 
	http://www.saila.com/usage/tips/defn.shtml?hr 
*/

/* For Internet Explorer */
hr { width: 100%; height: 1px; color: black; border: none; }

ul 
{ 
	list-style-type: disc; 
	/*
	border-left-style: dotted;
	border-width: 1px;
	*/
	
	margin-left: 0px;
	padding-left: 20px;

	margin-top: 5px;
	margin-bottom: 5px;
}
.constant { color: green; }
.node { color: black; }
.id { color: navy; }
.comment { font-style: italic; font-family: sans-serif; }
.keyword { color: teal; }

div
{
	margin: 5px 0px 10px 0px;
	padding: 0px 0px 0px 0px;
}
.h2 
{ 	
	border-top-style: solid;
	border-width: 1px; 
}
.h3
{
	border-top-style: solid;
	border-width: 1px; 
	margin: 0px 0px 20px 20px;
}
h1 { font-size: 20pt; font-width: bold; }
h2 { font-size: 16pt; font-width: bold; }
h3 { font-size: 12pt; font-width: bold; }

/*	Tables
*/

table, th, td
{
	border: none;
}

th, td
{
	padding: 5px 10px 5px 10px;
}

th
{
	background-color: #D3D3D3;
}

td
{
	background-color: #E0E0E0;
}
			</style>
			<title>
				<xsl:value-of select="@id"/>
			</title>
		</head>
		<body>
			<xsl:apply-templates select="." mode="api:html"/>
		</body>
	</html>	
</xsl:template>

<xsl:template match="api:library">
	<xsl:apply-templates select="." mode="api:html.root"/>
</xsl:template>

</xsl:stylesheet>
