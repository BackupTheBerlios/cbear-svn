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

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:cpp">
	<typedef id="{@id}">
		<type.ref>
			<type.id/>
			<type.id id="cbear_sourceforge_net"/>
			<type.id id="com"/>
			<type.id id="object">				
				<type.parameters>
					<type.ref>
						<type.id/>
						<type.id id="{@id}"/>
					</type.ref>
				</type.parameters>
			</type.id>
		</type.ref>
	</typedef>
<!--
	<class>
		<type.ref><type.id id="{@id}"/></type.ref>
		<access access="public">
			<type.ref>
				<type.id/>
				<type.id id="cbear_sourceforge_net"/>
				<type.id id="com"/>
				<type.id id="object">				
					<type.parameters>
						<type.ref>
							<type.id/>
							<type.id id="{@id}"/>
						</type.ref>
					</type.parameters>
				</type.id>
			</type.ref>
			<xsl:apply-templates select="*" mode="odl:cpp"/>
		</access>
	</class>
-->
</xsl:template>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:cpp"/>

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
		</header>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:cpp"/>
</xsl:template>

</xsl:stylesheet>
