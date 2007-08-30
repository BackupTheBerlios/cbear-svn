<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:B="http://cbear.berlios.de/bat"
	exclude-result-prefixes="C S B">

	<xsl:import href="html.xsl"/>

	<xsl:param name="C:nxslt"/>
	<xsl:param name="C:cbear"/>
	<xsl:param 
		name="C:html" select="concat($C:cbear, 'cbear.berlios.de/cms/html.xsl')"/>

	<!-- entry, index -->

	<xsl:template match="entry" mode="C:index">
		<xsl:param name="language"/>
		<xsl:param name="path"/>
		<B:command 
			name="CMS to HTML"
			text="{concat(
				$C:nxslt, ' ', 
				$path, @name, ' ', 
				$C:html, ' ',
				'-o ', $path, 'index', $language, '.html ',
				'xmlns:C=http://cbear.berlios.de/cms ',
				'C:extension=html')}"/>
	</xsl:template>

	<xsl:template match="entry"/>

	<xsl:template 
		match="entry[@kind='file' and substring-before(@name, '.')='index']">
		<xsl:param name="path"/>
		<xsl:variable name="after" select="substring-after(@name, '.')"/>
		<xsl:choose>
			<xsl:when test="$after='xml'">
				<xsl:apply-templates select="." mode="C:index">
					<xsl:with-param name="path" select="$path"/>
				</xsl:apply-templates>
			</xsl:when>
			<xsl:when test="substring-after($after, '.')='xml'">
				<xsl:apply-templates select="." mode="C:index">
					<xsl:with-param 
						name="language" 
						select="concat('.', substring-before($after, '.'))"/>
					<xsl:with-param name="path" select="$path"/>
				</xsl:apply-templates>
			</xsl:when>
		</xsl:choose>
	</xsl:template>

	<!-- entry, dir -->

	<xsl:template match="entry[@kind='dir' and @name!='']">
		<xsl:param name="path"/>
		<xsl:apply-templates 
			select="document(concat('../', @name, '/', $C:svn), .)/*/*">
			<xsl:with-param name="path" select="concat($path, @name, '/')"/>
		</xsl:apply-templates>
	</xsl:template>

	<!-- /C:section -->

	<xsl:template match="/C:section">
		<B:bat 
			name="C Bear CMS" 
			log="_list.log.xml" 
			stylesheet="{concat(
				'file:///', $C:cbear, 'cbear.berlios.de/bat/html.xsl')}">
			<xsl:apply-templates select="document($C:svn, .)/*/*"/>
		</B:bat>
	</xsl:template>

</xsl:stylesheet>
