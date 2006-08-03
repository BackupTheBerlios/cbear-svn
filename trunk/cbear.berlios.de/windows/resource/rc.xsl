<?xml version="1.0"?>
<xsl:stylesheet
	version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:rc="http://cbear.berlios.de/windows/resource"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:svn="svn:">
	
<xsl:import href="../../text/main.xsl"/>

<xsl:import href="../../cms/html.xsl"/>

<xsl:output method="text" encoding="ascii"/>

<!--
<xsl:param name="rc:root"/>
<xsl:param name="rc:setup"/>
-->

<xsl:variable name="rc:line" select="'&#10;'"/>

<xsl:template match="C:section">

	<xsl:variable name="company">
		<xsl:apply-templates select="." mode="C:company"/>
	</xsl:variable>

	<xsl:variable name="product">
		<xsl:value-of select='@name'/>
	</xsl:variable>

	<xsl:variable name="description">
		<xsl:value-of select="@title"/>
	</xsl:variable>

	<xsl:variable name="date">
		<xsl:apply-templates select="." mode="C:date"/>
	</xsl:variable>

	<xsl:variable name="version">
		<xsl:apply-templates select="." mode="C:version"/>
	</xsl:variable>

	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="C:id"/>
	</xsl:variable>

	<xsl:variable name="type">
		<xsl:choose>
			<xsl:when test="@type='exe'">
				<xsl:value-of select="'VFT_APP'"/>
			</xsl:when>
			<xsl:when test="@type='dll'">
				<xsl:value-of select="'VFT_DLL'"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:message terminate="yes">Unknown file type</xsl:message>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:value-of select="concat(
		'#include &lt;WinVer.h&gt;', $rc:line,
		'1 VERSIONINFO', $rc:line,
		'FILEVERSION ', translate($version, '.', ','), $rc:line,		
		'PRODUCTVERSION ', translate($version, '.', ','), $rc:line,
		'FILEFLAGSMASK 0x3FL', $rc:line,
		'FILEFLAGS 0', $rc:line,
		'FILEOS VOS_NT_WINDOWS32', $rc:line,
		'FILETYPE ', $type, $rc:line,
		'BEGIN', $rc:line,
		'BLOCK &#x22;StringFileInfo&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'BLOCK &#x22;000004B0&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'VALUE &#x22;CompanyName&#x22;, &#x22;', $company, '&#x22;', $rc:line,
		'VALUE &#x22;FileDescription&#x22;, &#x22;', $description, '&#x22;', $rc:line,
		'VALUE &#x22;FileVersion&#x22;, &#x22;', $version, '&#x22;', $rc:line,
		'VALUE &#x22;InternalName&#x22;, &#x22;', $id, '&#x22;', $rc:line,
		'VALUE &#x22;LegalCopyright&#x22;, &#x22;\xA9 ', 
			substring($date, 1, 4), ' ', $company, '&#x22;', $rc:line,
		'VALUE &#x22;OriginalFileName&#x22;, &#x22;', $id, '.', @type, '&#x22;', 
			$rc:line,
		'VALUE &#x22;ProductName&#x22;, &#x22;', $product, '&#x22;', $rc:line,
		'VALUE &#x22;ProductVersion&#x22;, &#x22;', $version, '&#x22;', $rc:line,
		'END', $rc:line,
		'END', $rc:line,
		'BLOCK &#x22;VarFileInfo&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'VALUE &#x22;Translation&#x22;, 0, 1200', $rc:line,
		'END', $rc:line,
		'END')"/>
</xsl:template>

</xsl:stylesheet>
