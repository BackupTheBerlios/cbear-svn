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

	<xsl:variable name="version">
		<xsl:value-of select="document($rc:setup)/setup/version/number"/>
		<xsl:value-of select="'.'"/>
		<xsl:value-of select="document(concat($rc:root, '/.svn/entries'))/svn:wc-entries/svn:entry[@name='']/@committed-rev"/>
	</xsl:variable>

	<xsl:value-of select="concat(
		'1 VERSIONINFO', $rc:line,
		'FILEVERSION ', translate($version, '.', ','), $rc:line,		
		'PRODUCTVERSION ', translate($version, '.', ','), $rc:line,
		'FILEFLAGMASK 0x17L', $rc:line,
		'FILEOS 0x4L', $rc:line,
		'BEGIN', $rc:line,
		'BLOCK &#x22;StringFileInfo&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'BLOCK &#x22;00000000&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'VALUE &#x22;CompanyName&#x22;, &#x22;', $company, '&#x22;', $rc:line,
		'VALUE &#x22;FileDescription&#x22;, &#x22;', @name, '&#x22;', $rc:line,
		'VALUE &#x22;FileVersion&#x22;, &#x22;', $version, '&#x22;', $rc:line,
		'VALUE &#x22;InternalName&#x22;, &#x22;', @id, '&#x22;', $rc:line,
		'VALUE &#x22;OriginalFileName&#x22;, &#x22;', @id, '.', @type, '&#x22;', $rc:line,
		'VALUE &#x22;ProductName&#x22;, &#x22;', $product, '&#x22;', $rc:line,
		'VALUE &#x22;ProductVersion&#x22;, &#x22;', $version, '&#x22;', $rc:line,
		'END', $rc:line,
		'END', $rc:line,
		'BLOCK &#x22;VarFileInfo&#x22;', $rc:line,
		'BEGIN', $rc:line,
		'VALUE &#x22;Translation&#x22;, 0, 0', $rc:line,
		'END', $rc:line,
		'END')"/>
</xsl:template>

</xsl:stylesheet>
