<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:O="http://cbear.berlios.de/windows/com"
	xmlns:D="http://cbear.berlios.de/windows/com/device" 
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:output method="xml"/>

	<xsl:param name="D:cbear"/>

	<xsl:variable 
		name="D:c.id" 
		select="translate(/O:library/@id, '.', '_')"/>

	<!-- interface -->

	<xsl:template match="O:interface" mode="D:interface">
		<xsl:param name="body"/>
		<C:function id="{translate(
			concat(/O:library/@id, '_device_', @id), '.', '_')}">
			<C:id.ref id="int"/>
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
	
	<!-- h -->
	
	<xsl:template match="*" mode="D:h"/>

	<xsl:template match="O:interface" mode="D:h">
		<xsl:apply-templates select="." mode="D:interface"/>
	</xsl:template>

	<!-- c -->
	
	<xsl:template match="*" mode="D:c"/>

	<xsl:template match="O:interface" mode="D:c">
		<xsl:apply-templates select="." mode="D:interface">
			<xsl:with-param name="body">
				<C:body>
					<C:switch>
						<C:id.ref type="*_">
							<C:id.ref type="()">
								<C:id.ref type="_*">
									<C:id.ref id="uint16"/>
								</C:id.ref>
							</C:id.ref>
							<C:id.ref id="_in"/>
						</C:id.ref>
						<C:body>
							<C:case>
								<C:id.ref type="const" value="0"/>
							</C:case>
							<C:break/>
							<C:case>
								<C:id.ref type="const" value="1"/>
							</C:case>
							<C:break/>							
						</C:body>
					</C:switch>
				</C:body>
			</xsl:with-param>
		</xsl:apply-templates>
	</xsl:template>
	
	<!-- library -->
		
	<xsl:template match="/O:library">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$D:cbear, 
				'cbear.berlios.de/c/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
		<C:unit id="{concat(/O:library/@id, '.device')}">
			<C:h>
				<xsl:apply-templates select="*" mode="D:h"/>
			</C:h>
			<C:c>
				<xsl:apply-templates select="*" mode="D:c"/>
			</C:c>
		</C:unit>
	</xsl:template>

</xsl:stylesheet>
