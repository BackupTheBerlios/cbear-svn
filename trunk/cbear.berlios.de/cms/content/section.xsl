<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<!-- Content -->

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
			<a href="{concat('#', $id)}" title="{@title}">
				<xsl:value-of select="@name"/>
			</a>
			<xsl:apply-templates select="C:section" mode="C:content.table"/>
		</div>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:content.table">
		<xsl:if test="C:section">
			<div class="menu">
				<xsl:apply-templates select="C:section" mode="C:content.table"/>
			</div>
		</xsl:if>
	</xsl:template>

	<xsl:template match="@title" mode="C:content.content">
		<div class="title">
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
		<xsl:value-of select="'10'"/>
		<xsl:apply-templates select="." mode="C:content.table"/>
		<div class="menu">
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="C:content.content"/>
				<xsl:apply-templates select="." mode="C:content.content"/>
			</div>
		</div>
	</xsl:template>

	<!-- -->

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
