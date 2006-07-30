<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:P="http://cbear.berlios.de/project"
	xmlns:S="svn:"
	exclude-result-prefixes="P S">

	<xsl:param name="P:extension" select="'xml'"/>
	<xsl:param name="P:svn" select="'_svn/entries'"/>
	<xsl:param name="P:style">
		body
		{
			font-family: sans-serif;
		}
		a
		{
			color: blue;
			text-decoration: none;
		}
		a:hover
		{
			text-decoration: underline;
		}
		li
		{
			list-style: disc;
		}
		pre
		{
			
			border: solid 1px lightgray;
		}
	</xsl:param>

	<!-- Language -->

	<xsl:template name="P:language">
		<xsl:param name="language" select="/P:section/@xml:lang"/>
		<xsl:if test="$language!=''">
			<xsl:value-of select="concat('.', $language)"/>
		</xsl:if>
	</xsl:template>

	<xsl:variable name="P:language">
		<xsl:call-template name="P:language"/>
	</xsl:variable>

	<!-- Header -->

	<xsl:template match="/P:section" mode="P:header">
		<h1><xsl:value-of select="@name"/></h1>
	</xsl:template>

	<!-- Path -->

	<xsl:variable 
		name="P:index" 
		select="concat('index', $P:language)"/>

	<xsl:variable 
		name="P:index.xml" 
		select="concat($P:index, '.xml')"/>

	<xsl:variable
		name="P:index.link"
		select="concat($P:index, '.', $P:extension)"/>

	<xsl:variable 
		name="P:path.prior" 
		select="concat('../', $P:index.xml)"/>

	<xsl:template match="/P:section" mode="P:path.prior">
		<xsl:param name="path" select="'../'"/>
		<xsl:for-each select="document($P:path.prior, .)/P:section">
			<xsl:apply-templates select="." mode="P:path.prior">
				<xsl:with-param name="path" select="concat('../', $path)"/>
			</xsl:apply-templates>
		</xsl:for-each>
		<span style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;">
			<a href="{concat($path, $P:index.link)}" title="{@title}">
				<xsl:value-of select="@name"/>
			</a>
		</span>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:path">
		<div style="padding: 1px 1px 1px 1px; margin: 1px 1px 1px 1px;">
			<xsl:for-each select="document($P:path.prior, .)/P:section">
				<xsl:apply-templates select="." mode="P:path.prior"/>
			</xsl:for-each>
		</div>
	</xsl:template>

	<!-- Menu -->

	<xsl:template match="/P:section" mode="P:menu">
		<xsl:for-each 
			select="
				document($P:svn, .)/
				S:wc-entries/
				S:entry[@kind='dir' and @name!='']">
			<xsl:sort select="@name"/>
			<xsl:variable 
				name="index.xml" 
				select="concat('../', @name, '/', $P:index.xml)"/>
			<div style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;">
				<xsl:choose>
					<xsl:when test="document($index.xml, .)/P:section/@name">
						<xsl:variable
							name="index.link"
							select="concat(@name, '/', $P:index.link)"/>
						<xsl:for-each 
							select="document($index.xml, .)/P:section">
							<a 
								href="{$index.link}"
								title="{@title}">
								<xsl:value-of 
									select="translate(@name, ' ', '&#160;')"/>
							</a>
						</xsl:for-each>
					</xsl:when>
					<xsl:otherwise>
						<span style="color: gray;">
							<xsl:value-of select="@name"/>
						</span>
					</xsl:otherwise>
				</xsl:choose>
			</div>
		</xsl:for-each>
	</xsl:template>

	<!-- Content -->

	<xsl:template match="P:section" mode="P:content.table">
		<xsl:if test="P:section">
			<div style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;">
				<xsl:for-each select="P:section">
					<div style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;">
						<a href="{concat('#', @name)}" title="{@title}">
							<xsl:value-of select="@name"/>
						</a>
						<xsl:apply-templates select="." mode="P:content.table"/>
					</div>
				</xsl:for-each>
			</div>
		</xsl:if>
	</xsl:template>

	<xsl:template match="*" mode="P:content.content">
		<xsl:apply-templates select="*|text()|comment()" mode="P:content"/>
	</xsl:template>

	<xsl:template match="@title" mode="P:content.content">
		<xsl:value-of select="."/>
	</xsl:template>

	<xsl:template match="text()" mode="P:content">
		<xsl:value-of select="."/>
	</xsl:template>

	<xsl:template match="comment()" mode="P:content">
		<xsl:copy-of select="."/>
	</xsl:template>

	<xsl:template match="*" mode="P:content">
		<xsl:element name="{local-name()}">
			<xsl:copy-of select="@*"/>
			<xsl:apply-templates select="." mode="P:content.content"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="P:a[not(*|text())]" mode="P:content">
		<a>
			<xsl:copy-of select="@*"/>
			<xsl:value-of select="@href"/>
		</a>
	</xsl:template>

	<xsl:template match="P:section" mode="P:content">
		<div 
			style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;"
			id="{@name}">
			<h2><xsl:value-of select="@name"/></h2>
			<xsl:apply-templates select="@title" mode="P:content.content"/>
			<xsl:apply-templates select="." mode="P:content.content"/>
		</div>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:content">
		<xsl:apply-templates select="." mode="P:content.table"/>
		<xsl:apply-templates select="@title" mode="P:content.content"/>
		<xsl:apply-templates select="." mode="P:content.content"/>
	</xsl:template>

	<!-- Language -->

	<xsl:template match="P:language" mode="P:language">
		<div style="border: solid 1px lightgray; margin: 1px 1px 1px 1px; padding: 1px 1px 1px 1px;">
			<xsl:variable name="id">
				<xsl:call-template name="P:language">
					<xsl:with-param name="language" select="@id"/>
				</xsl:call-template>
			</xsl:variable>
			<xsl:choose>
				<xsl:when test="$id=$P:language">
					<xsl:value-of select="@name"/>
				</xsl:when>
				<xsl:otherwise>
					<a href="{concat('index', $id, '.', $P:extension)}">
						<xsl:value-of select="@name"/>
					</a>
				</xsl:otherwise>
			</xsl:choose>
		</div>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:language">
		<xsl:apply-templates 
			select="document('languages.xml')/P:languages/P:language"
			mode="P:language"/>
	</xsl:template>

	<!-- Revision -->

	<xsl:template match="/P:section" mode="P:revision">
		<xsl:value-of 
			select="
				concat(
					'Revision:&#160;',
					document($P:svn, .)/
						S:wc-entries/S:entry[@name='']/@revision)"/>
	</xsl:template>

	<!-- -->

	<xsl:variable name="P:td">
		border: lightgray solid 1px;
	</xsl:variable>

	<xsl:variable name="P:tr">
		height: 100%;
	</xsl:variable>
	
	<xsl:template match="/P:section">
		<html>
			<head>
				<title>
					<xsl:value-of select="@name"/>
				</title>
				<style type="text/css">
					<xsl:value-of select="normalize-space($P:style)"/>
				</style>
			</head>
			<body>
				<table style="margin: 0 auto 0 auto; padding: 0 0 0 0;">
					<!-- Header -->
					<tr>
						<td colspan="2" style="{$P:td}">
							<xsl:apply-templates select="." mode="P:header"/>
						</td>
					</tr>
					<!-- Path -->
					<xsl:variable name="path">
						<xsl:apply-templates select="." mode="P:path"/>
					</xsl:variable>
					<xsl:if test="string($path)!=''">
						<tr>
							<td colspan="2" style="{$P:td}">
								<xsl:copy-of select="$path"/>
							</td>
						</tr>
					</xsl:if>
					<!-- -->
					<tr style="{$P:tr}">
						<!-- Menu -->
						<td style="{$P:td}">
							<xsl:apply-templates select="." mode="P:menu"/>
						</td>
						<!-- Content -->
						<td rowspan="3" style="width: 100%; vertical-align: top;">
							<xsl:apply-templates select="." mode="P:content"/>
						</td>
					</tr>
					<tr style="{$P:tr}">
						<!-- Language -->
						<td style="{$P:td}">
							<xsl:apply-templates select="." mode="P:language"/>
						</td>
					</tr>
					<tr style="vertical-align: top;">
						<!-- Revision -->
						<td style="{$P:td}">
							<xsl:apply-templates select="." mode="P:revision"/>
						</td>
					</tr>
				</table>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
