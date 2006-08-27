<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:template match="C:a" mode="C:content.a">
		<xsl:param name="href" select="@href"/>
		<xsl:param name="name" select="@href"/>
		<xsl:param name="title" select="@title"/>
		<a href="{$href}" title="{$title}">
			<xsl:choose>
				<xsl:when test="not(*|text())">
					<xsl:value-of select="$name"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:apply-templates select="." mode="C:content.content"/>
				</xsl:otherwise>
			</xsl:choose>
		</a>
	</xsl:template>

	<xsl:template match="C:a" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.a"/>
	</xsl:template>

	<xsl:template match="C:a[@type]" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.a">
			<xsl:with-param name="href" select="concat(@type, '://', @href)"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="C:a[@type='mailto']" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.a">
			<xsl:with-param name="href" select="concat('mailto:', @href)"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="C:a[@type='file']" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.a">
			<xsl:with-param name="href" select="concat('file:///', @href)"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="C:a[@type='wikipedia']" mode="C:content">
		<xsl:variable name="language">
			<xsl:for-each select="/C:section/@xml:lang">
				<xsl:value-of select="concat(., '.')"/>
			</xsl:for-each>
		</xsl:variable>
		<xsl:apply-templates select="." mode="C:content.a">
			<xsl:with-param 
				name="href" 
				select="concat('http://', $language, 'wikipedia.org/wiki/', @href)"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="C:a[@type='cms']" mode="C:content">		
		<xsl:param name="index.xml" select="concat(@href, '/', $C:index.xml)"/>
		<xsl:apply-templates select="." mode="C:content.a">
			<xsl:with-param 
				name="href" 
				select="concat(@href, '/', $C:index.xml)"/>
			<xsl:with-param 
				name="name"
				select="document($index.xml, .)/C:section/@name"/>
			<xsl:with-param 
				name="title"
				select="document($index.xml, .)/C:section/@title"/>
		</xsl:apply-templates>		
	</xsl:template>

</xsl:stylesheet>
