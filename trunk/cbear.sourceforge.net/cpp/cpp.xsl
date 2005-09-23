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
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.sourceforge.net/cpp"
	xmlns:cbear.exslt.common="http://cbear.sourceforge.net/exslt/common"
	extension-element-prefixes="exsl">

<xsl:import href="../exslt/common/document.xsl"/>
<xsl:import href="html.xsl"/>

<xsl:output method="text" encoding="ascii"/>

<xsl:template match="*" mode="cpp:cpp">
	<xsl:apply-templates select="." mode="cpp:html"/>
</xsl:template>

<xsl:template match="cpp:unit" mode="cpp:cpp">

	<xsl:variable name="header">
		<document
			href="{concat(@id, '.hpp')}"
			method="text"
			encoding="ascii">
			<xsl:apply-templates select="cpp:header" mode="cpp:cpp"/>
		</document>
	</xsl:variable>

	<xsl:apply-templates 
		select="exsl:node-set($header)/*" mode="cbear.exslt.common:document"/>

	<xsl:if test="cpp:code">
		<xsl:variable name="code">
			<document
				href="{concat(@id, '.cpp')}"
				method="text"
				encoding="ascii">
				<xsl:apply-templates select="cpp:code" mode="cpp:cpp"/>
			</document>
		</xsl:variable>

		<xsl:apply-templates 
			select="exsl:node-set($code)/*" mode="cbear.exslt.common:document"/>
	</xsl:if>
</xsl:template>

<xsl:template match="cpp:*">
	<xsl:apply-templates select="." mode="cpp:cpp"/>
</xsl:template>

</xsl:stylesheet>
