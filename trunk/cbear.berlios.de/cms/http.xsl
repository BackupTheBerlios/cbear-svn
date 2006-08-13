<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns="http://www.w3.org/1999/xhtml"
	exclude-result-prefixes="S">

	<xsl:import href="html.xsl"/>

	<xsl:template match="/C:section">
		<div>
			<h1><xsl:value-of select="@name"/></h1>
			<h2><xsl:value-of select="@name"/></h2>
		</div>
	</xsl:template>

</xsl:stylesheet>
