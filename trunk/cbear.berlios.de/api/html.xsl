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

<xsl:template match="*" mode="api:html"/>

<xsl:template match="api:comment" mode="api:html">
	<div class="comment"><xsl:copy-of select="*|text()"/></div>
</xsl:template>

<xsl:template match="api:enum" mode="api:html">
	<div>
		<hr/>		
		<h2>The <span class="id"><xsl:value-of select="@id"/></span> Enumeration</h2>
		<xsl:apply-templates select="*" mode="api:html"/>
	</div>
</xsl:template>

<xsl:template match="api:struct" mode="api:html">
	<div>
		<hr/>		
		<h2>The <span class="id"><xsl:value-of select="@id"/></span> Structure</h2>
		<xsl:apply-templates select="*" mode="api:html"/>
	</div>
</xsl:template>

<xsl:template match="api:interface" mode="api:html">
	<div>
		<hr/>		
		<h2>The <span class="id"><xsl:value-of select="@id"/></span> Interface</h2>
		<xsl:apply-templates select="*" mode="api:html"/>
	</div>
</xsl:template>

<xsl:template match="api:library" mode="api:html">
	<html>
		<head>
			<style type="text/css">
body { font-family: monospace; }

/* 	'hr'
	For more information about styling 'hr' see http://www.saila.com/usage/tips/defn.shtml?hr 
*/

/* For Internet Explorer */
hr { width: 100%; height: 1px; color: black; border: none; }

ul 
{ 
	list-style-type: disc; 
	border-left-style: dotted;
	border-width: 1px;
	
	margin-left: 0px;
	padding-left: 20px;

	margin-top: 5px;
	margin-bottom: 5px;
}
.constant { color: green; }
.node { color: black; }
.id { color: blue; }
.comment { font-style: italic; }
			</style>
		</head>
		<body>
			<h1>The <span class="id"><xsl:value-of select="@id"/></span> Library</h1>
			<xsl:apply-templates select="*" mode="api:html"/>
		</body>
	</html>	
</xsl:template>

<xsl:template match="api:library">
	<xsl:apply-templates select="." mode="api:html"/>
</xsl:template>

</xsl:stylesheet>
