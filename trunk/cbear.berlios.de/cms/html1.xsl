<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:S="svn:"
	exclude-result-prefixes="C S">

	<xsl:output method="xml" indent="no"/>

	<xsl:param name="C:extension" select="'xml'"/>
	<xsl:param name="C:languages" select="'languages.xml'"/>

	<xsl:variable name="C:svn1" select="'_svn/entries'"/>
	<xsl:variable name="C:svn2" select="'.svn/entries'"/>

	<xsl:param name="C:svn">
		<xsl:choose>
			<xsl:when test="document($C:svn1, .)/*">
				<xsl:value-of select="$C:svn1"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$C:svn2"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:param>

	<xsl:param name="C:style">
		body, table
		{
			font-family: sans-serif;
			font-size: 10pt;
		}
		table
		{ 
			border: none; border-spacing: 1px; background-color: gray; 
		}
		th, td 
		{ 
			padding: 1px 5px 1px 5px; margin: 0 0 0 0; 
		}
		th 
		{ 
			background-color: #E0E8FF; 
		}
		td 
		{ 
			background-color: white; 
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
		ul li
		{
			list-style: disc;
		}
		pre
		{
			border-left: solid 1px #00007F;
			padding-left: 5px;
			background-color: #F0F7FF;
		}
		table.main
		{
			background-color: white;
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
		div.content-table
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
		div.title
		{
			font-style: italic;
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
		a.disable
		{
			color: navy;
		}
		span.id
		{
			font-family: monospace;
		}
	</xsl:param>

	<!-- Language -->

	<xsl:template name="C:language">
		<xsl:param name="language" select="/C:section/@xml:lang"/>
		<xsl:if test="$language!=''">
			<xsl:value-of select="concat('.', $language)"/>
		</xsl:if>
	</xsl:template>

	<xsl:variable name="C:language">
		<xsl:call-template name="C:language"/>
	</xsl:variable>

	<!-- Header -->

	<xsl:template match="/C:section" mode="C:header">
		<h1><xsl:value-of select="@name"/></h1>
	</xsl:template>

	<!-- Path -->

	<xsl:variable 
		name="C:index" 
		select="concat('index', $C:language)"/>

	<xsl:variable 
		name="C:index.xml" 
		select="concat($C:index, '.xml')"/>

	<xsl:variable
		name="C:index.link"
		select="concat($C:index, '.', $C:extension)"/>

	<xsl:variable 
		name="C:path.prior" 
		select="concat('../', $C:index.xml)"/>

	<xsl:template match="/C:section" mode="C:path.prior">
		<xsl:param name="path" select="'../'"/>
		<xsl:for-each select="document($C:path.prior, .)/C:section">
			<xsl:apply-templates select="." mode="C:path.prior">
				<xsl:with-param name="path" select="concat('../', $path)"/>
			</xsl:apply-templates>
		</xsl:for-each>
		<span class="path">
			<a href="{concat($path, $C:index.link)}" title="{@title}">
				<xsl:value-of select="@name"/>
			</a>
		</span>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:path">
		<xsl:for-each select="document($C:path.prior, .)/C:section">
			<xsl:apply-templates select="." mode="C:path.prior"/>
		</xsl:for-each>
	</xsl:template>

	<!-- Id -->

	<xsl:template name="C:id">
		<xsl:param name="url" select="@url"/>
		<xsl:choose>
			<xsl:when test="contains($url, '/')">
				<xsl:call-template name="C:id">
					<xsl:with-param name="url" select="substring-after($url, '/')"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="translate($url, '.', '_')"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:id">
		<xsl:variable name="prior">
			<xsl:apply-templates select="document($C:path.prior, .)/*" mode="C:id"/>
		</xsl:variable>
		<xsl:if test="string($prior)!=''">
			<xsl:value-of select="concat($prior, '.')"/>
		</xsl:if>
		<xsl:for-each select="document($C:svn, .)/S:wc-entries/S:entry[@name='']">
			<xsl:call-template name="C:id"/>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="/C:section[@id]" mode="C:id">
		<xsl:value-of select="@id"/>
	</xsl:template>

	<!-- Version -->

	<xsl:template match="/C:section" mode="C:version.user">
		<xsl:apply-templates 
			select="document($C:path.prior, .)/*" mode="C:version.user"/>
	</xsl:template>

	<xsl:template match="/C:section[@version]" mode="C:version.user">
		<xsl:value-of select="@version"/>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:version">
		<xsl:variable name="user">
			<xsl:apply-templates select="." mode="C:version.user"/>
		</xsl:variable>
		<xsl:if test="string($user)!=''">
			<xsl:value-of select="concat($user, '.')"/>
		</xsl:if>
		<xsl:value-of select="
			document($C:svn, .)/S:wc-entries/S:entry[@name='']/@revision"/>
	</xsl:template>

	<!-- Date -->

	<xsl:template match="/C:section" mode="C:date">
		<xsl:variable name="prior">
			<xsl:apply-templates select="document($C:path.prior, .)/*" mode="C:date"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($prior)">
				<xsl:value-of select="$prior"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="
					document($C:svn, .)/S:wc-entries/S:entry[@name='']/@committed-date"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- Company -->

	<xsl:template match="/C:section" mode="C:company">
		<xsl:apply-templates select="document($C:path.prior, .)/*" mode="C:company"/>
	</xsl:template>

	<xsl:template match="/C:section[@company]" mode="C:company">
		<xsl:value-of select="@company"/>
	</xsl:template>

	<!-- Type -->

	<xsl:template match="/C:section" mode="C:type">
		<xsl:value-of select="@type"/>
	</xsl:template>

	<!-- Menu -->

	<xsl:template match="/C:section" mode="C:menu">
		<xsl:variable name="menu">
			<xsl:for-each 
				select="
					document($C:svn, .)/
					S:wc-entries/
					S:entry[@kind='dir' and @name!='']">
				<xsl:sort select="@name"/>
				<xsl:variable 
					name="index.xml" 
					select="concat('../', @name, '/', $C:index.xml)"/>
				<div class="menu-item">
					<xsl:choose>
						<xsl:when test="document($index.xml, .)/C:section/@name">
							<xsl:variable
								name="index.link"
								select="concat(@name, '/', $C:index.link)"/>
							<xsl:for-each 
								select="document($index.xml, .)/C:section">
								<a 
									href="{$index.link}"
									title="{@title}">
									<xsl:value-of 
										select="translate(@name, ' ', '&#160;')"/>
								</a>
							</xsl:for-each>
						</xsl:when>
						<xsl:otherwise>
							<a href="{@name}" class="disable">
								<xsl:value-of select="concat(@name, '/')"/>
							</a>
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

	<!-- Files -->

	<xsl:template match="/C:section" mode="C:files">
		<xsl:variable name="menu">
			<xsl:for-each select="
				document($C:svn, .)/S:wc-entries/S:entry[
					@kind='file' and substring-before(@name, '.')!='index']">
				<xsl:sort select="@name"/>
				<div class="menu-item">
					<a href="{@name}" class="disable"><xsl:value-of select="@name"/></a>
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

	<xsl:template match="C:section" mode="C:content.number">		
		<xsl:if test="..!=.">
			<xsl:apply-templates select=".." mode="C:content.number"/>
			<xsl:value-of select="concat(count(preceding-sibling::C:section) + 1, '.')"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content.table">
		<xsl:variable name="number">
			<xsl:apply-templates select="." mode="C:content.number"/>
		</xsl:variable>
		<div class="content-table">
			<a href="{concat('#', $number)}" title="{@title}">
				<xsl:value-of select="concat($number, ' ', @name)"/>
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

	<xsl:template match="*" mode="C:content.content">
		<xsl:apply-templates select="*|text()|comment()" mode="C:content"/>
	</xsl:template>

	<xsl:template match="@title" mode="C:content.content">
		<div class="title">
			<xsl:value-of select="."/>
		</div>
	</xsl:template>

	<xsl:template match="text()" mode="C:content">
		<xsl:value-of select="."/>
	</xsl:template>

	<xsl:template match="comment()" mode="C:content">
		<xsl:copy-of select="."/>
	</xsl:template>

	<xsl:template match="*" mode="C:content">
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

	<xsl:template match="comment()" mode="C:content.source">
		<xsl:value-of select="concat('&lt;!--', ., '--&gt;')"/>
	</xsl:template>

	<xsl:template match="C:*" mode="C:content.source.begin">
		<xsl:value-of select="concat('&lt;', local-name())"/>
		<xsl:for-each select="@*">
			<xsl:value-of select="concat(' ', local-name(), '=&#34;', ., '&#34;')"/>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="C:*" mode="C:content.source">
		<xsl:apply-templates select="." mode="C:content.source.begin"/>
		<xsl:value-of select="'/&gt;'"/>
	</xsl:template>

	<xsl:template match="C:*[*|text()|comment()]" mode="C:content.source">
		<xsl:apply-templates select="." mode="C:content.source.begin"/>
		<xsl:value-of select="'&gt;'"/>
		<xsl:apply-templates select="*|text()|comment()" mode="C:content.source"/>
		<xsl:value-of select="concat('&lt;/',local-name(), '&gt;')"/>
	</xsl:template>

	<xsl:template match="C:section" mode="C:content">
		<xsl:variable name="number">
			<xsl:apply-templates select="." mode="C:content.number"/>
		</xsl:variable>
		<div 
			class="content-section"
			id="{$number}">
			<h2><xsl:value-of select="concat($number, ' ', @name)"/></h2>
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="C:content.content"/>
				<xsl:if test="@source='yes'">
					<pre>
						<xsl:apply-templates select="*|text()|comment()" mode="C:content.source"/>
					</pre>
				</xsl:if>
				<xsl:apply-templates select="." mode="C:content.content"/>
			</div>
		</div>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.table"/>
		<div class="menu">
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="C:content.content"/>
				<xsl:apply-templates select="." mode="C:content.content"/>
			</div>
		</div>
	</xsl:template>

	<!-- Language -->

	<xsl:template match="C:language" mode="C:language">
		<div class="menu-item">
			<xsl:variable name="id">
				<xsl:call-template name="C:language">
					<xsl:with-param name="language" select="@id"/>
				</xsl:call-template>
			</xsl:variable>
			<xsl:choose>
				<xsl:when test="$id=$C:language">
					<xsl:value-of select="@name"/>
				</xsl:when>
				<xsl:otherwise>
					<a href="{concat('index', $id, '.', $C:extension)}">
						<xsl:value-of select="@name"/>
					</a>
				</xsl:otherwise>
			</xsl:choose>
		</div>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:language">		
		<xsl:apply-templates 
			select="document($C:languages)/C:languages/C:language"
			mode="C:language"/>
	</xsl:template>

	<!-- Property -->

	<xsl:template name="C:property">
		<xsl:param name="name"/>
		<xsl:param name="value"/>
		<xsl:if test="string($value)!=''">
			<div class="menu-item">
				<xsl:value-of select="concat($name, ':&#160;', $value)"/>
			</div>
		</xsl:if>
	</xsl:template>

	<xsl:template match="/C:section" mode="C:properties">
		<div class="menu">
			<xsl:call-template name="C:property">
				<xsl:with-param name="name" select="'Id'"/>
				<xsl:with-param name="value">
					<xsl:apply-templates select="." mode="C:id"/>
				</xsl:with-param>
			</xsl:call-template>
			<xsl:call-template name="C:property">
				<xsl:with-param name="name" select="'Type'"/>
				<xsl:with-param name="value">
					<xsl:apply-templates select="." mode="C:type"/>
				</xsl:with-param>
			</xsl:call-template>
			<div class="menu-item">
<!--
				<xsl:variable name="date">
					<xsl:apply-templates select="." mode="C:date"/>
				</xsl:variable>
				<xsl:variable name="company">
					<xsl:apply-templates select="." mode="C:company"/>
				</xsl:variable>
-->
				<xsl:value-of select="translate(
					concat(
						'Copyright &#169; ', 
							substring($date, 1, 4), 
						' ', 
						$company),
					' ', 
					'&#160;')"/>
			</div>
			<xsl:call-template name="C:property">
				<xsl:with-param name="name" select="'Version'"/>
				<xsl:with-param name="value">
					<xsl:apply-templates select="." mode="C:version"/>
				</xsl:with-param>
			</xsl:call-template>
		</div>
	</xsl:template>

	<!-- -->
	
	<xsl:template match="/C:section">
		<html>
			<head>
				<title>
					<xsl:value-of select="@name"/>
				</title>
				<style type="text/css">
					<xsl:value-of select="normalize-space($C:style)"/>
				</style>
			</head>
			<body>
				<table class="main">
					<tr>
						<td colspan="2" class="menu">
							<xsl:apply-templates select="." mode="C:header"/>
						</td>
					</tr>
					<xsl:variable name="path">
						<xsl:apply-templates select="." mode="C:path"/>
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
					<tr class="tr">
						<td class="menu">
							<xsl:apply-templates select="." mode="C:properties"/>
<!--
							<!- - Menu - ->
							<xsl:apply-templates select="." mode="C:menu"/>
							<!- - Language - ->
							<xsl:variable name="languages">
								<div class="menu">
									<xsl:apply-templates select="." mode="C:language"/>
								</div>
							</xsl:variable>
							<xsl:if test="string($languages)!=''">
								<xsl:copy-of select="$languages"/>
							</xsl:if>
							<!- - Files - ->
							<xsl:apply-templates select="." mode="C:files"/>
-->
						</td>
<!--
						<td class="content">
							<!- - Content - ->
							<xsl:apply-templates select="." mode="C:content"/>
						</td>
-->
					</tr>
				</table>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
