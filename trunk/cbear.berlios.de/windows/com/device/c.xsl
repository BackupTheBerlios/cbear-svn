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

	<!-- coclass -->

	<xsl:template match="O:coclass" mode="D:coclass">
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

	<xsl:template match="O:coclass" mode="D:h">
		<xsl:apply-templates select="." mode="D:coclass"/>
	</xsl:template>

	<!-- c.count -->
	
	<xsl:template match="O:interface" mode="D:c.count.current">
		<xsl:variable name="parent">
			<xsl:apply-templates select="O:type.ref" mode="D:c.count.current"/>	
		</xsl:variable>
		<xsl:value-of select="$parent + 1"/>
	</xsl:template>

	<xsl:template match="O:type.ref" mode="D:c.count.current">
		<xsl:apply-templates 
			select="/O:library/O:interface[current()/@id=@id]" 
			mode="D:c.count.current"/>
	</xsl:template>

	<xsl:template match="O:type.ref[@library]" mode="D:c.count.current">
		<xsl:apply-templates 
			select="
				document(concat(@library, '.odl.xml'), .)/
					O:library/O:interface[current()/@id=@id]"
			mode="D:c.count.current"/>
	</xsl:template>

	<xsl:template 
		match="O:type.ref[@library='stdole' and @id='IUnknown']" 
		mode="D:c.count.current">
		<xsl:value-of select="0"/>
	</xsl:template>

	<xsl:template 
		match="O:type.ref[@library='stdole' and @id='IDispatch']"
		mode="D:c.count.current">
		<xsl:value-of select="0"/>
	</xsl:template>

	<xsl:template match="O:type.ref" mode="D:c.count">
		<xsl:variable name="current">
			<xsl:apply-templates select="." mode="D:c.count.current"/>
		</xsl:variable>
		<xsl:variable name="next">
			<xsl:apply-templates select="following::O:type.ref[1]" mode="D:c.count"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="string($next)=''">
				<xsl:value-of select="$current"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$next + $current"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- c -->

	<xsl:template match="*" mode="D:c"/>

	<xsl:template match="O:coclass" mode="D:c">
		<xsl:apply-templates select="." mode="D:coclass">
			<xsl:with-param name="body">
				<C:body>
					<C:switch>
						<C:id.ref type="*_">
							<C:id.ref id="_in"/>
						</C:id.ref>
						<C:body>
							<C:case>
								<C:id.ref type="const" value="0"/>
							</C:case>
							<C:exp>
								<C:id.ref type="=">
									<C:id.ref type="*_">
										<C:id.ref id="_out"/>
									</C:id.ref>
									<xsl:variable name="count">
										<xsl:apply-templates 
											select="O:type.ref[1]" mode="D:c.count"/>
									</xsl:variable>
									<C:id.ref type="const" value="{$count}"/>
								</C:id.ref>
							</C:exp>
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
