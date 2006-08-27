<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:variable name="C:source.comment" select="'color: #FF00FF;'"/>

	<xsl:template match="comment()" mode="C:source">
		<xsl:call-template name="C:span">
			<xsl:with-param name="style" select="$C:source.comment"/>
			<xsl:with-param name="text" select="concat('&lt;!--', ., '--&gt;')"/>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>
