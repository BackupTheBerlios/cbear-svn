<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:import href="sha1.xsl"/>

	<xsl:template match="/*">
		<html>
			<body>
				<pre>
					<xsl:for-each select="*">
						<xsl:variable name="hex">
							<xsl:call-template name="H:ascii.hex">
								<xsl:with-param name="text" select="."/>
							</xsl:call-template>
						</xsl:variable>
						<xsl:value-of select="concat(., '&#10;')"/>
						<xsl:call-template name="H:sha1">
							<xsl:with-param name="source" select="$hex"/>
						</xsl:call-template>
						<xsl:value-of select="'&#10;'"/>
					</xsl:for-each>
				</pre>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
