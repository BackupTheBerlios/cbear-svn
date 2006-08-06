<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:S="svn:"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:B="http://cbear.berlios.de/bat"
	exclude-result-prefixes="C S B">

	<xsl:import href="list.xsl"/>

	<xsl:param name="C:_7z" select="'&#34;c:\Program Files\7-zip\7z&#34;'"/>

	<!-- /C:section -->

	<xsl:template match="/C:section">
		<B:bat
			name="C Bear Build" 
			log="_list.log.xml"
			stylesheet="{concat(
				'file:///', $C:cbear, 'cbear.berlios.de/bat/html.xsl')}">
			<xsl:apply-templates select="document($C:svn, .)/*/*"/>
			<xsl:variable name="id">
				<xsl:apply-templates select="." mode="C:id"/>
			</xsl:variable>
			<xsl:variable name="version">
				<xsl:apply-templates select="." mode="C:version"/>
			</xsl:variable>
			<B:command 
				name="7z"
				text="{concat(
					$C:_7z, ' ',
					'a ',
					'-r ',
					'-bd ',
					'-tzip ',
					'-x@cms/x.txt ',
					'../', $id, '-', $version , '.zip ',
					'*')}"/>
		</B:bat>
	</xsl:template>

</xsl:stylesheet>
