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
	xmlns:cs="http://cbear.berlios.de/cs"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:txt="http://cbear.berlios.de/text"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cs txt">

<xsl:import href="../text/main.xsl"/>

<xsl:output method="xml"/>

<xsl:param name="odl:cs.xsd"/>
<xsl:param name="odl:cs.xsl"/>
<xsl:param name="odl:cs.path"/>

<!-- * -->

<xsl:template match="*" mode="odl:cpp">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag: &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- libray -->

<xsl:template match="odl:library" mode="odl:cpp">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$odl:cs.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<xsl:variable name="path" select="concat($odl:cs.path, @id)"/>
	<unit
		xsi:schemaLocation="{concat(
			'http://cbear.berlios.de/cs ', $odl:cs.xsd)}"
		id="{$path}">
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:cpp"/>
</xsl:template>

</xsl:stylesheet>
