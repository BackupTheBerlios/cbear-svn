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
<xsl:param name="P:language" select="/P:section/@xml:lang"/>
<xsl:param name="P:style">
body
{
	font-family: sans-serif;
	margin: 0 0 0 0;
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
ul
{
	list-style: disc;
}
.p-menu
{
	list-style: none;
	background-color: #E0E8FF;
}
div.p-menu
{
	padding: 0px 10px 0px 10px;
	border: solid 1px white;
}
.p-menu-disable
{
	color: gray;
}
table, tr, td
{
	border-collapse: collapse;
	padding: 0 0 5px 0;
}
.p-header
{
	font-size: 40pt;
}
.p-content-table
{
	background-color: cyan;
	padding: 0 0 0 10px;
}
</xsl:param>

<xsl:variable name="P:index">
	<xsl:call-template name="P:index"/>	
</xsl:variable>

<!-- P:index -->

<xsl:template name="P:index">
	<xsl:param name="language" select="$P:language"/>
	<xsl:variable name="extension">
		<xsl:if test="$language!=''">
			<xsl:value-of select="concat('.', $language)"/>
		</xsl:if>
	</xsl:variable>	
	<xsl:value-of select="concat('index', $extension)"/>
</xsl:template>

<!-- P:global.content.table -->

<xsl:template match="/S:wc-entries" mode="P:global.content.table">
	<xsl:param name="path"/>
	<xsl:for-each select="S:entry[@kind='dir' and @name!='']">
		<xsl:sort select="@name"/>
		<div class="p-menu">
			<xsl:variable
				name="file" select="concat('../', @name, '/', $P:index, '.xml')"/>
			<xsl:choose>
				<xsl:when test="document($file, .)/P:section">
					<xsl:variable 
						name="href" 
						select="concat($path, @name, '/', $P:index, '.', $P:extension)"/>
					<xsl:for-each select="document($file, .)/P:section">
						<a
							href="{$href}"
							class="p-menu"
							title="{@title}">
							<xsl:value-of select="translate(@name, ' ', '&#160;')"/>
						</a>
					</xsl:for-each>
				</xsl:when>
				<xsl:otherwise>
					<span class="p-menu-disable">
						<xsl:value-of select="@name"/>
					</span>
				</xsl:otherwise>
			</xsl:choose>
<!--
			<xsl:apply-templates select="document(concat('../', @name, '/_svn/entries'), .)/*" mode="P:global.content.table"/>
-->
		</div>
	</xsl:for-each>
</xsl:template>

<!-- P:local.content.table -->

<xsl:template match="P:section" mode="P:local.content.table">
	<xsl:if test="P:section">
		<div class="p-content-table">
			<xsl:for-each select="P:section">
				<div class="p-content-table">
					<a href="{concat('#', @name)}" title="{@title}">
						<xsl:value-of select="@name"/>
					</a>
					<xsl:apply-templates select="." mode="P:local.content.table"/>
				</div>
			</xsl:for-each>
		</div>
	</xsl:if>
</xsl:template>

<!-- P:content -->

<xsl:template match="*" mode="P:content">
	<xsl:element name="{local-name(.)}">
		<xsl:copy-of select="@*"/>
		<xsl:apply-templates select="*|text()" mode="P:content"/>
	</xsl:element>
</xsl:template>

<xsl:template match="P:a[.='']" mode="P:content">
	<a>
		<xsl:copy-of select="@*"/>
		<xsl:value-of select="@href"/>
	</a>
</xsl:template>

<xsl:template match="P:section" mode="P:content">
	<h2 name="{@name}"><xsl:value-of select="@name"/></h2>
	<xsl:apply-templates select="*|text()" mode="P:content"/>
</xsl:template>

<!-- -->

<xsl:template match="/P:section">
	<html>
		<head>
			<title>
				<xsl:value-of select="@name"/>
			</title>
			<style type="text/css"><xsl:value-of select="$P:style"/></style>
		</head>
		<body>
			<!-- P:title -->
			<table style="margin: 0 auto 0 auto;">
				<tr>
					<td colspan="2">
						<div class="p-menu">
							<span class="p-header">
								<xsl:value-of select="@name"/>
							</span>
						</div>
					</td>
				</tr>
				<tr style="height: 100%;">
					<td style="width: auto;">
						<xsl:for-each select="
							document(concat('../', $P:index, '.xml'), .)/P:section">
							<div class="p-menu">
								<a 
									class="p-menu" 
									href="{concat('../', $P:index, '.', $P:extension)}">
									<xsl:value-of select="'..'"/>
								</a>
							</div>
						</xsl:for-each>
						<xsl:apply-templates 
							select="document($P:svn, .)/*" mode="P:global.content.table"/>
					</td>
					<td style="width: 100%; vertical-align: top;" rowspan="3">
						<xsl:apply-templates select="." mode="P:local.content.table"/>
						<xsl:apply-templates select="*|text()" mode="P:content"/>
					</td>
				</tr>
				<tr style="height: 100%;">
					<td>
						<!-- P:language -->
						<xsl:for-each select="document('languages.xml')/P:languages">
							<xsl:for-each select="P:language">
								<div class="p-menu">
									<xsl:variable name="index">
										<xsl:call-template name="P:index">
											<xsl:with-param name="language" select="@id"/>
										</xsl:call-template>
									</xsl:variable>
									<xsl:choose>
										<xsl:when test="string(@id)=string($P:language)">
											<span class="p-menu-disable">
												<xsl:value-of select="@name"/>
											</span>
										</xsl:when>
										<xsl:otherwise>
											<a
												href="{concat($index, '.', $P:extension)}"
												class="p-menu">
												<xsl:value-of select="@name"/>
											</a>
										</xsl:otherwise>
									</xsl:choose>
								</div>
							</xsl:for-each>
						</xsl:for-each>
					</td>
				</tr>
				<tr style="vertical-align: top;">
					<td>
						<div class="p-menu">
							<xsl:value-of select="concat(
								'Revision:&#160;',
								document($P:svn, .)/S:wc-entries/S:entry[@name='']/@revision)"/>
						</div>
					</td>
				</tr>
			</table>
			<!-- -->
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
