<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="S">

	<xsl:output method="xml" indent="no"/>

	<xsl:template match="/C:section">
		<div>
			<div>
				<h1><xsl:value-of select="@name"/></h1>
				<h2>Blin</h2>
			</div>
		</div>
	</xsl:template>

</xsl:stylesheet>
