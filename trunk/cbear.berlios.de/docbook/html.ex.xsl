<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	exclude-result-prefixes="xi">

<xsl:import href="html.xsl"/>

<!-- Include, Reference -->
<xsl:template match="xi:include" mode="docbook.html.href">
	<xsl:variable name="name">
		<xsl:apply-templates select="." mode="docbook.html.name"/>
	</xsl:variable>
	<xsl:value-of select="concat($name, '.html')"/>
</xsl:template>

</xsl:stylesheet>
