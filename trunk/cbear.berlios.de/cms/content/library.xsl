<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	exclude-result-prefixes="C">

	<xsl:variable 
		name="C:content.library" 
		select="''"/>

	<xsl:template match="C:library" mode="C:content">
		<div>
			<b>COM Library:</b>
			<xsl:value-of select="' '"/>
			<a href="{concat(@href, @id, '.odl.xml')}">
				<xsl:value-of select="@id"/>
			</a>
		</div>
	</xsl:template>

</xsl:stylesheet>
