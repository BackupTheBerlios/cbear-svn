<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:import href="any.xsl"/>
	<xsl:import href="a.xsl"/>
	<xsl:import href="section.xsl"/>
	<xsl:import href="../source/main.xsl"/>

	<xsl:template match="/C:section" mode="C:content">
		<xsl:apply-templates select="." mode="C:content.table"/>
		<div class="menu">
			<div class="content-section-content">
				<xsl:apply-templates select="@title" mode="C:content.title"/>
				<xsl:apply-templates select="." mode="C:content.inside"/>
			</div>
		</div>
	</xsl:template>

</xsl:stylesheet>
