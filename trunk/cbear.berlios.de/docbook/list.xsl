<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear="http://cbear.berlios.de"
	xmlns:map="http://www.google.com/schemas/sitemap/0.84"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="cbear xi map">

<xsl:import href="html.ex.xsl"/>

<xsl:output 
	method="xml" 
	version="1.0"
	indent="yes"
	standalone="yes"
	doctype-public="" 
	doctype-system=""/>

<xsl:param name="url"/>

<!-- Path -->
<xsl:template name="path">
	<xsl:param name="path"/>
	<xsl:if test="contains($path, '/')">
		<xsl:value-of select="concat(substring-before($path, '/'), '/')"/>
		<xsl:call-template name="path">
			<xsl:with-param 
				name="path" select="substring-after($path, '/')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- Back Path -->
<xsl:template name="backpath">
	<xsl:param name="path"/>
	<xsl:if test="contains($path, '/')">
		<xsl:text>../</xsl:text>
		<xsl:call-template name="backpath">
			<xsl:with-param name="path" select="substring-after($path, '/')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- * -->
<xsl:template match="*" mode="docbook.list">
	<xsl:param name="path"/>
	<xsl:param name="top"/>
	<xsl:param name="up"/>
	<xsl:apply-templates select="*" mode="docbook.list">
		<xsl:with-param name="path" select="$path"/>
		<xsl:with-param name="top" select="$top"/>
		<xsl:with-param name="up" select="$up"/>
	</xsl:apply-templates>
</xsl:template>

<!-- Default Transformation -->
<xsl:template match="cbear:parameters">
	<xsl:param name="document"/>

	<xsl:message terminate="no">
		<xsl:value-of select="exsl:node-set($document)/section/title"/>
	</xsl:message>

	<exsl:document
		href="{@output}"
		encoding="utf-8"
		method="xml"
		doctype-public="-//W3C//DTD XHTML 1.1//EN"
  	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
		<xsl:apply-templates 
			select="exsl:node-set($document)/section" mode="docbook.html.root">
			<xsl:with-param 
				name="top" select="cbear:parameter[@name='docbook.html.top']/@value"/>
			<xsl:with-param 
				name="up" select="cbear:parameter[@name='docbook.html.up']/@value"/>
			<xsl:with-param 
				name="root" select="cbear:parameter[@name='docbook.html.root']/@value"/>
		</xsl:apply-templates>
	</exsl:document>
</xsl:template>

<!-- Document -->
<xsl:template name="document">
	<xsl:param name="document"/>
	<xsl:param name="fullname"/>
	<xsl:param name="top"/>
	<xsl:param name="up"/>
	<xsl:param name="root"/>

	<map:url>
		<map:loc>
			<xsl:value-of select="concat('http://', $url, '/', $fullname, '.html')"/>
		</map:loc>
	</map:url>

	<xsl:variable name="parameters">
		<cbear:parameters
			source="{concat($fullname, '.xml')}"
			output="{concat($fullname, '.html')}">
			<cbear:parameter name="docbook.html.external" value="1"/>
			<xsl:if test="$top">
				<cbear:parameter name="docbook.html.top" value="{$top}"/>
			</xsl:if>
			<xsl:if test="$up">
				<cbear:parameter name="docbook.html.up" value="{$up}"/>
			</xsl:if>
			<xsl:if test="$root">
				<cbear:parameter name="docbook.html.root" value="{$root}"/>
			</xsl:if>
		</cbear:parameters>
	</xsl:variable>

	<xsl:apply-templates select="exsl:node-set($parameters)/cbear:parameters">
		<xsl:with-param name="document" select="$document"/>
	</xsl:apply-templates>

</xsl:template>

<!-- Include -->
<xsl:template match="xi:include" mode="docbook.list">
	<xsl:param name="path"/>
	<xsl:param name="top"/>
	<xsl:param name="up"/>

	<xsl:variable name="name">
		<xsl:apply-templates select="." mode="docbook.html.name"/>
	</xsl:variable>

	<xsl:variable name="fullname" select="concat($path, $name)"/>
	<xsl:variable name="backpath">
		<xsl:call-template name="backpath">
			<xsl:with-param name="path" select="$name"/>
		</xsl:call-template>
	</xsl:variable>

	<xsl:variable name="document" select="document(@href)"/>
	
	<xsl:call-template name="document">
		<xsl:with-param name="document" select="$document"/>
		<xsl:with-param name="fullname" select="$fullname"/>
		<xsl:with-param name="top" select="concat($backpath, $top)"/>
		<xsl:with-param name="up" select="concat($backpath, $up)"/>
		<xsl:with-param name="root" select="$backpath"/>
	</xsl:call-template>

	<xsl:apply-templates select="exsl:node-set($document)/*" mode="docbook.list">
		<xsl:with-param name="path">
			<xsl:call-template name="path">
				<xsl:with-param name="path" select="$fullname"/>
			</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="top" select="concat($backpath, $top)"/>
		<xsl:with-param name="up" select="concat($backpath, $name, '.html')"/>
	</xsl:apply-templates>
</xsl:template>

<!-- Root -->
<xsl:template match="/">
	<exsl:document
		href="sitemap.xml"
		method="xml">
		<map:urlset>
			<xsl:call-template name="document">
				<xsl:with-param name="document" select="."/>
				<xsl:with-param name="fullname" select="'index'"/>
			</xsl:call-template>
			<xsl:apply-templates select="*" mode="docbook.list">
				<xsl:with-param name="top" select="'index.html'"/>
				<xsl:with-param name="up" select="'index.html'"/>
			</xsl:apply-templates>
		</map:urlset>
	</exsl:document>
</xsl:template>

</xsl:stylesheet>
