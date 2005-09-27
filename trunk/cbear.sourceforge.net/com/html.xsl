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

<xsl:template match="*" mode="odl:doc.html.content.table">
	<li>
		<a href="{concat('#', @id)}"><xsl:value-of select="@id"/></a>
	</li>
</xsl:template>
	
<xsl:template match="*" mode="odl:doc.html">
	<span class="error">
		<xsl:value-of select="concat('&lt;', local-name(), '&gt;')"/>
	</span>
	<xsl:apply-templates select="*" mode="odl:doc.html"/>
	<span class="error">
		<xsl:value-of select="concat('&lt;/', local-name(), '&gt;')"/>
	</span>
</xsl:template>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:doc.html.content.table"/>
	
<!-- library -->

<xsl:template match="odl:library" mode="odl:doc.html">
	<html>
		<head>
			<style type="text/css">
.error { color: red; }
			</style>
		</head>
		<body>
			<div>
				<h2>Table Of Contents</h2>
				<ul>
					<xsl:apply-templates select="*" mode="odl:doc.html.content.table"/>
				</ul>
			</div>
			<xsl:apply-templates select="*" mode="odl:doc.html"/>
		</body>
	</html>
</xsl:template>
	
<!-- Entry Point -->
	
<xsl:template match="*">
	<xsl:apply-templates select="." mode="odl:doc.html"/>
</xsl:template>

</xsl:stylesheet>
