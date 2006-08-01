<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:O="http://cbear.berlios.de/windows/com"
	xmlns:D="http://cbear.berlios.de/windows/com/device">

	<xsl:output method="xml"/>

	<xsl:param name="D:cbear"/>

	<!-- size, * -->

	<xsl:template match="O:*" mode="D:size">
		<D:size library="{/O:library/@id}" id="{@id}">unknown</D:size>
	</xsl:template>

	<!-- size, enum -->

	<xsl:template match="O:enum" mode="D:size">
		<D:size library="{/O:library/@id}" id="{@id}">1</D:size>
	</xsl:template>

	<!-- size, struct -->

	<xsl:template match="O:struct" mode="D:size">
		<D:struct library="{/O:library/@id}" id="{@id}">
			<xsl:apply-templates select="O:object/O:type.ref" mode="D:size"/>
		</D:struct>
	</xsl:template>

	<!-- size, typedef -->

	<xsl:template match="O:typedef" mode="D:size">
		<xsl:apply-templates select="O:*" mode="D:size"/>
	</xsl:template>

	<!-- size, type.ref -->

	<xsl:template match="O:type.ref" mode="D:size">
		<xsl:variable name="content">
			<xsl:apply-templates 
				select="/O:library/O:*[current()/@id=@id]" mode="D:size"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($content)=''">
				<D:size id="{@id}">unknown</D:size>
			</xsl:when>
			<xsl:otherwise>
				<xsl:copy-of select="$content"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='CHAR']" mode="D:size">
		<D:size id="{@id}">1</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='BYTE']" mode="D:size">
		<D:size id="{@id}">1</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='SHORT']" mode="D:size">
		<D:size id="{@id}">2</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='USHORT']" mode="D:size">
		<D:size id="{@id}">2</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='LONG']" mode="D:size">
		<D:size id="{@id}">4</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='ULONG']" mode="D:size">
		<D:size id="{@id}">4</D:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='*']" mode="D:size">
		<xsl:apply-templates select="O:type.ref" mode="D:size"/>
	</xsl:template>

	<xsl:template name="D:size.array">
		<xsl:param name="value"/>
		<xsl:param name="size"/>
		<xsl:if test="$size &gt; 0">
			<xsl:copy-of select="$value"/>
			<xsl:call-template name="D:size.array">
				<xsl:with-param name="value" select="$value"/>
				<xsl:with-param name="size" select="$size - 1"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='[]']" mode="D:size">
		<D:array>
			<xsl:call-template name="D:size.array">
				<xsl:with-param name="value">
					<xsl:apply-templates select="O:type.ref" mode="D:size"/>
				</xsl:with-param>
				<xsl:with-param name="size" select="O:const/@value"/>
			</xsl:call-template>
		</D:array>
	</xsl:template>

	<xsl:template match="O:type.ref[@library]" mode="D:size">
		<xsl:variable name="content">
			<xsl:apply-templates 
				select="
					document(concat(@library, '.odl.xml'), .)/
					O:library/O:*[current()/@id=@id]"
				mode="D:size"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($content)=''">
				<D:size library="{@library}" id="{@id}">unknown</D:size>
			</xsl:when>
			<xsl:otherwise>
				<xsl:copy-of select="$content"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- interface -->

	<xsl:template match="O:interface">
		<D:interface 
			library="{/O:library/@id}" 
			id="{@id}" 
			uuid="{O:attribute[@id='uuid']/O:value}">
			<xsl:apply-templates select="O:type.ref"/>		
			<xsl:for-each select="O:method">
				<D:method id="{@id}">
					<xsl:for-each select="O:parameter">
						<D:parameter>
							<xsl:if test="O:attribute[@id='in']"><D:in/></xsl:if>
							<xsl:if test="O:attribute[@id='out']"><D:out/></xsl:if>
							<xsl:apply-templates select="O:type.ref" mode="D:size"/>
						</D:parameter>
					</xsl:for-each>
				</D:method>
			</xsl:for-each>
		</D:interface>
	</xsl:template>

	<!-- type.ref -->

	<xsl:template match="O:type.ref">
		<xsl:apply-templates select="/O:library/O:interface[current()/@id=@id]"/>
	</xsl:template>

	<xsl:template match="O:type.ref[@library]">
		<xsl:apply-templates select="
			document(concat(@library, '.odl.xml'), .)/
			O:library/O:interface[current()/@id=@id]"/>
	</xsl:template>

	<!-- library -->
		
	<xsl:template match="/O:library">
<!--
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$D:cbear, 
				'cbear.berlios.de/windows/com/device/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
-->
		<D:library id="{@id}" uuid="{O:attribute[@id='uuid']/O:value}">
			<xsl:for-each select="O:coclass">
				<D:coclass 
					id="{@id}" 
					uuid="{O:attribute[@id='uuid']/O:value}">
					<xsl:apply-templates select="O:type.ref"/>
				</D:coclass>
			</xsl:for-each>
		</D:library>
	</xsl:template>

</xsl:stylesheet>
