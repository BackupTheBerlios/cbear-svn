<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms">
	<xsl:output method="text" encoding="ascii"/>
	<xsl:param name="C:target"/>
	<xsl:template match="/info">
		<xsl:value-of select="'@setlocal&#10;'"/>
		<xsl:for-each select="entry[@kind='dir' and position() != 1]">
			<xsl:value-of select="concat(
				'@set target=', $C:target, @path, '/&#10;')"/>
			<xsl:value-of select="
				'@call %cbear%cbear.berlios.de/cms/svn/one.build.bat&#10;'"/>
		</xsl:for-each>
		<xsl:value-of select="'@endlocal&#10;'"/>
	</xsl:template>
</xsl:stylesheet>