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
	xmlns:T="http://cbear.berlios.de/test"
	xmlns:S="svn:"
	extension-element-prefixes="exsl">

<xsl:output method="text"/>

<xsl:param name="T:gpp" select="'c:/mingw/bin/g++'"/>
<xsl:param name="T:boost" select="'c:/boost/include/boost-1_33_1'"/>
<xsl:param name="T:cbear" select="'c:/cbear'"/>

<xsl:template name="T:dir">
	<xsl:param name="path"/>
	<xsl:value-of select="concat('rem ', $path, '&#10;')"/>
	<xsl:apply-templates 
		select="document(concat($path, '_svn/entries'))/S:wc-entries/S:entry">
		<xsl:with-param name="path" select="$path"/>
	</xsl:apply-templates>
</xsl:template>

<!-- unknown -->
<xsl:template match="S:entry"/>

<!-- directory -->
<xsl:template match="S:entry[@kind='dir']">
	<xsl:param name="path"/>
	<xsl:call-template name="T:dir">
		<xsl:with-param name="path" select="concat($path, @name, '/')"/>
	</xsl:call-template>
</xsl:template>

<!-- current directory -->
<xsl:template match="S:entry[@name='']"/>

<!-- *.hpp -->
<xsl:template match="S:entry[
	substring(@name, string-length(@name) - 3, 4)='.hpp' and @kind='file']">

	<xsl:param name="path"/>

	<xsl:variable name="name" select="concat($path, @name)"/>
	<xsl:value-of select="concat('rem ', $name, '&#10;')"/>
	<xsl:variable name="name.test.cpp" select="concat(
		substring($name, 1, string-length($name) - 4), 
		'.test.cpp')"/>
	<xsl:value-of select="concat(
		$T:gpp, ' -I', $T:cbear, ' ', $name.test.cpp, '&#10;')"/>
</xsl:template>

<xsl:template match="T:main">
	<xsl:call-template name="T:dir">
		<xsl:with-param name="path" select="@root"/>
	</xsl:call-template>
</xsl:template>

</xsl:stylesheet>
