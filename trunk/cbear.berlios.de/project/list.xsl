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
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:prj="http://cbear.berlios.de/project"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear.html="http://cbear.berlios.de/html"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="prj xi">

<xsl:import href="../url/main.xsl"/>
<xsl:import href="../html/main.xsl"/>
<xsl:import href="html.xsl"/>

<xsl:template match="prj:section[@href]" mode="prj:html">
	<xsl:apply-imports/>
	<xsl:apply-templates 
		select="document(concat(@href, '.xml'), .)/prj:section" mode="prj:list">
		<xsl:with-param name="filename" select="@href"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="/prj:section" mode="prj:list">
	<xsl:param name="filename"/>
	<xsl:message terminate="no"><xsl:value-of select="$filename"/></xsl:message>
	<exsl:document 
		href="{concat($filename, '.html')}"
		encoding="utf-8"
		method="xml"
		doctype-public="{$cbear.html:main.xhtml11.doctype-public}"
		doctype-system="{$cbear.html:main.xhtml11.doctype-system}">
		<xsl:apply-templates select="." mode="prj:html"/>
	</exsl:document>
</xsl:template>

<xsl:template match="*">
	<xsl:apply-templates select="." mode="prj:list">
		<xsl:with-param name="filename" select="'index.xml'"/>
	</xsl:apply-templates>
</xsl:template>

</xsl:stylesheet>
