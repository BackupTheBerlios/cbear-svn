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
	xmlns:api="http://cbear.sourceforge.net/api"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.sourceforge.net/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi api cpp">

<xsl:output method="xml" indent="yes"/>

<xsl:param name="api:com.cpp.xsd"/>
<xsl:param name="api:com.cpp.xsl"/>

<!--
<xsl:param name="api:com.cpp.name" select="/api:library/@id"/>
-->

<!-- * -->

<xsl:template match="*" mode="api:com.cpp">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag: &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- interface -->

<xsl:template match="api:interface" mode="api:com.cpp">
	<class>
		<type.ref><type.id id="{@id}"/></type.ref>
		<xsl:apply-templates select="*" mode="api:com.cpp"/>
	</class>
</xsl:template>

<!-- libray -->

<xsl:template match="api:library" mode="api:com.cpp">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$api:com.cpp.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<unit
		xsi:schemaLocation="{concat(
			'http://cbear.sourceforge.net/cpp ', $api:com.cpp.xsd)}"
		id="{@id}">
		<header>
			<include href="{concat(@id, '.odl.h')}"/>
			<namespace id="{translate(@id, '.\/', '___')}">
				<xsl:apply-templates select="*" mode="api:com.cpp"/>
			</namespace>
		</header>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="api:*">
	<xsl:apply-templates select="." mode="api:com.cpp"/>
</xsl:template>

</xsl:stylesheet>
