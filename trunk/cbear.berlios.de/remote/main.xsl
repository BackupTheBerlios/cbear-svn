<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:O="http://cbear.berlios.de/windows/com"
	xmlns:R="http://cbear.berlios.de/remote">

	<xsl:output method="xml"/>

	<xsl:param name="R:cbear"/>

	<!-- size, * -->

	<xsl:template match="O:*" mode="R:size">
		<R:size library="{/O:library/@id}" id="{@id}">unknown</R:size>
	</xsl:template>

	<!-- size, enum -->

	<xsl:template match="O:enum" mode="R:size">
		<R:size library="{/O:library/@id}" id="{@id}">1</R:size>
	</xsl:template>

	<!-- size, struct -->

	<xsl:template match="O:struct" mode="R:size">
		<R:struct library="{/O:library/@id}" id="{@id}">
			<xsl:apply-templates select="O:object/O:type.ref" mode="R:size"/>
		</R:struct>
	</xsl:template>

	<!-- size, typedef -->

	<xsl:template match="O:typedef" mode="R:size">
		<xsl:apply-templates select="O:*" mode="R:size"/>
	</xsl:template>

	<!-- size, type.ref -->

	<xsl:template match="O:type.ref" mode="R:size">
		<xsl:variable name="content">
			<xsl:apply-templates 
				select="/O:library/O:*[current()/@id=@id]" mode="R:size"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($content)=''">
				<R:size id="{@id}">unknown</R:size>
			</xsl:when>
			<xsl:otherwise>
				<xsl:copy-of select="$content"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='CHAR']" mode="R:size">
		<R:size id="{@id}">1</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='BYTE']" mode="R:size">
		<R:size id="{@id}">1</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='SHORT']" mode="R:size">
		<R:size id="{@id}">2</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='USHORT']" mode="R:size">
		<R:size id="{@id}">2</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='LONG']" mode="R:size">
		<R:size id="{@id}">4</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='ULONG']" mode="R:size">
		<R:size id="{@id}">4</R:size>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='*']" mode="R:size">
		<xsl:apply-templates select="O:type.ref" mode="R:size"/>
	</xsl:template>

	<xsl:template name="R:size.array">
		<xsl:param name="value"/>
		<xsl:param name="size"/>
		<xsl:if test="$size &gt; 0">
			<xsl:copy-of select="$value"/>
			<xsl:call-template name="R:size.array">
				<xsl:with-param name="value" select="$value"/>
				<xsl:with-param name="size" select="$size - 1"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template match="O:type.ref[@id='[]']" mode="R:size">
		<R:array>
			<xsl:call-template name="R:size.array">
				<xsl:with-param name="value">
					<xsl:apply-templates select="O:type.ref" mode="R:size"/>
				</xsl:with-param>
				<xsl:with-param name="size" select="O:const/@value"/>
			</xsl:call-template>
		</R:array>
	</xsl:template>

	<xsl:template match="O:type.ref[@library]" mode="R:size">
		<xsl:variable name="content">
			<xsl:apply-templates 
				select="
					document(concat(@library, '.odl.xml'), .)/
					O:library/O:*[current()/@id=@id]"
				mode="R:size"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($content)=''">
				<R:size library="{@library}" id="{@id}">unknown</R:size>
			</xsl:when>
			<xsl:otherwise>
				<xsl:copy-of select="$content"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- interface -->

	<xsl:template match="O:interface">
		<R:interface 
			library="{/O:library/@id}" 
			id="{@id}" 
			uuid="{O:attribute[@id='uuid']/O:value}">
			<xsl:apply-templates select="O:type.ref"/>		
			<xsl:for-each select="O:method">
				<R:method id="{@id}">
					<xsl:for-each select="O:parameter">
						<R:parameter>
							<xsl:if test="O:attribute[@id='in']"><R:in/></xsl:if>
							<xsl:if test="O:attribute[@id='out']"><R:out/></xsl:if>
							<xsl:apply-templates select="O:type.ref" mode="R:size"/>
						</R:parameter>
					</xsl:for-each>
				</R:method>
			</xsl:for-each>
		</R:interface>
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
				$R:cbear, 
				'cbear.berlios.de/windows/com/device/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
-->
		<R:library 
			id="{substring-before(
				substring-after(
					O:attribute[
						@id='custom' and 
						O:value[1]='0F21F359-AB84-41E8-9A78-36D110E6D2F9']/O:value[2], 
					'&#34;'),
				'&#34;')}" 
			uuid="{O:attribute[@id='uuid']/O:value}">
			<xsl:for-each select="O:coclass">
				<R:coclass 
					id="{@id}" 
					uuid="{O:attribute[@id='uuid']/O:value}">
					<xsl:apply-templates select="O:type.ref"/>
				</R:coclass>
			</xsl:for-each>
		</R:library>
	</xsl:template>

</xsl:stylesheet>
