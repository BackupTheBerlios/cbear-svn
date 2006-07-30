<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear="http://cbear.berlios.de"
	extension-element-prefixes="exsl">

<xsl:output method="text" encoding="ascii"/>

<!-- File Name -->
<xsl:template name="url.filename">
	<xsl:param name="path"/>
	<xsl:choose>
		<xsl:when test="contains($path, '/')">
			<xsl:call-template name="url.filename">
				<xsl:with-param name="path" select="substring-after($path, '/')"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="."/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- Path -->
<xsl:template name="url.path">
	<xsl:param name="path"/>
	<xsl:if test="contains($path, '/')">
		<xsl:value-of select="concat(substring-before($path, '/'), '/')"/>
		<xsl:call-template name="url.path">
			<xsl:with-param 
				name="path" select="substring-after($path, '/')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- Back Path -->
<xsl:template name="url.backpath">
	<xsl:param name="path"/>
	<xsl:if test="contains($path, '/')">
		<xsl:text>../</xsl:text>
		<xsl:call-template name="url.backpath">
			<xsl:with-param name="path" select="substring-after($path, '/')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- Extension, Details -->
<xsl:template name="url.extension.detail">
	<xsl:param name="filename"/>
	<xsl:choose>
		<xsl:when test="contains($filename, '.')">
			<xsl:call-template name="url.extension.detail">
				<xsl:with-param 
					name="filename" select="substring-after($filename, '.')"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$filename"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- Extension -->
<xsl:template name="url.extension">
	<xsl:param name="path"/>
	<xsl:variable name="filename">
		<xsl:call-template name="url.filename">
			<xsl:with-param name="path" select="$path"/>
		</xsl:call-template>
	</xsl:variable>
	<xsl:if test="contains($filename, '.')">
		<xsl:call-template name="url.extension.detail">
			<xsl:with-param name="filename" select="substring-after($filename, '.')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

</xsl:stylesheet>
