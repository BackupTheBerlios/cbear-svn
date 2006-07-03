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
	xmlns:A="http://cbear.berlios.de/api"
	xmlns:B="http://cbear.berlios.de/bat"
	xmlns:S="svn:">

<xsl:output method="xml"/>

<!-- parameters -->

<xsl:param name="A:name" select="A:config/@name"/>

<xsl:param name="A:dir" select="A:config/@dir"/>

<xsl:param name="A:log" select="A:config/@log"/>

<xsl:param name="A:api.xml" select="A:config/@api.xml"/>

<xsl:param name="A:odl.xml" select="A:config/@odl.xml"/>
<xsl:param name="A:odl" select="A:config/@odl"/>

<xsl:param name="A:tlb" select="A:config/@tlb"/>
<xsl:param name="A:h" select="A:config/@h"/>
<xsl:param name="A:iid" select="A:config/@iid"/>

<xsl:param name="A:hpp.xml" select="A:config/@hpp.xml"/>
<xsl:param name="A:hpp" select="A:config/@hpp"/>

<xsl:param name="A:cs.xml" select="A:config/@cs.xml"/>
<xsl:param name="A:cs" select="A:config/@cs"/>

<xsl:param name="A:html" select="A:config/@html"/>

<xsl:param name="A:dnet.key" select="A:config/@dnet.key"/>
<xsl:param name="A:dnet.dll" select="A:config/@dnet.dll"/>

<xsl:param name="A:midl.options" select="A:config/@midl.options"/>
<xsl:param name="A:tlbimp.options" select="A:config/@tlbimp.options"/>

<xsl:param name="A:cbear" select="A:config/@cbear"/>
<xsl:param name="A:nxslt" select="A:config/@nxslt"/>
<xsl:param name="A:vc.var" select="A:config/@vc.var"/>
<xsl:param name="A:tlbimp" select="A:config/@tlbimp"/>

<!-- a directory for the given file -->
<xsl:template name="A:file.dir">
	<xsl:param name="file"/>
	<xsl:variable name="file.norm" select="translate($file, '\', '/')"/>
	<xsl:if test="contains($file.norm, '/')">
		<xsl:value-of select="concat(substring-before($file.norm, '/'), '/')"/>
		<xsl:call-template name="A:file.dir">
			<xsl:with-param name="file" select="substring-after($file.norm, '/')"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- make a directory for the given file -->
<xsl:template name="A:make.file.dir">
	<xsl:param name="file"/>
	<xsl:variable name="dir">
		<xsl:call-template name="A:file.dir">
			<xsl:with-param name="file" select="$file"/>
		</xsl:call-template>
	</xsl:variable>
	<xsl:if test="$dir">
		<B:line
			text="{concat('md &#34;', $dir, '&#34;&gt;nul 2&gt;&amp;1')}"/>
	</xsl:if>
</xsl:template>

<!-- entry point -->

<xsl:template match="A:config">
	<B:bat 
		name="{$A:name}"
		log="{$A:log}"
		stylesheet="{concat('file:///', $A:cbear, 'cbear.berlios.de/bat/html.xsl')}">

		<B:command
			name="Set a working directory"
			text="{concat('cd ', $A:dir)}"/>

		<B:command
			name="VC enviroment variables"	
			text="{$A:vc.var}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:odl.xml"/>
		</xsl:call-template>

		<B:command 
			name="API.XML to ODL.XML"
			text="{concat(
				$A:nxslt, ' ', 
				$A:api.xml, ' ', 
				$A:cbear, 'cbear.berlios.de/api/com.odl.xsl ', 
				'-o ', $A:odl.xml, ' ',
				'xmlns:api=http://cbear.berlios.de/api ',
				'api:com.odl.xsl=file:///', $A:cbear, 'cbear.berlios.de/windows/com/color.xsl')}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:odl"/>
		</xsl:call-template>

		<B:command
			name="ODL.XML to ODL"
			text="{concat(
				$A:nxslt, ' ', 
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/odl.xsl ',
				'-o ', $A:odl)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:tlb"/>
		</xsl:call-template>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:h"/>
		</xsl:call-template>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:iid"/>
		</xsl:call-template>

		<B:command
			name="MIDL: ODL to TLB, H, IID"
			text="{concat(
				'midl /W4 /robust /error all /nologo /env win32 ', 
				'/tlb ', $A:tlb, ' ',
				'/header ', $A:h, ' ',
				'/iid ', $A:iid, ' ',
				$A:odl, ' ',
				$A:midl.options)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:dnet.dll"/>
		</xsl:call-template>

		<B:command
			name="TLB to .NET DLL"
			text="{concat(
				$A:tlbimp, ' ',
				$A:tlb, ' ',
				'/primary ',
				'/keyfile:', $A:dnet.key, ' ',
				'/out:', $A:dnet.dll, ' ',
				$A:tlbimp.options)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:hpp.xml"/>
		</xsl:call-template>

		<B:command
			name="ODL.XML to HPP.XML"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/cpp.xsl ',
				'-o ', $A:hpp.xml)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:hpp"/>
		</xsl:call-template>

		<B:command
			name="HPP.XML to HPP"
			text="{concat(
				$A:nxslt, ' ',
				$A:hpp.xml, ' ',
				$A:cbear, 'cbear.berlios.de/cpp/cpp.xsl ',
				'-o ', $A:hpp)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:html"/>
		</xsl:call-template>

		<B:command
			name="API.XML to HTML"
			text="{concat(
				$A:nxslt, ' ', 
				$A:api.xml, ' ',
				'-pi ',
				'-o ', $A:html)}"/>

		<B:command
			name="ODL.XML to CS.XML"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/cs.xsl ',
				'-o ', $A:cs.xml)}"/>

		<B:command
			name="CS.XML to CS"
			text="{concat(
				$A:nxslt, ' ',
				$A:cs.xml, ' ',
				$A:cbear, 'cbear.berlios.de/cs/cs.xsl ',
				'-o ', $A:cs)}"/>

	</B:bat>
</xsl:template>

</xsl:stylesheet>
