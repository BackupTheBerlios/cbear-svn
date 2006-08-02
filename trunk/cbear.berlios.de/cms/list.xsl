<?xml version="1.0"?>
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

<xsl:template match="prj:section" mode="prj:html.link.href">
	<xsl:param name="filename" select="@href"/>
	<xsl:value-of select="concat(
		substring($filename, 1, string-length($filename) - 4), '.html')"/>
</xsl:template>

<xsl:template match="prj:section[@href]" mode="prj:html">
	<xsl:apply-imports/>
	<xsl:apply-templates 
		select="document(@href, .)/prj:section" mode="prj:list">
		<xsl:with-param name="filename" select="@href"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="/prj:section" mode="prj:list">
	<xsl:param name="filename"/>
	<xsl:variable name="name">
		<xsl:apply-templates select="." mode="prj:html.link.href">
			<xsl:with-param name="filename" select="$filename"/>
		</xsl:apply-templates>
	</xsl:variable>
	<xsl:message terminate="no">
		<xsl:value-of select="$filename"/>
		<xsl:text>|</xsl:text>
		<xsl:value-of select="$name"/>
	</xsl:message>
	<exsl:document 
		href="{$name}"
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
