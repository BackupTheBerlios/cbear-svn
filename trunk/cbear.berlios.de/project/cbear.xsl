<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:prj="http://cbear.berlios.de/project"
	xmlns:cbear.html="http://cbear.berlios.de/html"
	exclude-result-prefixes="prj">

<xsl:import href="list.xsl"/>

<xsl:template match="prj:section" mode="prj:html.body">
	<table style="margin: 0 auto 0 auto;">
		<tr>
			<td style="vertical-align: top; width: 100%;">
				<div style="text-align: center; border: none;">
					<!--
					<img border="0" src="http://cbear.berlios.de/mainlogo.png"/>
					-->
					<img border="0" src="mainlogo.png"/>
				</div>
				<xsl:apply-imports/>
			</td>
			<xsl:copy-of select="document('cbear.xml')"/>			
		</tr>
	</table>
</xsl:template>

</xsl:stylesheet>
