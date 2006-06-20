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
	xmlns:T="http://cbear.berlios.de/test"
	xmlns:B="http://cbear.berlios.de/bat"
	xmlns:S="svn:">

<xsl:output method="xml" encoding="ascii"/>

<!-- parameters -->

<xsl:param name="T:name" select="/T:config/@name"/>

<xsl:param name="T:root" select="/T:config/@root"/>

<xsl:param name="T:psdk" select="/T:config/@psdk"/>
<xsl:param name="T:vcvar" select="/T:config/@vcvar"/>

<xsl:param name="T:gcc" select="/T:config/@gcc"/>
<xsl:param name="T:vc" select="/T:config/@vc"/>
<xsl:param name="T:dmc" select="/T:config/@dmc"/>

<xsl:param name="T:dmc.stlport" select="/T:config/@dmc.stlport"/>
<xsl:param name="T:boost" select="/T:config/@boost"/>
<xsl:param name="T:cbear" select="/T:config/@cbear"/>

<xsl:param name="T:log" select="/T:config/@log"/>

<xsl:param name="T:stylesheet" select="/T:config/@stylesheet"/>

<!-- templates -->

<!-- directory -->
<xsl:template name="T:dir">
	<xsl:param name="path"/>

	<B:bat name="{concat('Directory: ', $path)}">

		<xsl:variable name="test.path" select="concat($path, '_test/')"/>

		<B:command 
			text="{concat('mkdir &#34;', $test.path, '&#34;')}" 
			name="{concat('make: ', $test.path)}"/>

			<xsl:apply-templates 
				select="document(concat($path, '_svn/entries'))/S:wc-entries/S:entry">
				<xsl:with-param name="path" select="$path"/>
			</xsl:apply-templates>

	</B:bat>

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

<!-- target name -->
<xsl:template name="T:target">
	<xsl:param name="compiler"/>
	<xsl:param name="file"/>

	<xsl:value-of select="concat($file, '.', $compiler, '.exe')"/>
</xsl:template>

<!-- Compiler -->
<xsl:template name="T:compiler">
	<xsl:param name="compiler"/>
	<xsl:param name="command"/>
	<xsl:param name="target"/>

	<B:message text="{concat('Compiler: ', $compiler)}"/>

	<B:bat name="{concat('Compiler: ', $compiler)}">
		<!--
		<B:command name="compiling" text="{$command}"/>		
		-->
		<xsl:copy-of select="$command"/>
		<B:command name="running" text="{concat('&#34;', $target, '&#34;')}"/>
	</B:bat>

</xsl:template>

<!-- SVN *.hpp -->
<xsl:template match="S:entry[
	substring(@name, string-length(@name) - 3, 4)='.hpp' and @kind='file']">

	<xsl:param name="path"/>


	<xsl:variable name="name" select="concat($path, @name)"/>
	<xsl:variable name="name.test.cpp" select="concat(
		substring($name, 1, string-length($name) - 4), 
		'.test.cpp')"/>

	<B:message text="{concat('File: ', $name)}"/>

	<B:bat name="{concat('File: ', $name)}">

		<xsl:variable name="target" select="concat($path, '_test/', @name)"/>
	
		<!-- GCC -->
		<xsl:variable name="gcc.target">
			<xsl:call-template name="T:target">
				<xsl:with-param name="compiler" select="'gcc'"/>
				<xsl:with-param name="file" select="$target"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="T:compiler">
			<xsl:with-param name="compiler" select="'gcc'"/>
			<xsl:with-param name="command"> 
				<B:command name="compiling and linking" text="{concat(
				$T:gcc, ' -I', $T:cbear, ' -I', $T:boost, 
				' -o', $gcc.target, ' ', $name.test.cpp)}"/>
			</xsl:with-param>
			<xsl:with-param name="target" select="$gcc.target"/>
		</xsl:call-template>

		<!-- VC -->
		<xsl:variable name="vc.target">
			<xsl:call-template name="T:target">
				<xsl:with-param name="compiler" select="'vc'"/>
				<xsl:with-param name="file" select="$target"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="T:compiler">
			<xsl:with-param name="compiler" select="'vc'"/>
			<xsl:with-param name="command">
				<xsl:variable name="obj" select="concat($vc.target, '.obj')"/>
				<B:command name="compiling and linking" text="{concat(
				$T:vc, ' -nologo -EHs -EHc -I', $T:cbear, ' -I', $T:boost, 
				' -Fe', $vc.target, 
				' -Fo', $obj,
				' ', 	$name.test.cpp)}"/>
			</xsl:with-param>
			<xsl:with-param name="target" select="$vc.target"/>
		</xsl:call-template>

		<!-- DMC -->
		<xsl:variable name="dmc.target">
			<xsl:call-template name="T:target">
				<xsl:with-param name="compiler" select="'dmc'"/>
				<xsl:with-param name="file" select="$target"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="T:compiler">
			<xsl:with-param name="compiler" select="'dmc'"/>
			<xsl:with-param name="command">
				<xsl:variable name="obj" select="concat($dmc.target, '.obj')"/>
				<B:command name="compiling" text="{concat(
					$T:dmc, ' -Ae -c -I', $T:dmc.stlport, ' -I', $T:cbear, ' -I', $T:boost,
					' -o', translate($obj, '/', '\'), ' ', $name.test.cpp)}"/>
				<B:command name="linking" text="{concat(
					$T:dmc, ' -LNOMAP -Ae -I', $T:dmc.stlport, ' -I', $T:cbear, ' -I', $T:boost,
					' -o', translate($dmc.target, '/', '\'), ' ', $obj)}"/>
			</xsl:with-param>
			<xsl:with-param name="target" select="$dmc.target"/>
		</xsl:call-template>

	</B:bat>

</xsl:template>

<!-- SVN current directory -->
<xsl:template match="S:entry[@name='']"/>

<!-- SVN deleted -->
<xsl:template match="S:entry[@deleted='true']"/>

<!-- T:config -->
<xsl:template match="T:config">

	<B:bat log="{$T:log}" stylesheet="{$T:stylesheet}" name="{$T:name}">

		<B:command text="{$T:psdk}" name="PSDK"/>
		<B:command text="{$T:vcvar}" name="VC enviroment"/>

		<xsl:call-template name="T:dir">
			<xsl:with-param name="path" select="$T:root"/>
		</xsl:call-template>

	</B:bat>

</xsl:template>

</xsl:stylesheet>
