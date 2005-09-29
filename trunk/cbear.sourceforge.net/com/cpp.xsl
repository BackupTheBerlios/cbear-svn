<?xml version="1.0"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
	xmlns="http://cbear.sourceforge.net/cpp"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.sourceforge.net/com"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.sourceforge.net/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cpp">

<xsl:output method="xml" indent="yes"/>

<xsl:param name="odl:cpp.xsd"/>
<xsl:param name="odl:cpp.xsl"/>

<!-- * -->

<xsl:template match="*" mode="odl:cpp">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag: &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:cpp"/>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:cpp"/>

<!-- item -->

<xsl:template match="odl:item" mode="odl:cpp">
	<item id="{@id}" value="{odl:const/@value}"/>
</xsl:template>

<!-- enum -->

<xsl:template match="odl:enum" mode="odl:cpp">
	<xsl:variable name="name">
		<name.ref><id.ref id="{@id}"/></name.ref>
	</xsl:variable>
	<xsl:variable name="internal">
		<name.ref><id.ref/><id.ref id="{@id}"/></name.ref>
	</xsl:variable>
	<xsl:variable name="base">
		<name.ref>
			<id.ref/>
			<id.ref id="cbear_sourceforge_net"/>
			<id.ref id="policy"/>
			<id.ref id="wrap">
				<type.parameters>
					<xsl:copy-of select="$name"/>
					<xsl:copy-of select="$internal"/>
				</type.parameters>
			</id.ref>
		</name.ref>
	</xsl:variable>
	<class>
		<name.ref><id.ref id="{@id}"/></name.ref>
		<access access="public">
			<xsl:copy-of select="$base"/>
			<enum id="type">
				<xsl:apply-templates select="odl:item" mode="odl:cpp"/>
			</enum>
			<method id="{@id}"/>
			<method id="{@id}">
				<parameter id="X">
					<xsl:copy-of select="$internal"/>
				</parameter>
				<call>
					<xsl:copy-of select="$base"/>
					<exp><name.ref><id.ref id="X"/></name.ref></exp>
				</call>
				<body>
				</body>
			</method>
			<method id="{@id}">
				<parameter id="X">
					<name.ref><id.ref id="type"/></name.ref>
				</parameter>
				<call>
					<xsl:copy-of select="$base"/>
					<exp><name.ref><id.ref id="X"/></name.ref></exp>
				</call>
				<body>
				</body>
			</method>
		</access>
	</class>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:cpp">
	<xsl:apply-templates select="*" mode="odl:cpp"/>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:cpp">
	<typedef id="{@id}">
		<name.ref>
			<id.ref/>
			<id.ref id="cbear_sourceforge_net"/>
			<id.ref id="com"/>
			<id.ref id="object">				
				<type.parameters>
					<name.ref>
						<id.ref/>
						<id.ref id="{@id}"/>
					</name.ref>
				</type.parameters>
			</id.ref>
		</name.ref>
	</typedef>
</xsl:template>

<xsl:template match="odl:interface" mode="odl:cpp.object">
	<template>
		<id id="Base"/>
		<class>
			<name.ref>
				<id.ref id="object_content">				
					<type.parameters>
						<name.ref>
							<id.ref/>
							<id.ref id="{@id}"/>
						</name.ref>
						<name.ref><id.ref id="Base"/></name.ref>
					</type.parameters>
				</id.ref>
			</name.ref>
			<access access="public">
				<name.ref>
					<id.ref id="object_content">
						<type.parameters>
							<name.ref>
								<id.ref/>
								<id.ref id="{odl:type.ref/@id}"/>
							</name.ref>
							<name.ref><id.ref id="Base"/></name.ref>
						</type.parameters>
					</id.ref>
				</name.ref>
			</access>
		</class>
	</template>
</xsl:template>

<!-- libray -->

<xsl:template match="odl:library" mode="odl:cpp">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$odl:cpp.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<unit
		xsi:schemaLocation="{concat(
			'http://cbear.sourceforge.net/cpp ', $odl:cpp.xsd)}"
		id="{@id}">
		<header>
			<include href="{concat(@id, '.odl.h')}"/>
			<include href="cbear.sourceforge.net/com/object.hpp"/>
			<namespace id="{translate(@id, '.\/', '___')}">
				<xsl:apply-templates select="*" mode="odl:cpp"/>
			</namespace>
			<namespace id="cbear_sourceforge_net">
				<namespace id="com">
					<xsl:apply-templates select="odl:interface" mode="odl:cpp.object"/>
				</namespace>
			</namespace>
		</header>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:cpp"/>
</xsl:template>

</xsl:stylesheet>
