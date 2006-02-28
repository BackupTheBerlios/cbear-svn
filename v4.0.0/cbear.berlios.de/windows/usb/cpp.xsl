<?xml version="1.0"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-->
<xsl:stylesheet 
	version="1.0"
	xmlns="http://cbear.berlios.de/cpp"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.berlios.de/windows/com"
	xmlns:usb="http://cbear.berlios.de/windows/usb"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cpp">

<xsl:import href="../com/cpp.xsl"/>

<xsl:output method="xml"/>

<xsl:param name="usb:cpp.xsl"/>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="usb:cpp.size">
	<xsl:variable name="id" select="@id"/>
	<xsl:if test="not(/odl:library/odl:*[@id=$id])">
		<xsl:message terminate="yes">
			<xsl:value-of select="concat('Unknown type: ', @id)"/>
		</xsl:message>
	</xsl:if>
	<xsl:apply-templates select="/odl:library/odl:*[@id=$id]" mode="usb:cpp.size"/>
</xsl:template>

<xsl:template match="odl:type.ref[@id='VARIANT_BOOL']" mode="usb:cpp.size">
	<parameter>1</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='BYTE']" mode="usb:cpp.size">
	<parameter>1</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='USHORT']" mode="usb:cpp.size">
	<parameter>2</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='ULONG']" mode="usb:cpp.size">
	<parameter>4</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='LONG']" mode="usb:cpp.size">
	<parameter>4</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='DOUBLE']" mode="usb:cpp.size">
	<parameter>8</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='DATE']" mode="usb:cpp.size">
	<parameter>8</parameter>
</xsl:template>

<xsl:template match="odl:type.ref[@id='array']" mode="usb:cpp.size">
	<xsl:variable name="size">
		<xsl:apply-templates select="odl:type.ref" mode="usb:cpp.size"/>
	</xsl:variable>
	<xsl:value-of 
		select="sum(exsl:node-set($size)/cpp:parameter) * odl:const/@value"/>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="usb:cpp.size">
	<xsl:apply-templates select="odl:type.ref" mode="usb:cpp.size"/>
</xsl:template>

<xsl:template match="odl:type.ref[@id='BSTR']" mode="usb:cpp.size"/>

<xsl:template match="odl:type.ref[@id='SAFEARRAY']" mode="usb:cpp.size"/>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="usb:cpp.size">
	<xsl:apply-templates 
		select="odl:struct/odl:object/odl:type.ref" mode="usb:cpp.size"/>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="usb:cpp.size"/>

<xsl:template match="odl:interface" mode="usb:cpp">
	<xsl:for-each select="odl:method">
		<xsl:variable name="id.long">
			<xsl:apply-templates select="." mode="odl:cpp.method.id.long"/>
		</xsl:variable>
		<method id="{$id.long}">
			<xsl:apply-templates select="." mode="odl:cpp.method.id.ref"/>
			<xsl:apply-templates select="odl:parameter" mode="odl:cpp"/>
			<override/>
			<body>
				<xsl:variable name="com">
					<id.ref/>
					<id.ref id="cbear_berlios_de"/>
					<id.ref id="windows"/>
					<id.ref id="com"/>
				</xsl:variable>
				<xsl:variable name="in-size">
					<xsl:apply-templates 
						select="odl:parameter[odl:attribute/@id='in']/odl:type.ref" 
						mode="usb:cpp.size"/>
				</xsl:variable>
				<xsl:variable name="out-size">
					<xsl:apply-templates 
						select="odl:parameter[odl:attribute/@id='out']/odl:type.ref" 
						mode="usb:cpp.size"/>
				</xsl:variable>
				<id.ref type="declare" id="archive">
					<id.ref type="::">
						<id.ref id="IoType"/>
						<id.ref type="&lt;&gt;" id="archive_t">					
							<id.ref 
								type="value"
								id="{sum(exsl:node-set($in-size)/cpp:parameter) + 1}"/>
							<id.ref
								type="value" 
								id="{sum(exsl:node-set($out-size)/cpp:parameter)}"/>
						</id.ref>
					</id.ref>
				</id.ref>
				<xsl:for-each select="odl:parameter[odl:attribute/@id='retval']">
					<id.ref 
						type="declare" 
						id="{concat('_', count(preceding-sibling::odl:parameter))}">
						<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
					</id.ref>
				</xsl:for-each>
				<xsl:for-each	select="odl:parameter[odl:attribute/@id='in']">
					<id.ref type="&lt;&lt;">
						<id.ref id="archive"/>
						<id.ref 
							id="{concat('_', count(preceding-sibling::odl:parameter))}"/>
					</id.ref>
				</xsl:for-each>
				<id.ref type="-&gt;">
					<id.ref id="this"/>
					<id.ref type="()" id="Io">
						<id.ref id="archive"/>
					</id.ref>
				</id.ref>
				<xsl:for-each	select="odl:parameter[odl:attribute/@id='out']">
					<id.ref type="&gt;&gt;">
						<id.ref id="archive"/>
						<id.ref 
							id="{concat('_', count(preceding-sibling::odl:parameter))}"/>
					</id.ref>
				</xsl:for-each>
				<xsl:for-each select="odl:parameter[odl:attribute/@id='retval']">
					<id.ref type="return">
						<id.ref 
							id="{concat('_', count(preceding-sibling::odl:parameter))}"/>
					</id.ref>
				</xsl:for-each>
			</body>
		</method>		
	</xsl:for-each>
</xsl:template>

<!-- library -->

<xsl:template match="odl:library" mode="usb:cpp">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$usb:cpp.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<unit id="{concat('usb.', @id)}">
		<header>
			<include href="{concat(@id, '.hpp')}"/>
			<namespace id="usb">
				<namespace id="{@id}">				
					<xsl:for-each select="odl:interface">
						<template>
							<id id="IoType"/>
							<class>
								<id.ref id="{@id}"/>
								<access access="public">
									<id.ref type="::">
										<id.ref/>
										<id.ref id="{../@id}"/>
										<id.ref id="{@id}"/>
										<id.ref id="implementation_type"/>
									</id.ref>							
									<method id="{@id}">
										<parameter id="Io">
											<id.ref type="&amp;">
												<id.ref type="const">
													<id.ref id="IoType"/>
												</id.ref>
											</id.ref>
										</parameter>
										<ctor>
											<id.ref type="()" id="Io">
												<id.ref id="Io"/>
											</id.ref>
										</ctor>
										<body>
										</body>
									</method>
									<xsl:apply-templates select="." mode="usb:cpp"/>
								</access>
								<access access="private">
									<object id="Io">
										<id.ref id="IoType"/>
									</object>									
								</access>
							</class>	
						</template>
					</xsl:for-each>
				</namespace>
			</namespace>
		</header>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="usb:cpp"/>
</xsl:template>

</xsl:stylesheet>
