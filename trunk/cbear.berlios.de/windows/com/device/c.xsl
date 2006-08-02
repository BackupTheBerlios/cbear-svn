<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:D="http://cbear.berlios.de/windows/com/device" 
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:output method="xml"/>

	<xsl:param name="D:cbear"/>

	<!-- coclass -->

	<xsl:template match="D:coclass">
		<xsl:param name="body"/>
		<C:function id="{concat(/D:library/@id, '_device_', @id)}">
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

	<xsl:template match="/D:library">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$D:cbear, 
				'cbear.berlios.de/c/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
		<C:unit id="{concat(@id, '.device')}">
			<C:h>
				<xsl:apply-templates select="D:*"/>
			</C:h>
			<C:c>
				<xsl:for-each select="D:coclass">
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
