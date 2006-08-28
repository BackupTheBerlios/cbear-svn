<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:import href="source.xsl"/>
	<xsl:import href="a.xsl"/>

	<xsl:variable name="C:content" select="'border-top: solid 1px #E0E0E0;'"/>
	<xsl:variable name="C:content.section.title" select="'font-style: italic;'"/>

	<xsl:template match="*" mode="C:content.div">
		<xsl:param name="content"/>
		<div>
			<xsl:attribute name="style">
				<xsl:value-of select="$C:content"/>
			</xsl:attribute>
			<xsl:copy-of select="$content"/>
		</div>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content.number">		
		<xsl:if test="..!=.">
			<xsl:apply-templates select=".." mode="C:content.number"/>
			<xsl:value-of select="concat(count(preceding-sibling::C:section) + 1, '.')"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content.id">		
		<xsl:value-of select="'o'"/>
		<xsl:apply-templates select="." mode="C:content.number"/>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content.table">
		<xsl:variable name="id">
			<xsl:apply-templates select="." mode="C:content.id"/>
		</xsl:variable>
		<div class="content-table">
			<xsl:apply-templates select="." mode="C:content.link">
				<xsl:with-param name="href" select="concat('#', $id)"/>
				<xsl:with-param name="name" select="string(@name)"/>
			</xsl:apply-templates>
			<xsl:apply-templates select="C:section" mode="C:content.table"/>
		</div>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:content.table">
		<xsl:if test="C:section">
			<xsl:apply-templates select="." mode="C:content.div">
				<xsl:with-param name="content">
					<xsl:apply-templates select="C:section" mode="C:content.table"/>
				</xsl:with-param>
			</xsl:apply-templates>
		</xsl:if>
	</xsl:template>

	<xsl:template match="@title" mode="C:content.content">
		<div>
			<xsl:attribute name="style">
				<xsl:value-of select="$C:content.section.title"/>
			</xsl:attribute>
			<xsl:value-of select="."/>
		</div>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content">
		<xsl:variable name="id">
			<xsl:apply-templates select="." mode="C:content.id"/>
		</xsl:variable>
		<div class="content-section" id="{$id}">
			<h2><xsl:value-of select="@name"/></h2>
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="C:content.content"/>
				<xsl:if test="@source='yes'">
					<pre title="XML">
						<xsl:apply-templates select="*|text()|comment()" mode="C:content.source"/>
					</pre>
				</xsl:if>
				<xsl:apply-templates select="." mode="C:content.content"/>
			</div>
		</div>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.table"/>
		<xsl:apply-templates select="." mode="C:content.div">
			<xsl:with-param name="content">
				<div class="content-section-content">
					<xsl:apply-templates select="@title" mode="C:content.content"/>
					<xsl:apply-templates select="." mode="C:content.content"/>
				</div>
			</xsl:with-param>
		</xsl:apply-templates>
	</xsl:template>

</xsl:stylesheet>
