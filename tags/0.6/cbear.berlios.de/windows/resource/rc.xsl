<?xml version="1.0"?>
<xsl:stylesheet
	version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:rc="http://cbear.berlios.de/windows/resource"
	xmlns:svn="svn:">
	
<xsl:import href="../../text/main.xsl"/>

<xsl:output method="text" encoding="ascii"/>

<xsl:param name="rc:root"/>
<xsl:param name="rc:setup"/>

<xsl:variable name="rc:line" select="'&#10;'"/>

<xsl:template match="section">

	<xsl:variable name="company">
		<xsl:value-of select="document($rc:setup)/setup/company"/>
	</xsl:variable>

	<xsl:variable name="product">
		<xsl:value-of select="document($rc:setup)/setup/name"/>
	</xsl:variable>

	<xsl:variable name="date">
		<xsl:value-of select="document(concat($rc:root, '/.svn/entries'))/
			svn:wc-entries/svn:entry[@name='']/@committed-date"/>
	</xsl:variable>

	<xsl:variable name="version">
		<xsl:value-of select="document($rc:setup)/setup/version/number"/>
		<xsl:value-of select="'.'"/>
		<xsl:value-of select="document(concat($rc:root, '/.svn/entries'))/
			svn:wc-entries/svn:entry[@name='']/@committed-rev"/>
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
		'VALUE &#x22;FileDescription&#x22;, &#x22;', @name, '&#x22;', $rc:line,
		'VALUE &#x22;FileVersion&#x22;, &#x22;', $version, '&#x22;', $rc:line,
		'VALUE &#x22;InternalName&#x22;, &#x22;', @id, '&#x22;', $rc:line,
		'VALUE &#x22;LegalCopyright&#x22;, &#x22;\xA9 ', 
			substring($date, 1, 4), ' ', $company, '&#x22;', $rc:line,
		'VALUE &#x22;OriginalFileName&#x22;, &#x22;', @id, '.', @type, '&#x22;', 
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
