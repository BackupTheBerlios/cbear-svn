<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:docbook="http://cbear.berlios.de/docbook"
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
