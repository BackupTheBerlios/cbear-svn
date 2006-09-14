<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:import href="html.xsl"/>

	<xsl:output method="text" encoding="ascii"/>

	<xsl:template match="/C:unit">
		<xsl:apply-templates select="C:h"/>
	</xsl:template>

</xsl:stylesheet>
