<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms">
	<xsl:output method="text" encoding="ascii"/>
	<xsl:param name="C:cbear"/>
	<xsl:param name="C:target"/>
	<xsl:template match="/info">
		<!--
		<xsl:variable name="path" select="entry[1]/@path"/>
		-->
		<xsl:for-each select="entry[@kind='dir' and position() != 1]">
			<xsl:value-of select="concat(
				'@call &#34;',
				$C:cbear, 
				'/cbear.berlios.de/cms/svn/one.build.bat&#34; &#34;',
				$C:target,
				'/',
				@path,
				'&#34;&#10;')"/>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>