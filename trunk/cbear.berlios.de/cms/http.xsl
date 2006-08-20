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
