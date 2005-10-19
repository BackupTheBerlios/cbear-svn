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
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear="http://cbear.berlios.de"
	extension-element-prefixes="exsl">

<xsl:import href="../url/main.xsl"/>

<!-- Any -->
<xsl:template match="*" mode="test">
	<xsl:param name="path"/>
	<xsl:apply-templates select="*" mode="test">
		<xsl:with-param name="path" select="$path"/>
	</xsl:apply-templates>
</xsl:template>

<!-- X Include -->
<xsl:template match="xi:include" mode="test">
	<xsl:param name="path"/>
	<xsl:apply-templates select="document(@href)/*" mode="test">
		<xsl:with-param name="path">
			<xsl:call-template name="url.path">
				<xsl:with-param name="path" select="concat($path, @href)"/>
			</xsl:call-template>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<!-- GCC -->
<xsl:template match="cbear:parameters" mode="cpp">
	<xsl:value-of select="concat(
		'c:/mingw/bin/g++ -DNOMINMAX -Ic:\ -Ic:\boost\include\boost-1_33 ',
		'-Lc:\boost\lib -lboost_thread-mgw-mt-1_33 -o',
		@output,
		' ',
		@source,
		' -luuid')"/>
</xsl:template>

<!-- File Name -->
<xsl:template match="filename" mode="test">
	<xsl:param name="path"/>
	<xsl:variable name="extension">
		<xsl:call-template name="url.extension">
			<xsl:with-param name="path" select="."/>
		</xsl:call-template>
	</xsl:variable>
	<xsl:if test="$extension='hpp'">
		<xsl:variable name="test" select="concat($path, ., '.test.cpp')"/>
		<xsl:variable name="exe" select="concat($test, '.exe')"/>
		<xsl:variable name="parameters">
			<cbear:parameters source="{$test}" output="{$exe}"/>
		</xsl:variable>
		<xsl:apply-templates select="exsl:node-set($parameters)" mode="cpp"/>
		<xsl:text>&#10;</xsl:text>
		<xsl:value-of select="translate($exe, '/', '\')"/>
		<xsl:text>&#10;</xsl:text>
	</xsl:if>
</xsl:template>

<!-- Root -->
<xsl:template match="/">
	<xsl:apply-templates select="/" mode="test"/>
</xsl:template>

</xsl:stylesheet>
