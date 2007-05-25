<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp">
<!--
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	extension-element-prefixes="exsl">
-->

<xsl:import href="html.xsl"/>

<xsl:output method="text" encoding="ascii"/>

<xsl:param name="cpp:cpp.root"/>

<xsl:template match="*" mode="cpp:cpp">
	<xsl:apply-templates select="." mode="cpp:html"/>
</xsl:template>

<xsl:template match="cpp:unit" mode="cpp:cpp">

	<xsl:variable name="header.content">
		<xsl:apply-templates select="cpp:header" mode="cpp:cpp"/>
	</xsl:variable>

	<exsl:document
		href="{concat($cpp:cpp.root, @id, '.hpp')}"
		method="text"
		encoding="ascii">
		<xsl:value-of select="$header.content"/>
	</exsl:document>

	<xsl:if test="cpp:code">
		<xsl:variable name="code.content">
			<xsl:apply-templates select="cpp:header" mode="cpp:cpp"/>
		</xsl:variable>
		<exsl:document
			href="{concat($cpp:cpp.root, @id, '.cpp')}"
			method="text"
			encoding="ascii">
			<xsl:value-of select="$code.content"/>
		</exsl:document>
	</xsl:if>
</xsl:template>

<xsl:template match="cpp:*">
	<xsl:apply-templates select="." mode="cpp:cpp"/>
</xsl:template>

</xsl:stylesheet>
