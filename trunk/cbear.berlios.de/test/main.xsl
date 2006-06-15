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

<xsl:output method="text" encoding="ascii"/>

<!-- parameters -->
<xsl:param name="T:gcc" select="'c:/mingw/bin/g++.exe'"/>
<xsl:param name="T:psdk" select="
	'C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\'"/>
<xsl:param name="T:vc" select="
	'&#34;C:\Program Files\Microsoft Visual Studio 8\VC\bin\cl.exe&#34;'"/>
<xsl:param name="T:dm" select="'c:/dm/bin/dmc.exe'"/>

<xsl:param name="T:dm.stlport" select="'c:/dm/stlport/stlport'"/>
<xsl:param name="T:boost" select="'c:/boost/include/boost-1_33_1'"/>
<xsl:param name="T:cbear" select="'c:/cbear'"/>

<xsl:param name="T:log" select="'log.xml'"/>

<!-- T:line -->
<xsl:template name="T:line">
	<xsl:param name="text"/>
	<xsl:value-of select="concat($text, '&#10;')"/>
</xsl:template>

<!-- T:message -->
<xsl:template name="T:message">
	<xsl:param name="text"/>
	<xsl:call-template name="T:line">
		<xsl:with-param name="text" select="concat('echo ', $text)"/>
	</xsl:call-template>
</xsl:template>

<!-- T:log.line -->
<xsl:template name="T:log.line">
	<xsl:param name="text"/>
	<xsl:param name="to" select="'&gt;&gt;'"/>
	<xsl:call-template name="T:message">
		<xsl:with-param name="text" select="concat($text, $to, $T:log)"/>
	</xsl:call-template>
</xsl:template>

<!-- T:tag -->
<xsl:template name="T:tag">
	<xsl:param name="name"/>
	<xsl:param name="attributes"/>
	<xsl:param name="content"/>
	<xsl:call-template name="T:log.line">
		<xsl:with-param 
			name="text" select="concat('^&lt;', $name, ' ', $attributes, '^&gt;')"/>
	</xsl:call-template>
	<xsl:value-of select="$content"/>
	<xsl:call-template name="T:log.line">
		<xsl:with-param name="text" select="concat('^&lt;/', $name, '^&gt;')"/>
	</xsl:call-template>
</xsl:template>

<!-- T:cdata -->
<xsl:template name="T:cdata">
	<xsl:param name="content"/>
	<xsl:call-template name="T:log.line">
		<xsl:with-param name="text" select="'^&lt;![CDATA['"/>
	</xsl:call-template>
	<xsl:value-of select="$content"/>
	<xsl:call-template name="T:log.line">
		<xsl:with-param name="text" select="']]^&gt;'"/>
	</xsl:call-template>
</xsl:template>

<!-- directory -->
<xsl:template name="T:dir">
	<xsl:param name="path"/>

	<xsl:call-template name="T:tag">
		<xsl:with-param name="name" select="'dir'"/>
		<xsl:with-param 
			name="attributes" select="concat('name=&#34;', $path, '&#34;')"/>
		<xsl:with-param name="content">
			<xsl:call-template name="T:command">
				<xsl:with-param 
					name="command" select="concat('mkdir &#34;', $path, '_test/&#34;')"/>
			</xsl:call-template>
			<xsl:apply-templates 
				select="document(concat($path, '_svn/entries'))/S:wc-entries/S:entry">
				<xsl:with-param name="path" select="$path"/>
			</xsl:apply-templates>
		</xsl:with-param>
	</xsl:call-template>

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

<xsl:template match="S:entry[@name='']" mode="T:count">
	<xsl:value-of select="0"/>
</xsl:template>

<!-- Command -->
<xsl:template name="T:command">
	<xsl:param name="command"/>
	<xsl:call-template name="T:tag">
		<xsl:with-param name="name" select="'command'"/>
		<xsl:with-param name="content">
			<xsl:call-template name="T:tag">
				<xsl:with-param name="name" select="'output'"/>
				<xsl:with-param name="content">
					<xsl:call-template name="T:cdata">
						<xsl:with-param name="content">
							<xsl:call-template name="T:line">
								<xsl:with-param 
									name="text" 
									select="
										concat($command, '&gt;&gt;', $T:log, ' 2&gt;&amp;1')"/>
							</xsl:call-template>
						</xsl:with-param>
					</xsl:call-template>
				</xsl:with-param>			
			</xsl:call-template>
			<xsl:call-template name="T:tag">
				<xsl:with-param name="name" select="'error'"/>
				<xsl:with-param 
					name="attributes" select="'level=^&#34;%ERRORLEVEL%^&#34;'"/>
			</xsl:call-template>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- Compiler -->
<xsl:template name="T:compiler">
	<xsl:param name="name"/>
	<xsl:param name="command"/>
	<xsl:param name="file"/>

	<xsl:call-template name="T:message">
		<xsl:with-param name="text" select="concat('compiler: ', $name)"/>
	</xsl:call-template>

	<xsl:call-template name="T:tag">
		<xsl:with-param name="name" select="'compiler'"/>
		<xsl:with-param 
			name="attributes" select="concat('name=&#34;', $name, '&#34;')"/>
		<xsl:with-param name="content">

			<xsl:call-template name="T:message">
				<xsl:with-param name="text" select="'compiling...'"/>
			</xsl:call-template>
			<xsl:call-template name="T:command">
				<xsl:with-param name="command" select="$command"/>
			</xsl:call-template>

			<xsl:variable name="label" select="concat('&#34;', $file, '&#34;')"/>

			<xsl:call-template name="T:line">
				<xsl:with-param name="text" select="
					concat('if not %ERRORLEVEL% == 0 goto ', $label)"/>
			</xsl:call-template>

			<xsl:call-template name="T:message">
				<xsl:with-param name="text" select="'running...'"/>
			</xsl:call-template>
			<xsl:call-template name="T:command">
				<xsl:with-param 
					name="command" select="concat('&#34;', $file, '.', $name, '.exe&#34;')"/>
			</xsl:call-template>

			<xsl:call-template name="T:line">
				<xsl:with-param name="text" select="concat(':', $label)"/>
			</xsl:call-template>

		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- SVN *.hpp -->
<xsl:template match="S:entry[
	substring(@name, string-length(@name) - 3, 4)='.hpp' and @kind='file']">

	<xsl:param name="path"/>

	<xsl:variable name="name" select="concat($path, @name)"/>
	<xsl:variable name="name.test.cpp" select="concat(
		substring($name, 1, string-length($name) - 4), 
		'.test.cpp')"/>

	<xsl:call-template name="T:message">
		<xsl:with-param name="text" select="concat('file: ', $name)"/>
	</xsl:call-template>

	<xsl:call-template name="T:tag">
		<xsl:with-param name="name" select="'file'"/>
		<xsl:with-param 
			name="attributes" select="concat('name=&#34;', $name, '&#34;')"/>

		<xsl:with-param name="content">
			<xsl:variable name="test" select="concat($path, '_test/')"/>

			<xsl:variable name="test.name" select="concat($test, @name)"/>
	
			<!-- GCC -->
			<xsl:call-template name="T:compiler">
				<xsl:with-param name="name" select="'gcc'"/>
				<xsl:with-param name="command" select="concat(
					$T:gcc, ' -I', $T:cbear, ' -I', $T:boost, 
					' -o', $test.name, '.gcc.exe ', 
					$name.test.cpp)"/>
				<xsl:with-param name="file" select="$name.test.cpp"/>
			</xsl:call-template>

			<!-- VC -->
			<xsl:call-template name="T:compiler">
				<xsl:with-param name="name" select="'vc'"/>
				<xsl:with-param name="command" select="concat(
					$T:vc, ' -nologo -EHs -EHc -I', $T:cbear, ' -I', $T:boost, ' ', 
					' -o', $test.name, '.vc.exe ',
					$name.test.cpp)"/>
				<xsl:with-param name="file" select="$name.test.cpp"/>
			</xsl:call-template>

			<!-- DM -->
			<xsl:call-template name="T:compiler">
				<xsl:with-param name="name" select="'dmc'"/>
				<xsl:with-param name="command" select="concat(
					$T:dm, ' -Ae -I', $T:dm.stlport, ' -I', $T:cbear, ' -I', $T:boost, 
					' -o', translate($test.name, '/', '\'), '.dmc.exe ',	
					$name.test.cpp)"/>
				<xsl:with-param name="file" select="$name.test.cpp"/>
			</xsl:call-template>
		</xsl:with-param>
	</xsl:call-template>

</xsl:template>

<!-- SVN deleted -->
<xsl:template match="S:entry[@deleted='true']"/>

<!-- entry point -->
<xsl:template match="T:main">

	<xsl:call-template name="T:line">
		<xsl:with-param name="text" select="'@echo off'"/>
	</xsl:call-template>

	<xsl:call-template name="T:log.line">
		<xsl:with-param 
			name="text" select="'^&lt;?xml version=&#34;1.0&#34;?^&gt;'"/>
		<xsl:with-param name="to" select="'&gt;'"/>
	</xsl:call-template>

	<xsl:call-template name="T:log.line">
		<xsl:with-param 
			name="text" 
			select="'^&lt;?xml-stylesheet type=&#34;text/xsl&#34; href=&#34;html.xsl&#34;?^&gt;'"/>
	</xsl:call-template>

	<xsl:call-template name="T:tag">
		<xsl:with-param name="name" select="'report'"/>
		<xsl:with-param 
			name="attributes" select="'xmlns=&#34;http://cbear.berlios.de/test&#34;'"/>
		<xsl:with-param name="content">
			<xsl:call-template name="T:command">
				<xsl:with-param name="command" select="
					'call &#34;C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\SetEnv.Cmd&#34;'"/>
			</xsl:call-template>
			<xsl:call-template name="T:command">
				<xsl:with-param 
					name="command" select="
					'call &#34;C:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat&#34;'"/>
			</xsl:call-template>
			<xsl:call-template name="T:dir">
				<xsl:with-param name="path" select="@root"/>
			</xsl:call-template>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

</xsl:stylesheet>
