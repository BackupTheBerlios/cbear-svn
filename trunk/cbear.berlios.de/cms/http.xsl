<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns="http://www.w3.org/1999/xhtml"
	exclude-result-prefixes="S">

	<xsl:import href="html.xsl"/>

	<xsl:param name="C:current"/>

	<xsl:variable 
		name="C:http.html.path" select="substring-before($C:current, '?')"/>

	<xsl:variable 
		name="C:current.file.path" select="substring-after($C:current, '?')"/>

	<xsl:template name="C:directory">
		<xsl:param name="file.path"/>
		<xsl:if test="contains($file.path, '/')">
			<xsl:value-of select="concat(substring-before($file.path, '/'), '/')"/>
			<xsl:call-template name="C:directory">
				<xsl:with-param 
					name="file.path" select="substring-after($file.path, '/')"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:variable name="C:current.directory">
		<xsl:call-template name="C:directory">
			<xsl:with-param name="file.path" select="$C:current.file.path"/>
		</xsl:call-template>
	</xsl:variable>

	<xsl:template name="C:href">
		<xsl:param name="current.directory" select="$C:current.directory"/>
		<xsl:param name="path"/>
		<xsl:choose>
			<xsl:when test="substring($path, 1, 3) = '../'">
				<xsl:call-template name="C:href">
					<xsl:with-param name="current.directory">
						<xsl:call-template name="C:directory">
							<xsl:with-param 
								name="file.path" 
								select="substring(
									$current.directory, 1, string-length($current.directory) - 1)"/>
						</xsl:call-template>
					</xsl:with-param>
					<xsl:with-param name="path" select="substring($path, 4)"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat(
					$C:http.html.path, '?', $C:current.directory, $path, $C:index.link)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="/C:section">
		<table>
			<tr>
				<td>
					<xsl:apply-templates select="." mode="C:header"/>
				</td>
			</tr>
			<xsl:variable name="path">
				<xsl:apply-templates select="." mode="C:path"/>
			</xsl:variable>
			<xsl:if test="$path">
				<tr>
					<td>
						<xsl:copy-of select="$path"/>
					</td>
				</tr>
			</xsl:if>
		</table>
	</xsl:template>

</xsl:stylesheet>
