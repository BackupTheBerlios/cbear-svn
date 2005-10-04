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
	xmlns:odl="http://cbear.berlios.de/com"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:txt="http://cbear.berlios.de/text"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cpp txt">

<xsl:import href="../text/main.xsl"/>

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
		<id.ref id="{@id}"/>
	</xsl:variable>
	<xsl:variable name="internal">
		<id.ref type="::"><id.ref/><id.ref id="{@id}"/></id.ref>
	</xsl:variable>
	<xsl:variable name="base">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="policy"/>
			<id.ref id="wrap" type="&lt;&gt;">
				<xsl:copy-of select="$name"/>
				<xsl:copy-of select="$internal"/>
			</id.ref>
		</id.ref>
	</xsl:variable>
	<class>
		<id.ref id="{@id}"/>
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
				<ctor>
					<id.ref>
						<xsl:copy-of select="$base"/>
						<id.ref type="()">
							<id.ref id="X"/>
						</id.ref>
					</id.ref>
				</ctor>
				<body>
				</body>
			</method>
			<method id="{@id}">
				<parameter id="X"><id.ref id="type"/></parameter>
				<ctor>
					<id.ref>
						<xsl:copy-of select="$base"/>
						<id.ref type="()">
							<id.ref id="X"/>
						</id.ref>
					</id.ref>
				</ctor>
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

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:cpp">
	<id.ref id="{concat(
		translate(@id, $txt:main.uppercase, $txt:main.lowercase), '_t')}">
		<xsl:if test="odl:type.ref">
			<xsl:attribute name="type">&lt;&gt;</xsl:attribute>
			<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
		</xsl:if>
	</id.ref>
</xsl:template>

<xsl:template 
	match="odl:type.ref[/odl:library/odl:*/@id=@id]" mode="odl:cpp">
	<id.ref type="::">
		<id.ref id="{/odl:library/@id}"/>
		<id.ref id="{@id}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:cpp">
	<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
</xsl:template>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:cpp">
	<parameter id="{concat('_', position())}">
		<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
	</parameter>
</xsl:template>

<xsl:template match="odl:parameter[odl:attribute/@id='retval']" mode="odl:cpp"/>

<!-- method -->

<xsl:template match="odl:method" mode="odl:cpp.method.id.ref">
	<id.ref id="void"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:parameter/odl:attribute/@id='retval']" 
	mode="odl:cpp.method.id.ref">
	<xsl:apply-templates select="
		odl:parameter[odl:attribute/@id='retval']/odl:type.ref" mode="odl:cpp"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.method.id">
	<xsl:value-of select="@id"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:cpp.method.id">
	<xsl:value-of select="concat('get_', @id)"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:cpp.method.id">
	<xsl:value-of select="concat('put_', @id)"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="odl:cpp.method.id"/>
	</xsl:variable>
	<method id="{$id}">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.ref"/>
		<xsl:apply-templates select="odl:parameter" mode="odl:cpp"/>
		<body>
			<id.ref type="::">
				<id.ref id="exception"/>
				<id.ref id="handle" type="()">
					<id.ref id="this"/>
					<id.ref id="{@id}"/>
				</id.ref>
			</id.ref>
		</body>
	</method>	
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:cpp">
	<typedef id="{@id}">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="com"/>
			<id.ref id="object" type="&lt;&gt;">				
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
			</id.ref>
		</id.ref>
	</typedef>
</xsl:template>

<xsl:template match="odl:interface" mode="odl:cpp.object">
	<template>
		<id id="Base"/>
		<class>
			<id.ref id="object_content" type="&lt;&gt;">				
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
				<id.ref id="Base"/>
			</id.ref>
			<access access="public">
				<id.ref id="object_content" type="&lt;&gt;">
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{odl:type.ref/@id}"/>
					</id.ref>
					<id.ref id="Base"/>
				</id.ref>
				<xsl:apply-templates select="odl:method" mode="odl:cpp"/>
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
			'http://cbear.berlios.de/cpp ', $odl:cpp.xsd)}"
		id="{@id}">
		<header>
			<include href="{concat(@id, '.odl.h')}"/>
			<include href="cbear.berlios.de/com/object.hpp"/>
			<namespace id="{translate(@id, '.\/', '___')}">
				<xsl:apply-templates select="*" mode="odl:cpp"/>
			</namespace>
			<namespace id="cbear_berlios_de">
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
