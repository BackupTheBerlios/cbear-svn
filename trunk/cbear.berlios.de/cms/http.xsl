<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="S">

	<xsl:output method="html"/>

	<xsl:template match="/C:section">
		<html>
			<body id="body">
				<h1><xsl:value-of select="@name"/></h1>
				<h2>Blin</h2>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
