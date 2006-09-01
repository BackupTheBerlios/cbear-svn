<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:import href="sha1.xsl"/>

	<xsl:template name="H:sha1.test">
		<xsl:param name="text"/>
		
		<xsl:variable name="hex">
			<xsl:call-template name="H:ascii.hex">
				<xsl:with-param name="text" select="$text"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="concat($text, '&#10;')"/>
		<xsl:call-template name="H:sha1">
			<xsl:with-param name="source" select="$hex"/>
		</xsl:call-template>
		<xsl:value-of select="'&#10;'"/>
	</xsl:template>

	<xsl:template match="/">
		<html>
			<body>
				<pre>
					<xsl:call-template name="H:sha1.test"/>
					<xsl:call-template name="H:sha1.test">
						<xsl:with-param 
							name="text"
							select="'The quick brown fox jumps over the lazy dog.'"/>
					</xsl:call-template>
					<xsl:call-template name="H:sha1.test">
						<xsl:with-param 
							name="text"
							select="'The quick brown fox jumps over the lazy cog.'"/>
					</xsl:call-template>
					<xsl:call-template name="H:sha1.test">
						<xsl:with-param 
							name="text"
							select="'The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy cog.'"/>
					</xsl:call-template>
				</pre>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
