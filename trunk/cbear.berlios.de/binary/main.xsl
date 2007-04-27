<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/cpp">

	<xsl:output method="xml"/>

	<xsl:template name="id">
		<xsl:param name="i"/>
		<xsl:param name="value"/>
		<xsl:if test="$i != 0">
			<xsl:call-template name="id">
				<xsl:with-param name="i" select="$i - 1"/>
				<xsl:with-param name="value" select="floor($value div 2)"/>
			</xsl:call-template>
		</xsl:if>
		<xsl:if test="$i mod 4 = 0">
			<xsl:value-of select="'_'"/>
		</xsl:if>
		<xsl:value-of select="$value mod 2"/>
	</xsl:template>

	<xsl:template name="const">
		<xsl:param name="width"/>
		<xsl:param name="value" select="255"/>
		<C:id.ref type="declare">
			<xsl:attribute name="id">
				<xsl:value-of select="_"/>
				<xsl:call-template name="id">
					<xsl:with-param name="i" select="$width - 1"/>
					<xsl:with-param name="value" select="$value"/>
				</xsl:call-template>
			</xsl:attribute>
			<C:id.ref type="const">
				<C:id.ref type="::">
					<C:id.ref/>
					<C:id.ref id="boost"/>
					<C:id.ref id="{concat('uint', $width, '_t')}"/>
				</C:id.ref>
			</C:id.ref>
			<C:id.ref type="value" id="{$value}"/>
		</C:id.ref>
		<xsl:if test="$value != 0">
			<xsl:call-template name="const">
				<xsl:with-param name="width" select="$width"/>
				<xsl:with-param name="value" select="$value - 1"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template match="/">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="'href=&#34;../cpp/html.xsl&#34; type=&#34;text/xsl&#34;'"/>
		</xsl:processing-instruction>
		<C:unit id="cbear.berlios.de/binary/main.hpp">
			<C:header>
				<C:namespace id="cbear.berlios.de">
					<C:namespace id="binary">
						<xsl:call-template name="const">
							<xsl:with-param name="width" select="8"/>
							<xsl:with-param name="value" select="255"/>
						</xsl:call-template>
						<xsl:call-template name="const">
							<xsl:with-param name="width" select="16"/>
							<xsl:with-param name="value" select="65535"/>
						</xsl:call-template>
					</C:namespace>
				</C:namespace>
			</C:header>
		</C:unit>
	</xsl:template>

</xsl:stylesheet>
