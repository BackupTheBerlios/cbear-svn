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
		body, table
		{
			font-family: sans-serif;
			font-size: 10pt;
		}
		h1, h2, div.menu
		{
			border-top: solid 1px #00007F;
		}
		h1, h2
		{
			background-color: #E0E8FF;
			color: #00003F;
			margin: 0 0 0 0;
			padding: 1px 1px 1px 1px;
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
			border-left: solid 1px #00007F;
			padding-left: 5px;
			background-color: #F0F7FF;
		}
		td.name
		{
			padding: 0 0 0 0;
		}
		td.menu, td.content
		{
			vertical-align: top;
		}
		td.content
		{
			width: 100%; 			
		}
		div.content-section, div.content-table
		{
			margin-left: 10px;
		}
		div.menu, h1
		{
			margin-left: 5px;
		}
		div.menu
		{
			padding-top: 5px;
			padding-bottom: 5px;			
		}
		div.menu-item
		{
			color: gray;
		}
		div.content-section
		{
			margin-top: 5px;
			margin-borrom: 5px;
		}
		div.content-section-content
		{
			padding: 0 0 0 0;
			margin: 5px 0 5px 0;
		}
		tr.tr
		{
			height: 100%;
		}
		span.path
		{
			padding-right: 20px;
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
		<span class="path">
			<a href="{concat($path, $P:index.link)}" title="{@title}">
				<xsl:value-of select="@name"/>
			</a>
		</span>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:path">
		<xsl:for-each select="document($P:path.prior, .)/P:section">
			<xsl:apply-templates select="." mode="P:path.prior"/>
		</xsl:for-each>
	</xsl:template>

	<!-- Menu -->

	<xsl:template match="/P:section" mode="P:menu">
		<xsl:variable name="menu">
			<xsl:for-each 
				select="
					document($P:svn, .)/
					S:wc-entries/
					S:entry[@kind='dir' and @name!='']">
				<xsl:sort select="@name"/>
				<xsl:variable 
					name="index.xml" 
					select="concat('../', @name, '/', $P:index.xml)"/>
				<div class="menu-item">
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
							<xsl:value-of select="@name"/>
						</xsl:otherwise>
					</xsl:choose>
				</div>
			</xsl:for-each>
		</xsl:variable>
		<xsl:if test="string($menu)!=''">
			<div class="menu">
				<xsl:copy-of select="$menu"/>
			</div>
		</xsl:if>
	</xsl:template>

	<!-- Content -->

	<xsl:template match="P:section" mode="P:content.table">
		<div class="content-table">
			<a href="{concat('#', @name)}" title="{@title}">
				<xsl:value-of select="@name"/>
			</a>
			<xsl:apply-templates select="P:section" mode="P:content.table"/>
		</div>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:content.table">
		<xsl:if test="P:section">
			<div class="menu">
				<xsl:apply-templates select="P:section" mode="P:content.table"/>
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
			class="content-section"
			id="{@name}">
			<h2><xsl:value-of select="@name"/></h2>
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="P:content.content"/>
				<xsl:apply-templates select="." mode="P:content.content"/>
			</div>
		</div>
	</xsl:template>

	<xsl:template match="/P:section" mode="P:content">
		<xsl:apply-templates select="." mode="P:content.table"/>
		<div class="menu">
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="P:content.content"/>
				<xsl:apply-templates select="." mode="P:content.content"/>
			</div>
		</div>
	</xsl:template>

	<!-- Language -->

	<xsl:template match="P:language" mode="P:language">
		<div class="menu-item">
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
				<table>
					<!-- Header -->
					<tr>
						<td colspan="2" class="menu">
							<xsl:apply-templates select="." mode="P:header"/>
						</td>
					</tr>
					<!-- Path -->
					<xsl:variable name="path">
						<xsl:apply-templates select="." mode="P:path"/>
					</xsl:variable>
					<xsl:if test="string($path)!=''">
						<tr>
							<td colspan="2" class="menu">
								<div class="menu">
									<xsl:copy-of select="$path"/>
								</div>
							</td>
						</tr>
					</xsl:if>
					<!-- -->
					<tr class="tr">
						<td class="menu">
							<!-- Menu -->
							<xsl:apply-templates select="." mode="P:menu"/>
							<!-- Language -->
							<div class="menu">
								<xsl:apply-templates select="." mode="P:language"/>
							</div>
							<!-- Revision -->
							<div class="menu">
								<xsl:apply-templates select="." mode="P:revision"/>
							</div>
						</td>
						<!-- Content -->
						<td class="content">
							<xsl:apply-templates select="." mode="P:content"/>
						</td>
					</tr>
				</table>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
