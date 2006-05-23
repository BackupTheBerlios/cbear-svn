<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:date="http://exslt.org/dates-and-times"
	xmlns:str="http://exslt.org/strings"
	xmlns:exsl="http://exslt.org/common"
	xmlns:build="http://cbear.berlios.de/build"
	xmlns:svn="svn:"
	xmlns="http://www.w3.org/1999/xhtml"
	extension-element-prefixes="date str exsl"
	exclude-result-prefixes="xi">

<!-- <xsl:import href="../exslt/common/document.xsl"/> -->

<xsl:output method="text" encoding="iso-8859-1"/>

<xsl:template match="build:build">
	<xsl:variable 
		name="name" 
		select="concat(
			'cbear.berlios.de\',
			@name, 
			'-',  
			@version,
			'.', 
			document('_svn/entries', .)/svn:wc-entries/svn:entry/@revision,
			'.zip')"/>
	<exsl:document
				href="_build.bat"
				method="text"
				encoding="iso-8859-1">
<xsl:value-of select="'cd ..&#10;'"/>
<xsl:value-of select="concat('del ', $name, '&#10;')"/>
	<xsl:value-of select="concat(
		'&#x22;c:\Program Files\7-zip\7z&#x22; a -r -tzip ',
		'-x@cbear.berlios.de/x.txt ',
		$name, 
		' cbear.berlios.de/*')"/>
	</exsl:document>
</xsl:template>

</xsl:stylesheet>
