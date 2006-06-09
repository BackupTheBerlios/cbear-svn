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

<!-- parameters -->
<xsl:param name="T:gpp" select="'c:/mingw/bin/g++.exe'"/>
<xsl:param name="T:vc" select="
	'&#34;C:\Program Files\Microsoft Visual Studio 8\VC\bin\cl.exe&#34;'"/>

<xsl:param name="T:boost" select="'c:/boost/include/boost-1_33_1/'"/>
<xsl:param name="T:cbear" select="'c:/cbear/'"/>

<!-- directory -->
<xsl:template name="T:dir">
	<xsl:param name="path"/>
	<xsl:text>echo ^&lt;dir name="</xsl:text>
	<xsl:value-of select="$path"/>
	<xsl:text>"^&gt;&#10;</xsl:text>
	<xsl:apply-templates 
		select="document(concat($path, '_svn/entries'))/S:wc-entries/S:entry">
		<xsl:with-param name="path" select="$path"/>
	</xsl:apply-templates>
	<xsl:text>echo ^&lt;/dir^&gt;&#10;</xsl:text>
</xsl:template>

<!-- SVN unknown -->
<xsl:template match="S:entry"/>

<!-- SVN directory -->
<xsl:template match="S:entry[@kind='dir']">
	<xsl:param name="path"/>
	<xsl:call-template name="T:dir">
		<xsl:with-param name="path" select="concat($path, @name, '/')"/>
	</xsl:call-template>
</xsl:template>

<!-- SVN current directory -->
<xsl:template match="S:entry[@name='']"/>

<!-- Compiler -->
<xsl:template name="T:compiler">
	<xsl:param name="name"/>
	<xsl:param name="command"/>

	<xsl:text>echo ^&lt;compiler name="</xsl:text>
	<xsl:value-of select="$name"/>
	<xsl:text>"^&gt;^&lt;text^&gt;^&lt;![CDATA[&#10;</xsl:text>

	<xsl:value-of select="concat($command, '&#10;')"/>

	<xsl:text>echo ]]^&gt;^&lt;/text^&gt;^&lt;error level=^"%ERRORLEVEL%^"/^&gt;&#10;</xsl:text>
	<xsl:text>echo ^&lt;/compiler^&gt;&#10;</xsl:text>
</xsl:template>

<!-- SVN *.hpp -->
<xsl:template match="S:entry[
	substring(@name, string-length(@name) - 3, 4)='.hpp' and @kind='file']">

	<xsl:param name="path"/>

	<xsl:variable name="name" select="concat($path, @name)"/>
	<xsl:variable name="name.test.cpp" select="concat(
		substring($name, 1, string-length($name) - 4), 
		'.test.cpp')"/>

	<xsl:text>echo ^&lt;file name="</xsl:text>
	<xsl:value-of select="$name"/>
	<xsl:text>"^&gt;&#10;</xsl:text>
	
	<!-- GCC -->
	<xsl:call-template name="T:compiler">
		<xsl:with-param name="name" select="'gcc'"/>
		<xsl:with-param name="command" select="concat(
			$T:gpp, ' -I', $T:cbear, ' ', $name.test.cpp)"/>
	</xsl:call-template>

	<!-- VC -->
	<xsl:call-template name="T:compiler">
		<xsl:with-param name="name" select="'vc'"/>
		<xsl:with-param name="command" select="concat(
			$T:vc, ' -nologo ', $name.test.cpp)"/>
	</xsl:call-template>

	<xsl:text>echo ^&lt;/file^&gt;&#10;</xsl:text>

</xsl:template>

<!-- entry point -->
<xsl:template match="T:main">
	<xsl:text>@echo off&#10;</xsl:text>
	<xsl:text>echo ^&lt;?xml version="1.0"?^&gt;&#10;</xsl:text>
	<xsl:text>echo ^&lt;?xml-stylesheet type="text/xsl" href="html.xsl"?^&gt;&#10;</xsl:text>
	<xsl:text>echo ^&lt;report xmlns="http://cbear.berlios.de/test"^&gt;&#10;</xsl:text>
	<xsl:text>call "C:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat"&#10;</xsl:text>
	<xsl:call-template name="T:dir">
		<xsl:with-param name="path" select="@root"/>
	</xsl:call-template>
	<xsl:text>echo ^&lt;/report^&gt;</xsl:text>
</xsl:template>

</xsl:stylesheet>
