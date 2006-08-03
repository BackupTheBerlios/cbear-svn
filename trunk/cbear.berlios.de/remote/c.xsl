<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:R="http://cbear.berlios.de/remote"
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:output method="xml"/>

	<xsl:param name="R:cbear"/>

	<!-- coclass -->

	<xsl:template match="R:coclass">
		<xsl:param name="body"/>
		<C:function id="{concat(/R:library/@id, '_device_', @id)}">
			<C:id.ref id="void"/>
			<C:parameter id="_in">
				<C:id.ref type="_*">
					<C:id.ref id="char"/>
				</C:id.ref>
			</C:parameter>
			<C:parameter id="_out">
				<C:id.ref type="_*">
					<C:id.ref id="char"/>
				</C:id.ref>
			</C:parameter>
			<xsl:copy-of select="$body"/>
		</C:function>
	</xsl:template>

	<!-- library -->

	<xsl:template match="/R:library">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$R:cbear, 
				'cbear.berlios.de/c/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
		<C:unit id="{concat(@id, '.device')}">
			<C:h>
				<xsl:apply-templates select="R:*"/>
			</C:h>
			<C:c>
				<xsl:for-each select="R:coclass">
					<xsl:apply-templates select=".">
						<xsl:with-param name="body">
							<C:body>
								<C:switch>
								</C:switch>
							</C:body>
						</xsl:with-param>
					</xsl:apply-templates>
				</xsl:for-each>
			</C:c>
		</C:unit>
	</xsl:template>

</xsl:stylesheet>
