<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<!-- Content -->

	<xsl:template match="*" mode="C:content.content">
		<xsl:apply-templates select="*|text()" mode="C:content"/>
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

</xsl:stylesheet>
