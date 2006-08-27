<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:import href="section.xsl"/>

	<!-- Content -->

	<xsl:template match="*" mode="C:content.content">
		<xsl:apply-templates select="*|text()" mode="C:content"/>
	</xsl:template>

	<xsl:template match="@title" mode="C:content.content">
		<div class="title">
			<xsl:value-of select="."/>
		</div>
	</xsl:template>

	<xsl:template match="text()" mode="C:content">
		<xsl:value-of select="."/>
	</xsl:template>

	<xsl:template match="*" mode="C:content" priority="-2">
		<xsl:element name="{local-name()}" />
	</xsl:template>

	<xsl:template match="*[*|@*|text()]" mode="C:content" priority="-1">
		<xsl:element name="{local-name()}">
			<xsl:copy-of select="@*"/>
			<xsl:apply-templates select="." mode="C:content.content"/>
		</xsl:element>
	</xsl:template>

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

	<xsl:template match="text()" mode="C:content.source">
		<xsl:value-of select="."/>
	</xsl:template>

	<xsl:template name="C:span">
		<xsl:param name="style"/>
		<xsl:param name="text"/>
		<span>
			<xsl:attribute name="style">
				<xsl:value-of select="$style"/>
			</xsl:attribute>
			<xsl:value-of select="$text"/>
		</span>
	</xsl:template>

	<xsl:template match="comment()" mode="C:content.source">
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.comment"/>
			<xsl:with-param name="text" select="concat('&lt;!--', ., '--&gt;')"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="C:*" mode="C:content.source.begin">
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.symbol"/>
			<xsl:with-param name="text" select="'&lt;'"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.name"/>
			<xsl:with-param name="text" select="local-name()"/>
		</xsl:call-template>
		<xsl:for-each select="@*">
			<xsl:value-of select="' '"/>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:style.attribute.name"/>
				<xsl:with-param name="text" select="local-name()"/>
			</xsl:call-template>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:style.attribute.symbol"/>
				<xsl:with-param name="text" select="'='"/>
			</xsl:call-template>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:style.attribute.value"/>
				<xsl:with-param name="text" select="concat('&#34;', ., '&#34;')"/>
			</xsl:call-template>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="C:*" mode="C:content.source">
		<xsl:apply-templates select="." mode="C:content.source.begin"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.symbol"/>
			<xsl:with-param name="text" select="'/&gt;'"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="C:*[*|text()|comment()]" mode="C:content.source">
		<xsl:apply-templates select="." mode="C:content.source.begin"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.symbol"/>
			<xsl:with-param name="text" select="'&gt;'"/>
		</xsl:call-template>
		<xsl:apply-templates select="*|text()|comment()" mode="C:content.source"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.symbol"/>
			<xsl:with-param name="text" select="'&lt;'"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.name"/>
			<xsl:with-param name="text" select="local-name()"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:style.element.symbol"/>
			<xsl:with-param name="text" select="'&gt;'"/>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>
