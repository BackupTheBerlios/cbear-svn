<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:variable name="C:source.element.name" select="'color: #007F7F;'"/>	
	<xsl:variable name="C:source.element.symbol" select="'color: #003F7F;'"/>
	<xsl:variable name="C:source.attribute.name" select="'color: #003F7F;'"/>
	<xsl:variable name="C:source.attribute.symbol" select="'color: #007F7F;'"/>
	<xsl:variable name="C:source.attribute.value" select="'color: #007F00;'"/>

	<xsl:template match="C:*" mode="C:source.begin">
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.symbol"/>
			<xsl:with-param name="text" select="'&lt;'"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.name"/>
			<xsl:with-param name="text" select="local-name()"/>
		</xsl:call-template>
		<xsl:for-each select="@*">
			<xsl:value-of select="' '"/>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:source.attribute.name"/>
				<xsl:with-param name="text" select="local-name()"/>
			</xsl:call-template>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:source.attribute.symbol"/>
				<xsl:with-param name="text" select="'='"/>
			</xsl:call-template>
			<xsl:call-template name="C:span">
				<xsl:with-param name="style" select="$C:source.attribute.value"/>
				<xsl:with-param name="text" select="concat('&#34;', ., '&#34;')"/>
			</xsl:call-template>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="C:*" mode="C:source">
		<xsl:apply-templates select="." mode="C:source.begin"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.symbol"/>
			<xsl:with-param name="text" select="'/&gt;'"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="C:*[*|text()|comment()]" mode="C:source">
		<xsl:apply-templates select="." mode="C:source.begin"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.symbol"/>
			<xsl:with-param name="text" select="'&gt;'"/>
		</xsl:call-template>
		<xsl:apply-templates select="*|text()|comment()" mode="C:source"/>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.symbol"/>
			<xsl:with-param name="text" select="'&lt;'"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.name"/>
			<xsl:with-param name="text" select="local-name()"/>
		</xsl:call-template>
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.element.symbol"/>
			<xsl:with-param name="text" select="'&gt;'"/>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>
