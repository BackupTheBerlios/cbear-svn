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
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:docbook="http://cbear.sourceforge.net/docbook"
	exclude-result-prefixes="xi docbook">

<xsl:output method="text"/>

<!-- * -->

<xsl:template match="*" mode="docbook:rtf"/>

<!-- text() -->

<xsl:template match="text()" mode="docbook:rtf">
	<xsl:value-of select="."/>
</xsl:template>

<!-- filename -->

<xsl:template match="filename" mode="docbook:rtf">
	<xsl:value-of select="."/>
</xsl:template>

<!-- ulink -->

<xsl:template match="ulink" mode="docbook:rtf">
	<xsl:value-of select="concat(@url, ' ', .)"/>
</xsl:template>

<!-- listitem -->

<xsl:template match="listitem/para" mode="docbook:rtf">
	<xsl:apply-templates select="*" mode="docbook:rtf"/>
</xsl:template>

<xsl:template match="listitem" mode="docbook:rtf">
	<xsl:apply-templates select="*" mode="docbook:rtf"/>
	<xsl:text>\par</xsl:text>
</xsl:template>

<!-- itimizedlist -->

<xsl:template match="itemizedlist" mode="docbook:rtf">
	<xsl:text>{\pard{\*\pn\pnlvlblt}</xsl:text>
	<xsl:apply-templates select="*" mode="docbook:rtf"/>
	<xsl:text>}</xsl:text>
</xsl:template>

<!-- orderedlist -->

<xsl:template match="orderedlist" mode="docbook:rtf">
	<xsl:apply-templates select="*" mode="docbook:rtf"/>
</xsl:template>

<!-- para -->

<xsl:template match="para" mode="docbook:rtf">
	<xsl:text>{\pard </xsl:text>
	<xsl:apply-templates select="*|text()" mode="docbook:rtf"/>
	<xsl:text>\par}</xsl:text>
</xsl:template>

<!-- section -->

<xsl:template match="section" mode="docbook:rtf.section">
	<xsl:text>{\pard \b </xsl:text>
	<xsl:value-of select="title"/>
	<xsl:text>\par}</xsl:text>
	<xsl:apply-templates select="*" mode="docbook:rtf"/>
</xsl:template>

<xsl:template match="section" mode="docbook:rtf">
	<xsl:apply-templates select="." mode="docbook:rtf.section"/>
</xsl:template>

<xsl:template match="/section" mode="docbook:rtf">
	<xsl:text>{\rtf </xsl:text>
	<xsl:apply-templates select="." mode="docbook:rtf.section"/>
	<xsl:text>}</xsl:text>
</xsl:template>

<!-- Default Root Template -->
<xsl:template match="/section">
	<xsl:apply-templates select="." mode="docbook:rtf"/>	
</xsl:template>

</xsl:stylesheet>
