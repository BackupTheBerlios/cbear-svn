<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns="http://www.w3.org/1999/xhtml"
	exclude-result-prefixes="S">

	<xsl:import href="html.xsl"/>

	<xsl:template match="/C:section">
		<table>			
			<tr>
				<td>1</td>
			</tr>
			<tr>
				<td>
					<xsl:apply-templates select="." mode="C:header"/>
				</td>
			</tr>
		</table>
	</xsl:template>

</xsl:stylesheet>
