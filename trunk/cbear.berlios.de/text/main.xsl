<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:txt="http://cbear.berlios.de/text"
	exclude-result-prefixes="txt xi">

<!-- Indent -->

<xsl:template match="*" mode="txt:main.indent">
	<xsl:text>&#9;</xsl:text>
</xsl:template>

<!-- Line -->

<xsl:template name="txt:main.line">
	<xsl:param name="text"/>
	<xsl:apply-templates select="ancestor::*" mode="txt:main.indent"/>
	<xsl:copy-of select="$text"/>	
	<xsl:text>&#10;</xsl:text>
</xsl:template>

<!-- Block -->

<xsl:template name="txt:main.block">
	<xsl:param name="begin" select="'{'"/>
	<xsl:param name="end" select="'}'"/>
	<xsl:param name="content"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text" select="$begin"/>
	</xsl:call-template>
	<xsl:copy-of select="$content"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text" select="$end"/>
	</xsl:call-template>
</xsl:template>

<!-- lower case characters -->

<xsl:variable name="txt:main.lowercase" select="'abcdefghijklmnopqrstuvwxyz'"/>

<!-- upper case characters -->

<xsl:variable name="txt:main.uppercase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

<!-- replace string -->
 
<xsl:template name="txt:replace-string">
	<xsl:param name="text"/>
	<xsl:param name="from"/>
	<xsl:param name="to"/>

	<xsl:choose>
		<xsl:when test="contains($text, $from)">
			<xsl:value-of select="concat(substring-before($text, $from), $to)"/>
			<xsl:call-template name="txt:replace-string">
				<xsl:with-param name="text" select="substring-after($text, $from)"/>
				<xsl:with-param name="from" select="$from"/>
				<xsl:with-param name="to" select="$to"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$text"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

</xsl:stylesheet>
