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
		<xsl:for-each select="entry[@kind='dir' and @path!='.']">
			<xsl:value-of select="concat(
				'call ',
				$C:cbear, 
				'cbear.berlios.de/cms/svn/one.build.bat ', 
				$C:target, 
				'/', 
				@path,
				'&#10;')"/>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>