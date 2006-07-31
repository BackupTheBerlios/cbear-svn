<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:A="http://cbear.berlios.de/api"
	xmlns:B="http://cbear.berlios.de/bat"
	xmlns:S="svn:">

<xsl:output method="xml"/>

<!-- parameters -->

<xsl:param name="A:api.xml" select="/A:library/A:config/A:api.xml"/>
<xsl:param name="A:output" select="/A:library/A:config/A:output"/>
<xsl:param name="A:cbear" select="/A:library/A:config/A:cbear"/>
<xsl:param name="A:nxslt" select="/A:library/A:config/A:nxslt"/>
<xsl:param name="A:vc.var" select="/A:library/A:config/A:vc.var"/>
<xsl:param name="A:tlbimp" select="/A:library/A:config/A:tlbimp"/>
<xsl:param name="A:dotnet.key" select="/A:library/A:config/A:dotnet.key"/>

<!-- variables -->

<xsl:variable name="A:name" select="/A:library/@id"/>
<xsl:variable name="A:output.file" select="concat($A:output, $A:name)"/>
<xsl:variable name="A:log" select="concat($A:output.file, '.log.xml')"/>
<xsl:variable name="A:odl.xml" select="concat($A:output.file, '.odl.xml')"/>
<xsl:variable name="A:odl" select="concat($A:output.file, '.odl')"/>
<xsl:variable name="A:strong.odl.xml" select="concat($A:output.file, '.strong.odl.xml')"/>
<xsl:variable name="A:strong.odl" select="concat($A:output.file, '.strong.odl')"/>
<xsl:variable name="A:tlb" select="concat($A:output.file, '.tlb')"/>
<xsl:variable name="A:h" select="concat($A:output.file, '.h')"/>
<xsl:variable name="A:iid" select="concat($A:output.file, '.iid.c')"/>
<xsl:variable name="A:strong.tlb" select="concat($A:output.file, '.strong.tlb')"/>
<xsl:variable name="A:dotnet.dll" select="concat($A:output.file, '.dotnet.dll')"/>
<xsl:variable name="A:hpp.xml" select="concat($A:output.file, '.hpp.xml')"/>
<xsl:variable name="A:hpp" select="concat($A:output.file, '.hpp')"/>
<xsl:variable name="A:html" select="concat($A:output.file, '.html')"/>
<xsl:variable name="A:device.c.xml" select="concat($A:output.file, '.device.c.xml')"/>
<xsl:variable name="A:odl.cs.xml" select="concat($A:output.file, '.odl.cs.xml')"/>
<xsl:variable name="A:odl.cs" select="concat($A:output.file, '.odl.cs')"/>

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

<!-- ODL -->

<xsl:template name="A:odl">
	<xsl:param name="name.odl.xml"/>
	<xsl:param name="name.odl"/>
	<xsl:param name="odl.xml"/>
	<xsl:param name="odl"/>
	<xsl:param name="param.odl.xml"/>

	<xsl:call-template name="A:make.file.dir">
		<xsl:with-param name="file" select="$odl.xml"/>
	</xsl:call-template>

	<B:command 
		name="{$name.odl.xml}"
		text="{concat(
			$A:nxslt, ' ', 
			$A:api.xml, ' ', 
			$A:cbear, 'cbear.berlios.de/api/com.odl.xsl ', 
			'-o ', $odl.xml, ' ',
			'xmlns:api=http://cbear.berlios.de/api ',
			'api:com.odl.xsl=file:///', $A:cbear, 'cbear.berlios.de/windows/com/color.xsl ',
			$param.odl.xml)}"/>

	<xsl:call-template name="A:make.file.dir">
		<xsl:with-param name="file" select="$odl"/>
	</xsl:call-template>

	<B:command
		name="{$name.odl}"
		text="{concat(
			$A:nxslt, ' ', 
			$odl.xml, ' ',
			$A:cbear, 'cbear.berlios.de/windows/com/odl.xsl ',
			'-o ', $odl)}"/>

</xsl:template>

<!-- entry point -->

<xsl:template match="A:library">
	<B:bat 
		name="{$A:name}"
		log="{$A:log}"
		stylesheet="{concat('file:///', $A:cbear, 'cbear.berlios.de/bat/html.xsl')}">

		<B:command
			name="VC enviroment variables"	
			text="{$A:vc.var}"/>

		<B:command
			name="Make output dir"
			text="{concat('mkdir &#34;', $A:output, '&#34;')}"/>

		<xsl:call-template name="A:odl">
			<xsl:with-param name="name.odl.xml" select="'API.XML to ODL.XML'"/>
			<xsl:with-param name="odl.xml" select="$A:odl.xml"/>
			<xsl:with-param name="name.odl" select="'ODL.XML to ODL'"/>
			<xsl:with-param name="odl" select="$A:odl"/>
		</xsl:call-template>

		<xsl:call-template name="A:odl">
			<xsl:with-param name="name.odl.xml" select="'API.XML to STRONG.ODL.XML'"/>
			<xsl:with-param name="odl.xml" select="$A:strong.odl.xml"/>
			<xsl:with-param name="param.odl.xml" select="'api:com.odl.prefix=yes'"/>
			<xsl:with-param name="name.odl" select="'ODL.XML to STRONG.ODL'"/>
			<xsl:with-param name="odl" select="$A:strong.odl"/>
		</xsl:call-template>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:tlb"/>
		</xsl:call-template>

		<B:command
			name="MIDL: ODL to TLB"
			text="{concat(
				'midl /W4 /robust /error all /nologo /env win32 ', 
				'/I ', $A:output, ' ',
				'/tlb ', $A:tlb, ' ',
				$A:odl)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:h"/>
		</xsl:call-template>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:iid"/>
		</xsl:call-template>

		<B:command
			name="MIDL: STRONG.ODL to STRONG.TLB, H, IID"
			text="{concat(
				'midl /W4 /robust /error all /nologo /env win32 ', 
				'/I ', $A:output, ' ',
				'/tlb ', $A:strong.tlb, ' ',
				'/header ', $A:h, ' ',
				'/iid ', $A:iid, ' ',
				$A:strong.odl)}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:dotnet.dll"/>
		</xsl:call-template>

		<xsl:variable name="tlb2dotnet.dll">
			<xsl:value-of select="concat(
				$A:tlbimp, ' ',
				$A:tlb, ' ',
				'/primary ',
				'/keyfile:', $A:dotnet.key, ' ',
				'/out:', $A:dotnet.dll, ' ')"/>
			<xsl:for-each select="A:using">
				<xsl:for-each 
					select="document(@href, .)/A:library[@id!='cbear_berlios_de.api.base']">
					<xsl:value-of select="concat('/reference:', $A:output, @id, '.dotnet.dll ')"/>
				</xsl:for-each>
			</xsl:for-each>
		</xsl:variable>

		<B:command
			name="TLB to .NET DLL"
			text="{$tlb2dotnet.dll}"/>

		<xsl:call-template name="A:make.file.dir">
			<xsl:with-param name="file" select="$A:hpp.xml"/>
		</xsl:call-template>

		<B:command
			name="ODL.XML to HPP.XML"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/cpp.xsl ',
				'-o ', $A:hpp.xml, ' ',
				'xmlns:O=http://cbear.berlios.de/windows/com ',
				'O:cpp.xsl=file://', $A:cbear, 'cbear.berlios.de/cpp/html.xsl')}"/>

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
			name="ODL.XML to DEVICE.C.XML"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/device/c.xsl ',
				'-o ', $A:device.c.xml, ' ',
				'xmlns:D=http://cbear.berlios.de/windows/com/device ',
				'D:cbear=', $A:cbear)}"/>

		<B:command
			name="ODL.XML to ODL.CS.XML"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.xml, ' ',
				$A:cbear, 'cbear.berlios.de/windows/com/cs.xsl ',
				'-o ', $A:odl.cs.xml)}"/>

		<B:command
			name="CS.XML to CS"
			text="{concat(
				$A:nxslt, ' ',
				$A:odl.cs.xml, ' ',
				$A:cbear, 'cbear.berlios.de/cs/cs.xsl ',
				'-o ', $A:odl.cs)}"/>

	</B:bat>
</xsl:template>

</xsl:stylesheet>
